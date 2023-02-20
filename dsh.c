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
void mode1exe(char *args[], int *numArgs){
    int status = 0;
    if (access(args[0], F_OK | X_OK) == 0) {
        if (strcmp(args[(*numArgs)], "&") == 0){
					int pid = fork();
                    //if its the child process
                    if (pid == 0){
                        execv(args[0], args);
                    }
		}else {
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
    result[len] = '\0';

    // Free dynamically allocated memory before returning
    

    return result;
}

char** split(char *str, char *delim, int *argc){
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
    *argc = count;

    count++;  // Add one for the last token
    char** args = (char**) malloc(sizeof(char*) * (count + 1));
    for (int i = 0; i < count; i++) {
        args[i] = (char*) malloc(MAX_TOK_LEN * sizeof(char));
    }

    int i = 0;
    char str_copy[MAXBUF] ;
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
void mode2exe(char *args[], int *numArgs){
    int found = 0;
    char *fullpath = (char*) malloc(MAX_PATH_LEN * sizeof(char));
    char *currentDir = getcwd(NULL, 0);
    snprintf(fullpath, sizeof(char) * MAX_PATH_LEN, "%s/%s", currentDir, args[0]);
    if (access(fullpath, F_OK | X_OK) == 0) {
        found = 1;
        mode1exe(args, numArgs);
            for (int i = 0; i <= *numArgs; ++i) 
		        free(args[i]);
		free(args);
		free(numArgs);
    }else{
        
        int *numLocs = (int*)malloc(sizeof(int));
        char **locs = split(getenv("PATH"), ":", numLocs);
        for (int i = 0; i <= *numLocs; i++){
            snprintf(fullpath, sizeof(char) * MAX_PATH_LEN, "%s/%s", locs[i], args[0]);
            if (access(fullpath, F_OK | X_OK) == 0) {
                found = 1;
                args[0] = fullpath;
                mode1exe(args, numArgs);
                for (int i = 0; i <= *numArgs; ++i) 
					free(args[i]);
				free(args);
				free(numArgs);
            }else continue;
        }
        
        for (int i = 0; i <= *numLocs; ++i) 
			free(locs[i]);
		free(locs);
        free(numLocs);
    }
    free(fullpath);
    free(currentDir);
    if (!found){
        perror("\nError");
    }
    

}