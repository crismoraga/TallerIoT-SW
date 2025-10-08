/*
 * ========================================
 * SENSOR DE TEMPERATURA Y HUMEDAD DHT11
 * ========================================
 * 
 * ¿QUÉ HACE ESTE SENSOR?
 * - Mide la temperatura del aire (en grados Celsius)
 * - Mide la humedad del aire (en porcentaje)
 * - Muy usado en estaciones meteorológicas caseras
 * 
 * ¿CÓMO FUNCIONA?
 * 1. Tiene un sensor de temperatura y uno de humedad
 * 2. Lee ambos valores y los envía por un solo cable
 * 3. Usa un protocolo especial de comunicación
 * 
 * CONEXIONES:
 * Pin 1 (VCC)  -> 5V de Arduino
 * Pin 2 (DATA) -> Pin 7 (puedes cambiar este número)
 * Pin 3 (NC)   -> No se conecta
 * Pin 4 (GND)  -> GND de Arduino
 * 
 * IMPORTANTE: Necesitas instalar la librería DHT
 * En Arduino IDE: Herramientas > Administrar Bibliotecas
 * Busca "DHT sensor library" de Adafruit e instálala
 * También instala "Adafruit Unified Sensor"
 * 
 * ========================================
 */

// Incluir las librerías necesarias
#include <DHT.h>

// Configuración del sensor
#define DHTPIN 7          // Pin donde está conectado el sensor
#define DHTTYPE DHT11     // Tipo de sensor (DHT11 o DHT22)

// Crear objeto del sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables
float temperatura = 0;    // Temperatura en grados Celsius
float humedad = 0;        // Humedad en porcentaje
float sensacionTermica = 0; // Cómo se siente la temperatura

void setup() {
  // Iniciamos comunicación con la computadora
  Serial.begin(9600);
  Serial.println("=== SENSOR DHT11 - TEMPERATURA Y HUMEDAD ===");
  Serial.println("");
  
  // Iniciar el sensor
  dht.begin();
  Serial.println("Sensor inicializado. Esperando lecturas...");
  delay(100);  // Esperar 2 segundos para que se estabilice
}

void loop() {
  // ===== LEER EL SENSOR =====
  // IMPORTANTE: El DHT11 tarda en leer, no leas muy rápido
  
  humedad = dht.readHumidity();           // Lee humedad
  temperatura = dht.readTemperature();     // Lee temperatura en Celsius
  
  // Verificar si la lectura falló
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("❌ Error al leer el sensor. Verifica las conexiones.");
    delay(100);
    return;  // Salir y volver a intentar
  }
  
  // Calcular sensación térmica (cómo se siente)
  sensacionTermica = dht.computeHeatIndex(temperatura, humedad, false);
  
  // ===== MOSTRAR VALORES =====
  Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
  
  Serial.print("🌡️  Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  
  Serial.print("💧 Humedad: ");
  Serial.print(humedad);
  Serial.println(" %");
  
  Serial.print("🤔 Sensación térmica: ");
  Serial.print(sensacionTermica);
  Serial.println(" °C");
  
  // ===== CLASIFICAR TEMPERATURA =====
  Serial.print("Estado: ");
  if (temperatura < 10) {
    Serial.println("❄️  MUY FRÍO");
  } else if (temperatura < 18) {
    Serial.println("🧊 FRESCO");
  } else if (temperatura < 25) {
    Serial.println("😊 AGRADABLE");
  } else if (temperatura < 30) {
    Serial.println("☀️  CÁLIDO");
  } else {
    Serial.println("🔥 MUY CALIENTE");
  }
  
  // ===== CLASIFICAR HUMEDAD =====
  Serial.print("Ambiente: ");
  if (humedad < 30) {
    Serial.println("🏜️  SECO");
  } else if (humedad < 60) {
    Serial.println("👌 CONFORTABLE");
  } else if (humedad < 80) {
    Serial.println("💦 HÚMEDO");
  } else {
    Serial.println("🌊 MUY HÚMEDO");
  }
  
  Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
  Serial.println("");
  
  // ===== EXPERIMENTOS PARA PROBAR =====
  
  // 1. Alarma de calor:
  
  if (temperatura > 28) {
    Serial.println("¡¡¡HACE MUCHO CALOR!!!");
    // Enciende un ventilador o LED rojo
  }
  
  // 2. Monitor de confort:
  /*
  if (temperatura > 20 && temperatura < 25 && humedad > 40 && humedad < 60) {
    Serial.println("✅ Condiciones ideales para estar cómodo");
  } else {
    Serial.println("⚠️  Ambiente no óptimo");
  }
  */
  
  // 3. Detector de cambios bruscos:
  /*
  static float tempAnterior = 0;
  if (abs(temperatura - tempAnterior) > 2) {
    Serial.println("¡Cambio brusco de temperatura!");
  }
  tempAnterior = temperatura;
  */
  
  // Esperar 3 segundos (el DHT11 necesita tiempo entre lecturas)
  delay(3000);
}

/*
 * ========================================
 * RETOS PARA EXPERIMENTAR:
 * ========================================
 * 1. Sopla aire caliente cerca del sensor ¿Qué pasa?
 * 2. Pon el sensor cerca de hielo ¿Cambia la lectura?
 * 3. Haz una estación meteorológica con este y otros sensores
 * 4. Conecta LEDs de colores según la temperatura
 * 5. Crea un sistema de control de aire acondicionado
 * 6. Registra los valores cada hora y haz una gráfica
 * 
 * NOTA: El DHT11 tarda 2-3 segundos entre lecturas
 * No intentes leer más rápido o dará errores
 * 
 * Si ves valores raros (nan), verifica:
 * - Las conexiones
 * - Que instalaste las librerías
 * - Que el sensor no esté dañado
 * 
 * ========================================
 */
