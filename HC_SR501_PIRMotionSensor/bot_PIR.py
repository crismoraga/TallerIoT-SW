#!/usr/bin/env python3
import telepot
import time
import threading
import serial

# === CONFIGURACIÓN ===

TELEGRAM_BOT_TOKEN = '8335197889:AAGEXznGGqJoYfIzihA8_z76TZDhyQnxNf4'
TELEGRAM_CHAT_ID = '1795996150'
SERIAL_PORT = '/dev/ttyACM0'  # Asegúrate que sea el puerto correcto
BAUD_RATE = 9600

# === FUNCIÓN PARA ENVIAR MENSAJES ===

def enviar_mensaje(texto=""):
    try:
        bot.sendMessage(TELEGRAM_CHAT_ID, texto)
        print(f"[TELEGRAM] {texto}")
    except Exception as e:
        print(f"[ERROR] No se pudo enviar mensaje: {e}")

# === MONITOREO DEL ARDUINO ===

def monitor_arduino():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"[INFO] Conectado a {SERIAL_PORT} a {BAUD_RATE} baud")
        time.sleep(2)  # Dar tiempo a que Arduino reinicie
    except serial.SerialException as e:
        print(f"[ERROR] No se pudo abrir el puerto serie: {e}")
        return

    while True:
        try:
            if ser.in_waiting > 0:
                line = ser.readline().decode(errors='ignore').strip()
                print(f"[ARDUINO] {line}")

                if "¡MOVIMIENTO DETECTADO!" in line:
                    enviar_mensaje("🚨 ¡Movimiento detectado por el sensor PIR!")
        except Exception as e:
            print(f"[ERROR] Fallo al leer puerto serie: {e}")
            break

# === INICIO DEL BOT ===

bot = telepot.Bot(TELEGRAM_BOT_TOKEN)

enviar_mensaje("🤖 Bot PIR iniciado. Monitoreando sensor de movimiento...")

arduino_thread = threading.Thread(target=monitor_arduino)
arduino_thread.daemon = True
arduino_thread.start()

print("[INFO] Monitoreando sensor PIR...")
while True:
    time.sleep(10)
