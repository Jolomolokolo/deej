#include <Arduino.h>
#define BUTTEN_A0 2


#define LED_PIN_A0 9


int A0_read;


const int NUM_SLIDERS = 1;
const int analogInputs[NUM_SLIDERS] = {A0};
int analogSliderValues[NUM_SLIDERS];
const byte mute_led_A[NUM_SLIDERS] = {LED_PIN_A0};
const byte button_A[NUM_SLIDERS] = {BUTTEN_A0};
bool mute_A[NUM_SLIDERS] = {false};

bool update = true;

class Button {
   private:
    byte PIN_BUTTON;
    bool oldstate;

   public:
    Button(byte pin_button_import) { PIN_BUTTON = pin_button_import; }

    bool press() {
        bool newstate = digitalRead(PIN_BUTTON);
        bool down = (oldstate == LOW && newstate == HIGH);
        oldstate = newstate == HIGH;
        return down;
    }
};
Button button_A0 = Button(BUTTEN_A0);


void sendSliderValues() {
    String builtString = String("");

    for (int i = 0; i < NUM_SLIDERS; i++) {
        builtString += String((int)analogSliderValues[i]);

        if (i < NUM_SLIDERS - 1) {
            builtString += String("|");
        }
    }

    Serial.println(builtString);
}
void updateSliderValues() {
    if (mute_A[0] == false) {
        analogSliderValues[0] = analogRead(analogInputs[0]);
    } else {
        analogSliderValues[0] = 0;
  }
}
void debugPrintEXE() {
    for (int i = 0; i < NUM_SLIDERS; i++) {
        String printedString = String(i + 1) + String(": ") +
                               String(analogSliderValues[i]) + String(" mV");
        Serial.write(printedString.c_str());

        if (i < NUM_SLIDERS - 1) {
            Serial.write(" | ");
        } else {
            Serial.write("\n");
        }
    }
}

void mute_on_of(byte i) {
    if (mute_A[i] == false) {
        mute_A[i] = true;
        digitalWrite(mute_led_A[i], HIGH);
        Serial.println("true");
    } else {
        mute_A[i] = false;
        digitalWrite(mute_led_A[i], LOW);
        Serial.println("false");
    }
}

void mute_button_X() {
    if (button_A0.press()) {
        mute_on_of(0);
    }

}

void setup() {
    for (int i = 0; i < NUM_SLIDERS; i++) {
        pinMode(analogInputs[i], INPUT);
    }

    Serial.begin(9600);
    pinMode(BUTTEN_A0, INPUT_PULLUP);


    for (int i = 0; i < NUM_SLIDERS; i++) {
        pinMode(mute_led_A[i], OUTPUT);
        digitalWrite(mute_led_A[i], LOW);
    }
}

void loop() {
 mute_button_X();
 updateSliderValues();
 sendSliderValues();
 debugPrintEXE();
 delay(10);
}