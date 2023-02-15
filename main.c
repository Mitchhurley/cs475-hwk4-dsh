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
#include "builtins.h"
#include "dsh.h"

int main(int argc, char **argv)
{
	 // stores user input from commmand line
	
	

	
	
	//print the shell bit
	do {
		char *cmdline = (char*) malloc(MAXBUF);
		printf(DSH_PROMPT);
		fgets(cmdline, MAXBUF, stdin);
		
		//trim input
		strcpy(cmdline, trimWhitespace(cmdline));
		//if the first character is forward slash, use mode1
		
		//declare array of arguments
		char **args = split(cmdline, " ");
		
		printf("\nGot input: %s", args[0]);
		//get the current command	
		cmd_t currComm = chkBuiltin(args[0]);
		//case of an external command
		if (currComm == CMD_EXT){
			//if the first char of the path starts with '/', its a full path
			if (args[0][0] == '/'){
				mode1exe(args);
			}
		}else if (currComm == CMD_CD){
			
		}else if (currComm == CMD_PWD){
			
		}else if (currComm == CMD_ECHO){
			
		}else if (currComm == CMD_EXIT){
			int i = 0;
			while(args[i] != NULL){
				free(args[i]);
				i++;
			}
			free(args);
			free(cmdline);
			exit(1);
		}
		free(cmdline);
	} while (1);
	
	//if input is empty reprompt

	return 0;
}
