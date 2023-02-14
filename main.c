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
	char path[MAXBUF];
	cmd_t currComm;
	
	
	//print the shell bit
	do {
		printf(DSH_PROMPT);
		fgets(cmdline, MAXBUF, stdin);
		//trim input
		strcpy(cmdline, trimWhitespace());
		//if the first character is forward slash, use mode1
		char *ptr = strtok(cmdline, " ");
		char *args[MAX_ARGS + 1];
		//gets the first arg
		*args[0] = strdup(ptr);
		i = 1;
		//read in the command line input and put it in 
		while (ptr != NULL && i < MAX_ARGS){
			args[i++] = strtok(NULL, DELIM);
		}
		//get the 
		currComm = chkBuiltin(*args[0]);
		//case of an external command
		if (currComm == CMD_EXT){
			//declare array of arguments
			
			//marks end of list
			args[i] = NULL;
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

		}else if (currComm == CMD_CD){
			
		}else if (currComm == CMD_EXIT){
			
		}else if (currComm == CMD_PWD){
			
		}else if (currComm == CMD_HISTORY){
			
		}else if (currComm == CMD_ECHO){
			
		}
		free(args[0]);

		
	} while (cmdline[0] != '/0')
		
	
	//if input is empty reprompt

	return 0;
}
