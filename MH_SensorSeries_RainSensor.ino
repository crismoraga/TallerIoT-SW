/*
 * ========================================
 * SENSOR DE LLUVIA MH-SENSOR SERIES
 * ========================================
 * 
 * ¿QUÉ HACE ESTE SENSOR?
 * - Detecta gotas de agua o lluvia
 * - Te dice si está lloviendo poco, medio o mucho
 * - Tiene 2 partes: la placa electrónica y la placa detectora
 * 
 * ¿CÓMO FUNCIONA?
 * 1. La placa detectora tiene pistas metálicas
 * 2. Cuando cae agua, conduce electricidad entre las pistas
 * 3. Mientras más agua haya, más electricidad conduce
 * 4. El sensor lee esto y te dice cuánta agua hay
 * 
 * CONEXIONES:
 * VCC -> 5V de Arduino
 * GND -> GND de Arduino
 * AO  -> Pin A0 (Señal analógica - lee valores de 0 a 1023)
 * DO  -> Pin 2 (Señal digital - lee solo SÍ o NO)
 * 
 * NOTA: Conecta la placa detectora a la placa electrónica
 * 
 * ========================================
 */

// Define los pines
const int pinAnalogico = A0;    // Lee valores entre 0 y 1023
const int pinDigital = 2;       // Lee solo 0 (seco) o 1 (mojado)

// Variables
int valorLluvia = 0;            // Guardará el nivel de lluvia
int estadoDigital = 0;          // Guardará si hay agua (0 o 1)

void setup() {
  // Configuramos los pines
  pinMode(pinDigital, INPUT);   // El pin digital es entrada
  
  // Iniciamos comunicación con la computadora
  Serial.begin(9600);
  Serial.println("=== SENSOR DE LLUVIA MH-SENSOR ===");
  Serial.println("Esperando lluvia...");
  Serial.println("");
}

void loop() {
  // ===== LEER EL SENSOR =====
  
  // Lectura analógica (valores de 0 a 1023)
  // 0 = mucha agua
  // 1023 = nada de agua (sensor seco)
  valorLluvia = analogRead(pinAnalogico);
  
  // Lectura digital (solo SÍ o NO)
  estadoDigital = digitalRead(pinDigital);
  
  // ===== MOSTRAR VALORES =====
  Serial.print("Valor analógico: ");
  Serial.print(valorLluvia);
  Serial.print(" | ");
  
  // ===== INTERPRETAR LOS DATOS =====
  if (estadoDigital == LOW) {
    Serial.print("Estado: AGUA DETECTADA | ");
  } else {
    Serial.print("Estado: SECO | ");
  }
  
  // Clasificar intensidad de lluvia
  // IMPORTANTE: Estos valores pueden cambiar según tu sensor
  // ¡Experimenta y ajústalos!
  if (valorLluvia > 900) {
    Serial.println("Nivel: SECO ☀️");
  } else if (valorLluvia > 600) {
    Serial.println("Nivel: LLUVIA LIGERA 🌦️");
  } else if (valorLluvia > 300) {
    Serial.println("Nivel: LLUVIA MODERADA 🌧️");
  } else {
    Serial.println("Nivel: LLUVIA FUERTE ⛈️");
  }
  
  // ===== EXPERIMENTOS PARA PROBAR =====
  
  // 1. Alerta de lluvia:
  /*
  if (valorLluvia < 500) {
    Serial.println("¡¡¡ALERTA: ESTÁ LLOVIENDO!!!");
  }
  */
  
  // 2. Contador de gotas:
  /*
  static int contadorGotas = 0;
  if (estadoDigital == LOW) {
    contadorGotas++;
    Serial.print("Gotas detectadas: ");
    Serial.println(contadorGotas);
    delay(1000);  // Espera para no contar la misma gota muchas veces
  }
  */
  
  // Esperar un segundo antes de leer de nuevo
  delay(1000);
}

/*
 * ========================================
 * RETOS PARA EXPERIMENTAR:
 * ========================================
 * 1. Pon gotas de agua en la placa detectora y observa los valores
 * 2. Ajusta los números (900, 600, 300) según tu sensor
 * 3. Conecta un LED que se encienda cuando detecte agua
 * 4. Haz que un buzzer suene como alarma cuando llueva
 * 5. Crea un sistema que cierre una "ventana" (servo) al detectar lluvia
 * 
 * CUIDADO: No sumerjas la placa electrónica en agua,
 * solo la placa detectora puede mojarse
 * ========================================
 */
