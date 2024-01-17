# A Makefile to build our Duplicates Program 
C11 = cc -std=c11
CFLAGS = -Wall -Werror -pedantic


duplicates : duplicates.h duplicates.c scandirectory.c list.c hashtable.c strSHA2.c findfiles.c global.c helper.c
	$(CC) $(CFLAGS) -o duplicates duplicates.c scandirectory.c list.c hashtable.c strSHA2.c findfiles.c global.c helper.c


