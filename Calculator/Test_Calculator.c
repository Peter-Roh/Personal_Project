#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Calculator.h"

int main(void)
{
	char InfixExpression[100];
	char PostfixExpression[100];

	double Result = 0.0;

	memset(InfixExpression, 0, sizeof(InfixExpression));
	memset(PostfixExpression, 0, sizeof(PostfixExpression));

	printf("Press z to end this program.\n");

	while(1)
	{
		printf("Enter Expression : ");
		scanf("%s", InfixExpression);

		if(_kbhit())
		{
			if(getch() == 'z')
				break;
		}
		
		GetPostfix(InfixExpression, PostfixExpression);

		Result = Calculate(PostfixExpression);
		printf("Calculation Result : %f\n", Result);
	}

	return 0;
}