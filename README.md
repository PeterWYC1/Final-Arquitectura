# Final-Arquitectura

# Integrantes

> Juanes Castaño

> Tomás Lopera

> Pedro Sierra

# Explicación de Hardware

La estructura de la fotopuerta está ensamblada con madera aglomerada que se reutilizó de un escritorio viejo. Se adjunta la imágen de la estructura. 

La fotopuerta consta de dos fotoresistencias y dos LEDs. Las fotoresistencias son sensores que cambian su resistencia eléctrica en función de la cantidad de luz que reciben. Los LEDs son diodos emisores de luz que se utilizan para indicar el estado de la fotopuerta.

Cuando un objeto pasa por la fotopuerta, bloquea la luz que llega a las fotoresistencias, lo que provoca un cambio en su resistencia eléctrica. Este cambio se detecta mediante la lectura de los valores de las fotoresistencias utilizando las entradas analógicas de la placa Arduino. Se utilizan las entradas analógicas A0 y A1 para leer los valores de las fotoresistencias.

Para las conexiones con la placa Arduino se utlizó alambre de timbre porque suele ser un conductor de cobre sólido con un aislamiento relativamente grueso y duradero. Además, de ser fácil para trabajar. Se utlizaron resistencias de 10k y 1k para limitar la corriente y evitar un corto circuito.

# Explicación de Software

El código se diseñó para utilizarse en Arduino, este permite detectar el bloqueo y desbloqueo de la luz en fotoresistencias, calcular la velocidad y la aceleración del objeto que pasa a través de la fotopuerta, y mostrar los resultados en el monitor serial.

En la función **setup()**, se configuran los pines de salida para los LED y se inicia la comunicación serial.

```cpp
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}
```

La función **loop()** es el bucle principal del programa. En este bucle, se leen los valores de las fotoresistencias, se realizan cálculos para detectar el bloqueo y desbloqueo de la luz en las fotoresistencias, se calcula la velocidad y la aceleración del objeto detectadoy se imprimen los resultados en el monitor serial.

```cpp
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
      
      }
    //  Serial.print(valorFoto1); 
    // Serial.println(valorFoto2);
      delay(1); // Ajusta el retardo según sea necesario
    }
```
