/*
 * ========================================
 * MÓDULO DE CÁMARA AL422B FIFO
 * ========================================
 * 
 * ⚠️ ADVERTENCIA: Este es un sensor AVANZADO
 * 
 * ¿QUÉ HACE ESTE MÓDULO?
 * - Captura imágenes en blanco y negro o color
 * - Guarda la imagen en memoria temporal (FIFO)
 * - Permite leer la imagen píxel por píxel
 * 
 * ¿CÓMO FUNCIONA?
 * 1. La cámara captura una imagen
 * 2. La imagen se guarda en el chip AL422B (memoria FIFO)
 * 3. Arduino lee los datos de la memoria
 * 4. Los datos se pueden guardar o enviar a una computadora
 * 
 * IMPORTANTE:
 * Este sensor es MUY complejo y requiere:
 * - Muchos pines (8-12 conexiones)
 * - Librerías especiales
 * - Conocimientos avanzados de programación
 * - Memoria externa (tarjeta SD) para guardar imágenes
 * 
 * ========================================
 * VERSIÓN SIMPLIFICADA PARA APRENDIZAJE
 * ========================================
 * 
 * Este código muestra el concepto básico, pero para usarlo
 * realmente necesitarás:
 * 1. Librería específica del fabricante
 * 2. Módulo con cámara + AL422B ya integrados
 * 3. Módulo de tarjeta SD
 * 4. Arduino con mucha memoria (Mega recomendado)
 * 
 */

// ===== PINES TÍPICOS DEL AL422B =====
// Estos pueden variar según tu módulo específico

// Control de la cámara
#define PIN_VSYNC  2    // Señal de sincronización vertical
#define PIN_HREF   3    // Señal de referencia horizontal
#define PIN_PCLK   4    // Señal de reloj de píxeles

// Control del FIFO (AL422B)
#define PIN_WEN    5    // Write Enable (habilitar escritura)
#define PIN_RRST   6    // Read Reset (reiniciar lectura)
#define PIN_RCK    7    // Read Clock (reloj de lectura)
#define PIN_OE     8    // Output Enable (habilitar salida)

// Pines de datos (8 bits)
#define PIN_D0     22   // Bit 0
#define PIN_D1     24   // Bit 1
#define PIN_D2     26   // Bit 2
#define PIN_D3     28   // Bit 3
#define PIN_D4     30   // Bit 4
#define PIN_D5     32   // Bit 5
#define PIN_D6     34   // Bit 6
#define PIN_D7     36   // Bit 7

// LED indicador
#define PIN_LED    13

void setup() {
  Serial.begin(115200);  // Velocidad alta para transferir imágenes
  
  Serial.println("========================================");
  Serial.println("   MÓDULO DE CÁMARA AL422B - FIFO");
  Serial.println("========================================");
  Serial.println("");
  Serial.println("⚠️  AVISO IMPORTANTE:");
  Serial.println("Este es un ejemplo educativo simplificado.");
  Serial.println("El módulo AL422B requiere configuración avanzada.");
  Serial.println("");
  
  // Configurar LED
  pinMode(PIN_LED, OUTPUT);
  
  // ===== EXPLICACIÓN DEL PROCESO =====
  Serial.println("📚 CÓMO FUNCIONA UNA CÁMARA DIGITAL:");
  Serial.println("1. La cámara captura luz a través del lente");
  Serial.println("2. Convierte la luz en señales eléctricas");
  Serial.println("3. Organiza los píxeles en filas y columnas");
  Serial.println("4. Guarda todo en memoria (AL422B)");
  Serial.println("5. Arduino lee esa memoria");
  Serial.println("6. Se guarda en tarjeta SD o se envía a PC");
  Serial.println("");
  
  Serial.println("📊 DATOS TÍPICOS:");
  Serial.println("- Resolución: 640x480 píxeles (VGA)");
  Serial.println("- Cada píxel: 2 bytes (en color)");
  Serial.println("- Tamaño imagen: ~614 KB");
  Serial.println("- Tiempo captura: 1-2 segundos");
  Serial.println("");
  
  Serial.println("🔌 CONEXIONES NECESARIAS:");
  Serial.println("Este módulo necesita ~12 pines:");
  Serial.println("- 8 pines de datos (D0-D7)");
  Serial.println("- 4 pines de control");
  Serial.println("- Alimentación (VCC, GND)");
  Serial.println("");
  
  // Parpadear LED para indicar que está listo
  for (int i = 0; i < 5; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(200);
    digitalWrite(PIN_LED, LOW);
    delay(200);
  }
}

void loop() {
  Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
  Serial.println("📸 Simulación de captura de imagen");
  Serial.println("");
  
  // ===== PASO 1: PREPARAR CAPTURA =====
  Serial.println("Paso 1: Preparando cámara...");
  digitalWrite(PIN_LED, HIGH);
  delay(500);
  
  // ===== PASO 2: CAPTURAR IMAGEN =====
  Serial.println("Paso 2: Capturando imagen...");
  Serial.println("   (La cámara toma la foto)");
  delay(1000);
  
  // ===== PASO 3: GUARDAR EN FIFO =====
  Serial.println("Paso 3: Guardando en memoria FIFO...");
  Serial.println("   (La imagen se almacena en AL422B)");
  delay(500);
  
  // ===== PASO 4: LEER DATOS =====
  Serial.println("Paso 4: Leyendo datos de memoria...");
  Serial.println("   (Arduino lee píxel por píxel)");
  
  // Simular lectura de algunos píxeles
  Serial.println("");
  Serial.println("Ejemplo de datos de píxeles:");
  for (int i = 0; i < 10; i++) {
    // Generar valores aleatorios para simular
    int valorPixel = random(0, 256);
    Serial.print("Píxel ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(valorPixel);
    delay(100);
  }
  
  Serial.println("   ...");
  Serial.println("   (Continúa leyendo 640x480 = 307,200 píxeles)");
  delay(500);
  
  // ===== PASO 5: GUARDAR O ENVIAR =====
  Serial.println("Paso 5: Procesando imagen...");
  Serial.println("   Opciones:");
  Serial.println("   - Guardar en tarjeta SD");
  Serial.println("   - Enviar por Serial a PC");
  Serial.println("   - Detectar colores o formas");
  Serial.println("");
  
  digitalWrite(PIN_LED, LOW);
  
  Serial.println("✅ Proceso completado");
  Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
  Serial.println("");
  
  // ===== INFORMACIÓN EDUCATIVA =====
  Serial.println("💡 PARA USAR ESTE MÓDULO REALMENTE:");
  Serial.println("1. Consigue un módulo de cámara compatible con Arduino");
  Serial.println("   (ArduCam, OV7670, etc.)");
  Serial.println("2. Instala la librería del fabricante");
  Serial.println("3. Conecta un módulo de tarjeta SD");
  Serial.println("4. Usa un Arduino Mega (tiene más pines y memoria)");
  Serial.println("5. Busca ejemplos específicos para tu módulo");
  Serial.println("");
  
  Serial.println("🎯 ALTERNATIVAS MÁS FÁCILES:");
  Serial.println("- ESP32-CAM: Tiene cámara integrada y WiFi");
  Serial.println("- PixyCam: Cámara inteligente que detecta objetos");
  Serial.println("- OpenMV: Cámara programable con visión artificial");
  Serial.println("");
  
  Serial.println("⏸️  Esperando 10 segundos...");
  delay(10000);
}

/*
 * ========================================
 * CONCEPTOS IMPORTANTES:
 * ========================================
 * 
 * FIFO: First In, First Out
 * - Es como una fila: lo primero que entra es lo primero que sale
 * - Permite guardar mucha información temporalmente
 * - El AL422B puede guardar una imagen completa
 * 
 * PÍXEL: Picture Element
 * - Es el punto más pequeño de una imagen
 * - Cada píxel tiene información de color
 * - Miles de píxeles forman una imagen completa
 * 
 * RESOLUCIÓN:
 * - 640x480 = 640 píxeles de ancho, 480 de alto
 * - Más píxeles = más calidad pero más memoria
 * 
 * ========================================
 * ¿POR QUÉ ES TAN COMPLEJO?
 * ========================================
 * 
 * 1. MUCHA INFORMACIÓN:
 *    - Una imagen tiene cientos de miles de píxeles
 *    - Arduino Uno solo tiene 2KB de RAM
 *    - No puede guardar una imagen completa en memoria
 * 
 * 2. SINCRONIZACIÓN:
 *    - La cámara envía datos muy rápido
 *    - Hay que leer en el momento exacto
 *    - Requiere señales de sincronización precisas
 * 
 * 3. PROCESAMIENTO:
 *    - Convertir datos a formato de imagen
 *    - Guardar en tarjeta SD
 *    - Requiere conocimientos avanzados
 * 
 * ========================================
 * PROYECTO ALTERNATIVO PARA PRINCIPIANTES:
 * ========================================
 * 
 * Si quieres trabajar con cámaras, te recomendamos:
 * 
 * 1. ESP32-CAM (~$5-10):
 *    - Cámara ya integrada
 *    - Fácil de programar
 *    - Puede enviar fotos por WiFi
 *    - Muchos tutoriales disponibles
 * 
 * 2. Empezar con sensores más simples:
 *    - Completar los otros sensores de este taller
 *    - Aprender sobre imágenes en la computadora
 *    - Luego pasar a cámaras
 * 
 * ========================================
 */
