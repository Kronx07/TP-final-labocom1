## Sistema de barrera con apertura por patente

**> TP Final — Laboratorio de Computación 1 | UNSAM**

Sistema que permite el ingreso a un estacionamiento mediante validación de patentes ingresadas por teclado matricial 4x4, con apertura automática de barrera, indicadores luminicos y sonoros, y modo administrador para gestión de patentes.

**> Descripción del sistema:☝️🤓**

Este sistema diseñado con arduino, simula el acceso a un estacionamiento privado por validacion de patentes, el usuario ingresa su patente desde un teclado matricial 4×4. Si se verifica la pantente contra una lista de patentes habilitadas almacenadas en memoria y hay espacio disponible en el estacionamiento, se abre la barrera, se prende el led verde dando señal de pasar y un sonido, tras 3 segundos, la barrera baja automaticamente. En caso de patente invalida o estacionamiento lleno, se muestra el mensaje correspondiente en el LCD, se enciede el led rojo y un sonido de alerta.

El sistema cuenta además con un **modo administrador** que permite agregar nuevas patentes a la lista habilitada sin necesidad de reprogramar el Arduino.

**> Diagrama de conexiones:**

<img width="1536" height="1024" alt="ChatGPT Image 10 jun 2026, 08_03_59 p m" src="https://github.com/user-attachments/assets/444ad9b7-5e84-4899-8967-df907ef4e411" />

**> Diagrama Logico:**



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


