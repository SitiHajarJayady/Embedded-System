
  int LED1=2;
  int LED2=4;
  int LED3=7;
  int LED4=8;
  int LED5 =12;
  
void setup() {


  pinMode(LED1, OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
}

void loop() {

  yellow1();
  blue();
  yellow2();
  green();
  red();
 

}
void yellow1()
 {
  digitalWrite(LED1, HIGH);   
  delay(781);                       
  digitalWrite(LED1, LOW);    
  delay(515);    
 }
void blue()
{  
  digitalWrite(LED2, HIGH);  
  delay(2014);            
  digitalWrite(LED2, LOW);   
  delay(1348);

 }
void yellow2()
{ 
  digitalWrite(LED3, HIGH);  
  delay(343);                     
  digitalWrite(LED3, LOW);    
  delay(573); 
}

void green()
{
  digitalWrite(LED4, HIGH);   
  delay(678);                     
  digitalWrite(LED4, LOW);    
  delay(1839);
}

void red()
{
  digitalWrite(LED5, HIGH);   
  delay(342);                     
  digitalWrite(LED5, LOW);    
  delay(534);
}
