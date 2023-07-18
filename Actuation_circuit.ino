// Define connections to sensor
#define TRIGPIN 9
#define ECHOPIN 10
#define RELAYPIN 7

float duration, distance;
bool pump;

void setup() {
  Serial.begin(9600);

  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(RELAYPIN, OUTPUT); // Set relay pin as OUTPUT
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
  duration = pulseIn(ECHOPIN, HIGH)/ 1000000.0;

  // Convert duration to distance in meters
  distance = (duration / 2) * 343;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" meters");

  // Check if distance is greater than 0.4m
  if (distance > 0.4) {
    digitalWrite(RELAYPIN, LOW); // Turn on the relay
    pump = true; // Turn on the pump
    Serial.println("Pump Status: ON");
  }
  // Check if distance is less than 0.3m
  else if (distance < 0.3) {
    digitalWrite(RELAYPIN, HIGH); // Turn off the relay
    pump = false; // Turn off the pump
    Serial.println("Pump Status: OFF");
  }

  delay(1000);
}
