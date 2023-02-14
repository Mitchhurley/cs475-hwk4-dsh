/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>
#include "builtins.h"

// TODO: Your function definitions (declarations in dsh.h)
void mode1exe(char *path){
    if (access(path, F_OK | X_OK) == 0) {
        // File exists and is executable! Can run!
    }
    else {
        // No good! File doesn't exist or is not executable!
        // Alert user and re-prompt
    }
}

char *trimWhitespace(char *string){
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
    return result;

}