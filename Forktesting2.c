#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM_CHILDREN 8									//Number of children to be created

void forking(int n)									//recurrsive function for creating children
{
	pid_t parentPid, childPid;							//pid for the parents and children
	int s = 0;									//status for the wait function
	
	int parent = (int) getpid();							//get that parent id for comparison
	
	if (n == NUM_CHILDREN) {							//final child says hello
		printf("Hello, PID: %d\n", (int) getpid());
		exit(0);
	}
	else {										//another child is made otherwise
		printf("I am: %d\n", (int) getpid());
		printf("My parent is: %d\n", (int) getppid());				//they say their parents name for clarification that it is going down the generations
		if ((childPid = fork()) < 0){						//error case
			printf("ERROR creating child. returned<0");
			exit(0);
		}
		if (getpid() != parent){						//this ensures that we have only one child per process
			forking(n+1);
		}
	}
	while((parentPid = wait(&s)) > 0);						//wait for all processes to end
	exit(0);
}

int main(int argc, char *argv[])
{
	pid_t parentPid, childPid;							//habit
	int s= 0;									//status for wait funcion
	
	printf("I am parent of parents: %d\n", (int) getpid());				//shows the id for the original process
	
	forking(0);									//starts the recurssion
	
	while((parentPid = wait(&s)) > 0);						//waits for all child processes to end
	return 0;
}
