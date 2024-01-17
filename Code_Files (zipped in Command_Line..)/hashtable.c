#include "duplicates.h"

// MAP A STRING TO A UNSIGNED 32 BIT INT
uint32_t hash_string(char *string)
{
	uint32_t hash = 0;

	while (*string != '\0'){
		hash = hash*33 + *string;
		++string;
	}
	return hash;
}

// ALLOCATE SPACE FOR A NEW HASHTABLE
HASHTABLE *hashtable_new(void){
	HASHTABLE *new = calloc(HASHTABLE_SIZE, sizeof(LIST *));
	if (new == NULL) {perror("Error: "); exit(EXIT_FAILURE);}
	return new;
}
