# Ventilador automático con monitoreo Wi-Fi

**Estado: prototipo de software compilado + simulador local probado por el autor; hardware nuevo pendiente.**

> ⚠️ El simulador NO mide temperatura real, NO se conecta a un ESP32 y NO constituye evidencia de funcionamiento físico o Wi-Fi real. El video histórico del ventilador anterior es un antecedente, no evidencia del nuevo prototipo.

## 1. Nombre del proyecto
Ventilador automático con monitoreo Wi-Fi.

## 2. Integrantes
- [COMPLETAR: nombres reales de los integrantes]
- Institución / asignatura / docente: [COMPLETAR]

## 3. Problema
El ventilador original se accionaba manualmente. Se propone un control automático por temperatura y una interfaz de consulta y control por Wi-Fi.

## 4. Objetivo general
Desarrollar el software de un sistema basado en ESP32 que controle un ventilador DC de 12 V según temperatura y permita monitoreo mediante una interfaz web local.

## 5. Objetivos específicos
- Leer temperatura y humedad de un DHT11 cuando se disponga del hardware.
- Aplicar encendido a 30 °C y apagado a 28 °C en modo automático.
- Permitir control manual y consulta de estado por web local.
- Verificar la lógica mediante un simulador independiente y documentar las limitaciones.

## 6. Funcionamiento
El firmware para ESP32 usa DHT11 en GPIO 4 y señal de control del relé en GPIO 26. La lógica automática enciende a ≥30 °C, apaga a ≤28 °C y mantiene el estado intermedio (histéresis). Permite modo manual y servidor web local. La simulación reproduce esa lógica con valores introducidos por el usuario; no implementa comunicación Wi-Fi real.

## 7. Componentes
**Disponible según lo indicado por el autor:** ventilador DC de 12 V con dos cables, rojo (+) y negro (−). **Pendientes:** ESP32 DevKit, DHT11, relé apto para control de 3,3 V y corriente del ventilador, fuente regulada de 12 V dimensionada según etiqueta del ventilador, cable USB de datos, cables y protoboard. El ESP32 se alimenta por USB 5 V, no por 12 V.

## 8. Arquitectura
En el montaje previsto: DHT11 → ESP32 (control y servidor web) → entrada del módulo relé → contacto de potencia → ventilador de 12 V. Fuente 12 V exclusiva del circuito del ventilador; alimentación del ESP32 separada por USB. En la simulación, la temperatura se ajusta con un deslizador y todo funciona dentro del navegador.

## 9. Diagrama de conexiones
Consultar [`diagramas/conexiones.md`](diagramas/conexiones.md). Es un esquema de diseño pendiente de verificar contra el relé y el ventilador reales; no conectar sin revisar especificaciones.

## 10. Software utilizado
Arduino IDE 2, paquete ESP32 by Espressif Systems, DHT sensor library y Adafruit Unified Sensor; firmware en [`codigo/ventilador_automatico_wifi.ino`](codigo/ventilador_automatico_wifi.ino). Simulador HTML/CSS/JavaScript sin dependencias en [`simulador/index.html`](simulador/index.html).

## 11. Instalación y ejecución
**Simulación:** descargar el repositorio, abrir `simulador/index.html` con Chrome o Edge; mover el deslizador y probar botones. No necesita hardware ni conexión a Internet.

**Firmware:** instalar Arduino IDE 2, paquete `esp32 by Espressif Systems` y librerías Adafruit DHT/Unified Sensor. Abrir `codigo/ventilador_automatico_wifi.ino`, seleccionar `ESP32 Dev Module` y pulsar **Verificar**. Para cargarlo a hardware futuro, primero revisar cableado y fuente, configurar credenciales Wi-Fi sin publicarlas, conectar ESP32 por USB y seleccionar puerto. La red de respaldo y sus credenciales de demostración se encuentran en el código y deben cambiarse antes de cualquier uso real.

## 12. Pruebas
Consultar [`pruebas/registro_de_pruebas.md`](pruebas/registro_de_pruebas.md). El autor reportó compilación exitosa en Arduino IDE y que el simulador funcionó en su PC. No se ha ejecutado una verificación independiente del hardware. Se proporcionan casos reproducibles para documentar resultados observados.

## 13. Evidencias fotográficas
Las fotografías del montaje **nuevo** están pendientes. No se han fabricado fotos. Se pueden agregar capturas auténticas de Arduino IDE y de la simulación, etiquetándolas como evidencias de software. Se requiere verificar si el docente acepta ese avance en sustitución parcial de evidencias físicas.

## 14. Video demostrativo
Guion en [`documentacion/guion_video.md`](documentacion/guion_video.md) para grabar una demostración real de pantalla de 3–5 minutos, explicando claramente que es simulación. El video del montaje anterior, si se incluye, debe identificarse como **antecedente histórico**.

## 15. Dificultades, soluciones y conclusiones
**Dificultad:** actualmente no se dispone de ESP32, DHT11, relé ni fuente 12 V para probar el nuevo montaje. **Solución parcial:** se implementó el firmware y una simulación local que permite probar la lógica de control sin componentes. **Conclusión:** el software está preparado y el simulador permite demostrar el algoritmo; quedan pendientes montaje, medición real, conmutación del ventilador y conectividad Wi-Fi física.

## Estado de entrega
- [x] Firmware preparado y compilado según captura del autor.
- [x] Simulador HTML preparado y probado por el autor.
- [x] Documentación y casos de prueba preparados.
- [ ] Evidencias físicas actuales (al menos cinco fotografías reales).
- [ ] Pruebas con hardware real y Wi-Fi real.
- [ ] Video de demostración grabado por el autor.
- [ ] Nombres, enlace de video y resultados observados completados.

## Seguridad y autoría
No conectar 12 V al ESP32 ni el motor a GPIO. Verificar polaridad, corriente y compatibilidad del relé. No trabajar con 110/120 V. No publicar contraseñas reales ni afirmar que las pruebas físicas se completaron. Código y simulador preparados con asistencia de ChatGPT; verificar reglas de atribución de la asignatura.
