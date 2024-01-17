#include "duplicates.h"

// REPORT THE REQUIRED OUTPUT
void print_results()
{

	printf("%-10i - total files\n", nfiles);
	printf("%-10lu - total bytes\n", total_size);
	printf("%-10i - unique files\n", unique_files);
	printf("%-10lu - possible minimum bytes\n", min_size);



}

// REPORT THE PROGRAMS SYNOPSIS
void usage()
{
	printf("Usage: duplicates-basic [options] dirname\n");
	printf("where options are:\n");
	printf("-a\t\tprocess all files, including hidden(.) files\n");
	printf("-A\t\treport if basic or advanced utility\n");
	printf("-l\t\tlist all duplicates found\n");
	printf("-q\t\tlook for duplicates quiety\n");
}



