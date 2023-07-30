#include <EEPROM.h>  // Include the EEPROM library

// Define connections to sensor
#define TRIGPIN 9
#define ECHOPIN 10
#define RELAYPIN 7

float duration, distance;
bool pump;

// Tank height in meters
const float tankHeight = 1.00;

void setup() {
  Serial.begin(9600);

  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(RELAYPIN, OUTPUT); // Set relay pin as OUTPUT

  // Read the last pump status from EEPROM
  int pumpStatus = EEPROM.read(0); // Address 0 in EEPROM
  pump = (pumpStatus == 1); // Convert the read value to a boolean
  digitalWrite(RELAYPIN, pump ? LOW : HIGH); // Set the relay based on pump status

  // Print the initial pump status
  Serial.print("Pump Status: ");
  Serial.println(pump ? "ON" : "OFF");
}

void loop() {
  // Set the trigger pin LOW for 2uS
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);

  // Set the trigger pin HIGH for 20us to send pulse
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(20);

  // Return the trigger pin to LOW
  digitalWrite(TRIGPIN, LOW);

  // Measure the width of the incoming pulse
  duration = pulseIn(ECHOPIN, HIGH) / 1000000.0;

  // Convert duration to distance in meters
  distance = (duration / 2) * 343;

  // Calculate the remaining distance in the tank
  float remainingDistance = tankHeight - distance;

  // Calculate water level as a percentage (0% to 100%)
  float waterLevelPercent = (remainingDistance / tankHeight) * 100;
  waterLevelPercent = constrain(waterLevelPercent, 0, 100); // Keep the value within 0 to 100 range

  // Print water level to the serial monitor
  Serial.print("Water Level: ");
  Serial.print(waterLevelPercent);
  Serial.println("%");

  // Check if water level is below or equal to 3%
  if (waterLevelPercent <= 10.0) {
    digitalWrite(RELAYPIN, LOW); // Turn on the relay
    pump = true; // Turn on the pump
    Serial.println("Pump Status: ON");
  }
  // Check if water level is above or equal to 97%
  else if (waterLevelPercent >= 70.0) {
    digitalWrite(RELAYPIN, HIGH); // Turn off the relay
    pump = false; // Turn off the pump
    Serial.println("Pump Status: OFF");
  }

  // Save the current pump status to EEPROM
  EEPROM.update(0, pump ? 1 : 0); // Address 0 in EEPROM

  delay(1000);
}
