#include <I2C_RTC.h>

#include <Wire.h>
#include <RTClib.h>

const int entrySensorPin = 2;
const int exitSensorPin = 3;
const int entryLedPin = 5;
const int exitLedPin = 6;

RTC_DS3232 rtc; // Create an RTC object

int entryCount = 0;
int exitCount = 0;
int totalPersons = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Initialize I2C communication

  pinMode(entrySensorPin, INPUT);
  pinMode(exitSensorPin, INPUT);
  pinMode(entryLedPin, OUTPUT);
  pinMode(exitLedPin, OUTPUT);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("RTC initialization failed!");
    while (1); // Stop execution if RTC initialization fails
  }

  // Uncomment the following line to set the RTC to the date and time of compiling the sketch
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  // Read current time from RTC
  DateTime now = rtc.now();

  // Check if a person is entering
  if (digitalRead(entrySensorPin) == HIGH) {
    delay(1000);  // Debounce delay (adjust as needed)
    if (digitalRead(entrySensorPin) == HIGH) {
      entryCount++;
      totalPersons++;
      updateDatabase(now, "enter", entryCount);
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
      updateDatabase(now, "exit", exitCount);
      Serial.println("Exit," + String(exitCount));
      indicateExit();
      printTotalPersons();
    }
  }

  // Add additional logic or functionality as needed

  delay(500);  // Adjust the delay based on your requirements
}

void updateDatabase(DateTime timestamp, String direction, int count) {
  // Include timestamp, direction, and count in the database entry
  Serial.print(timestamp.year(), DEC);
  Serial.print('/');
  Serial.print(timestamp.month(), DEC);
  Serial.print('/');
  Serial.print(timestamp.day(), DEC);
  Serial.print(' ');
  Serial.print(timestamp.hour(), DEC);
  Serial.print(':');
  Serial.print(timestamp.minute(), DEC);
  Serial.print(':');
  Serial.print(timestamp.second(), DEC);
  Serial.print(",");
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
