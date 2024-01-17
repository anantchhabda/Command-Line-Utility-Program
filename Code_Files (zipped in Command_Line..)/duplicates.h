#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <stdint.h>

#if     defined(__linux__)
extern  char    *strdup(const char *string);
#endif

// MACRO FOR SIZE OF OUR HASHTABLE
#define HASHTABLE_SIZE 997

// MACRO FOR OPTLIST (FOR SWITCHES)
#define OPTLIST "aAf:h:lq"

// MACRO TO HELP WITH CHECKING IF ALLOCATIONS WERE SUCCESFUL
#define CHECK_ALLOC(p) if(p == NULL) {perror(__func__); exit(EXIT_FAILURE);}


//A SIMPLE LIST DATATYPE TO STORE VARIOUS ATRRIBUTES OF A FILE AND A POINTER TO ANOTHER LIST
typedef struct _list {
	char   *pathname;
	char   *file_hash;
	size_t file_size;
	bool   duplicate_found;
	struct _list *next;
} LIST;

// DEFINE HASHTABLE AS A DYNAMICALLY ALLOCATED ARRAY OF LISTS
typedef LIST * HASHTABLE;

// DECLARE GLOBAL VARIABLES TO HELP WITH ACCUMULATING STATS
extern int     nfiles;
extern size_t  total_size;
extern int     unique_files;
extern size_t  min_size;


// THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN scandirectory.c :

// SCAN DIRECTORY RECURSIVELY, IGNORING HIDDEN FILES
extern HASHTABLE *process_directory1(char *dirname);

// SCAN DIRECTORY RECURSIVELY, ALLOW ALL FILES
extern HASHTABLE *process_directory2(char *dirname);

// HELP process_directory1 TO SCAN RECURSIVELY
extern void scan_directory1(HASHTABLE *hashtable, char *dirname);

// HELP process_directory2 TO SCAN RECURSIVELY
extern void scan_directory2(HASHTABLE *hashtable, char *dirname);




// THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED in hashtable.c :

// MAP A STRING TO A UNSIGNED 32 BIT INT
extern uint32_t hash_string(char *string);

// ALLOCATE SPACE FOR A NEW HASHTABLE
extern HASHTABLE *hashtable_new(void);




// THIS FUNCTION IS DECLARED HERE, AND DEFINED IN list.c :

// ADD A NEW ITEM TO AN EXISTING LIST
extern LIST *list_add(LIST *list, char *location, size_t filesize, char *hash);




// THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN findfiles.c :

// FIND DUPLICATES WITH RESPECT TO FLAGS GIVEN
extern bool find_duplicates(HASHTABLE *hashtable, bool lflag, bool qflag);

// FIND FILES WITH SAME SHA2 HASH MATCH AS INDICATED FILE
extern bool find_filename(HASHTABLE *hashtable, char *filename);

// FIND FILES WITH THE INDICATED SHA2 HASH
extern bool find_hash(HASHTABLE *hashtable, char *hash);




//THESE FUNCTIONS ARE DECLARE HERE, AND DEFINED IN helper.c :

//REPORT THE REQUIRED OUTPUT
extern void print_results(void);

//REPORT THE PROGRAMS SYNOPSIS
extern void usage(void);



// THIS FUNCTION IS DECLARED HERE, AND DEFINED IN strSHA2.c :

// CRYPTOGRAPHIC HASH FUNCTION TO EXAMINE FILE CONTENT
extern char *strSHA2(char *filename);



