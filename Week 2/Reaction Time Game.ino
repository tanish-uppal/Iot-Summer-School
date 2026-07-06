// Define Hardware Pins
const int ledRed = 8;
const int ledYellow = 9;
const int ledGreen = 10;
const int buttonPin = 2;

// Array to make randomizing the LEDs easier
const int leds[] = {ledRed, ledYellow, ledGreen};

void setup() {
  // Start Serial Monitor at 9600 baud rate
  Serial.begin(9600);
  
  // Set LED pins as outputs
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  
  // Set button pin as input with internal pull-up resistor
  // This means the pin reads HIGH when unpressed, and LOW when pressed
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Seed the random generator using noise from an unconnected analog pin
  randomSeed(analogRead(0));
  
  Serial.println("--- Arduino Reaction Time Game ---");
  Serial.println("Open Serial Monitor to see your time!");
  delay(2000);
}

void loop() {
  Serial.println("\nGet ready...");
  delay(1000);
  
  // 1. Unpredictable Blinking Sequence
  // Choose to blink between 5 and 12 times
  int blinkCount = random(5, 13); 
  
  for (int i = 0; i < blinkCount; i++) {
    int randomLed = leds[random(0, 3)]; // Pick a random LED (0, 1, or 2)
    int randomDuration = random(100, 500); // Keep it on for 100ms to 500ms
    
    digitalWrite(randomLed, HIGH);
    delay(randomDuration);
    digitalWrite(randomLed, LOW);
    
    // Tiny random pause between blinks
    delay(random(50, 150)); 
  }
  
  // 2. The Final Wait (All LEDs off)
  // Wait a random time between 1 and 3 seconds before the Green LED turns on
  int waitTime = random(1000, 3000); 
  unsigned long waitStart = millis();
  bool cheated = false;
  
  // Check if the user presses the button BEFORE the green light
  while (millis() - waitStart < waitTime) {
    if (digitalRead(buttonPin) == LOW) { // LOW means pressed
      cheated = true;
      break; 
    }
  }
  
  // Penalty for early pressing
  if (cheated) {
    Serial.println("False start! You pressed too early.");
    // Flash all LEDs to indicate a penalty
    for(int i = 0; i < 3; i++) {
      digitalWrite(ledRed, HIGH); digitalWrite(ledYellow, HIGH); digitalWrite(ledGreen, HIGH);
      delay(150);
      digitalWrite(ledRed, LOW); digitalWrite(ledYellow, LOW); digitalWrite(ledGreen, LOW);
      delay(150);
    }
    delay(1000);
    return; // Restart the loop from the beginning
  }
  
  // 3. GO! Turn on Green LED and start timer
  digitalWrite(ledGreen, HIGH);
  unsigned long startTime = millis();
  
  // 4. Wait for the player to react
  // The loop blocks here until the button is pressed (pin goes LOW)
  while (digitalRead(buttonPin) == HIGH) {
    // Waiting for reaction...
  }
  
  // 5. Button pressed! Stop timer and turn off LED
  unsigned long endTime = millis();
  digitalWrite(ledGreen, LOW);
  
  // 6. Calculate and display result
  unsigned long reactionTime = endTime - startTime;
  
  Serial.print("Reaction Time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");
  
  if (reactionTime < 200) {
    Serial.println("Lightning fast!");
  } else if (reactionTime < 300) {
    Serial.println("Good job!");
  } else {
    Serial.println("Too slow, try again.");
  }
  
  // Wait a bit before starting the next round
  delay(3000);
}
