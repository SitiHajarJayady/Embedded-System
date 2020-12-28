void setup()
{
    char* ddrb=(char*)0x24;  //Points to DDRB register
    char* portb=(char*)0x25; //Points to PORB register
    *ddrb= 0b00001111; //Set the 4 pins as output
    
    char DriveSteps[] = {1,2,4,8}; //Activation pattern of wave drive
    char position=0;
    Serial.begin(9600);
    
    while(1)
    {
        *portb=DriveSteps[position];
        position++;
        if(position>=4)
        {
          position =0;
        }
        
        Serial.println((unsigned char)*portb, BIN); //Serial printing is just for trouble shooting
        delay(5);//Delay for 5ms before stepping again
     }
}
void loop()
{
  //
}
