#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM_CHILDREN 8								//Sets the number of children processes you want to have

int main(int argc, char *argv[])
{
	pid_t parentPid, childPid;						//Initializing pids for later use
	int s= 0;								//A status flag for the wait function
	
	printf("I am parent: %d\n", (int) getpid());				//gives the parent's id number
	int parent = (int) getpid();						//saves the parent's id number for later use
	
	int i = 0;								//didn't want to do a for loop
	
	while(i<NUM_CHILDREN){							//loop to create children that say hello and their id number
		if ((childPid = fork()) < 0) {					//for when a process doesnt work
			printf("ERROR creating child. returned<0");		//shoots an error message if the child process doesnt run
			exit(0);
		}
		if ((int) getpid() != parent) {					//we use the parent id to differentiate between the parent and children
			printf("Hello, PID: %d\n", (int) getpid());		//children say hello and their id no
			exit(0);						//children exit so as not to continue the while loop
		}
		i++;								//parent continues the while loop until all children are made
	}
	while((parentPid = wait(&s)) > 0);					//parent waits for the children processes to end
	return 0;
}
