int LED1=2;
int LED2=4;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}


void loop() {

  BLINK1();
  BLINK2();                    
       
}
void BLINK1()
{
  digitalWrite(LED1, HIGH);   
  delay(750);                       
  digitalWrite(LED1, LOW);    
  delay(350);   
}

void BLINK2()
{
  digitalWrite(LED2, HIGH);   
  delay(400);                       
  digitalWrite(LED2, LOW);    
  delay(600);    
}
