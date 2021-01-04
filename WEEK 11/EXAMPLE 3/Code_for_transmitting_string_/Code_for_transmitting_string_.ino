char* ddrb=(char*)0x24;
char* portb= (char*)0x25;

void Transmit(unsigned char data,int BaudRate)
{
    unsigned long delay_us=1000000/BaudRate;
    *portb |=1 <<2;  //Send start bit (HIGH)
    delayMicroseconds(delay_us);
    
    for(int i=7; i>=0; i--)     //MSB first (decrementing loop)
    {
      if(data & (1 <<i))    //If the ith bit is HIGH
      {
        *portb |=1 <<2;   //Send HIGH bit
      }
      else
      {
        *portb &= ~(1 <<2);     //Send LOW bit
      }
      
     delayMicroseconds(delay_us);
    }
    
     *portb &= ~(1 <<2);  //Send stop bit (LOW)  // after finished sending the LSB data, will be low for (delay_us) time
     delayMicroseconds(delay_us);
}

void setup()
{
    *ddrb |=(1 <<2);
    Transmit("YUSOF\n",2000); // transmit string at 2000 baudRate
}
void loop()
{
  //
}
