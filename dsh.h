/*
 * dsh.h
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

#define MAXBUF 256
#define HISTORY_LEN 100
#define DSH_PROMPT "dsh> "

// TODO: Your function prototypes below
void mode1exe(char *path);
char *trimWhitespace(char *string);