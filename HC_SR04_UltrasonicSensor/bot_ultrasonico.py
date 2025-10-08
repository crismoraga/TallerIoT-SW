#!/usr/bin/env python3
import telepot
import time
import threading
import serial
import re
from datetime import datetime

# === CONFIGURACIÓN ===

TELEGRAM_BOT_TOKEN = '8335197889:AAGEXznGGqJoYfIzihA8_z76TZDhyQnxNf4'
TELEGRAM_CHAT_ID = '1795996150'
SERIAL_PORT = '/dev/ttyACM0'  # Ajusta si tu puerto es diferente
BAUD_RATE = 9600
DISTANCIA_UMBRAL = 5.0  # cm

# === VARIABLES GLOBALES ===

ultima_distancia = None
datos_disponibles = False
alertas_enviadas = 0
timestamps_alertas = []

# === FUNCIÓN PARA ENVIAR MENSAJES ===

def enviar_mensaje(texto=""):
    try:
        bot.sendMessage(TELEGRAM_CHAT_ID, texto)
        print(f"[TELEGRAM] {texto}")
    except Exception as e:
        print(f"[ERROR] No se pudo enviar mensaje: {e}")

# === MONITOREO DEL ARDUINO ===

def monitor_arduino():
    global ultima_distancia, datos_disponibles, alertas_enviadas, timestamps_alertas

    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"[INFO] Conectado a {SERIAL_PORT} a {BAUD_RATE} baud")
        time.sleep(2)
    except serial.SerialException as e:
        print(f"[ERROR] No se pudo abrir el puerto serie: {e}")
        return

    while True:
        try:
            if ser.in_waiting > 0:
                line = ser.readline().decode(errors='ignore').strip()
                print(f"[ARDUINO] {line}")

                # Buscar patrón: "Distancia: XX.XX cm"
                match = re.search(r'Distancia:\s*([\d.]+)', line)
                if match:
                    distancia_actual = float(match.group(1))
                    ultima_distancia = distancia_actual
                    datos_disponibles = True

                    # Chequear si se sobrepasó la distancia mínima
                    if distancia_actual <= DISTANCIA_UMBRAL:
                        # Para no saturar con alertas, enviamos solo si es la primera vez o si la última alerta fue hace >10 segundos
                        ahora = time.time()
                        if (not timestamps_alertas) or (ahora - timestamps_alertas[-1].timestamp() > 1):
                            alertas_enviadas += 1
                            timestamps_alertas.append(datetime.now())
                            enviar_mensaje(f"🚨 ALERTA: Objeto detectado muy cerca! Distancia: {distancia_actual} cm")

        except Exception as e:
            print(f"[ERROR] Fallo al leer puerto serie: {e}")
            break

# === MANEJADOR DE COMANDOS DE TELEGRAM ===

def handle(msg):
    global ultima_distancia, datos_disponibles, alertas_enviadas, timestamps_alertas

    content_type, chat_type, chat_id = telepot.glance(msg)
    if content_type != 'text':
        return

    comando = msg['text'].strip().lower()

    if str(chat_id) != TELEGRAM_CHAT_ID:
        bot.sendMessage(chat_id, "⛔ Acceso denegado.")
        return

    if comando == '/distancia':
        if datos_disponibles:
            respuesta = f"📏 Última distancia medida: {ultima_distancia} cm"
        else:
            respuesta = "⏳ Aún no hay datos disponibles del sensor."
        enviar_mensaje(respuesta)

    elif comando == '/metricas':
        if alertas_enviadas == 0:
            respuesta = "ℹ️ No se ha detectado que la distancia haya sido menor o igual a 5 cm aún."
        else:
            lista_tiempos = "\n".join(ts.strftime("%Y-%m-%d %H:%M:%S") for ts in timestamps_alertas)
            respuesta = (
                f"📊 Métricas:\n"
                f"- Cantidad de alertas de proximidad: {alertas_enviadas}\n"
                f"- Tiempos de alerta:\n{lista_tiempos}"
            )
        enviar_mensaje(respuesta)

    elif comando == '/start' or comando == '/comandos':
        enviar_mensaje(
            "📋 Comandos disponibles:\n"
            "/distancia - Mostrar última distancia detectada\n"
            "/metricas - Ver cantidad y tiempos de alertas por proximidad"
        )

    else:
        enviar_mensaje("❓ Comando no reconocido. Usa /comandos para ver las opciones.")

# === INICIO DEL BOT ===

bot = telepot.Bot(TELEGRAM_BOT_TOKEN)
bot.message_loop(handle)

enviar_mensaje("🤖 Bot HC-SR04 iniciado. Monitoreando distancia...")

arduino_thread = threading.Thread(target=monitor_arduino)
arduino_thread.daemon = True
arduino_thread.start()

print("[INFO] Bot funcionando y escuchando comandos...")

while True:
    time.sleep(10)
