# Guion de video demostrativo (3 a 5 minutos)

**Grabar pantalla propia. No afirmar que el montaje nuevo existe físicamente.**

**0:00–0:35 — Presentación:** “Este es mi proyecto Ventilador automático con monitoreo Wi-Fi. En esta etapa presento el código para ESP32 y una simulación funcional de la lógica; todavía no hay hardware conectado.”

**0:35–1:15 — Antecedente:** describir brevemente el ventilador anterior de 12 V y su control manual. Si se muestra el video propio anterior, rotular “montaje anterior, no prueba del sistema Wi-Fi”.

**1:15–2:00 — Código:** abrir Arduino IDE, enseñar `ventilador_automatico_wifi.ino`, GPIO 4, GPIO 26 y umbrales 30/28 °C. Mostrar compilación si se puede reproducir.

**2:00–3:30 — Simulador:** abrir `simulador/index.html`. Mostrar 26 °C apagado, 30 °C encendido, 29 °C aún encendido, 28 °C apagado; probar encender y apagar manualmente.

**3:30–4:15 — Evidencias:** descargar CSV, enseñar estructura del repositorio y explicar que el navegador simula la interfaz, no hay lectura real de DHT11 ni Wi-Fi real.

**4:15–4:45 — Conclusión:** explicar pendientes: ESP32, sensor, relé, fuente 12 V, montaje, pruebas físicas y Wi-Fi. Agradecer.

**Después de grabar:** guardar video propio en `evidencias/videos/` si el tamaño lo permite, o publicar un enlace verificable en esta sección y en el README. No usar un video generado como sustituto de una demostración real.
