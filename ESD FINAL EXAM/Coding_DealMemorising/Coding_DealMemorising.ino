#include <Servo.h> // include servo library
#include <Wire.h> // library for I2C communication
#include <LiquidCrystal_I2C.h> // library for LCD

LiquidCrystal_I2C lcd(0x27, 16, 2); //lcd address

Servo myservo;
 
int LED[] = {13, 6, 10};       // initialize the LED ( three LEDs : YELLOW, GREEN, RED)
int PUSHBUTTON[] = {3, 4, 5}; // initialize the pushbutton (for every LED)
int Count = 3;  // number of LEDs
int buzzer = 8;
int pos=0;                   // idle position for servo at 0 degree
 
int ledState = 0;
int gameState = 0;

#define ROUND 6 // number of round need to be succeed
int gameValues[ROUND];
int roundNum = 0;
 
//declare functions
void setLed(int ledNum);
void arduinoTurn(int roundNum);
boolean waitForInput(int buttonNum);
 
void setup () {

myservo.attach(2); // servo connected to pin 2 ; to provide the sweets / reward
lcd.init();
lcd.backlight();
Serial.begin(9600);


Serial.println("setup");
 
  for(int Pin = 0; Pin < Count; Pin++) // set the LED as OUTPUT
  {
  //set all leds to output
  pinMode(LED[Pin], OUTPUT);
  }
    
  for(int Pin = 0; Pin < Count; Pin++) //set the PUSHBUTTON as INPUT
  {
  
  pinMode(PUSHBUTTON[Pin], INPUT_PULLUP);
  }
 
 //if analog input pin 0 is unconnected
 //random analog noise will cause the call to randomSeed() to generate
 //different seed numbers each time the sketch runs
 //randomSeed() will shuffle the random function that we call during gameplay
 randomSeed(analogRead(0));
 }

void loop () {
  myservo.write(pos);  // move the servo to its initial position
  if (gameState == 0)
  {
     int button0 = digitalRead(PUSHBUTTON[0]);
     int button1 = digitalRead(PUSHBUTTON[1]);  
     int button2 = digitalRead(PUSHBUTTON[2]); 
     
    //if no buttons are pressed 
    if (button0 && button1 && button2)
    {
      pre_game();
    }
    // if a button is pressed set up for the game
    else
    {
   
      lcd.clear();
      lcd.setCursor(0, 0);  // Set the cursor on the first column, first row.
      lcd.print("You have six"); // print on the LCD
      lcd.setCursor(0, 1);  
      lcd.print("rounds to play:)"); 
      delay (3000);
      lcd.clear(); // clear the LCD
      
      //turn leds off before starting game --> function setLed() states that if ledNum is <0 led is LOW
      setLed(-1);
      //set the round number to zero, the first round
      roundNum = 0;
      delay (1000);
      //set gameState to 1 
      gameState = 1;
    }
  }

  if (gameState == 1)
  {
    gamePlay();
  }
  
  if (gameState == 2)
  {
    
    delay(500);
    winning_sound(); // winning sound
    winDisplay(); // LEDs winning display

    //dislpay " YOU ARE AWESOME, TAKE YOUR REWARD"
    lcd.setCursor(0, 0);  
    lcd.print("YOU ARE AWESOME!! "); 
    delay (2000);
    lcd.clear();
    lcd.setCursor(0, 0);  
    lcd.print("TAKE YOUR REWARD "); 
 

    for (pos = 15; pos <= 40; pos += 1) {
        myservo.write(pos);              // servo will open the cap of the container to supply sweets
        delay(15);                       // wait 15ms for the servo to reach the position
      }

      for (pos = 40; pos >= 15; pos -= 1) {
        myservo.write(pos);              // servo will close the cap of the container
        delay(15);                       // waits 15ms for the servo to reach the position
      }

    
    delay (3000);
    lcd.clear();
    
    
   
    delay (1000);
    
    //reset gameState to zero to call pre_game
    gameState = 0;
  }
  
  if (gameState == 3)
  {
    // playing the lose sound and LEDs display for losing
    delay(500); 
    losing_sound();
    loseDisplay();

    //display "You lose"
    lcd.setCursor(0, 0);  
    lcd.print("You Lose "); 
    delay(2000);
    lcd.clear();

    //display "It's okay Try again"
    lcd.setCursor(0, 0);  
    lcd.print("Tt's okay"); 
    lcd.setCursor(0, 1);  
    lcd.print("Try again :)");
    delay (3000);
    lcd.clear();

    delay (1000);
    //reset gameState to zero to call pre_game
    gameState = 0;
  } 
}

//pre_game
void pre_game()
{
  // display "press any button to start game"
   lcd.setCursor(0, 0);  
   lcd.print("Press any button"); 
   lcd.setCursor(0, 1);  
   lcd.print("to start game:)"); 
  
   digitalWrite(LED[0], HIGH);
   digitalWrite(LED[1], HIGH);
   digitalWrite(LED[2], HIGH);
   delay(400);
   digitalWrite(LED[0], LOW);
   digitalWrite(LED[1], LOW);
   digitalWrite(LED[2], LOW);
   delay(400);
 
}

//function for while game is playing
void gamePlay()
{
  //pre-load array with random numbers for game
  for ( int i=0; i<ROUND; i++)
  {
    //use floor to round number down to nearest integer and random to choose random numbers from 0 to 3 to put in the gameValues array.
    gameValues[i] = floor(random(0,3));
  }

  for (int r=0; r<ROUND; r++)
  {
    arduinoTurn(roundNum);
  
    for (int i=0; i<=roundNum; i++)
    {      
  
      //wait for user input and see if they're correct, if correct wait for next input etc.. if not correct, fail
      if (waitForInput(gameValues[i]))
      {
        //correct input
        if (i==roundNum)
        {
          
          lcd.setCursor(0, 0);  
          lcd.print("EXCELLENT !! "); 
          delay(2000);
          lcd.clear();
          
          //check if final round 
          if (roundNum == ROUND-1)
          {
            
           // you won! 
           // set gameState to 2 to run winning fuction
           gameState = 2;
           return;
          }
          else 
          {
            lcd.setCursor(0, 0);  
            lcd.print("Continue..  "); 
            delay(1000);
            lcd.clear();
          }
        }
      }
      else 
      {
        //incorrect input
        Serial.println("You Lose!");
        

        // you lost :(
        // set gameState to 3 to run losing function
        gameState = 3;
        return;
      }
    }
    //User made it through the round, increment round number to continue
    roundNum++;
   
    delay(1000);
  }
}

void setLed(int ledNum)
{
  //if the led number is less than zero turn all the leds off
  if (ledNum<0)
  {
   for (int i = 0; i<Count; i++)
   {
   digitalWrite(LED[i], LOW);
   }
  }
  else
  {
    //turn on the specified led, turn off the other leds
    for (int i = 0; i<Count; i++)
    {
      if (i == ledNum)
      {
        digitalWrite(LED[i], HIGH);
      }
      else 
      {
        digitalWrite(LED[i], LOW);
      }
    }
  }
 }


 void arduinoTurn(int roundNum)
 {
  //turn all lights off
  setLed(-1);
  for (int i=0; i<=roundNum; i++)
  {
    //turn on led that matches current round
    setLed(gameValues[i]);
    delay(750);
    setLed(-1);
    delay(250);
  }
 }

boolean waitForInput(int buttonNum)
{
  //read all the buttons continuously until a button is pressed, check the pressed button if it's correct and return true. if not, return false. 
  while(true) 
  {
   int button0 = digitalRead(PUSHBUTTON[0]);
   int button1 = digitalRead(PUSHBUTTON[1]);  
   int button2 = digitalRead(PUSHBUTTON[2]); 
 
   
   //because the input_pullup ! indicted a button is pressed,if any button is pressed go to the rest of the code
   if (!button0 || !button1 || !button2)
   {
      //Delay briefly to avoid double counting button press
      delay(250);

      //light up the corresponding led when a button is pressed
      if (buttonNum == 0)
      {
        digitalWrite(LED[0], HIGH);
        delay(250);
        digitalWrite(LED[0], LOW);
      }
      else if (buttonNum == 1)
      {
        digitalWrite(LED[1], HIGH);
        delay(250);
        digitalWrite(LED[1], LOW);
      }
      else if (buttonNum == 2)
      {
        digitalWrite(LED[2], HIGH);
        delay(250);
        digitalWrite(LED[2], LOW);
      }
      
      //check if correct button was pressed
      if (buttonNum == 0 && button0 == 0)
      {
        return true;
      }
      else if (buttonNum == 1 && button1 == 0)
      {
        return true;
      }
      else if (buttonNum == 2 && button2 == 0)
      {
        return true;
      }
  
      else
      {
        return false;
      }
    }
  }
}


void winDisplay()
{
digitalWrite(LED[0], HIGH);
delay(75);
digitalWrite(LED[0], LOW);
delay(75);
digitalWrite(LED[1], HIGH);
delay(75);
digitalWrite(LED[1], LOW);
delay(75);
digitalWrite(LED[2], HIGH);
delay(75);
digitalWrite(LED[2], LOW);
delay(75);
}

void winning_sound(void)
{
  tone(buzzer, 294, 250);
  delay(200);
  tone(buzzer, 294, 250);
  delay(200);
  tone(buzzer, 294, 250);
  delay(200);
  tone(buzzer, 392, 500);
  delay(500);
  
  tone(buzzer, 392, 250);
  delay(200);
  tone(buzzer, 440, 250);
  delay(200);
  tone(buzzer, 392, 250);
  delay(200);
  tone(buzzer, 440, 250);
  delay(200);
  tone(buzzer, 494, 500);
}


void loseDisplay()
{
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  delay(200);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], LOW);
  delay(200);
}

void losing_sound(void)
{
 
  tone(buzzer, 98, 250);
  delay(250);
   tone(buzzer, 93, 250);
  delay(250);
   tone(buzzer, 87, 250);
  delay(250);
}
