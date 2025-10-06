/*
 * ========================================
 * SENSOR DE NIVEL DE AGUA
 * ========================================
 * 
 * ¿QUÉ HACE ESTE SENSOR?
 * - Mide qué tan lleno está un tanque o recipiente
 * - Detecta el nivel del agua (bajo, medio, alto)
 * - Útil para acuarios, tanques, plantas, etc.
 * 
 * ¿CÓMO FUNCIONA?
 * 1. Tiene varias pistas metálicas a diferentes alturas
 * 2. Cuando el agua toca las pistas, conduce electricidad
 * 3. Mientras más alto el agua, más pistas se mojan
 * 4. Lee el valor y determina el nivel
 * 
 * CONEXIONES:
 * + (VCC) -> 5V de Arduino
 * - (GND) -> GND de Arduino
 * S (Signal) -> Pin A1 (puedes usar cualquier pin analógico)
 * 
 * IMPORTANTE: Puedes sumergir el sensor pero NO los cables
 * 
 * ========================================
 */

// Define el pin
const int pinSensor = A1;       // Pin analógico para leer el sensor

// Variables
int nivelAgua = 0;              // Guardará el valor leído (0 a 1023)
int porcentaje = 0;             // Nivel de agua en porcentaje

void setup() {
  // No necesitamos configurar pinMode para pines analógicos
  
  // Iniciamos comunicación con la computadora
  Serial.begin(9600);
  Serial.println("=== SENSOR DE NIVEL DE AGUA ===");
  Serial.println("Midiendo nivel del agua...");
  Serial.println("");
}

void loop() {
  // ===== LEER EL SENSOR =====
  nivelAgua = analogRead(pinSensor);
  
  // Convertir a porcentaje (0% = vacío, 100% = lleno)
  // NOTA: El valor máximo puede variar según tu sensor
  // Ajusta el número si es necesario (prueba sumergirlo completamente)
  porcentaje = map(nivelAgua, 0, 520, 0, 100);
  
  // Asegurarse de que esté entre 0 y 100
  porcentaje = constrain(porcentaje, 0, 100);
  
  // ===== MOSTRAR VALORES =====
  Serial.print("Valor del sensor: ");
  Serial.print(nivelAgua);
  Serial.print(" | Nivel: ");
  Serial.print(porcentaje);
  Serial.print("% | ");
  
  // ===== BARRA VISUAL =====
  Serial.print("[");
  int barras = porcentaje / 10;  // Dibuja una barra cada 10%
  for (int i = 0; i < 10; i++) {
    if (i < barras) {
      Serial.print("█");
    } else {
      Serial.print("-");
    }
  }
  Serial.print("] | ");
  
  // ===== CLASIFICAR NIVEL =====
  if (nivelAgua < 10) {
    Serial.println("VACÍO 🏜️");
  } else if (porcentaje < 25) {
    Serial.println("NIVEL MUY BAJO ⚠️");
  } else if (porcentaje < 50) {
    Serial.println("NIVEL BAJO 📊");
  } else if (porcentaje < 75) {
    Serial.println("NIVEL MEDIO 💧");
  } else if (porcentaje < 90) {
    Serial.println("NIVEL ALTO 💦");
  } else {
    Serial.println("LLENO ✅");
  }
  
  // ===== EXPERIMENTOS PARA PROBAR =====
  
  // 1. Alarma de nivel bajo:
  /*
  if (porcentaje < 20) {
    Serial.println("¡¡¡ALERTA: AGUA BAJA!!!");
    // Aquí podrías encender un LED o buzzer
  }
  */
  
  // 2. Alarma de desbordamiento:
  /*
  if (porcentaje > 90) {
    Serial.println("¡¡¡CUIDADO: SE VA A DESBORDAR!!!");
  }
  */
  
  // 3. Control de bomba automática:
  /*
  if (porcentaje < 30) {
    Serial.println(">>> Activar bomba de agua <<<");
    // digitalWrite(pinBomba, HIGH);
  } else if (porcentaje > 80) {
    Serial.println(">>> Apagar bomba <<<");
    // digitalWrite(pinBomba, LOW);
  }
  */
  
  // Esperar un segundo
  delay(1000);
}

/*
 * ========================================
 * RETOS PARA EXPERIMENTAR:
 * ========================================
 * 1. Sumerge el sensor poco a poco en agua y observa los valores
 * 2. Ajusta el número 520 en la función map() según tu sensor
 * 3. Conecta un LED RGB:
 *    - Rojo cuando esté bajo
 *    - Amarillo cuando esté medio
 *    - Azul cuando esté lleno
 * 4. Haz sonar un buzzer cuando el agua esté muy baja
 * 5. Crea un medidor para plantas que avise cuando necesiten agua
 * 
 * CALIBRACIÓN:
 * - Primero lee el valor con el sensor seco (anótalo)
 * - Luego sumérgelo completamente en agua (anótalo)
 * - Usa esos dos valores en la función map()
 * 
 * ========================================
 */
