void setup()
{
    char* ddrb= (char*)0x24;  //Points to DDRB register
    char* portb= (char*)0x25; //Points to PORTB register
    *ddrb=0b00001111; //Set the 4 pins as output
    char DriveSteps[] = {1,2,4, 8}; //Activation pattern of wave drive
    char position=0;
    
    Serial.begin(9600);
    
    unsigned long last;//Stores last time the motor moved
    
    while(1)
    {
        unsigned long now =millis();
        if(now-last>=5)//If the motor has not moved for 5 ms
        {
          *portb=DriveSteps[position];
          position++;
          
          if(position>=4)
          {
            position =0;
          }
          last = now;
          Serial.println((unsigned char)*portb,BIN);//Serial printing is just for trouble shooting
        }
    }
}
void loop()
{
  //
}
