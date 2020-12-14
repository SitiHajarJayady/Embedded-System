
unsigned char*pind =(unsigned char*)0x29;
unsigned char*ddrb =(unsigned char*)0x24;
unsigned char*portb =(unsigned char*)0x25;
unsigned char*sreg =(unsigned char*)0x5F; // VARIABLE FOR STATUS REGISTER 
unsigned char*eimsk =(unsigned char*)0x3D; // VARIABLE TO TURN ON EXTERNAL INTERRUPT
unsigned char*eicra =(unsigned char*)0x69;  // VARIABLE TO SET MODE

void setup()
{
  *ddrb=1 <<5;//Set PB5 as output 
  *sreg|=(1 <<7); //Enable interrupts in general
  *eimsk=1; //Enable INT0 // TURN ON EXTERNAL INTERRUPT 0
  *eicra=1; // ISC00 // Set interrupt mode to LOW LEVEL
}
  ISR(INT0_vect)
{
  bool pin_status= ((*pind) &4); // COMPARE 00011101 & 00000100
  *portb=pin_status<<5; //Same as digitalWrite(13, digitalRead(2)); // 00000100 BECAME 10000000
}

void loop()
{
  //
}
