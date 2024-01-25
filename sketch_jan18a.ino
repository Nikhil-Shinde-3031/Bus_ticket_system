#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonUp = A0;
const int buttonDown = A1;
const int buttonEnter = A2;
const int buttonExit = A3;

int selectedOption = 1; // Initial menu option

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_PAGEADDR, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonEnter, INPUT_PULLUP);
  pinMode(buttonExit, INPUT_PULLUP);

  delay(2000);
  display.clearDisplay();
  display.display();
}

void displayMenu(int option) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Display menu options
  display.print(F("1. Select Pickup.\n"));
  display.print(F("2. Select Drop.\n"));
  display.print(F("3. Payment.\n"));
  display.print(F("4. Exit.\n"));

  // Highlight the selected option
  display.setCursor(0, (option - 1) * 8);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.print(option);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  displayMenu(selectedOption);

  // Check button presses
  if (digitalRead(buttonUp) == LOW) {
    delay(200); // debounce
    selectedOption = (selectedOption > 1) ? (selectedOption - 1) : 4;
  }

  if (digitalRead(buttonDown) == LOW) {
    delay(200); // debounce
    selectedOption = (selectedOption < 4) ? (selectedOption + 1) : 1;
  }

  if (digitalRead(buttonEnter) == LOW) {
    delay(200); // debounce
    executeOption(selectedOption);
  }

  if (digitalRead(buttonExit) == LOW) {
    delay(200); // debounce
    // Handle exit or go back
  }
}

void executeOption(int option) {
  // Implement logic for each menu option
  switch (option) {
    case 1:
      displayDestinations();
      break;
    case 2:
      // Execute code for option 2
      break;
    case 3:
      // Execute code for option 3
      break;
    case 4:
      // Execute code for option 4
      break;
  }
}
void displayDestinations() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Display destinations
  const char* destinations[] = {
    "Akurdi Railway Station",
    "Akurdi Police Station",
    "Sambhaji Chowk",
    "Bijalinagar Corner",
    // ... add more destinations as needed ...
    "Chhatrapati Shivaji Maharaj Putala Ma.Na.Pa.",
    "Manapa Bhavan - Mangala Talkies"
  };

  for (int i = 0; i < sizeof(destinations) / sizeof(destinations[0]); ++i) {
    display.println(destinations[i]);
  }

  display.display();
  delay(5000); // Display destinations for 5 seconds (adjust as needed)
  display.clearDisplay();
  display.display();
}
