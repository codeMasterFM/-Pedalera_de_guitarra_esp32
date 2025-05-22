# 🎸 Pedalera Digital Casera con ESP32 + Bluetooth

Este proyecto convierte un ESP32 en una pedalera MIDI/HID Bluetooth que emula un teclado para controlar efectos o loops en tu DAW, software de guitarra, o presentaciones. Perfecto para guitarristas que buscan una solución simple, inalámbrica y casera.

## 🚀 ¿Cómo funciona?

- El ESP32 actúa como un teclado Bluetooth (BLE).
- Utiliza un solo botón conectado al pin **GPIO 32** con `INPUT_PULLUP`.
- Detecta la cantidad de toques (pulsos) en el botón para enviar teclas específicas:

| Toques | Acción       | Tecla Enviada |
|--------|--------------|----------------|
| 1      | Toggle A     | A              |
| 2      | Toggle B     | B              |
| 3      | Toggle C     | C              |
| 4      | Toggle D     | D              |
| 5      | **Reset**    | Libera todas   |

> Puedes acumular combinaciones (ej. A y B activas al mismo tiempo). Presionar 5 veces limpia todo.

## 🛠️ Requisitos

- ESP32 con Bluetooth BLE
- Arduino IDE con soporte ESP32
- Biblioteca: [`BleKeyboard`](https://github.com/T-vK/ESP32-BLE-Keyboard)

## 💡 Características adicionales

- **Debounce inteligente**: evita múltiples registros por un solo toque.
- **LED de feedback**: se enciende brevemente para confirmar el reconocimiento del toque.
- **Modo acumulativo**: puedes mantener activas múltiples teclas simultáneamente.

## 📦 Instalación y carga

1. Instala la librería `ESP32 BLE Keyboard` desde el Gestor de Bibliotecas del Arduino IDE.
2. Conecta tu ESP32.
3. Carga el código `pedalera_ble.ino`.
4. Empareja el ESP32 con tu PC como dispositivo Bluetooth (aparecerá como `TecladoBLE`).
5. ¡Listo para usar!

## 📜 Licencia

MIT © Franklyn Martínez  
Contribuciones y mejoras son bienvenidas.
