/*
Austin Byrd
CS 2060 002
HW 3
Implement a Maintainable Quality Solution
*/

//preprocessor directives
#include <stdio.h>
#include <math.h>

//declare global constants for modularity
const int MINTIME = 3;
const int PIVOTTIME = 7;
const int MAXTIME = 10;
const int MINPRICE = 50;
const int MAXPRICE = 80;
const int HOURLYPRICE = 8;

// function declarations
int checkValidity(float hours);
float price(float hours);
void display(int sum, float time, int count);

// Start main
int main() 
{
	//Declare input variable 
	float inputtemp;
	float input;
	int sum = 0; //totalprice
	int counter = 1; //boards rented
	unsigned int time = 1;

	do
	{
		//Ask for input 
		printf("%s", "Enter the number of hours the board was rented or enter -1 to quit.\n");

		//recieve input
		scanf("%10f", &inputtemp);
		//check invalid character input
		while ((getchar()) != '\n'); 
		//round input time to next highest hour
		input = ceil(inputtemp);
		

		// Check input's validity
		//return error message if input is invalid
		if (checkValidity(input) == 0 ) 
		{
			printf("%s", "\aError: Enter the time rented. (From 0.1 to 10 hours)\n");
			continue;// I know, I know you said not to, but this fixes problems; if you feel like it isn't please chastise me in class by explaining very clearly what to do instead
		}
		//continue program if input is valid and not -1
		else if (checkValidity(input) == 1)
		{
			sum += price(input);
			display(price(input), inputtemp, counter);
		}
		//if the sentinel value (-1) is entered
		else
		{

		}

		//increment boards and time rented
		counter++;
		time += input;
	} while (input != -1);
	//if no boards were rented, display message
	if (counter == 2) 
	{
		printf("%s", "No boards were rented today.\n");
	}

	//prints final data and PRICE, corrects counter from final loop increments
	display(sum, time, counter-2);
}

// Function checks inputs numerical validity
int checkValidity(float hours)
{
	if (hours == -1)
	{
		return 2;
	}
	if (hours <= 0)
	{
		return 0;
	}
	else if (hours > MAXTIME)
	{
		return 0;
	}
	else
	{
		return 1;
	}

	
}

//calculates price
float price(float hours)
{
	if (hours <= MINTIME) 
	{
		return MINPRICE;
	}
	else if (hours >=  PIVOTTIME)
	{
		return MAXPRICE;
	}
	else
	{
		return ((hours - MINTIME) * HOURLYPRICE) + MINPRICE;
	}
}

// Prints final price and data for user after hours have been entered
void display(int total, float time, int count)
{
	printf("%s", "Board\tHours\tCharge\n");
	printf("%d\t%1.2f\t$%d\n", count, time, total);
}