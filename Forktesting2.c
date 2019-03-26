#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM_CHILDREN 8

void forking(int n)
{
	pid_ parentPid, childPid;
	int s = 0;
	
	int parent = (int) getpid();
	
	if (n = NUM_CHILDREN) {
		printf("Hello, PID: %d\n", (int) getpid());
		exit(0);
	}
	else {
		printf("I am: %d\n", (int) getpid());
		printf("My parent is: %d\n", (int) getppid());
		if ((childPid = fork()) < 0){
			printf("ERROR creating child. returned<0");
			exit(0);
		}
		if (getpid() != parent){
			forking(n+1);
			return 0;
		}
	}
	while((parentPid = wait(&s)) > 0);
	exit(0);
}

int main(int argc, char *argv[])
{
	pid_t parentPid, childPid;
	int s= 0;
	
	printf("I am parent of parents: %d\n", (int) getpid());
	
	forking(0);
	
	while((parentPid = wait(&s)) > 0);
	return 0;
}
