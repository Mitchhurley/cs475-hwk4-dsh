/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "dsh.h"

int main(int argc, char **argv)
{
	char cmdline[MAXBUF]; // stores user input from commmand line
	//print the shell bit
	printf(DSH_PROMPT);
	fgets(cmdline, MAXBUF, stdin);
	//trim input
	while (cmdline[0] != '/0'){

	}
	//if input is empty reprompt

	return 0;
}
