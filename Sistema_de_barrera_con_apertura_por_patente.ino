// PROYECTO SIN DELAY + EEPROM
// Barrera por patente + OLED + teclado + servo + sensor MH

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <Servo.h>
#include <EEPROM.h>

// OLED
#define ANCHO 128
#define ALTO 32
#define OLED_RESET -1

Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, OLED_RESET);
Servo SERVO;

// PINES
#define SERVO_PIN 10
#define LED_VERDE 13
#define LED_ROJO 12
#define BUZZER 11
#define SENSOR_MH A0

// ESTADOS
#define MENU 0
#define LEYENDO_PATENTE 1
#define ABIERTO 2
#define MENSAJE 3

// ACCIONES
#define NINGUNA 0
#define INGRESO 1
#define AGREGAR 2
#define SALIDA 3

int estado = MENU;
int accion = NINGUNA;

// EEPROM
#define EEPROM_MARCA_ADDR 0
#define EEPROM_CANT_ADDR 1
#define EEPROM_OCUP_ADDR 2
#define EEPROM_PAT_ADDR 10
#define EEPROM_MARCA 85

// TECLADO
const byte FILAS = 4;
const byte COLUMNAS = 4;

char teclas[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinesFilas[FILAS] = {9, 8, 7, 6};
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2};

Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// PATENTES
char patente[8];
int indice = 0;

char patentes[10][8] = {
  "1234",
  "456B",
  "789C"
};

int cantidadPatentes = 3;

// ESTACIONAMIENTO
int ocupacion = 0;
int capacidadMaxima = 5;

// MENU
bool pagina = false;

// TIEMPOS
unsigned long tiempoActual = 0;
unsigned long tiempoInicio = 0;
unsigned long tiempoBarrera = 3000;
unsigned long tiempoMensaje = 2000;

// SENSOR
bool sensorDetectaEnLow = true;

void setup() {
  Serial.begin(9600);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(SENSOR_MH, INPUT_PULLUP);

  SERVO.attach(SERVO_PIN);
  cerrarBarrera();

  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.display();

  limpiarPatente();

  cargarDesdeEEPROM();

  mostrarMenu();
}

void loop() {
  tiempoActual = millis();

  char tecla = teclado.getKey();

  if (tecla) {
    leerTecla(tecla);
  }

  if (estado == ABIERTO) {

    if (sensorDetectado()) {
      tiempoInicio = tiempoActual;
      mensaje("Vehiculo detectado", "No cerrar");
    }

    if (tiempoActual - tiempoInicio >= tiempoBarrera) {
      cerrarBarrera();
      limpiarPatente();
      estado = MENU;
      mostrarMenu();
    }
  }

  if (estado == MENSAJE) {
    if (tiempoActual - tiempoInicio >= tiempoMensaje) {
      limpiarPatente();
      estado = MENU;
      mostrarMenu();
    }
  }
}

void leerTecla(char tecla) {

  if (estado == MENU) {

    if (tecla == 'A') {
      pagina = !pagina;
      mostrarMenu();
    }

    else if (tecla == '1') {
      accion = INGRESO;
      limpiarPatente();
      estado = LEYENDO_PATENTE;
      pantallaPatente("Ingreso vehiculo");
    }

    else if (tecla == '2') {
      accion = AGREGAR;
      limpiarPatente();
      estado = LEYENDO_PATENTE;
      pantallaPatente("Agregar patente");
    }

    else if (tecla == '3') {
      pantallaOcupacion();
      estado = MENSAJE;
      tiempoInicio = tiempoActual;
    }

    else if (tecla == '4') {
      accion = SALIDA;
      limpiarPatente();
      estado = LEYENDO_PATENTE;
      pantallaPatente("Salida vehiculo");
    }

    else if (tecla == 'D') {
      inicializarEEPROM();
      mensaje("EEPROM RESET", "Datos iniciales");
      estado = MENSAJE;
      tiempoInicio = tiempoActual;
    }
  }

  else if (estado == LEYENDO_PATENTE) {

    if (tecla == '*') {
      limpiarPatente();
      pantallaPatente("Patente:");
    }

    else if (tecla == '#') {
      ejecutarAccion();
    }

    else {
      agregarCaracter(tecla);
    }
  }
}

void ejecutarAccion() {

  if (accion == INGRESO) {

    if (patenteExiste()) {

      if (ocupacion < capacidadMaxima) {
        ocupacion++;
        guardarOcupacionEEPROM();

        mensaje("Ingreso OK", "Barrera abierta");
        abrirBarrera();

        tone(BUZZER, 1000, 200);

        estado = ABIERTO;
        tiempoInicio = tiempoActual;
      }

      else {
        mensaje("Sin lugar", "Estac. lleno");
        tone(BUZZER, 250, 700);

        estado = MENSAJE;
        tiempoInicio = tiempoActual;
      }
    }

    else {
      mensaje("No registrada", patente);
      tone(BUZZER, 300, 700);

      estado = MENSAJE;
      tiempoInicio = tiempoActual;
    }
  }

  else if (accion == AGREGAR) {

    if (cantidadPatentes < 10) {
      strcpy(patentes[cantidadPatentes], patente);

      guardarPatenteEEPROM(cantidadPatentes);

      cantidadPatentes++;
      guardarCantidadEEPROM();

      mensaje("Patente OK", patente);
      tone(BUZZER, 1200, 200);
    }

    else {
      mensaje("Lista llena", "Max 10 patentes");
      tone(BUZZER, 300, 700);
    }

    estado = MENSAJE;
    tiempoInicio = tiempoActual;
  }

  else if (accion == SALIDA) {

    if (patenteExiste() && ocupacion > 0) {
      ocupacion--;
      guardarOcupacionEEPROM();

      mensaje("Salida OK", "Barrera abierta");

      abrirBarrera();

      tone(BUZZER, 900, 200);

      estado = ABIERTO;
      tiempoInicio = tiempoActual;
    }

    else {
      mensaje("Error salida", patente);
      tone(BUZZER, 300, 700);

      estado = MENSAJE;
      tiempoInicio = tiempoActual;
    }
  }
}

bool patenteExiste() {
  for (int i = 0; i < cantidadPatentes; i++) {
    if (strcmp(patente, patentes[i]) == 0) {
      return true;
    }
  }

  return false;
}

bool sensorDetectado() {
  int lectura = digitalRead(SENSOR_MH);

  if (sensorDetectaEnLow == true) {
    return lectura == LOW;
  } else {
    return lectura == HIGH;
  }
}

void agregarCaracter(char tecla) {
  if (indice < 7) {
    patente[indice] = tecla;
    indice++;
    patente[indice] = '\0';

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Patente:");

    display.setTextSize(2);
    display.setCursor(0, 16);
    display.print(patente);

    display.setTextSize(1);
    display.display();
  }
}

void limpiarPatente() {
  indice = 0;
  patente[0] = '\0';
}

void abrirBarrera() {
  SERVO.write(90);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_ROJO, LOW);
}

void cerrarBarrera() {
  SERVO.write(0);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, HIGH);
}

void mostrarMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);

  if (!pagina) {
    display.println("1.Ing Veh");
    display.println("2.Agr Pat");
    display.println("A: Mas opciones");
  }
  else {
    display.println("3.Ocupacion");
    display.println("4.Salida");
    display.println("D: Reset EEPROM");
  }

  display.display();
}

void pantallaPatente(const char* titulo) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(titulo);
  display.println("# OK  * BORRAR");
  display.display();
}

void pantallaOcupacion() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Ocupacion:");
  display.print(ocupacion);
  display.print("/");
  display.println(capacidadMaxima);
  display.display();
}

void mensaje(const char* linea1, const char* linea2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(linea1);
  display.println(linea2);
  display.display();
}

// ================= EEPROM =================

int direccionPatente(int numero) {
  return EEPROM_PAT_ADDR + (numero * 8);
}

void cargarDesdeEEPROM() {

  byte marca = EEPROM.read(EEPROM_MARCA_ADDR);

  if (marca != EEPROM_MARCA) {
    inicializarEEPROM();
    return;
  }

  cantidadPatentes = EEPROM.read(EEPROM_CANT_ADDR);
  ocupacion = EEPROM.read(EEPROM_OCUP_ADDR);

  if (cantidadPatentes < 0 || cantidadPatentes > 10) {
    cantidadPatentes = 3;
  }

  if (ocupacion < 0 || ocupacion > capacidadMaxima) {
    ocupacion = 0;
  }

  for (int i = 0; i < 10; i++) {
    int dir = direccionPatente(i);

    for (int j = 0; j < 8; j++) {
      patentes[i][j] = EEPROM.read(dir + j);
    }

    patentes[i][7] = '\0';
  }
}

void inicializarEEPROM() {

  strcpy(patentes[0], "1234");
  strcpy(patentes[1], "456B");
  strcpy(patentes[2], "789C");

  for (int i = 3; i < 10; i++) {
    patentes[i][0] = '\0';
  }

  cantidadPatentes = 3;
  ocupacion = 0;

  EEPROM.update(EEPROM_MARCA_ADDR, EEPROM_MARCA);
  guardarCantidadEEPROM();
  guardarOcupacionEEPROM();

  for (int i = 0; i < 10; i++) {
    guardarPatenteEEPROM(i);
  }
}

void guardarCantidadEEPROM() {
  EEPROM.update(EEPROM_CANT_ADDR, cantidadPatentes);
}

void guardarOcupacionEEPROM() {
  EEPROM.update(EEPROM_OCUP_ADDR, ocupacion);
}

void guardarPatenteEEPROM(int numero) {
  int dir = direccionPatente(numero);

  for (int j = 0; j < 8; j++) {
    EEPROM.update(dir + j, patentes[numero][j]);
  }
}
