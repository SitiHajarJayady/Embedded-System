void setup()
{
    char*adcsra= (char*)0x7A;
    char*acsr= (char*)0x50;
    
    *adcsra=0;
    *acsr= 1<< 7;
    
    DeepSleep();
    
    for(;;)
    {
      //
    }
}
void loop()
{
  //
}

void DeepSleep()
{
    char*smcr= (char*)0x53;
    volatile char *mcucr= (char*) 0x55;
    
    *smcr=5;//Sleep mode = POWER DOWN, Sleep Enable = True
    *mcucr=0b01100000;//Set Both BODS and BODSE
    *mcucr=0b01000000;//Set BODS and clear BODSE
    
    asm("sleep"); //Invoke in line assembler to sleep
}
