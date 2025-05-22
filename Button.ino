#include <BleKeyboard.h>

BleKeyboard bleKeyboard("TecladoBLE", "Fabricante", 100);

const int BUTTON_PIN = 32;
const int LED_PIN = 2;

// Mapeo de pulsos a teclas
const char TECLAS[] = {'A', 'B', 'C', 'D', 'X'}; // 1-5 pulsos (X es placeholder)

struct TeclaEstado {
  char tecla;
  bool presionada;
  unsigned long ultimoCambio;
};
TeclaEstado estadosTeclas[4] = {
  {'A', false, 0},
  {'B', false, 0},
  {'C', false, 0},
  {'D', false, 0}
};

volatile int pulsos = 0;
unsigned long ultimoPulso = 0;

// Variables para LED y debounce
unsigned long ledEncendido = 0;
bool estadoLed = false;
int estadoBoton = HIGH;
int ultimoEstadoBoton = HIGH;
unsigned long ultimoDebounce = 0;
const int DEBOUNCE_MS = 50;

void toggleTecla(int indice) {
  TeclaEstado& tecla = estadosTeclas[indice];
  tecla.presionada = !tecla.presionada;
  tecla.ultimoCambio = millis();
  
  if(tecla.presionada) {
    bleKeyboard.press(tecla.tecla);
  } else {
    bleKeyboard.release(tecla.tecla);
  }
}

void liberarTodas() {
  for(int i = 0; i < 4; i++) {
    if(estadosTeclas[i].presionada) {
      estadosTeclas[i].presionada = false;
      bleKeyboard.release(estadosTeclas[i].tecla);
    }
  }
}

void manejarPulsos() {
  if(pulsos >= 1 && pulsos <= 4) {
    int indice = pulsos - 1;
    toggleTecla(indice);
  }
  else if(pulsos == 5) {
    liberarTodas();
  }
  
  // Feedback LED
  digitalWrite(LED_PIN, HIGH);
  ledEncendido = millis();
  estadoLed = true;
  
  pulsos = 0;
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  bleKeyboard.begin();
}

void loop() {
  unsigned long ahora = millis();
  int lectura = digitalRead(BUTTON_PIN);

  // Actualizar límite de pulsos a 5
  if (lectura != ultimoEstadoBoton) ultimoDebounce = ahora;
  if ((ahora - ultimoDebounce) > DEBOUNCE_MS && lectura != estadoBoton) {
    estadoBoton = lectura;
    if (estadoBoton == LOW) {
      pulsos = min(pulsos + 1, 5);  // Permitir hasta 5 pulsos
      ultimoPulso = ahora;
    }
  }
  ultimoEstadoBoton = lectura;

  // Manejar pulsos después de 500ms
  if (pulsos > 0 && (ahora - ultimoPulso) >= 500) {
    manejarPulsos();
  }

  // Apagar LED
  if (estadoLed && (ahora - ledEncendido) >= 100) {
    digitalWrite(LED_PIN, LOW);
    estadoLed = false;
  }
}