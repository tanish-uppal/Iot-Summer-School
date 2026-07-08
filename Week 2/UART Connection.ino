//Sender Code 
void setup() {
  Serial.begin(9600);   // Start UART at 9600 baud - MUST match on both boards
}

void loop() {
  Serial.println("Hello from A"); // Sends text out over TX (pin 1)
  delay(500);                    // Wait 1 second before sending again
}

// Reciever code 
void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(data);
  }
}
