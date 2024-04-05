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
  if (digitalRead(entrySensorPin) == LOW) {
    delay(1000); // Debounce delay
    entryCount++;
    totalPersons++;
    Serial.println("Enter," + String(entryCount));
    digitalWrite(entryLedPin, HIGH);
    delay(1000);
    digitalWrite(entryLedPin, LOW);
    printTotalPersons();
  }

  if (digitalRead(exitSensorPin) == LOW && exitCount < entryCount) {
    delay(1000); // Debounce delay
    exitCount++;
    totalPersons--;
    Serial.println("Exit," + String(exitCount));
    digitalWrite(exitLedPin, HIGH);
    delay(1000);
    digitalWrite(exitLedPin, LOW);
    printTotalPersons();
  }

  delay(500); // Adjust delay based on requirements
}

void printTotalPersons() {
  Serial.print("Total Persons: ");
  Serial.println(totalPersons);
}
