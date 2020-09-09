#include <stdbool.h>
#include <stdio.h>
#include <wiringPi.h>

void initialise(bool *bits)
{
	// call to wiringPi.h setup function
	wiringPiSetup();
	// set all pints to output and initialse LOW
	for (int i; i < 7; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
		bits[i] = 0;
	}
}

void toggleBit(int pinNo, bool *bits)
{
	if (bits[pinNo])
	{
		digitalWrite(pinNo, LOW);
		bits[pinNo] = 0;
	}
	else
	{
		digitalWrite(pinNo, HIGH);
		bits[pinNo] = 1;
	}
}

void update(bool *bits)
{
	int i;
	scanf("%d", &i);
	
	if (i >= 0 && i <= 7)
	{
		toggleBit(i, bits);
	}
}

int main(void)
{
	// array of seven booleans to keep track of status of the pins
	// the array will decay to a pointer so pass straight to init function
	static bool bitStatus[7];
	initialise(bitStatus);
	
	while(1)
	{
		update(bitStatus);
	}

	return 0;
}
