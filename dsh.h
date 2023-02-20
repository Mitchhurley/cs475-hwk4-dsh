/*
 * dsh.h
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

#define MAXBUF 256
#define MAX_PATH_LEN 1028
#define HISTORY_LEN 100
#define DSH_PROMPT "dsh> "
#define MAX_TOK_LEN 256

// TODO: Your function prototypes below
void mode1exe(char *args[], int *numArgs);
char* trimWhitespace(char *string);
char** split(char *str, char *delim, int *argc);