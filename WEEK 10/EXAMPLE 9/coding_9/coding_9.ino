class Blinky
{
  private:
    unsigned long OnTime;//The ON duration in μs
    unsigned long OffTime; //The OFF duration in μs
    unsigned long last_time=0; //The last time a transition occurred
    char mask;//If pin = 3, mask = 0000 1000
    char mask_inv; //If pin = 3, mask_inv= 1111 0111
    char* DDR;
    char* PORT;
  
  public:
    Blinky()  //Constructor without arguments
    {
      Initialize('B',0,1000000,1000000);
      Initialize('B',1,1000000,1000000);
      Initialize('B',2,1000000,1000000);
      Initialize('B',3,1000000,1000000);
    }
  
    Blinky(char port,int pin,long ontime,long offtime) //Constructor with arguments
    {
    Initialize(port,pin,ontime,offtime);
    }
    
    void Initialize(char port,int pin,long ontime,long offtime)
    {
    OnTime=ontime;
    OffTime=offtime;
    
    switch(port)
    {
      case'B':
        DDR = (char*)0x24;
        PORT = (char*)0x25;
        break;
    case'C':
        DDR =(char*)0x27;
        PORT =(char*)0x28;
        break;
    case'D':
        DDR = (char*)0x2A;
        PORT = (char*)0x2B;
        break;
     }
     
    mask = (1 << pin); //The expression (1 << pin) will be used often, it is faster to store it
    mask_inv= ~mask;//The inverse of the expression (1 << pin) will also be used often
    *DDR |=mask;//Set the pin as output pin
    }
    
void ChangeOnOffTimes(long ontime,long offtime)
{
    OnTime=ontime;
    OffTime=offtime;
}
    
//The refresh function needs to be constantly called. It performs respective transitions.

void Refresh()
{
unsigned long now =micros();
  if (*PORT & mask)//The pin is currently HIGH
  {
    if(now -last_time>=OnTime)//If the pin has been HIGH for long enough
    {
      if(OffTime>0)//If OffTimeis 0, no need to even turn it OFF
        {
         *PORT &=mask_inv; //Make the pin LOW
        }
      last_time=now;//Take note of the time
     }
   }
   
  else//The pin is currently LOW
  {
    if(now -last_time>=OffTime)//If the pin has been LOW for long enough
    {
      if (OnTime>0)//If OnTimeis 0, no need to even turn it ON
        {
          *PORT |=mask;//Make the pin HIGH
        }
      last_time=now;//Take note of the time
    }
  }
}
};

class Servo
{
    private:
      Blinky oscillator;
      int Period;
      
    public:
      Servo(char port,int pin,int period)
      {
          Initialize(port,pin,period);
      }
      void Initialize(char port,int pin,int period)
      {
          Period =period;
          oscillator.Initialize(port,pin,0,period);
      }
      void Write(int ontime)
      {
          oscillator.ChangeOnOffTimes(ontime, Period -ontime);
      }
      void Refresh()
      {
          oscillator.Refresh();
      }
};
void setup()
{
  // using 4 servos connected into 4 portB
  Servo motor1('B',0,20000); // PB0 until PB3
  Servo motor2('B',1,20000);
  Servo motor3('B',2,20000);
  Servo motor4('B',3,20000);
  
  motor1.Write(1500); // assuming motor require 1.5ms to turn to 90 degree
  motor2.Write(1500);
  motor3.Write(1500);
  motor4.Write(1500);
  
  while(1)
  {
    motor1.Refresh();
    motor2.Refresh();
    motor3.Refresh();
    motor4.Refresh();
  }
}

void loop()
{
  //
}
