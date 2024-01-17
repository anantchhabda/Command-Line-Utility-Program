#include "duplicates.h"

// HELP process_directory1 TO SCAN RECURSIVELY
void scan_directory1(HASHTABLE *hashtable, char *dirname){

	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(dirname);
	if (dirp == NULL) {} //ignore inside directories if unreadable etc.
	else {
		while ((dp = readdir(dirp)) != NULL){
			if (dp->d_name[0] == '.'){}
			else {
				struct stat stat_info;
				char pathname [MAXPATHLEN];

				sprintf(pathname, "%s/%s", dirname, dp->d_name);

				if(stat(pathname, &stat_info) != 0){}

				else {
					if ( S_ISDIR(stat_info.st_mode)){
						scan_directory1(hashtable, pathname); //recursive call to dig in directory
					}

					else if ( S_ISREG(stat_info.st_mode)){
						nfiles++;
						total_size+=stat_info.st_size;
						char *hash = strdup(strSHA2(pathname));
						CHECK_ALLOC(hash);
						uint32_t index = hash_string(hash) % HASHTABLE_SIZE;
						hashtable[index] = list_add(hashtable[index], pathname, stat_info.st_size, hash);
					}

					else {}
				}
			}
		}
	}

		closedir(dirp);
}
	





// SCAN DIRECTORY RECURSIVELY, IGNORING HIDDEN FILES
HASHTABLE *process_directory1(char *dirname){

	HASHTABLE *hashtable = hashtable_new(); //create HASHTABLE to store the data

	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(dirname);
	if (dirp == NULL) {perror("Error: "); exit(EXIT_FAILURE);}

	while ((dp = readdir(dirp)) != NULL){
		if (dp->d_name[0] == '.'){}

		else {
			struct stat stat_info;
			char   pathname[MAXPATHLEN];

			sprintf(pathname, "%s/%s", dirname, dp->d_name);

			if(stat(pathname, &stat_info) != 0){}

			else {
				if ( S_ISDIR(stat_info.st_mode)) {
					scan_directory1(hashtable, pathname);}

				else if ( S_ISREG(stat_info.st_mode)) {
					nfiles++;
					total_size+=stat_info.st_size;
					char *hash = strdup(strSHA2(pathname));
					CHECK_ALLOC(hash);
					uint32_t index = hash_string(hash) % HASHTABLE_SIZE;
					hashtable[index] = list_add(hashtable[index], pathname, stat_info.st_size, hash);
				}
				else {}
			}
		}
	}
	closedir(dirp);
	return hashtable;
	
}

// HELP process_directory2 TO SCAN RECURSIVELY
void scan_directory2(HASHTABLE *hashtable, char *dirname){

	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(dirname);
	if (dirp == NULL) {}

	else {
		while ((dp = readdir(dirp)) != NULL){

			if (strcmp(".", dp->d_name) == 0 || strcmp("..", dp->d_name) == 0) {}

			else {
				struct stat stat_info;
				char pathname [MAXPATHLEN];
				sprintf(pathname, "%s/%s", dirname, dp->d_name);

				if(stat(pathname, &stat_info) != 0){}
				else {
					if ( S_ISDIR(stat_info.st_mode)){
						printf("%s is a directory\n", pathname);
						scan_directory2(hashtable, pathname);
					}
					else if ( S_ISREG(stat_info.st_mode)){
						printf("%s is a regular file\n", pathname);
						nfiles++;
						total_size+= stat_info.st_size;
						char *hash = strdup(strSHA2(pathname));
						CHECK_ALLOC(hash);
						uint32_t index = hash_string(hash) % HASHTABLE_SIZE;
						hashtable[index] = list_add(hashtable[index], pathname, stat_info.st_size, hash);
					}
					else {}
				}
			}
		}
	}
	closedir(dirp);
}


// SCAN DIRECTORY RECURSIVELY, ALLOW ALL FILES
HASHTABLE *process_directory2(char *dirname){

	HASHTABLE *hashtable = hashtable_new(); //create HASHTABLE to store the data


	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(dirname);
	if (dirp == NULL) {perror("Error: "); exit(EXIT_FAILURE);}

	while ((dp = readdir(dirp)) != NULL){

		if (strcmp(".", dp->d_name) == 0 || strcmp("..", dp->d_name) == 0) {} //ignore . and .. directories

		else{
			struct stat stat_info;
			char   pathname[MAXPATHLEN];
			sprintf(pathname, "%s/%s", dirname, dp->d_name);

			if(stat(pathname, &stat_info) != 0){}

			else {
				if ( S_ISDIR(stat_info.st_mode)) {
					scan_directory2(hashtable, pathname);	
			}
				else if ( S_ISREG(stat_info.st_mode)) {
					nfiles++;
					total_size+=stat_info.st_size;
					char *hash = strdup(strSHA2(pathname));
					CHECK_ALLOC(hash);
					uint32_t index = hash_string(hash) % HASHTABLE_SIZE;
					hashtable[index] = list_add(hashtable[index], pathname, stat_info.st_size, hash);
				}

				else {}
			}
		}
	}
	closedir(dirp);
	return hashtable;
}

	


