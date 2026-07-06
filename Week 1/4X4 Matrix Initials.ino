int rows[] = {2,4,7,8}; // Row 1 to Row 4
int cols[] = {6,9,10,11 };     // Column 1 to Column 4
// 4x4 Matrix representation for the letter 'T'
// 1 = LED ON, 0 = LED OFF
int pattern[4][4] = {
  {1, 1, 1, 1},  // Row 1: Top bar of the T
  {0, 1, 1, 0},  // Row 2: Center stem
  {0, 1, 1, 0},  // Row 3: Center stem
  {0, 1, 1, 0}   // Row 4: Center stem
};
void setup() {
  // Set all Row and Column pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
    
    digitalWrite(rows[i], LOW);   // Clear rows
    digitalWrite(cols[i], HIGH);  // Deactivate columns
  }
}
void loop() {
  // Rapidly loop through the rows to display the character
  for (int r = 0; r < 4; r++) {
    // Activate the current row
    digitalWrite(rows[r], HIGH);   
    for (int c = 0; c < 4; c++) {
      if (pattern[r][c] == 1) {
        digitalWrite(cols[c], LOW);  // Pull column LOW to complete circuit (Turn ON)
      } else {
        digitalWrite(cols[c], HIGH); // Keep column HIGH (Turn OFF)
      }
    }
    delay(2); 
    digitalWrite(rows[r], LOW);
    for (int c = 0; c < 4; c++) {
      digitalWrite(cols[c], HIGH);
    }
  }
}
