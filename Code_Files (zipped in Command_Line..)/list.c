#include "duplicates.h"

// ALLOCATE SPACE FOR A NEW LIST ITEM
LIST *list_new_item(char *location, size_t filesize, char *hash){

	LIST *new = calloc(1, sizeof(LIST));
	CHECK_ALLOC(new);
	new -> pathname = strdup(location);
	CHECK_ALLOC(new->pathname);
	new -> file_size = filesize;
	new -> file_hash = hash;
	new -> duplicate_found = false;
	new -> next = NULL;
	return new;

}

// ADD A NEW ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, char *location, size_t filesize, char *hash)
{

	LIST *new = list_new_item(location, filesize, hash);
	new -> next = list; //connect it to existing list
	return new;
}





