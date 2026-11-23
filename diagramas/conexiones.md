# Conexiones previstas — ventilador DC de 12 V

**Esquema para montaje futuro, no validado físicamente.**

```text
DHT11 (módulo de 3 pines)           ESP32
VCC ------------------------------- 3V3
DATA ------------------------------ GPIO 4
GND ------------------------------- GND

ESP32 GPIO 26 --------------------- IN del relé (compatible con 3,3 V)
ESP32 GND ------------------------- GND lógico del módulo relé*
Relé VCC -------------------------- alimentación exigida por su modelo*

Fuente 12 V (+) ---- COM [contacto relé] NO ---- (+) rojo ventilador
Fuente 12 V (-) ------------------------------ (-) negro ventilador

ESP32: alimentación USB 5 V independiente.
```

`*` La alimentación y referencia de tierra del relé dependen de su diseño. Si usa optoaislamiento o fuente independiente, seguir estrictamente el esquema del fabricante. El circuito de contactos de 12 V no se debe unir al pin 3V3 ni al GPIO del ESP32.

**Antes de conectar:** comprobar en la etiqueta del ventilador voltaje y corriente; elegir fuente regulada de 12 V con margen suficiente; comprobar polaridad de ambos cables; verificar corriente y tensión admisibles de contactos del relé y compatibilidad de su entrada con 3,3 V. Usar bornes/empalmes aislados, nunca cables sueltos. Este esquema no indica que el hardware haya sido montado.
