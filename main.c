#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	char c = '\0';
	char buff[128];
	char *argv[3];
	int argc = 0;
	int indexf,indexs;
	int cpid;

	while(1){

		printf(">> ");
		indexs = indexf = 0;

		while(1){
			c = getchar();
			buff[indexf] = c;
			if(c == ' ' || c=='\n'){
				break;
			}
			indexf++;
		}

		if(buff[indexf]==' ')
			argc = 2;
		else
			argc = 1;

		buff[indexf] = '\0';
		
		if (strcmp(buff,"exit")==0)
			break;	

		

		for(int i = 0;i < 2 ;i++){ 
			argv[i]=(char *)malloc(sizeof(strlen(buff))+1);
            if(!argv[i])
                perror("out of memory");
			strcpy(argv[i],buff);
		}
				
	
		if(argc == 2){
			while(1){
				c = getchar();
				buff[indexs] = c;
				if (c == '\n')
					break;
				indexs++;
			}
		}
	
		buff[indexs] = '\0';
		argv[2] = (char *)malloc(sizeof(strlen(buff))+1);
        if(!argv[2])
            perror("out of memory");
		strcpy(argv[2],buff);


		cpid = fork();
        if(cpid == -1)
            perror("figlio non creato\n");
		if(cpid == 0){
			if(argc == 1){
				execlp(argv[0],argv[1],NULL);
				exit(1);
			}
			else if (argc == 2){
				execlp(argv[0],argv[1],argv[2],NULL);
				exit(2);
			}	
		}else
			wait((int *)0);

		for (int i = 0; i < 3; ++i)
			free(argv[i]);
	}	



	return 0;
}
