#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int answer[3];
	int player[3];
	int strike = 0;
	int ball = 0;
	int i, j;
	int cnt = 0;
	char ch;

	srand((int)time(NULL));

	printf("--------------------------------------------------\n");
	printf("Enter a three-digit number like '1 2 3'.\n");
	printf("If you get the number and digit place right, it's a strike.\n");
	printf("If you get the number right but digit place wrong, it's a ball\n");
	printf("You can try to guess the number 9 times.\n");
	printf("--------------------------------------------------\n\n");

	printf("Game Start!\n");

	do
	{
		for(i = 0; i < 3; i++)
		{
			answer[i] = rand() % 10;

			for(j = 0; j < i; j++)
			{
				if(answer[i] == answer[j])
				{
					i--;
					break;
				}

				if(answer[0] == 0)
				{
					i--;
					break;
				}
			}
		}

		while(1)
		{
			cnt++;
			printf("\n");
			printf("Enter a three-digit number. : ");
			scanf("%d %d %d", &player[0], &player[1], &player[2]);
	
			if((player[0] == player[1]) || (player[1] == player[2]) || (player[2] == player[0]))
			{
				printf("The digits must be all different.\n");
				cnt--;
				continue;
			}

			if(player[0] == 0)
			{
				printf("The first number cannot be 0. Please enter again.\n");
				cnt--;
				continue;
			}

			for(i = 0; i < 3; i++)
			{
				for(j = 0; j < 3; j++)
				{
					if(answer[i] == player[j] && i == j)
						strike++;
					if(answer[i] == player[j] && i != j)
						ball++;
				}
			}

			if(strike == 3)
			{
				printf("Correct answer!\n");
				break;
			}

			printf("%d Strike %d Ball.\n", strike, ball);

			if(cnt == 9)
			{
				printf("\nFail!\n");
				break;
			}

			strike = 0;
			ball = 0;
		}

		strike = 0;
		ball = 0;
		cnt = 0;

		printf("Again? y/n\n");
		scanf("%s", &ch);

	} while(ch == 'y');
	
	return 0;
}