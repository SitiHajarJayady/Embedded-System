volatile bool changed;
unsigned char*sreg= (unsigned char*)0x5F;
unsigned char*pcicr= (unsigned char*)0x68;
unsigned char*pcmsk0 = (unsigned char*)0x6B;
 
void setup()
{
  Serial.begin(9600);
  *sreg|= (1 <<7); //Enable interrupts in general  // 10000000
  *pcicr=1; //Enable pin change interrupt 0, INT0 BECOMES HIGH
  *pcmsk0 =255; //Enable pin change interrupt on all the Port B pin // 11111111


 while(1)
{
  if(changed)
{
  Serial.println("Sensor values changed");
  //Perform necessary investigation and subsequent operations
  changed =0;
}
  //Do other things or go back to sleep
  
}
}

  ISR(PCINT0_vect)
{
changed =1;
}
