// Christopher Cao
// ch282858
// COP 3502, Fall 2020

// Preprocessor directives
#include "Orcheeseo.h"
#include <stdio.h>
#include <string.h>

// Start of main function
int main(int argc, char **argv)
{
	// If there is no user input
	if (argv[1] == NULL)
		printf("No cookie. :(\n");
	
	// Passes valid user input to printOrcheeseo
	else
		printOrcheeseo(argv[1]);
	
	return 0;
}

// Start of printOrcheeseo function
void printOrcheeseo(char *str)
{
	// Variable declaration
	int i, j;
	int argLen = 0;
	int goldfish = 0;
	int hasCheese = 0;
	double goldfishHeight = 0.0;
	double orcheeseoHeight = 0.0;
	
	// Set argLen to the length of user input
	argLen = strlen(str);
	
	// Loop to read user input
	for (i = 0; i < argLen; i++)
	{
		// Statement to print Orcheeseo
		switch (str[i])
		{
			// Prints out cookie layer and updates height
			case 'o':
				printf("==========\n");
				orcheeseoHeight = orcheeseoHeight + 0.40;
				break;
			
			// Prints out creme layer and updates height
			case 'c':
				printf(" ~~~~~~~~\n");
				orcheeseoHeight = orcheeseoHeight + 0.25;
				break;
			
			// Prints out Goldfish layer and updates height
			case 'g':
				// Defines the cookie as having cheese
				hasCheese = 1;
				
				// Counts number of consecutive Goldfish
				for (j = i; j < argLen; j++)
				{
					if (str[j] == 'g')
						goldfish++;
					
					else
						break;
				}
				
				// Passes number of consecutive Goldfish to printGoldfish and updates height
				orcheeseoHeight = orcheeseoHeight + printGoldfish(goldfish);
				i = i + goldfish - 1;
				goldfish = 0;
				break;
			
			// Prints out warning for incompatible input; only for debugging
			default:
				// printf("BAD VALUE!\n");
		}
	}
	
	// Post-diagram output; if the Orcheeseo is too messy
	if (str[0] != 'o' || str[argLen-1] != 'o')
		printf("Too messy. :(\n");
	
	// If the Orcheeseo is too tall
	else if (orcheeseoHeight > 4.0)
		printf("Oh nooooo! Too tall. :(\n");
	
	// If the Orcheeseo is well-formed but missing cheese
	else if (str[0] == 'o' && str[argLen-1] == 'o' && hasCheese == 0)
		printf("Om nom nom! Oreo!\n");
	
	// If the Orcheeseo is well-formed and cheesy
	else if (str[0] == 'o' && str[argLen-1] == 'o' && hasCheese == 1)
		printf("Om nom nom! Orcheeseo!\n");
	
	return;
}

// Start of printGoldfish function
double printGoldfish(int numGoldfish)
{
	// Variable declaration
	double goldfishHeight = 0.0;

	// Prints out Goldfish layer(s) and calculates height of Goldfish layer(s)
	while (numGoldfish != 0)
	{
		// Prints out a standard layer and updates variables
		if (numGoldfish % 3 == 0 || numGoldfish > 4)
		{
			printf(" xoxoxoxo\n");
			
			numGoldfish = numGoldfish - 3;
			goldfishHeight = goldfishHeight + 0.25;
		}
	
		// Prints out an impoverished layer and updates variables
		else if (numGoldfish % 3 == 2)
		{
			printf("  xoxoxo\n");
			
			numGoldfish = numGoldfish - 2;
			goldfishHeight = goldfishHeight + 0.25;
		}
	
		// Prints out a crumbly layer and updates variables
		else if (numGoldfish == 1)
		{
			printf("  .,.,.,\n");
			
			numGoldfish = numGoldfish - 1;
			goldfishHeight = goldfishHeight + 0.10;
		}
		
		// Prints out an extended layer and updates variables
		else if (numGoldfish % 3 == 1 && numGoldfish != 1 || numGoldfish == 4)
		{
			printf("xoxoxoxoxo\n");
			
			numGoldfish = numGoldfish - 4;
			goldfishHeight = goldfishHeight + 0.25;
		}
	}
	
	return goldfishHeight;
}

int returnThirtyTwo(void)
{
	return 32;
}

void printThirtyTwo(void)
{
	printf("32\n");
	return;
}

double difficultyRating(void)
{
	return 3.5;
}

double hoursSpent(void)
{
	return 10.0;
}
