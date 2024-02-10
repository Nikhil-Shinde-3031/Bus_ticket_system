const int entrySensorPin = 2;
const int exitSensorPin = 3;
const int entryLedPin = 5;
const int exitLedPin = 6;

int entryCount = 0;
int exitCount = 0;
int totalPersons = 0;

void setup() {
  Serial.begin(9600);

  pinMode(entrySensorPin, INPUT);
  pinMode(exitSensorPin, INPUT);
  pinMode(entryLedPin, OUTPUT);
  pinMode(exitLedPin, OUTPUT);
}

void loop() {
  // Check if a person is entering
  if (digitalRead(entrySensorPin) == HIGH) {
    delay(1000);  // Debounce delay (adjust as needed)
    if (digitalRead(entrySensorPin) == HIGH) {
      entryCount++;
      totalPersons++;
      updateDatabase("enter", entryCount);
      Serial.println("Enter," + String(entryCount));
      indicateEntry();
      printTotalPersons();
    }
  }

  // Check if a person is exiting
  if (digitalRead(exitSensorPin) == HIGH && exitCount < entryCount) {
    delay(1000);  // Debounce delay (adjust as needed)
    if (digitalRead(exitSensorPin) == HIGH) {
      exitCount++;
      totalPersons--;
      updateDatabase("exit", exitCount);
      Serial.println("Exit," + String(exitCount));
      indicateExit();
      printTotalPersons();
    }
  }

  // Add additional logic or functionality as needed

  delay(500);  // Adjust the delay based on your requirements
}

void updateDatabase(String direction, int count) {
  // Implement the code to update the local database (e.g., text file)
  // You can use the SD card library or other storage options depending on your setup
  // Include timestamp, direction, and count in the database entry
  // Example: timestamp,enter,1 or timestamp,exit,2

  // For this example, we will send the data to the computer via serial
  Serial.print("Timestamp,");
  Serial.print(direction);
  Serial.print(",");
  Serial.println(count);
}

void indicateEntry() {
  digitalWrite(entryLedPin, HIGH);  // Turn on green LED
  delay(1000);  // Indication duration (adjust as needed)
  digitalWrite(entryLedPin, LOW);   // Turn off green LED
}

void indicateExit() {
  digitalWrite(exitLedPin, HIGH);   // Turn on red LED
  delay(1000);  // Indication duration (adjust as needed)
  digitalWrite(exitLedPin, LOW);    // Turn off red LED
}

void printTotalPersons() {
  Serial.print("Total Persons: ");
  Serial.println(totalPersons);
}
