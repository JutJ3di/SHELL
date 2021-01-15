#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	
	char *buffer = malloc(1024);
	int buffer_size = 1024;
	int buffer_used;

	if(buffer == NULL) {
		// out of memory
		printf("Uoops! Out of memory!\n");
		return -1;
	}

	int  word_offsets[128];
	char *argv[128];
	int  argc;
	char c;
	int last_argument_index;

	while(1) {

		argc = 0;
		buffer_used = 0;
		last_argument_index = -1;

		printf("> ");

		while(1) {

			c = getc(stdin);

			if(buffer_used == buffer_size) {


				buffer = realloc(buffer, buffer_size * 2);
				buffer_size *= 2;

				if(buffer == NULL) {
					printf("Uoops! Out of memory!\n");
					return -1;
				}

			}

			if(c == ' ' || c == '\n') {

				buffer[buffer_used++] = '\0';

				if(last_argument_index != -1) {
					word_offsets[argc++] = last_argument_index;
					last_argument_index = -1;
				}

				if(c == '\n')
					break;

			} else {

				if(last_argument_index == -1)
					last_argument_index = buffer_used;

				buffer[buffer_used++] = c;
			}


		}

		for(int i = 0; i < argc; i++)
			argv[i] = buffer + word_offsets[i];
		argv[argc] = NULL;

		if(argc == 0)
			continue;

		// how do i get out of this loop?

        if (strcmp(argv[0],"exit") == 0)
        {
            break;
        }
        


		if(fork() == 0)
			execvp(argv[0], argv);

		wait(0);

	}

	free(buffer);

	return 0;
}

