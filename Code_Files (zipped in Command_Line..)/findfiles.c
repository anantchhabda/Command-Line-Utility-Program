#include "duplicates.h"


// FIND FILES WITH SAME SHA2 HASH MATCH AS INDICATED FILE
bool find_filename(HASHTABLE *hashtable, char *filename)
{
	char *hash_req = strSHA2(filename);
	uint32_t index = hash_string(hash_req) % HASHTABLE_SIZE; //find index with respect to hash_req
	bool found_file = false;

	// JUST NEED TO LOOK AT THE LINKED LIST AT THIS INDEX
	LIST *list = hashtable[index];

	while(list != NULL){
		if (strcmp(list->file_hash, hash_req) == 0){
			found_file = true;
			if (strcmp(list -> pathname, filename) != 0){
				printf("%s\n", list->pathname);
			}
		}
		list = list -> next;
	} 
	return found_file;
}


// FIND FILES WITH THE INDICATED SHA2 HASH
bool find_hash(HASHTABLE *hashtable, char *hash)
{
	uint32_t index = hash_string(hash) % HASHTABLE_SIZE;
	bool found_file = false;

	LIST *list = hashtable[index];

	while (list!=NULL){
		if (strcmp(list->file_hash, hash) == 0){
			found_file = true;
			printf("%s\n", list -> pathname);
		}
		list = list->next;
	}
	return found_file;
}


// FIND DUPLICATES WITH RESPECT TO FLAGS GIVEN
bool find_duplicates(HASHTABLE *hashtable, bool lflag, bool qflag){

	for(int i=0; i<HASHTABLE_SIZE; i++){

		if (hashtable[i] == NULL) {} //meaning nothing stored here yet

		else {
			LIST *check_file = hashtable[i];

			//RECURSIVELY GO FROM LEFT TO RIGHT FOR EACH INDEX
			while (check_file != NULL && check_file -> duplicate_found != true){

				unique_files++;
				min_size += check_file -> file_size;
				bool printed_once = false;

				char *check_hash = check_file -> file_hash;
				LIST *next_file = check_file -> next; 

				while(next_file!= NULL){
					if (strcmp(check_hash, next_file -> file_hash) == 0){
						if (qflag == true){
							return false;
						}
						if (lflag == true){
							if (!printed_once){
								printf("%s\t", check_file -> pathname);
								printed_once = !printed_once;
							}
							printf("%s\t", next_file -> pathname);
						}

						next_file -> duplicate_found = true;}

					next_file = next_file -> next;
				}
				if (printed_once) {printf("\n");}
				check_file = check_file -> next;
			}

		}

	}
	return nfiles == unique_files;
}


