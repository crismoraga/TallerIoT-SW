#include <Arduino.h>

/*
 * ========================================
 * SENSOR ULTRASÓNICO HC-SR04
 * ========================================
 * 
 * ¿QUÉ HACE ESTE SENSOR?
 * - Mide distancias usando ondas de sonido (como los murciélagos)
 * - Puede detectar objetos de 2cm hasta 400cm
 * - Útil para robots que evitan obstáculos
 * 
 * ¿CÓMO FUNCIONA?
 * 1. Envía un sonido ultrasónico (que no podemos escuchar)
 * 2. El sonido rebota en los objetos
 * 3. Mide cuánto tiempo tarda en volver
 * 4. Calcula la distancia
 * 
 * CONEXIONES:
 * VCC  -> 5V de Arduino
 * GND  -> GND de Arduino
 * TRIG -> Pin 11 (puedes cambiar este número)
 * ECHO -> Pin 12 (puedes cambiar este número)
 * 
 * ========================================
 */

// Define los pines que usaremos
const int pinTrigger = 11;   // Pin que envía el sonido
const int pinEcho = 12;     // Pin que recibe el sonido

// Variables para guardar datos
long duracion;              // Tiempo que tarda el sonido
int distancia;              // Distancia calculada en centímetros

void setup() {
  // Configuramos los pines
  pinMode(pinTrigger, OUTPUT);  // TRIG es salida (envía señal)
  pinMode(pinEcho, INPUT);      // ECHO es entrada (recibe señal)
  
  // Iniciamos la comunicación con la computadora
  Serial.begin(9600);
  Serial.println("=== SENSOR ULTRASÓNICO HC-SR04 ===");
  Serial.println("Midiendo distancias...");
  Serial.println("");
}

void loop() {
  // ===== PASO 1: Limpiar el sensor =====
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  
  // ===== PASO 2: Enviar sonido ultrasónico =====
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);        // Envía sonido por 10 microsegundos
  digitalWrite(pinTrigger, LOW);
  
  // ===== PASO 3: Leer cuánto tardó en volver =====
  duracion = pulseIn(pinEcho, HIGH);
  
  // ===== PASO 4: Calcular distancia =====
  // Velocidad del sonido: 340 m/s
  // Dividimos entre 2 porque va y vuelve
  distancia = duracion * 0.034 / 2;
  
  // ===== PASO 5: Mostrar resultado =====
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  // ===== EXPERIMENTOS PARA PROBAR =====
  // 1. Si hay algo cerca, encender un LED:
  /*
  if (distancia < 20) {
    Serial.println("¡OBJETO CERCA!");
  }
  */
  
  // 2. Hacer un sensor de estacionamiento:
  /*
  if (distancia < 10) {
    Serial.println("¡¡¡MUY CERCA!!!");
  } else if (distancia < 30) {
    Serial.println("Cuidado, acércate despacio");
  } else {
    Serial.println("Vía libre");
  }
  */
  
  // Esperar medio segundo antes de medir de nuevo
  delay(500);
}

/*
 * ========================================
 * RETOS PARA EXPERIMENTAR:
 * ========================================
 * 1. Cambia el delay(500) a delay(100) ¿Qué pasa?
 * 2. Activa el código comentado para detectar objetos cerca
 * 3. Conecta un LED y hazlo parpadear cuando detecte algo cerca
 * 4. Intenta hacer que un buzzer suene más rápido cuando algo se acerca
 * 
 * ========================================
 */
