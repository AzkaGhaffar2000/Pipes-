
#include <stdio.h>
#include <sys/file.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int in_file, out_file, fd[2];;  
	int n, i, r, status; 
	char array[100];
	
	if (argc < 3)
	{
		printf("Please give an input and output file\n");
		exit(1);
	}
	
	if (!strcmp(argv[1], argv[2]))
	{
		printf("\nBoth files must be different\n");
		exit(2);
	}
	
	out_file = open(argv[2], O_CREAT|O_RDWR|O_APPEND, 0644);		
	if (out_file == -1)
	{
		printf("\nUnable to open the output file\n");
		exit(4);
	}
	
	if (pipe(fd) == -1)	{	
		printf("Pipe Error: Could not create a pipe");
		exit(1);
	}
	
	if (fork() == 0)
	{		
		close(fd[0]);
	
		in_file = open(argv[1], O_RDONLY);		
		if (in_file == -1)
		{
		printf("\nUnable to open the input file\n");
		exit(3);
		}
		n = read(in_file, array, 100);
		write(fd[1], array, strlen(array));
		
		close(fd[1]);
		exit(0);
	}
	else
	{	
		char file[100];	
		close(fd[1]); 
		r = read(fd[0], file, 100);	
		n = write(out_file, file, r);
			
		close(fd[0]);
		printf("\nPARENT: Done\n");
		
		wait(&status);
	}
	
	close(in_file);
	close(out_file);	
		
	return 0;
}













