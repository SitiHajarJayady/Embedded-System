

const int A = 2;     
const int B = 3;
const int C= 4;


int buttonState1 = 0;        
int buttonState2 = 0;  
int buttonState3 = 0; 

int countA=0;
int countB=0;
int countC=0;

void setup() {
  Serial.begin(9600);
  
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C, INPUT_PULLUP);
}

void loop() {
 
  //read the state of the pushbuttons value:
  buttonState1 = digitalRead(A);
  buttonState2 = digitalRead(B);
  buttonState3 = digitalRead(C);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState1 == HIGH) 
      updateA();
     

    else if (buttonState2 == HIGH) 
      updateB();

     else if (buttonState3 == HIGH) 
      updateC();
     
    
  
}

void updateA() {
      delay(300);
      countA++;

      Serial.print("A = ");
      Serial.print(countA);
      Serial.print(" B = ");
      Serial.print(countB);
      Serial.print(" C = ");
      Serial.print(countC);
      Serial.println();
      
     }

void updateB(){
      delay(300);
      countB++;

      Serial.print("A = ");
      Serial.print(countA);
      Serial.print(" B = ");
      Serial.print(countB);
      Serial.print(" C = ");
      Serial.print(countC);
      Serial.println();
 
     }
void updateC(){
      delay(300);
      countC++;

      Serial.print("A = ");
      Serial.print(countA);
      Serial.print(" B = ");
      Serial.print(countB);
      Serial.print(" C = ");
      Serial.print(countC);
      Serial.println();
 
     }
