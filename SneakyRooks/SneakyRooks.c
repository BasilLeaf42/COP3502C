// Christopher Cao
// ch282858
// COP 3502, Fall 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "SneakyRooks.h"

// mandatory function
int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
{
	// variable declaration
	int i, j, returnValue = 1;
	int *rows, *columns;
	Coordinate *coord;
	
	rows = malloc(sizeof(int) * (boardSize + 1));
	columns = malloc(sizeof(int) * (boardSize + 1));
	coord = malloc(sizeof(Coordinate));
	
	// loop to initialize board values to 0
	for (i = 0; i < (boardSize + 1); i++)
	{
		rows[i] = 0;
		columns[i] = 0;
	}
	
	// loop to sort through each rook
	for (j = 0; j < numRooks; j++)
	{
		parseCoordinateString(rookStrings[j], coord);
		
		// statement to break from loop if rooks are unsafe
		if (rows[coord->row] == 3502 || columns[coord->col] == 3502)
		{
			returnValue = 0;
			break;
		}
		
		// statement to fill row and column otherwise
		else
		{
			rows[coord->row] = 3502;
			columns[coord->col] = 3502;
		}
	}
	
	// free memory
	free(rows);
	free(columns);
	free(coord);
	
	return returnValue;
}

// mandatory function
void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
{
	// variable declaration
	int i, rookStringLength;
	
	rookStringLength = strlen(rookString);
	rookCoordinate->row = 0;
	rookCoordinate->col = 0;
	
	// loop to sort through each character in the rookString
	for (i = 0; i < rookStringLength; i++)
	{
		// statements to update row and column values
		if (isdigit(rookString[i]))
		{
			rookCoordinate->row = rookCoordinate->row * 10 + (rookString[i] - '0');
		}
		
		else
		{
			rookCoordinate->col = rookCoordinate->col * 26 + (rookString[i] + 1 - 'a');
		}
	}
}

double difficultyRating(void)
{
	return 3.5;
}

double hoursSpent(void)
{
	return 8.0;
}
