# Pipes

#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 80

void createPipe();
void process();
void process1();
void process2();
void process3();
int fd1[2], fd2[2], fd3[2], fd4[2];

int main(void)
{
    //Initialize variables
    pid_t pid[3];
    int i,status;

    //Make 4 pipes
    for(i = 0; i < 4; i++) {
	createPipe(i);
    }

    //Create 3 children and run respective functions
    for(i = 0; i < 3; i++) {
	pid[i] = fork();
	if (pid[i] == 0) {
	    printf("Hi I'm Process %d\n",i+1);
	    process(i);
	}
    }

    //Wait for all children to finish
    for(i = 0; i < 3; i++) {
	waitpid(pid[0],&status,0);
	if(status == 0) {
		printf("Process %d finished. Bye!\n",i+1);
	} else {
		printf("Process %d failed.\n",i+1);
	}
    }
    return 0;
}

void createPipe(n){
    switch(n) {
	case 0:
	    if (pipe(fd1) < 0)
	    	fprintf(stderr, "pipe error \n");
	case 1:
	    if (pipe(fd2) < 0)
		fprintf(stderr, "pipe error \n");
	case 2:
	    if (pipe(fd3) < 0)
		fprintf(stderr, "pipe error \n");
	case 3:
	    if (pipe(fd4) < 0)
		fprintf(stderr, "pipe error \n");
    }
}

void process(n){
    switch(n) {
	case 0:
	    process1();
	    exit(0);
	case 1:
	    process2();
	    exit(0);
	case 2:
	    process3();
	    exit(0);
    }
}

void process1(){
    int i;
    char line[80];
    FILE *fp = fopen("mobydick.txt", "r");
    //Check if input file can be found
    if(fp == NULL){
        perror("File cannot be found.");
        exit(1);
    }
    while( fgets(line, 80, fp) != NULL) {
	write(fd1[1], line, 80);
	//Check if process 2 sends back "orangemarmalade"
	read(fd2[0], line, 80);
	if( strcmp(line, "orangemarmalade") != 0) {
		perror("No good");
		exit(1);
	}
    }
    fclose(fp);
    return;
}

void process2(){
    int n,i;
    char line[MAXLINE];
    while( (n = read(fd1[0], line, MAXLINE)) != 0 ) {
        write(fd2[1], "orangemarmalade", MAXLINE);
	//Reverse case for each letter in given line
	for(i=0;i<n;i++){
		if ( isupper(line[i]) ) {
			line[i] = tolower(line[i]);
		} else if( islower(line[i]) ) {
			line[i] = toupper(line[i]);
		}
	}
	write(fd3[1],line,MAXLINE);
	//Check if process 3 sends back "orangemarmalade"
	read(fd4[0], line, 80);
	if( strcmp(line, "orangemarmalade") != 0) {
		perror("No good");
		exit(1);
	}
    }
}

void process3(){
    int n,i;
    char line[MAXLINE];
    FILE *fp = fopen("mobydicknew.txt","w");
    //Checks if output file is created correctly
    if(fp == NULL){
        perror("File creation failed.");
        exit(1);
    }
    while( (n = read(fd3[0],line,MAXLINE)) != 0 ) {
	fprintf(fp,"%s",line);
	fflush(fp);
        write(fd4[1],"orangemarmalade",MAXLINE);
    }
    fclose(fp);
}
