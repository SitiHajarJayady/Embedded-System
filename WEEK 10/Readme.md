EXAMPLE 1:

Using Blinky class to blink LED (1s for On state and 1s for off state)

EXAMPLE 2:

Using Blinky class to generate PWM waveform on port B, PB5 
200 micro seconds for On time and 300 micro seconds for off time

EXAMPLE 3:

Using Blinky class to generate PWM waveform at PB5
On time= 100 micro seconds
Off time= 200 micro seconds

EXAMPLE 4:

Using DCMotor class to generate a 50 Hz PWM waveform at PB0
Duty cycle is at constant 50%

EXAMPLE 5:

Using DCMotor class to generate 1KHz PWM waveform at PB0
Duty cycle is constant at 20%

EXAMPLE 6:

Connecting 4 DC motors at PB0, PB1, PB2 and PB3
Using DCMotor class to operate the motors with PWM frequency of 500 Hz
Duty cycle for each DC motor:
at PB0 = 20%
at PB1= 40%
at PB2= 60%
at PB3= 80%

EXAMPLE 7:

Connecting 4 DC motors at PB0, PB1, PB2 and PB3
Using DCMotor class to operate the motors with PWM frequency of 1000 Hz
Duty cycle for each DC motor:
at PB0 = 20%
at PB1= 40%
at PB2= 60%
at PB3= 80%

EXAMPLE 9:

Rotate DC motor by 90 degree:
Connecting 4 DC motors at PB0, PB1, PB2 and PB3
Using DCMotor class to operate the motors with PWM frequency of 20 KHz
Setting pulse width of 1.5 ms ; assuming the servo require 1.5 ms to rotate about 90 degree

EXAMPLE 10:

Rotating servo back and forth (sweeping) ; connected to PB0
where:
Minimum pulse width = 544us
Maximum pulse width = 2400us
Step size = 10us.
Delay = 25ms







