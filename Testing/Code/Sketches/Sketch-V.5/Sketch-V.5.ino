#include <Arduino.h>

// Definitionen für die 5 Mute-Buttons
#define BUTTON_A0 0
#define BUTTON_A1 1
#define BUTTON_A2 2
#define BUTTON_A3 3
#define BUTTON_A4 4

// Definitionen für die 5 LEDs
#define LED_PIN_A0 5
#define LED_PIN_A1 6
#define LED_PIN_A2 7
#define LED_PIN_A3 8
#define LED_PIN_A4 9

// Definitionen für die 12 Potentiometer
const int potPins[12] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};

// Arrays für die Mute-Buttons, LEDs und Mute-Zustände für die ersten 5 Potentiometer
const byte buttonPins[5] = {BUTTON_A0, BUTTON_A1, BUTTON_A2, BUTTON_A3, BUTTON_A4};
const byte ledPins[5] = {LED_PIN_A0, LED_PIN_A1, LED_PIN_A2, LED_PIN_A3, LED_PIN_A4};
bool muteStates[5] = {false};

// Array für die Potentiometer-Werte
int potValues[12] = {0};

class Button {
   private:
    byte pin;
    bool oldState;

   public:
    Button(byte pin) : pin(pin), oldState(HIGH) {
        pinMode(pin, INPUT_PULLUP);
    }

    bool isPressed() {
        bool newState = digitalRead(pin);
        bool pressed = (oldState == HIGH && newState == LOW);
        oldState = newState;
        return pressed;
    }
};

// Initialisierung der Buttons
Button buttons[5] = {Button(BUTTON_A0), Button(BUTTON_A1), Button(BUTTON_A2), Button(BUTTON_A3), Button(BUTTON_A4)};

void sendSliderValues() {
    String builtString = "";
    for (int i = 0; i < 12; i++) {
        builtString += String(potValues[i]);
        if (i < 11) {
            builtString += "|";
        }
    }
    Serial.println(builtString);
}

void updateSliderValues() {
    // Aktualisiere die Werte der ersten 5 Potentiometer (mit Mute)
    for (int i = 0; i < 5; i++) {
        potValues[i] = muteStates[i] ? 0 : analogRead(potPins[i]);
    }
    // Aktualisiere die Werte der restlichen 7 Potentiometer (ohne Mute)
    for (int i = 5; i < 12; i++) {
        potValues[i] = analogRead(potPins[i]);
    }
}

void toggleMute(int index) {
    muteStates[index] = !muteStates[index];
    digitalWrite(ledPins[index], muteStates[index] ? HIGH : LOW);
}

void checkButtons() {
    for (int i = 0; i < 5; i++) {
        if (buttons[i].isPressed()) {
            toggleMute(i);
        }
    }
}

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 5; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
}

void loop() {
    checkButtons();
    updateSliderValues();
    sendSliderValues();
    delay(10);
}

