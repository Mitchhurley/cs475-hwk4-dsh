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
		int *numArgs = (int*)malloc(sizeof(int));
		printf("%s", DSH_PROMPT);
		fgets(cmdline, MAXBUF, stdin);
		if (cmdline[0] != '\n'){
			cmdline[strlen(cmdline) - 1] = '\0';
			char *tmp = trimWhitespace(cmdline);
			//trim input
			strcpy(cmdline, tmp);
			free(tmp);
			//if the first character is forward slash, use mode1
			
			//declare array of arguments
			char **args = split(cmdline, " ", numArgs);
			//get the current command	
			cmd_t currComm = chkBuiltin(args[0]);
			//case of an external command
			if (currComm == CMD_EXT){
				//if the first char of the path starts with '/', its a full path
				
				if (args[0][0] == '/'){
					mode1exe(args, numArgs);
					for (int i = 0; i <= *numArgs; ++i) 
						free(args[i]);
					free(args);
					free(numArgs);
					free(cmdline);
					
				}else {
					mode2exe(args, numArgs);
					for (int i = 0; i <= *numArgs; ++i) 
						free(args[i]);
					free(args);
					free(numArgs);
					free(cmdline);
				}
			}else if (currComm == CMD_CD){
				
				if (chdir(args[1]) == 0){
					for (int i = 0; i <= *numArgs; ++i) 
						free(args[i]);
					free(args);
					free(numArgs);
					free(cmdline);
					;
				}else{
					perror("\nIssue Changing directory");
					for (int i = 0; i <= *numArgs; ++i) 
						free(args[i]);
					free(args);
					free(numArgs);
					free(cmdline);
					;
				}
				
			}else if (currComm == CMD_PWD){
				char cwd[MAX_PATH_LEN];
    			getcwd(cwd, sizeof(cwd));
    			printf("\n%s", cwd);
				for (int i = 0; i <= *numArgs; ++i) 
						free(args[i]);
					free(args);
					free(numArgs);
					free(cmdline);
			
			}else if (currComm == CMD_ECHO){
				
			}else if (currComm == CMD_EXIT){
				for (int i = 0; i <= *numArgs; ++i) 
					free(args[i]);
				free(args);
				free(numArgs);
				free(cmdline);
				exit(1);
			}
		} else {
			free(cmdline);
			free(numArgs);
		}
		
	} while (1);
	
	//if input is empty reprompt

	return 0;
}
