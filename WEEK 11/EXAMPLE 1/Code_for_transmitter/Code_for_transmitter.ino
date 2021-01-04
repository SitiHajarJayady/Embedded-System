char* ddrb=(char*)0x24;
char* portb= (char*)0x25;

void Transmit(unsigned char data,unsigned long BaudRate) // build a Transmit function
{
  unsigned long delay_=1000000/BaudRate;    //Delay in microseconds
  unsigned long clock_delay=delay_/2;    //Period of CLK is half of signal
  
  for(int i=7 ;i>=0 ; i--)  // Sending data   //Start with 7th bit (MSB) first until the LEAST SIGNIFICANT BIT
  {
    if (data & (1 <<i))   //If the ith bit is HIGH
    {
      *portb |= 1 <<2;   //Make PB2 HIGH
    }
    else
    {
      *portb &= ~(1 <<2);//Make PB2 LOW
    }
    
    *portb |=1 <<3;  //Make CLK HIGH // make data able to be send
    delayMicroseconds(clock_delay);
    *portb &= ~(1 <<3);//Make CLK LOW;
    delayMicroseconds(delay_-clock_delay); // make data unable to be send
   }
   
    *portb &= ~(1 <<2);   //Done. Make PB2 back to LOW // make data unable to be send
}

void setup()
{
    *ddrb |=(1 <<2); //setting portB, PB2 as output  
    *ddrb |=(1 <<3); // PB3 as output
     
     Transmit(167,100000);    //Transmit 1010 0111 at 100kBd.
}
void loop()
{
  //
}
