#!/usr/bin/env python3
import telepot
import time
import threading
import serial
import re

# === CONFIGURACIÓN ===

TELEGRAM_BOT_TOKEN = 'CAMBIAR ESTO POR EL QUE TE DIO BOTFATHER'
TELEGRAM_CHAT_ID = 'CAMBIAR ESTO POR TU ID'
SERIAL_PORT = '/dev/ttyACM0'
BAUD_RATE = 9600

# === VARIABLES GLOBALES ===

ultima_temperatura = None
ultima_humedad = None
datos_disponibles = False

# === FUNCIÓN PARA ENVIAR MENSAJES ===

def enviar_mensaje(texto=""):
    try:
        bot.sendMessage(TELEGRAM_CHAT_ID, texto)
        print(f"[TELEGRAM] {texto}")
    except Exception as e:
        print(f"[ERROR] No se pudo enviar mensaje: {e}")

# === MONITOREO DEL ARDUINO ===

def monitor_arduino():
    global ultima_temperatura, ultima_humedad, datos_disponibles

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

                # Buscar temperatura
                match_temp = re.search(r'Temperatura:\s*([\d.]+)', line)
                if match_temp:
                    ultima_temperatura = match_temp.group(1)

                # Buscar humedad
                match_hum = re.search(r'Humedad:\s*([\d.]+)', line)
                if match_hum:
                    ultima_humedad = match_hum.group(1)

                # Si ambos valores están disponibles, marcamos como válido
                if ultima_temperatura and ultima_humedad:
                    datos_disponibles = True

        except Exception as e:
            print(f"[ERROR] Fallo al leer puerto serie: {e}")
            break

# === MANEJADOR DE COMANDOS DE TELEGRAM ===

def handle(msg):
    global ultima_temperatura, ultima_humedad, datos_disponibles

    content_type, chat_type, chat_id = telepot.glance(msg)
    if content_type != 'text':
        return

    comando = msg['text'].strip().lower()

    if str(chat_id) != TELEGRAM_CHAT_ID:
        bot.sendMessage(chat_id, "⛔ Acceso denegado.")
        return

    if comando == '/temp':
        if datos_disponibles:
            respuesta = (
                f"📡 Última lectura:\n"
                f"🌡 Temperatura: {ultima_temperatura} °C\n"
                f"💧 Humedad: {ultima_humedad} %"
            )
        else:
            respuesta = "⏳ Aún no hay datos disponibles del sensor."
        enviar_mensaje(respuesta)

    elif comando == '/start' or comando == '/comandos':
        enviar_mensaje("📋 Comandos disponibles:\n/temp - Mostrar temperatura y humedad actual")

    else:
        enviar_mensaje("❓ Comando no reconocido. Usa /comandos para ver las opciones.")

# === INICIO DEL BOT ===

bot = telepot.Bot(TELEGRAM_BOT_TOKEN)
bot.message_loop(handle)

enviar_mensaje("🤖 Bot DHT11 iniciado. Monitoreando temperatura y humedad...")

arduino_thread = threading.Thread(target=monitor_arduino)
arduino_thread.daemon = True
arduino_thread.start()

print("[INFO] Bot funcionando y escuchando comandos...")

while True:
    time.sleep(10)
