# Seguridad y verificación

- Ventilador real informado por el autor: DC 12 V, dos cables rojo (+) y negro (-).
- No conectar el ventilador a un pin del ESP32 ni 12 V al pin 5V/3V3.
- Fuente DC regulada 12 V: dimensionar corriente según placa del ventilador; el valor 2 A solo es un candidato sujeto a verificación.
- Verificar compatibilidad de control a 3,3 V del relé, su alimentación y la corriente nominal de contactos.
- No conectar tensión de red doméstica al montaje.
- El esquema de conexiones es orientativo hasta confirmar el modelo exacto de relé.
- El software puede compilar sin hardware; la compilación no demuestra que el sensor, relé o Wi-Fi funcionen.
- El simulador no usa Wi-Fi real y no mide datos reales.
