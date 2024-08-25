// Define row and column pins
const int ROWS = 4;
const int COLS = 4;
const int rowPins[ROWS] = {6, 7, 8, 9}; // Connect to the row pinouts of the matrix
const int colPins[COLS] = {2, 3, 4, 5}; // Connect to the column pinouts of the matrix

// Define the characters on the buttons of the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

void setup() {
  Serial.begin(9600);

  // Initialize row pins as outputs
  for (int row = 0; row < ROWS; row++) {
    pinMode(rowPins[row], OUTPUT);
    digitalWrite(rowPins[row], HIGH); // Set rows to HIGH initially
  }

  // Initialize column pins as inputs
  for (int col = 0; col < COLS; col++) {
    pinMode(colPins[col], INPUT_PULLUP); // Set columns to input with pull-up
  }
}

void loop() {
  for (int row = 0; row < ROWS; row++) {
    // Set current row to LOW
    digitalWrite(rowPins[row], LOW);

    // Check each column for a button press
    for (int col = 0; col < COLS; col++) {
      if (digitalRead(colPins[col]) == LOW) { // Button press detected
        Serial.print("Button pressed: ");
        Serial.println(keys[row][col]);
        delay(250); // Debounce delay
      }
    }

    // Set the row back to HIGH
    digitalWrite(rowPins[row], HIGH);
  }
}
