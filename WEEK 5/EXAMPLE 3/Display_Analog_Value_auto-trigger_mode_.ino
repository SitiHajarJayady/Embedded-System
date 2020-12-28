char*admux= (char*)0x7C; // ADC Selection register
char*adcsra= (char*)0x7A;
volatile unsigned char*adch= (unsigned char*)0x79;
volatile unsigned char*adcl= (unsigned char*)0x78;


void setup ()//To run on Arduino, just change this function to void setup()
{
  *admux=0b01000001; // selected bit is ADC1, REFS=01; AVCC
  *adcsra=0b11100111; //1110 0XXX ; auto-trigger mode //XXX for desired clock rate 9615 ; ADPS=111 
  Serial.begin(9600);

}
void loop(){
  
  while(1){
 
  int lowbyte= (*adcl); //Capture low byte
  int highbyte= (*adch); //Capture high byte
  int value = (highbyte<<8) | lowbyte; //Merge high byte and low byte
  Serial.println(value);
  }
}
