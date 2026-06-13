## Sistema de barrera con apertura por patente

**> TP Final — Laboratorio de Computación 1 | UNSAM**

Sistema que permite el ingreso a un estacionamiento mediante validación de patentes ingresadas por teclado matricial 4x4, con apertura automática de barrera, indicadores luminicos y sonoros, y modo administrador para gestión de patentes.

**> Descripción del sistema:☝️🤓**

Este sistema diseñado con arduino, simula el acceso a un estacionamiento privado por validacion de patentes, el usuario ingresa su patente desde un teclado matricial 4×4. Si se verifica la pantente contra una lista de patentes habilitadas almacenadas en memoria y hay espacio disponible en el estacionamiento, se abre la barrera, se prende el led verde dando señal de pasar y un sonido, tras 3 segundos, la barrera baja automaticamente. En caso de patente invalida o estacionamiento lleno, se muestra el mensaje correspondiente en el LCD, se enciede el led rojo y un sonido de alerta.

El sistema cuenta además con un **modo administrador** que permite agregar nuevas patentes a la lista habilitada sin necesidad de reprogramar el Arduino.

**> Diagrama Logico:**


<img width="863" height="1823" alt="ChatGPT Image Jun 12, 2026, 04_51_16 PM" src="https://github.com/user-attachments/assets/5f5c5b40-f049-4200-b916-003679532785" />


**> Diagrama de conexiones:**


<img width="1536" height="1024" alt="ChatGPT Image Jun 12, 2026, 05_06_32 PM" src="https://github.com/user-attachments/assets/1bf1abe7-4079-42df-82ca-3152efe97867" />


**> Diagrama de circuito:**


<img width="1082" height="785" alt="Screenshot 2026-06-13 173726" src="https://github.com/user-attachments/assets/6e72887a-0587-4ff1-a24e-49f49b33cd80" />


*> Aclaraciones importantes sobre el diagrama de circuito:**

*_ Ya que Tinkercad Circuits no cuenta con algunos de los componentes utilizados en el sistema fisico, fue necesario cambiar ciertos detalles para poder representar el funcionamiento general del proyecto dentro de la simulacion. En primer lugar, el sistema fisico utiliza un sensor infrarrojo MH para la deteccion de vehiculos. Debido a esto, como este componente no se encuentra disponible en tinkercad, se utilizo un sensor ultrasonico como reemplazo en el diseño del circuito. Por este motivo, sobre la linea donde se declara el sensor ("#define SENSOR_MH A0") se agrego el comentario: "// En la simulacion es el Ultrasonic Distance Sensor !!!", ademas, el sistema fisico esta diseñado para trabajar con una pantalla OLED SSD1306. Como este modelo tampoco esta disponible en el catalogo de Tinkercad Circuits, se decidio por utilizar una pantalla LCD 16x2 con interfaz I2C para representar su funcionamiento en la simulacion. Para detallar esta diferencia, se añadio el siguiente comentario antes de la inicialización de la pantalla: "// En la simulacion seria el LCD 16x2 (I2C) !!!".*

**> ⚙️ Lista de componentes:**

| Componente | Funcion |
| :---       |  ---: |
| Arduino UNO R3 | Microcontrolador |
| Teclado matricial 4x4 | Ingreso de patentes  |
| Pantalla OLED SSD1306 | Mensajes y datos mostrados en pantalla |
| Servomotor | Barrera fisica |
| 🟢 LED verde | Inidicador de acceso permitido |
| 🔴 LED rojo | Indicador de acceso denegado |
| Buzzer activo | Señal sonora de confirmación/alerta |
| Resistencias 220Ω | Limitador de corriente  |
| Protoboard | Instalacion de leds y resistencias |
| Cables dupont | Conexion del circuito arduino y los componentes |
| Sensor infrarojo MH | Deteccion de vehiculos |

**> Librerias:**

| Librerias | Funcion |
| --- | --- |
| #include <Wire.h> | Comunicación I2C  |
| #include <Adafruit_GFX.h> | Motor gráfico |
| #include <Adafruit_SSD1306.h> | Driver para pantalla OLED SSD1306  | 
| #include <Keypad.h> | Teclado matricial 4x4 | 
| #include <Servo.h> | Servomotor (Barrera) | 
| #include <EEPROM.h> | Lectura y escritura en la memoria no volátil del ATmega | 

**> Integrantes:**

| Alumnos 🧐 | 
| --- | 
| 1 . Alex Sosa D´Estefano |  
| 2 . Rodrigo Caceres |  
| 3 . Gaston Casanova |
| 4 . Julieta Paez |
| 5 . Martina Chalekian |

*TP Final — Laboratorio de Computación 1 | UNSAM x Sin Delay*
