#include <stdio.h>
#include <wiringPi.h>

int* init(void)
{
	wiringPiSetup();
	for (int i; i < 7; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}

	static int bits[7] = {0};

	return bits;
}

void toggleBit(int pinNo, int pinStatus)
{
	if (pinStatus == 1)
	{
		digitalWrite(pinNo, LOW);
	}
	else
	{
		digitalWrite(pinNo, HIGH);
	}
}

int main(void)
{
	int *bitStatus[7] = init();
	return 0;
}
