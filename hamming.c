#include <stdbool.h>
#include <stdio.h>
#include <wiringPi.h>

void initialise(bool *bits)
{
	// call to wiringPi.h setup function
	wiringPiSetup();
	// set all pints to output and initialse LOW
	for (int i = 0; i < 7; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
		bits[i] = 0;
	}
}

void setBit(int pinNo, bool *bits)
{
	// set high and update status
	digitalWrite(pinNo, HIGH);
	bits[pinNo] = 1;
}

void clearBit(int pinNo, bool *bits)
{
	// set low and update status
	digitalWrite(pinNo, LOW);
	bits[pinNo] = 0;
}

void toggleBit(int pinNo, bool *bits)
{
	// switch on if off, or vice versa
	if (bits[pinNo])
	{
		clearBit(pinNo, bits);
	}
	else
	{
		setBit(pinNo, bits);
	}
}

void setParityLogic(int pinNo, bool *bits)
{
	// needed to read the parity bits and set the lights as appropriate
	if (bits[pinNo])
	{
		digitalWrite(pinNo, HIGH);
	}
	else
	{
		digitalWrite(pinNo, LOW);
	}
}

void parityLogic(bool *bits)
{
	// apply hamming code logic
	bits[4] = bits[3] ^ bits[1] ^ bits[0];
	bits[5] = bits[3] ^ bits[2] ^ bits[0];
	bits[6] = bits[3] ^ bits[2] ^ bits[1];
}

void updateData(bool *bits)
{
	// scan for character input and set toggle bit if required
	int i;
	scanf("%d", &i);
	
	if (i >= 0 && i <= 3)
	{
		toggleBit(i, bits);
	}
	fflush(stdin);
}

void printBitset(bool *bits)
{
	for (int k = 0; k < 7; k++)
	{
		printf(bits[k] ? "1" : "0");
	}
	printf("\n");
}

int main(void)
{
	// array of seven booleans to keep track of status of the pins
	// the array will decay to a pointer so pass straight to init function
	static bool bitStatus[7];
	initialise(bitStatus);	
	while(1)
	{
		// read input and control data lights
		updateData(bitStatus);
		// apply the logic to the parity bits and alter bitStatus array
		parityLogic(bitStatus);
		// loop through parity bits and switch light on or off as required
		for (int j = 4; j < 7; j++)
		{
			setParityLogic(j, bitStatus);
		}
		printBitset(bitStatus);
	}

	return 0;
}
