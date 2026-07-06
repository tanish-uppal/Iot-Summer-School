int RED = 12;
int YELLOW = 11;
int GREEN = 10;

void setup(){
  pinMode(RED,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(GREEN,OUTPUT);
}
void loop(){
  digitalWrite(RED,HIGH);
  digitalWrite(YELLOW,LOW);
  digitalWrite(GREEN,LOW);
  delay(4000);
  
  digitalWrite(GREEN,HIGH);
  digitalWrite(RED,LOW);
  digitalWrite(YELLOW,LOW);
  delay(3000);
  
  digitalWrite(YELLOW,HIGH);
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  delay(1500);
}
