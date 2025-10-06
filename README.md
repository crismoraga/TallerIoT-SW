# 🎓 Taller de Sensores Arduino para Niños

Bienvenidos al taller de IoT y Sensores. Aquí aprenderás a usar diferentes sensores con Arduino de forma divertida y educativa.

---

## 📦 Sensores Incluidos en el Taller

### 1. 📏 HC-SR04 - Sensor Ultrasónico

**Archivo:** `HC_SR04_UltrasonicSensor.ino`

**¿Qué hace?**
- Mide distancias como los murciélagos (usando sonido)
- Detecta objetos de 2 cm hasta 4 metros

**Conexiones:**
```
VCC  → 5V
GND  → GND
TRIG → Pin 9
ECHO → Pin 10
```

**Diagrama de Conexión:**

![Diagrama HC-SR04](./diagrama_sensor_infrarrojo.png)

**Experimentos sugeridos:**
- 🚗 Sensor de estacionamiento
- 🤖 Robot que evita obstáculos
- 📊 Medidor de altura

---

### 2. 🌧️ MH-Sensor-Series - Sensor de Lluvia

**Archivo:** `MH_SensorSeries_RainSensor.ino`

**¿Qué hace?**
- Detecta cuando cae agua o lluvia
- Mide la intensidad (poca, media, mucha lluvia)

**Conexiones:**
```
VCC → 5V
GND → GND
AO  → Pin A0
DO  → Pin 2
```

**Diagrama de Conexión:**

![Diagrama MH-Sensor](./diaagrama_sensor_MH-Sensor-Series.png)

**Experimentos sugeridos:**
- ☔ Alarma de lluvia
- 🪟 Cierre automático de ventanas
- 🌱 Sistema de riego inteligente

---

### 3. 💧 Sensor de Nivel de Agua

**Archivo:** `WaterLevelSensor.ino`

**¿Qué hace?**
- Mide qué tan lleno está un tanque
- Detecta nivel bajo, medio y alto

**Conexiones:**
```
+ (VCC) → 5V
- (GND) → GND
S       → Pin A1
```

**Diagrama de Conexión:**

![Diagrama Nivel Agua](./diagrama_sensor_movimiento.png)

**Experimentos sugeridos:**
- 🐠 Monitor de acuario
- 🚰 Alarma de tanque vacío
- 🌿 Sistema de riego automático

---

### 4. 🌡️ DHT11 - Sensor de Temperatura y Humedad

**Archivo:** `DHT11_TemperatureHumidity.ino`

**¿Qué hace?**
- Mide temperatura del aire (°C)
- Mide humedad del aire (%)

**Conexiones:**
```
Pin 1 (VCC)  → 5V
Pin 2 (DATA) → Pin 7
Pin 3 (NC)   → No conectar
Pin 4 (GND)  → GND
```

**Diagrama de Conexión:**

![Diagrama DHT11](./diagrama_sensor_humedad.png)

**⚠️ IMPORTANTE:** Necesitas instalar librerías:
1. Abre Arduino IDE
2. Ve a: Herramientas → Administrar Bibliotecas
3. Busca e instala:
   - "DHT sensor library" de Adafruit
   - "Adafruit Unified Sensor"

**Experimentos sugeridos:**
- 🏠 Estación meteorológica
- ❄️ Control de aire acondicionado
- 🌡️ Termómetro digital

---

### 5. 👋 HC-SR501 - Sensor de Movimiento PIR

**Archivo:** `HC_SR501_PIRMotionSensor.ino`

**¿Qué hace?**
- Detecta personas o animales en movimiento
- "Ve" el calor que emiten los cuerpos

**Conexiones:**
```
VCC → 5V
OUT → Pin 8
GND → GND
```

**Diagrama de Conexión:**

![Diagrama PIR](./diagrama_sensor_movimiento.png)

**⚠️ IMPORTANTE:**
- Necesita calibrarse 30-60 segundos sin movimiento al iniciar
- Tiene 2 potenciómetros para ajustar:
  - **Sensibilidad:** Distancia de detección (3-7 metros)
  - **Tiempo:** Duración de la señal (5 seg - 5 min)

**Experimentos sugeridos:**
- 💡 Luz automática
- 🚨 Alarma de seguridad
- 🔢 Contador de personas

---

### 6. 📸 AL422B - Módulo de Cámara (AVANZADO)

**Archivo:** `AL422B_CameraModule.ino`

**¿Qué hace?**
- Captura imágenes
- Guarda en memoria temporal

**⚠️ ADVERTENCIA:** Este sensor es MUY COMPLEJO
- Requiere 12+ pines
- Necesita Arduino Mega (no Uno)
- Requiere tarjeta SD
- Necesita librerías especiales

**Diagrama de Conexión (ejemplo):**

![Diagrama Cámara](./diagrama_sensor_infrarrojo.png)

**Recomendación para principiantes:**
- Empieza con los otros sensores primero
- Considera usar ESP32-CAM como alternativa más fácil
- Este archivo es principalmente educativo

---

## 🚀 Cómo Empezar

### Paso 1: Instalar Arduino IDE

1. Descarga Arduino IDE desde [arduino.cc](https://www.arduino.cc/en/software)
2. Instálalo en tu computadora
3. Abre el programa

### Paso 2: Conectar Arduino

1. Conecta tu Arduino a la computadora con cable USB
2. En Arduino IDE, ve a: Herramientas → Placa → Arduino Uno (o tu modelo)
3. Ve a: Herramientas → Puerto → Selecciona el puerto COM de tu Arduino

### Paso 3: Abrir un Archivo

1. Abre uno de los archivos `.ino` de este taller
2. Lee las explicaciones en los comentarios
3. Conecta el sensor según las instrucciones

### Paso 4: Subir el Código

1. Haz clic en el botón "Verificar" (✓) para revisar errores
2. Haz clic en el botón "Subir" (→) para cargar a Arduino
3. Abre el Monitor Serial: Herramientas → Monitor Serial
4. Configura velocidad a 9600 baudios (abajo a la derecha)

### Paso 5: Experimenta

- Lee los valores que aparecen
- Prueba los experimentos sugeridos en los comentarios
- Modifica los números y ve qué pasa
- ¡Diviértete aprendiendo!

---

## 💡 Consejos para el Taller

### Para Profesores

✅ Empezar con sensores simples (HC-SR04, HC-SR501)  
✅ Dejar que los niños experimenten modificando valores  
✅ Hacer que comparen resultados entre equipos  
✅ Combinar sensores para proyectos más complejos  
✅ El sensor de cámara es solo para mostrar conceptos avanzados

### Para Estudiantes

✅ Lee todos los comentarios en el código  
✅ No tengas miedo de experimentar  
✅ Si algo no funciona, revisa las conexiones  
✅ Anota qué pasa cuando cambias valores  
✅ Trabaja en equipo y comparte descubrimientos

### Solución de Problemas

❌ **No aparecen datos:** Revisa las conexiones  
❌ **Error al compilar:** Verifica que instalaste las librerías (DHT11)  
❌ **Valores raros:** Reinicia Arduino y recarga el código  
❌ **Puerto no disponible:** Desconecta y vuelve a conectar el USB

---

## 🎯 Proyectos Finales Sugeridos

Combina varios sensores para crear:

1. **🏠 Casa Inteligente**
   - Luz automática con HC-SR501
   - Control de temperatura con DHT11
   - Alarma de lluvia con sensor de lluvia

2. **🤖 Robot Autónomo**
   - Evasión de obstáculos con HC-SR04
   - Detección de movimiento con HC-SR501

3. **🌱 Sistema de Riego Inteligente**
   - Sensor de nivel de agua
   - Sensor de lluvia
   - Sensor de temperatura

4. **📊 Estación Meteorológica**
   - DHT11 para temperatura y humedad
   - Sensor de lluvia
   - Registrar datos cada hora

---

## 📚 Recursos Adicionales

- [Arduino.cc - Tutoriales oficiales](https://www.arduino.cc/en/Tutorial/HomePage)
- [Foros de Arduino en español](https://forum.arduino.cc/c/international/spanish/12)
- [Tinkercad - Simulador online](https://www.tinkercad.com/)

---

## ⚠️ Seguridad

- Nunca conectes directamente a 220V (corriente de casa)
- Usa solo 5V de Arduino
- No mojes la placa Arduino ni las conexiones
- Pide ayuda a un adulto si no estás seguro
- Desconecta el Arduino antes de cambiar conexiones

---

## 📝 Lista de Verificación

Antes de cada sesión, asegúrate de tener:

- [ ] Arduino conectado a la computadora
- [ ] Cable USB funcionando
- [ ] Arduino IDE instalado
- [ ] Librerías instaladas (si usas DHT11)
- [ ] Sensor correctamente conectado
- [ ] Monitor Serial abierto
- [ ] ¡Muchas ganas de aprender!

---

## 🎉 Diviértete

Recuerda: **No hay preguntas tontas, solo curiosidad por aprender.**

La programación y electrónica se aprenden **haciendo y experimentando**.

**¿Cometiste un error?** ¡Perfecto! Los errores son la mejor forma de aprender.

---

**Creado para el Taller de IoT y Software** 🚀  
*Versión educativa para niños y principiantes*
