# Registro de pruebas — simulación y hardware

## Evidencia reportada por el autor
- **Compilación Arduino IDE / ESP32 Dev Module:** exitosa según captura compartida; consumo indicado: programa 76 %, RAM 15 %. Esto demuestra compilación, no ejecución en placa.
- **Simulador local HTML:** el autor indicó que “salió todo bien”; sin registro CSV ni captura de resultados específicos adjuntos a este paquete.

## Casos para ejecutar y registrar en el simulador

| ID | Pasos | Resultado esperado | Resultado observado | Evidencia |
|---|---|---|---|---|
| S1 | Reiniciar; seleccionar automático; temperatura 30 °C | Ventilador ENCENDIDO | [COMPLETAR] | [captura/CSV] |
| S2 | Después de S1, bajar a 29 °C | Permanece ENCENDIDO | [COMPLETAR] | [captura/CSV] |
| S3 | Después de S2, bajar a 28 °C | Ventilador APAGADO | [COMPLETAR] | [captura/CSV] |
| S4 | Elegir encender manualmente con 26 °C | ENCENDIDO | [COMPLETAR] | [captura/CSV] |
| S5 | Elegir apagar manualmente con 35 °C | APAGADO | [COMPLETAR] | [captura/CSV] |

**Para generar evidencias reales:** abrir `simulador/index.html`, ejecutar S1–S5, tomar capturas y pulsar “Descargar registro CSV”. Guardar los archivos aquí. No rellenar resultados hasta ejecutar cada prueba.

## Pruebas físicas pendientes
- P1: lectura real de DHT11 y temperatura/humedad.
- P2: conmutación de relé y ventilador de 12 V con fuente adecuada.
- P3: conexión Wi-Fi real y control desde otro dispositivo.

**Estado P1–P3: NO REALIZADAS.**
