#include <Wire.h>

void setup() {
  Wire.begin();      // Master
}

void loop() {

  Wire.beginTransmission(8);   // Slave address

  Wire.write("Hello");

  Wire.endTransmission();

  delay(1000);
}


// Slave 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD at common address 0x27, 16 columns x 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Receive buffer used by ISR - keep small and fixed-size
volatile char rxBuffer[33]; // allow up to 32 bytes + null
volatile uint8_t rxLen = 0;
volatile bool rxReady = false;

void receiveEvent(int bytes)
{
  // Read at most rxBuffer size - 1 to leave room for null terminator
  uint8_t i = 0;
  while (Wire.available() && i < (sizeof(rxBuffer) - 1)) {
    rxBuffer[i++] = (char)Wire.read();
  }
  // Drain any remaining bytes (avoid leaving them in the buffer)
  while (Wire.available()) {
    (void)Wire.read();
  }
  rxBuffer[i] = '\0';
  rxLen = i;
  rxReady = true; // flag main loop to process the data
}

void setup()
{
  // Initialize LCD
  lcd.init();       // init() used by many LiquidCrystal_I2C variants
  lcd.backlight();
  lcd.clear();

  // Initialize I2C as slave at address 8
  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  // Show waiting message
  lcd.setCursor(0, 0);
  lcd.print("I2C Slave (addr8)");
  lcd.setCursor(0, 1);
  lcd.print("Waiting...");
}

void loop()
{
  if (rxReady) {
    // Temporarily disable interrupts while copying shared data
    noInterrupts();
    char localBuf[33];
    uint8_t localLen = rxLen;
    // copy the received bytes
    for (uint8_t i = 0; i <= localLen; ++i) { // include null terminator
      localBuf[i] = rxBuffer[i];
    }
    rxReady = false;
    interrupts();

    // Update LCD outside of ISR
    lcd.clear();
    lcd.setCursor(0, 0);
    // If the message is empty, show placeholder
    if (localLen == 0) {
      lcd.print("(empty message)");
    } else {
      // Print up to 16 chars on first line, remaining on second if any
      // Ensure null-termination
      localBuf[32] = '\0';
      // First line
      lcd.print(localBuf);
      // If message longer than 16, show remainder on second line
      if (localLen > 16) {
        lcd.setCursor(0, 1);
        // create pointer to remainder
        lcd.print(&localBuf[16]);
      }
    }
  }

  // Small delay to avoid busy looping; responsive enough for typical I2C bursts
  delay(50);
}
