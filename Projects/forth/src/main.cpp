#include "forth.hpp"

const char *operators = "+-";
const char *whitespace = "\r\n\t\b ";
const char *invalid = "Invalid character";

void setup()
{
	Serial.begin(115200);
	Serial.PrintLn("\033[2J");
	Serial.PrintLn("Hello World");
	Serial.PrintLn();
}

void loop()
{
	char c = Serial.getChar();
	int8_t idx;
	idx = indexOf(c, whitespace);
	if (idx != -1)
	{
	}

	idx = indexOf(c, operators);
	if (idx == -1) //not an operator
		;

	if (c >= '0' && c <= '9')
	{
	}
}

int main()
{
}