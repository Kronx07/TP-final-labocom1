## Sistema de barrera con apertura por patente

**> TP Final — Laboratorio de Computación 1 | UNSAM**

Sistema que permite el ingreso a un estacionamiento mediante validación de patentes ingresadas por teclado matricial 4x4, con apertura automática de barrera, indicadores luminicos y sonoros, y modo administrador para gestión de patentes.

**> Descripción del sistema:☝️🤓**

Este sistema diseñado con arduino, simula el acceso a un estacionamiento privado por validacion de patentes, el usuario ingresa su patente desde un teclado matricial 4×4. Si se verifica la pantente contra una lista de patentes habilitadas almacenadas en memoria y hay espacio disponible en el estacionamiento, se abre la barrera, se prende el led verde dando señal de pasar y un sonido, tras 3 segundos, la barrera baja automaticamente. En caso de patente invalida o estacionamiento lleno, se muestra el mensaje correspondiente en el LCD, se enciede el led rojo y un sonido de alerta.

El sistema cuenta además con un **modo administrador** que permite agregar nuevas patentes a la lista habilitada sin necesidad de reprogramar el Arduino.

**> Adjunto de imagenes (Diagrama lógico y diagrama de conexiones).

------------------------------------------------

**> ⚙️ Lista de componentes:**

| Componente | Funcion |
| :---       |  ---: |
| Arduino UNO R3 | Microcontrolador |
| Teclado matricial 4x4 | Ingreso de patentes  |
| LCD 16 x 2 | Mensajes y datos mostrados en pantalla |
| Servomotor | Barrera fisica |
| 🟢 LED verde | Inidicador de acceso permitido |
| 🔴 LED rojo | Indicador de acceso denegado |
| Buzzer activo | Señal sonora de confirmación/alerta |
| Resistencias 220Ω | Limitador de corriente  |
| Protoboard | Instalacion de leds y resistencias |
| Cables dupont | Conexion del circuito arduino y los componentes |
| Sensor infrarojo MH | Deteccion de vehiculos |

