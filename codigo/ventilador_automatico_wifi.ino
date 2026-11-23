/*
  Proyecto: Ventilador automático con monitoreo Wi-Fi
  Plataforma: ESP32 DevKit V1
  Sensor: DHT11 (módulo de 3 pines recomendado)
  Actuador: módulo relé de 1 canal + ventilador DC de 5 V

  IMPORTANTE:
  - Este código es una base preparada; aún debe compilarse y probarse con el hardware real.
  - Cambia WIFI_SSID y WIFI_PASSWORD antes de cargarlo.
  - Verifica que el módulo relé acepte señal lógica de 3.3 V del ESP32.
  - No conectes el ventilador directamente a un pin GPIO.
  - No uses tensión de red doméstica (110/120 V) en este montaje.
*/

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// ---------- CONFIGURACIÓN DEL USUARIO ----------
const char* WIFI_SSID = "NOMBRE_DE_TU_WIFI";
const char* WIFI_PASSWORD = "CONTRASENA_DE_TU_WIFI";

// Si el relé se activa con LOW, deja true. Si se activa con HIGH, cambia a false.
const bool RELAY_ACTIVE_LOW = true;

// ---------- PINES ----------
#define DHT_PIN 4
#define DHT_TYPE DHT11
const int RELAY_PIN = 26;

// ---------- CONTROL AUTOMÁTICO ----------
const float TEMP_ENCENDIDO = 30.0; // Enciende al alcanzar esta temperatura
const float TEMP_APAGADO = 28.0;   // Apaga al bajar a esta temperatura

DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

enum ControlMode { AUTO_MODE, MANUAL_MODE };
ControlMode controlMode = AUTO_MODE;

bool fanOn = false;
float temperatureC = NAN;
float humidity = NAN;
unsigned long lastSensorRead = 0;
const unsigned long SENSOR_INTERVAL_MS = 2000;

void setFan(bool turnOn) {
  fanOn = turnOn;
  int activeLevel = RELAY_ACTIVE_LOW ? LOW : HIGH;
  int inactiveLevel = RELAY_ACTIVE_LOW ? HIGH : LOW;
  digitalWrite(RELAY_PIN, turnOn ? activeLevel : inactiveLevel);
}

String modeText() {
  return controlMode == AUTO_MODE ? "Automático" : "Manual";
}

void readSensor() {
  float newTemp = dht.readTemperature();
  float newHumidity = dht.readHumidity();

  if (!isnan(newTemp)) temperatureC = newTemp;
  if (!isnan(newHumidity)) humidity = newHumidity;
}

void updateAutomaticControl() {
  if (controlMode != AUTO_MODE || isnan(temperatureC)) return;

  if (temperatureC >= TEMP_ENCENDIDO) {
    setFan(true);
  } else if (temperatureC <= TEMP_APAGADO) {
    setFan(false);
  }
}

String htmlPage() {
  return R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Ventilador inteligente</title>
<style>
body{font-family:Arial,sans-serif;background:#eef2f7;color:#172033;margin:0;padding:22px}
main{max-width:520px;margin:auto;background:white;padding:22px;border-radius:16px;box-shadow:0 5px 20px #0001}
h1{font-size:24px;margin-top:0}.metric{font-size:30px;font-weight:bold;margin:8px 0 18px}
button{border:0;border-radius:9px;padding:13px 16px;margin:5px;background:#1769aa;color:white;font-size:15px}
button.secondary{background:#475569}.status{padding:12px;background:#f1f5f9;border-radius:10px;margin:10px 0}
small{color:#64748b}
</style>
</head>
<body><main>
<h1>Ventilador automático Wi-Fi</h1>
<div class="status">Temperatura<div class="metric" id="temp">-- °C</div></div>
<div class="status">Humedad<div class="metric" id="hum">-- %</div></div>
<p><b>Ventilador:</b> <span id="fan">--</span></p>
<p><b>Modo:</b> <span id="mode">--</span></p>
<button onclick="send('/mode/auto')">Automático</button>
<button onclick="send('/mode/on')">Encender</button>
<button class="secondary" onclick="send('/mode/off')">Apagar</button>
<p><small>Actualización automática cada 2 segundos.</small></p>
</main>
<script>
async function refresh(){
 try{
  const r=await fetch('/status'); const d=await r.json();
  document.getElementById('temp').textContent=d.temperature+' °C';
  document.getElementById('hum').textContent=d.humidity+' %';
  document.getElementById('fan').textContent=d.fan;
  document.getElementById('mode').textContent=d.mode;
 }catch(e){}
}
async function send(path){await fetch(path);refresh();}
refresh();setInterval(refresh,2000);
</script>
</body></html>
)rawliteral";
}

void setupRoutes() {
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html; charset=utf-8", htmlPage());
  });

  server.on("/status", HTTP_GET, []() {
    String temp = isnan(temperatureC) ? "Sin lectura" : String(temperatureC, 1);
    String hum = isnan(humidity) ? "Sin lectura" : String(humidity, 1);
    String json = "{\"temperature\":\"" + temp +
                  "\",\"humidity\":\"" + hum +
                  "\",\"fan\":\"" + String(fanOn ? "Encendido" : "Apagado") +
                  "\",\"mode\":\"" + modeText() + "\"}";
    server.send(200, "application/json", json);
  });

  server.on("/mode/auto", HTTP_GET, []() {
    controlMode = AUTO_MODE;
    updateAutomaticControl();
    server.send(200, "text/plain", "Modo automático activado");
  });

  server.on("/mode/on", HTTP_GET, []() {
    controlMode = MANUAL_MODE;
    setFan(true);
    server.send(200, "text/plain", "Ventilador encendido manualmente");
  });

  server.on("/mode/off", HTTP_GET, []() {
    controlMode = MANUAL_MODE;
    setFan(false);
    server.send(200, "text/plain", "Ventilador apagado manualmente");
  });

  server.onNotFound([]() {
    server.send(404, "text/plain", "Ruta no encontrada");
  });
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  setFan(false);

  dht.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a Wi-Fi");

  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado a Wi-Fi.");
    Serial.print("Abre esta dirección en tu celular o PC: http://");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nNo se pudo conectar. Creando punto de acceso propio.");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Ventilador-ESP32", "ventilador123");
    Serial.print("Conéctate a Ventilador-ESP32 y abre http://");
    Serial.println(WiFi.softAPIP());
  }

  setupRoutes();
  server.begin();
  readSensor();
}

void loop() {
  server.handleClient();

  if (millis() - lastSensorRead >= SENSOR_INTERVAL_MS) {
    lastSensorRead = millis();
    readSensor();
    updateAutomaticControl();

    Serial.print("Temperatura: ");
    Serial.print(temperatureC);
    Serial.print(" °C | Humedad: ");
    Serial.print(humidity);
    Serial.print(" % | Ventilador: ");
    Serial.println(fanOn ? "ON" : "OFF");
  }
}
