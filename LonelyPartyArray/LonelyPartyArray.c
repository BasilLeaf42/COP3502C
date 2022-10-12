// Christopher Cao
// ch282858
// COP 3502, Fall 2020

// pre-processor directives
#include "LonelyPartyArray.h"
#include <stdio.h>
#include <stdlib.h>

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int i;
	LPA *party;
	party = (LPA*) malloc(sizeof(LPA));

	// loop to terminate function if num_fragments, fragment_length, or party have invalid values
	if (num_fragments <= 0 || fragment_length <= 0 || party == NULL)
	{
		return NULL;
	}
	
	// struct allocation
	party->size = 0;
	party->num_fragments = num_fragments;
	party->fragment_length = fragment_length;
	party->num_active_fragments = 0;
	party->fragments = malloc(sizeof(int*) * num_fragments);
	party->fragment_sizes = malloc(sizeof(int) * num_fragments);
	
	// loop to terminate function if party->fragments or party->fragment_sizes have invalid values
	if (party->fragments == NULL || party->fragment_sizes == NULL)
	{
		free(party);
		free(party->fragments);
		free(party->fragment_sizes);
		return NULL;
	}
	
	// loop to initialize party
	for (i = 0; i < num_fragments; i++)
	{
		party->fragments[i] = NULL;
		party->fragment_sizes[i] = 0;
	}
	
	printf("-> A new LonelyPartyArray has emerged from the void. ");
	printf("(capacity: %d, fragments: %d)\n", (num_fragments * fragment_length), num_fragments);
	
	return party;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int i;

	// loop to free fragments
	for (i = 0; i < (party->num_fragments); i++)
	{
		free(party->fragments[i]);
	}

	// functions to free the rest of the party
	free(party->fragments);
	free(party->fragment_sizes);
	free(party);

	printf("-> The LonelyPartyArray has returned to the void.\n");
	
	return NULL;
}

int set(LonelyPartyArray *party, int index, int key)
{
	int fragment, offset, lowest_value, highest_value, i;
	fragment = index / party->fragment_length;
	offset = index % party->fragment_length;
	
	// loop to terminate function if party value is invalid
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}
	
	// loop to terminate function if index value is invalid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in set(). ");
		printf("(index: %d, fragment: %d, offset: %d)\n", index, fragment, offset);
		return LPA_FAILURE;
	}
	
	// loop to set party
	if (party->fragments[fragment] == NULL)
	{
		party->fragments[fragment] = malloc(sizeof(int*) * party->fragment_length);
		
		// loop to terminate function if fragments[fragment] value is invalid post-malloc
		if (party->fragments[fragment] == NULL)
		{
			return LPA_FAILURE;
		}
		
		// loop to mark elements of party as UNUSED
		for (i = 0; i < party->fragment_length; i++)
		{
			party->fragments[fragment][i] = UNUSED;
		}

		party->num_active_fragments = party->num_active_fragments + 1;
		lowest_value = party->fragment_length * fragment;
		highest_value = party->fragment_length * (fragment + 1) - 1;
		
		printf("-> Spawned fragment %d. ", fragment);
		printf("(capacity: %d, indices: %d..%d)\n", party->fragment_length, lowest_value, highest_value);
	}
	
	// loop to count unused elements of party
	if (party->fragments[fragment][offset] == UNUSED)
	{
		party->size = party->size + 1;
		party->fragment_sizes[fragment] = party->fragment_sizes[fragment] + 1;
	}
	
	party->fragments[fragment][offset] = key;
	
	return LPA_SUCCESS;
}

int get(LonelyPartyArray *party, int index)
{
	int fragment, offset;
	fragment = index / party->fragment_length;
	offset = index % party->fragment_length;
	
	// loop to terminate function if party value is invalid
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}
	
	// loop to terminate function if index value is invalid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in get(). ");
		printf("(index: %d, fragment: %d, offset: %d)\n", index, fragment, offset);
		return LPA_FAILURE;
	}
	
	// loop to return UNUSED if fragment is unallocated
	if (party->fragments[fragment] == NULL)
	{
		return UNUSED;
	}
	
	return party->fragments[fragment][offset];
}

int delete(LonelyPartyArray *party, int index)
{
	int fragment, offset, lowest_value, highest_value;
	fragment = index / party->fragment_length;
	offset = index % party->fragment_length;
	
	// loop to terminate function if party value is invalid
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}

	// loop to terminate function if index value is invalid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in delete(). ");
		printf("(index: %d, fragment: %d, offset: %d)\n", index, fragment, offset);
		return LPA_FAILURE;
	}
	
	// loop to terminate function if party->fragments[fragment] value is invalid
	if (party->fragments[fragment] == NULL)
	{
		return LPA_FAILURE;
	}
	
	// loop to terminate function if party->fragments[fragment][offset] value is invalid
	if (party->fragments[fragment][offset] == UNUSED)
	{
		return LPA_FAILURE;
	}
	
	// update party elements
	party->fragments[fragment][offset] = UNUSED;
	party->size = party->size - 1;
	party->fragment_sizes[fragment] = party->fragment_sizes[fragment] - 1;
	
	// loop to clear party values
	if (party->fragment_sizes[fragment] == 0)
	{
		free(party->fragments[fragment]);
		party->fragments[fragment] = NULL;
		party->num_active_fragments = party->num_active_fragments - 1;
		lowest_value = party->fragment_length * fragment;
		highest_value = party->fragment_length * (fragment + 1) - 1;
		
		printf("-> Deallocated fragment %d. ", fragment);
		printf("(capacity: %d, indices: %d..%d)\n", party->fragment_length, lowest_value, highest_value);
	}
	
	return LPA_SUCCESS;
}

int containsKey(LonelyPartyArray *party, int key)
{
	int i, j;

	// loop to terminate function if party value is invalid
	if (party == NULL)
	{
		return 0;
	}
	
	// loop to inspect party->num_fragments
	for (i = 0; i < party->num_fragments; i++)
	{
		// loop to examine non-NULL values
		if (party->fragments[i] != NULL)
		{
			// loop to search for key
			for (j = 0; j < party->fragment_length; j++)
			{
				// loop to return 1 if a key is found
				if (party->fragments[i][j] == key)
				{
					return 1;
				}
			}
		}
	}
	
	return 0;
}

int isSet(LonelyPartyArray *party, int index)
{
	int fragment, offset, i;
	
	// loop to terminate function if party value is invalid
	if (party == NULL)
	{
		return 0;
	}
	
	// loop to terminate function if index value is invalid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		return 0;
	}
	
	fragment = index / party->fragment_length;
	offset = index % party->fragment_length;
	
	// loop to terminate function if party->fragments[fragment] value is invalid
	if (party->fragments[fragment] == NULL)
	{
		return 0;
	}
	
	// loop to terminate function if party->fragments[fragment][offset] value is invalid
	if (party->fragments[fragment][offset] == UNUSED)
	{
		return 0;
	}
	
	return 1;
}

int printIfValid(LonelyPartyArray *party, int index)
{
	int fragment, offset;
	fragment = index / party->fragment_length;
	offset = index % party->fragment_length;
	
	// loop to terminate function if party value is invalid
	if (party == NULL)
	{
		return LPA_FAILURE;
	}
	
	// loop to terminate function if index value is invalid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		return LPA_FAILURE;
	}
	
	// loop to terminate function if party->fragments[fragment] value is invalid
	if (party->fragments[fragment] == NULL)
	{
		return LPA_FAILURE;
	}
	
	// loop to terminate function if party->fragments[fragment][offset] value is invalid
	if (party->fragments[fragment][offset] == UNUSED)
	{
		return LPA_FAILURE;
	}
	
	printf("%d\n", party->fragments[fragment][offset]);
	
	return LPA_SUCCESS;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	int i, capacity;
	
	// loop to terminate function if party value is invalid
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
		return party;
	}

	// loop to inspect party->num_fragments
	for (i = 0; i < party->num_fragments; i++)
	{
		// loop to search for non-NULL values
		if (party->fragments[i] != NULL)
		{
			free(party->fragments[i]);
		}
		
		party->fragments[i] = NULL;
	}
	
	party->size = 0;
	party->num_active_fragments = 0;
	capacity = party->num_fragments * party->fragment_length;
	
	printf("-> The LonelyPartyArray has returned to its nascent state. ");
	printf("(capacity: %d, fragments: %d)\n", capacity, party->num_fragments);
	
	return party;
}

int getSize(LonelyPartyArray *party)
{
	int size;
	
	if (party == 0)
	{
		return -1;
	}
	
	// calculation for party size
	size = party->size;
	
	return size;
}

int getCapacity(LonelyPartyArray *party)
{
	int capacity;
	
	if (party == NULL)
	{
		return -1;
	}
	
	// calculation for party capacity
	capacity = party->num_fragments * party->fragment_length;
	
	return capacity;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
	int cell_count;
	
	if (party == NULL)
	{
		return -1;
	}
	
	// calculation for number of allocated cells
	cell_count = party->num_active_fragments * party->fragment_length;
	
	return cell_count;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	long long unsigned int bytes;
	
	if (party == NULL)
	{
		return 0;
	}
	
	// calculation for number of bytes
	bytes = getCapacity(party) * sizeof(int);
	
	return bytes;
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	long long unsigned int pointer, struc, frag_array, frag_sizes_array, active_frags, bytes;
	
	if (party == NULL)
	{
		return 0;
	}
	
	// calculations for number of bytes
	pointer = sizeof(LPA*);
	struc = sizeof(LPA);
	frag_array = sizeof(party->fragments) * party->num_fragments;
	frag_sizes_array = sizeof(int) * party->num_fragments;
	active_frags = sizeof(int) * party->fragment_length * party->num_active_fragments;
	bytes = pointer + struc + frag_array + frag_sizes_array + active_frags;
	
	return bytes;
}

double difficultyRating(void)
{
	return 5.0;
}

double hoursSpent(void)
{
	return 50.0;
}

// bonus function
LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
	int i, num_fragments, fragments, capacity;
	LPA *clone;
	clone = (LPA*) malloc(sizeof(LPA));
	
	// loop to terminate function if party or clone values are invalid
	if (party == NULL || clone == NULL)
	{
		return NULL;
	}
	
	// struct allocation
	clone->size = 0;
	clone->num_fragments = party->num_fragments;
	clone->fragment_length = party->fragment_length;
	clone->num_active_fragments = 0;
	clone->fragments = malloc(sizeof(int*) * num_fragments);
	clone->fragment_sizes = malloc(sizeof(int) * num_fragments);
	
	// loop to terminate function if clone->fragments or clone->fragment_sizes have invalid values
	if (clone->fragments == NULL || clone->fragment_sizes == NULL)
	{
		free(clone);
		free(clone->fragments);
		free(clone->fragment_sizes);
		return NULL;
	}
	
	printf("“-> Successfully cloned the LonelyPartyArray. ");
	printf("(capacity: %d, fragments: %d)", capacity, fragments);
	
	return clone;
}
