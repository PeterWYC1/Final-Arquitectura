const int ft1 = A0;
const int ft2 = A1;
const int led1 = 12;
const int led2 = 11;

const float distancia = 0.2; 
bool objetoDetectado = false;
unsigned long tiempoInicio = 0;
unsigned long tiempoDeteccion = 0;

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int valorFoto1 = analogRead(ft1);
  int valorFoto2 = analogRead(ft2);
  float velocidad = 0.0;
  float aceleracion = 0.0;
  float aceleracion2 = 0.0;

  int minFT1 = 720;
  int minFT2 = 450;

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  // Detección del bloqueo de la luz en la primera fotoresistencia
  if (valorFoto1 < minFT1 && !objetoDetectado) {
    tiempoInicio = millis(); // Guardar el tiempo actual
    objetoDetectado = true;
  }

  // Detección del desbloqueo en la segunda fotoresistencia
  if (valorFoto2 < minFT2 && objetoDetectado) {
    tiempoDeteccion = millis() - tiempoInicio; // Calcular el tiempo que pasó
    objetoDetectado = false;

    // Calcular velocidad y aceleración
    velocidad = distancia / (tiempoDeteccion / 1000.0); // m/s
    aceleracion = velocidad / (tiempoDeteccion / 1000.0); // m/s^2
    aceleracion2 = (2 * (distancia))/((tiempoDeteccion*tiempoDeteccion)*1000.0);
    // Imprimir resultados en el monitor serie
    
    Serial.print("Tiempo de deteccion: ");
    Serial.print(tiempoDeteccion);
    Serial.print(" ms, Velocidad: ");
    Serial.print(velocidad);
    Serial.print(" m/s, Aceleración: ");
    // Serial.print(aceleracion);
    Serial.print(aceleracion);
    Serial.println(" m/s^2");
    Serial.print("Aceleración 2: ");
    // Serial.print(aceleracion);
    Serial.print(aceleracion2);

  
  }
//  Serial.print(valorFoto1); 
// Serial.println(valorFoto2);
  delay(1); // Ajusta el retardo según sea necesario
}
