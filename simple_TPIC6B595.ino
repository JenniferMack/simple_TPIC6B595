/*
+-~-+-~-+-~-+-~-+-~-+-~-+-~-+-~-+-~-+-~-+
Sketch: simple_TPIC6B595.ino
Created on: Sat Jan 18 11:07:11 MST 2014
+-~-+-~-+-~-+-~-+-~-+-~-+-~-+-~-+-~-+-~-+

Notes:
This setup outputs 8 bits in 128/64/32/16/8/4/2/1 order
                              |  /  /  |  | | | |
                              |  |  |  |  | |  \ \
                             D0 D1 D2 D3 D4 D5 D6 D7

The TPIC6B595 is a medium current shift register, that can sink
(supply ground to) upto 150ma. Be sure to use resistors on your LEDs,
because they will pop if the full 150 mA gets run through them.

Make sure to use a pull-up resistor (5K+ ohms) from pin 8 (SRCLR) to
positive power, otherwise the outputs will not see the data that's fed
in.

If you plan on have multiple high-current LED on at the same time,
make sure to tie all three ground pins to 0V.

*/

#define GATE_DELAY 20

// Arduino pins defined here.
#define SER_IN 2
#define SRCK   5
#define RCK    4

void b595_write(byte bits)
{
    shiftOut(SER_IN, SRCK, LSBFIRST, bits);

    // Must pulse the latch (RCK) to output the byte
    delayMicroseconds(GATE_DELAY);
    digitalWrite(RCK, HIGH);
    delayMicroseconds(GATE_DELAY);
    digitalWrite(RCK, LOW);
}

void setup()
{
    pinMode(SER_IN, OUTPUT);
    pinMode(SRCK, OUTPUT);
    pinMode(RCK, OUTPUT);
}

void loop()
{
    for (int i=0; i<256; i++)
    {
        b595_write(i);
        delay(500);
    }
}

