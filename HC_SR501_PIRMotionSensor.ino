#include <Arduino.h>
/*
 * ========================================
 * SENSOR DE MOVIMIENTO PIR HC-SR501
 * ========================================
 * 
 * ¿QUÉ HACE ESTE SENSOR?
 * - Detecta movimiento de personas o animales
 * - "Ve" el calor que emiten los cuerpos (radiación infrarroja)
 * - Usado en luces automáticas y alarmas de seguridad
 * 
 * ¿CÓMO FUNCIONA?
 * 1. Detecta cambios en la radiación infrarroja (calor)
 * 2. Cuando algo caliente se mueve, lo detecta
 * 3. Envía una señal HIGH cuando hay movimiento
 * 4. Envía LOW cuando no hay movimiento
 * 
 * CONEXIONES:
 * VCC -> 5V de Arduino
 * OUT -> Pin 8 (puedes cambiar este número)
 * GND -> GND de Arduino
 * 
 * AJUSTES DEL SENSOR (potenciómetros en el sensor):
 * - Sensibilidad: Qué tan lejos puede detectar (3 a 7 metros)
 * - Tiempo: Cuánto dura la señal activa (5 seg a 5 min)
 * 
 * JUMPER (el pequeño conector):
 * - H: Modo repetible (detecta mientras hay movimiento)
 * - L: Modo único (detecta una vez y espera)
 * 
 * ========================================
 */

// Define el pin
const int pinPIR = 8;           // Pin donde está conectado el sensor
const int pinLED = 13;          // LED integrado de Arduino (para pruebas)

// Variables
int estadoMovimiento = LOW;     // Estado actual del sensor
int lecturaAnterior = LOW;      // Para detectar cambios
unsigned long tiempoDeteccion = 0;  // Cuándo se detectó movimiento
int contadorMovimientos = 0;    // Contador de detecciones

void setup() {
  // Configurar pines
  pinMode(pinPIR, INPUT);       // El sensor es entrada
  pinMode(pinLED, OUTPUT);      // El LED es salida
  
  // Iniciamos comunicación
  Serial.begin(9600);
  Serial.println("=== SENSOR DE MOVIMIENTO PIR HC-SR501 ===");
  Serial.println("");
  Serial.println("⏳ Calibrando sensor...");
  Serial.println("   No te muevas durante 30 segundos");
  
  // El sensor necesita calibrarse al inicio
  // Espera 30-60 segundos sin movimiento
  for (int i = 30; i > 0; i--) {
    Serial.print(i);
    Serial.println(" segundos...");
    delay(1000);
  }
  
  Serial.println("✅ Sensor calibrado y listo");
  Serial.println("👀 Esperando movimiento...");
  Serial.println("");
}

void loop() {
  // ===== LEER EL SENSOR =====
  estadoMovimiento = digitalRead(pinPIR);
  
  // ===== DETECTAR CAMBIO DE ESTADO =====
  if (estadoMovimiento == HIGH && lecturaAnterior == LOW) {
    // Se detectó movimiento por primera vez
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    Serial.println("🚨 ¡MOVIMIENTO DETECTADO!");
    tiempoDeteccion = millis();  // Guardar el momento
    contadorMovimientos++;       // Aumentar contador
    
    Serial.print("Detección número: ");
    Serial.println(contadorMovimientos);
    
    // Encender LED
    digitalWrite(pinLED, HIGH);
    
    lecturaAnterior = HIGH;
  }
  
  if (estadoMovimiento == LOW && lecturaAnterior == HIGH) {
    // El movimiento terminó
    Serial.println("✅ Movimiento finalizado");
    
    // Calcular cuánto duró
    unsigned long duracion = millis() - tiempoDeteccion;
    Serial.print("Duración: ");
    Serial.print(duracion / 1000);
    Serial.println(" segundos");
    Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    Serial.println("");
    
    // Apagar LED
    digitalWrite(pinLED, LOW);
    
    lecturaAnterior = LOW;
  }
  
  // ===== EXPERIMENTOS PARA PROBAR =====
  
  // 1. Alarma simple:
  /*
  if (estadoMovimiento == HIGH) {
    tone(pinBuzzer, 1000);  // Hacer sonar buzzer
  } else {
    noTone(pinBuzzer);
  }
  */
  
  // 2. Luz automática:
  /*
  if (estadoMovimiento == HIGH) {
    digitalWrite(pinLuzLED, HIGH);  // Encender luz
    delay(5000);  // Mantener encendida 5 segundos
  } else {
    digitalWrite(pinLuzLED, LOW);
  }
  */
  
  // 3. Contador de personas:
  /*
  // Útil para contar cuántas veces pasa alguien
  if (estadoMovimiento == HIGH && lecturaAnterior == LOW) {
    Serial.print("Personas detectadas hoy: ");
    Serial.println(contadorMovimientos);
  }
  */
  
  // 4. Sistema de seguridad:
  /*
  static boolean alarmaActivada = true;
  if (alarmaActivada && estadoMovimiento == HIGH) {
    Serial.println("🚨🚨🚨 ¡INTRUSO DETECTADO! 🚨🚨🚨");
    // Activar sirena, enviar mensaje, etc.
  }
  */
  
  // Pequeña pausa para no saturar la lectura
  delay(100);
}

/*
 * ========================================
 * RETOS PARA EXPERIMENTAR:
 * ========================================
 * 1. Muévete frente al sensor y observa qué pasa
 * 2. Ajusta los potenciómetros del sensor para cambiar:
 *    - Sensibilidad (distancia de detección)
 *    - Tiempo que permanece activo
 * 3. Conecta un buzzer para hacer una alarma
 * 4. Conecta un relé para encender una lámpara real
 * 5. Haz un contador de personas que entran a una habitación
 * 6. Crea un sistema que envíe alerta cuando detecte movimiento de noche
 * 
 * TIPS:
 * - El sensor detecta mejor el movimiento lateral que frontal
 * - Necesita "ver" cambios de temperatura
 * - No funciona bien detrás de cristales
 * - La luz solar directa puede causar falsas alarmas
 * 
 * SOLUCIÓN DE PROBLEMAS:
 * - Si detecta todo el tiempo: Reduce la sensibilidad
 * - Si no detecta nada: Aumenta la sensibilidad
 * - Si da lecturas raras: Recalíbralo (reinicia Arduino)
 * 
 * ========================================
 */
