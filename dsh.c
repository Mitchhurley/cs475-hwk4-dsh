/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"
#include "builtins.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>


// TODO: Your function definitions (declarations in dsh.h)
void mode1exe(char *args[]){
    int status = 0;
    if (access(args[0], F_OK | X_OK) == 0) {
       int pid = fork();
			//if its the child process
		if (pid == 0){
			execv(args[0], args);
		}
		else if (pid > 0) {
		// parent process
			wait(&status);
		} else {
			// fork failed
			perror("fork");
			exit(1);
		}
    }
    else {
        // No good! File doesn't exist or is not executable!
        // Alert user and re-prompt
    }
}

char *trimWhitespace(char *str){
    const char *end;
    int len;
    //use addressing to increment to the right place
    while (isspace(*str)) str++;

    if (*str == 0)
        return strdup("");

    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;

    len = end - str + 1;
    char *result = (char *)malloc(len + 1);
    if (!result)
        return NULL;

    memcpy(result, str, len);
    result[len] = 0;

    // Free dynamically allocated memory before returning


    return result;
}

char** split(char *str, char *delim){
    int count = 0;
    //tallies instances of delim
    char* p = str;
    while (*p) {
        if (strstr(p, delim) == p) {
            count++;
            p += strlen(delim);
        } else {
            p++;
        }
    }
    //handles case of no instances
    

    count++;  // Add one for the last token
    printf("\nCount is %d", count);
    printf("\nBytes are %ld", sizeof(char*) * (count + 1));
    char** args = (char**) malloc(sizeof(char*) * (count + 1));
    for (int i = 0; i <= count; i++) {
        printf("\nMalloc'ing to args[%d]", i);
        args[i] = (char*) malloc(MAX_TOK_LEN * sizeof(char));
    }

    int i = 0;
    char str_copy[MAXBUF];
    strcpy(str_copy, str);
    char* token = strtok(str_copy, delim);

    //while still having tokens
    while (token != NULL) {
        strcpy(args[i++], token);
        token = strtok(NULL, delim);
    }
    //sets the last arg to be null
    args[i] = NULL;

    return args;

}