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

// List of all locations
const char *locations[] = {
  "Akurdi Railway St",
  "Sambhaji Chowk",
  "Bijalinagar Corn",
  "Chaphekar Chowk",
  "Chinchwad Gaon",
  "M.M.School BRTS",
  "Dhangarbaba Mand",
  "Rahatani Phata",
  "Nakhate Wasti",
  "Rahatani Gaon",
  "Pimple Saudagar",
  "Aundh Gaon",
  "Pune Vidyapeeth",
  "Pune Central Ma",
  "Shivajinagar",
  "C.O.E.P.Hostel ",
  "Manapa Bhavan"
};

int selectedPickupIndex = -1;
int selectedDropIndex = -1;
float fare = -1.0;

int selectedOption = 1; // Initial menu option

void displayMenu(int option);
int selectLocation(const char *title, int &selectedIndex);
float calculateFare(int pickupIndex, int dropIndex);
void handleOption(int option);
void handlePaymentOption();
void returnToMainMenu();

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_PAGEADDR, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonEnter, INPUT_PULLUP);
  pinMode(buttonExit, INPUT_PULLUP);

  delay(2000);
  display.clearDisplay();
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
    handleOption(selectedOption);
  }

  // Check if in Payment option and Exit button is pressed
  if (selectedOption == 3 && digitalRead(buttonExit) == LOW) {
    delay(200); // debounce
    returnToMainMenu();
  }
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

int selectLocation(const char *title, int &selectedIndex) {
  selectedIndex = 0;

  while (true) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(title);

    for (int i = selectedIndex; i < min(selectedIndex + SCREEN_HEIGHT / 8, sizeof(locations) / sizeof(locations[0])); ++i) {
      // Display numbers along with locations
      display.print(i + 1);
      display.print(". ");

      // Highlight the selected location
      if (i == selectedIndex) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.print(">");
      } else {
        display.setTextColor(SSD1306_WHITE);
        display.print(" ");
      }

      display.println(locations[i]);
    }

    display.display();

    if (digitalRead(buttonUp) == LOW) {
      delay(200); // debounce
      selectedIndex = (selectedIndex > 0) ? (selectedIndex - 1) : 0;
    }

    if (digitalRead(buttonDown) == LOW) {
      delay(200); // debounce
      selectedIndex = (selectedIndex < sizeof(locations) / sizeof(locations[0]) - 1) ? (selectedIndex + 1) : selectedIndex;
    }

    if (digitalRead(buttonEnter) == LOW) {
      delay(200); // debounce
      // User has selected a location, exit the function
      display.clearDisplay();
      display.display();
      Serial.print(F("Selected Location Index: "));
      Serial.println(selectedIndex);
      return selectedIndex;
    }

    if (digitalRead(buttonExit) == LOW) {
      delay(200); // debounce
      return -1; // Indicate exit
    }
  }
}

float calculateFare(int pickupIndex, int dropIndex) {
  const float farePerStop = 10.0;
  const float baseFare = 5.0;

  float fare = abs(dropIndex - pickupIndex) * farePerStop + baseFare;

  return fare;
}

void handleOption(int option) {
  if (option == 1) {
    // Select Pickup
    selectedPickupIndex = selectLocation("Select Pickup", selectedPickupIndex);
  } else if (option == 2) {
    // Select Drop
    selectedDropIndex = selectLocation("Select Drop", selectedDropIndex);
  } else if (option == 3) {
    handlePaymentOption();
  } else if (option == 4) {
    // Exit option selected
    Serial.println(F("Exit option selected"));
    // Implement exit logic here
    returnToMainMenu();
  }
}


void handlePaymentOption() {
  int exitStatus = -1;

  // Payment option selected
  Serial.println(F("Payment option selected"));

  // Check if both pickup and drop locations are selected
  if (selectedPickupIndex != -1 && selectedDropIndex != -1) {
    fare = calculateFare(selectedPickupIndex, selectedDropIndex);

    // Display pickup, drop, and fare information
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(F("Pickup: "));
    display.println(locations[selectedPickupIndex]);
    display.print(F("Drop: "));
    display.println(locations[selectedDropIndex]);

    if (fare >= 0) {
      display.print(F("Fare: $"));
      display.println(fare, 2); // Display fare with 2 decimal places
    } else {
      display.println(F("Invalid locations"));
    }

    display.display();

    // Dynamic delay allowing responsiveness
    unsigned long startTime = millis();
    while ((millis() - startTime) < 5000) {
      if (digitalRead(buttonExit) == LOW) {
        delay(200); // debounce
        exitStatus = 1; // Indicate exit
        break;
      }
    }
  } else {
    Serial.println(F("Please select both pickup and drop locations."));
  }

  if (exitStatus == 1) {
    returnToMainMenu();
  }
}


void returnToMainMenu() {
  selectedOption = 1; // Return to the main menu
  selectedPickupIndex = -1;
  selectedDropIndex = -1;
  fare = -1.0;
}
