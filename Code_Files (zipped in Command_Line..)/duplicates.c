// CITS2002 Project 2 2021
// Name: Anant Chhabda 
// Student Number: 21712878


#include "duplicates.h"

int main(int argc, char *argv[])
{
	int opt;
	bool aflag = false;
	bool Aflag = false;
	bool fflag = false;
	bool hflag = false;
	bool lflag = false;
	bool qflag = false;
	char *filename = NULL; 
	char *hash = NULL; 
	HASHTABLE *hashtable;

	// PROCESS COMMAND-LINE OPTIONS
	opterr = 0;
	while ((opt = getopt(argc, argv, OPTLIST)) != -1) 
	{
		if (opt == 'a'){aflag = !aflag;}
		else if(opt == 'A'){Aflag = !Aflag;}
		else if (opt == 'f'){fflag = !fflag; filename = strdup(optarg);}
		else if (opt == 'h'){hflag = !hflag; hash = strdup(optarg);}
		else if (opt == 'l'){lflag = !lflag;}
		else if (opt == 'q'){qflag = !qflag;}
		else {argc = -1;} //any other switch unacceptable
	}

	if (argc < 0 || optind ==  argc) {usage(); exit(EXIT_FAILURE);}

	// BASIC SOLUTION IMPLEMENTED 
	if (Aflag == true){exit(EXIT_FAILURE); }

	// PROCESS DIRECTORIES W.R. "-a" SWITCH
	if (aflag==false) {hashtable = process_directory1(argv[optind]);}
	else {hashtable = process_directory2(argv[optind]);} 

        // CHECK "-f" SWITCH
	if (fflag == true) {
		bool result1 = find_filename(hashtable,filename);
		if (result1 == true) {exit(EXIT_SUCCESS);}
		else {exit(EXIT_FAILURE);}
	}

	// CHECK "-h" SWITCH
	if (hflag == true){
		bool result2 = find_hash(hashtable, hash);
		if (result2 == true) {exit(EXIT_SUCCESS);}
		else {exit(EXIT_FAILURE);}
	}

	bool result3 = find_duplicates(hashtable,lflag,qflag); //standard duplicate file finder with some switches functionality

	if (qflag == true) 
	{
		if (result3 == false) {exit(EXIT_FAILURE);}
		else {exit(EXIT_SUCCESS);}
	}
	if (lflag == true){exit(EXIT_SUCCESS);} //online sample solution for project always exit -l switch with success

	print_results();

	exit(EXIT_SUCCESS);
}
