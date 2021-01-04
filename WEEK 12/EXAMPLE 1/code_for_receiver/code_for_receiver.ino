volatile char *pinb= (char*)0x23;

char Receive()
{
    char ReceivedData;
    bool previous_CLK= ((*pinb) & (1 <<3)); //previous_CLK= digitalRead(11);
    
    for(int i=7; i>=0; i--)
    {
      for(;;)
      {
        bool current_CLK= ((*pinb) & (1 << 3));
        
        if(current_CLK && !previous_CLK)//PGT
        {
          previous_CLK=current_CLK;
          break;  //Break statement can be avoided
        }
        
        previous_CLK=current_CLK;
      }
      
     if((*pinb) & (1 <<2))  //If PB2 (data pin) is HIGH
      {
        ReceivedData |=1 <<i; //Set the ithbit
      }
     else
      {
        ReceivedData &= ~(1 <<i); //Clear the ithbit
      }
    }
    
    return ReceivedData;
}


void setup()
{
    Serial.begin(9600);
    
    while(1)
    {
      unsigned char data =Receive();  //Get the incoming data
      Serial.println(data); //Print the incoming data
    }
}
