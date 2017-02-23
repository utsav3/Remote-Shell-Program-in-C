#include "header.h"


int readAndParseCmdLine(char **, char **);

void error(char *msg){
  perror(msg);
  printf("HELLO--");
  exit(1);
}


void main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen; //int variable that is used later
    char buffer[256]; //buffer of size created
    struct sockaddr_in serv_addr, cli_addr; //calling the library struct
    int n;


//Checks if the num of argument is 2, if not error message is displayed.
    if(argc<2)
    {
      fprintf(stderr,"Num of argument Error");
    }


    //1st IP Address 2nd TCP Concept 3rd Socket
    sockfd= socket(AF_INET, SOCK_STREAM,0);
    if(sockfd == -1)
    {
      error("Could not connect to socket");
    }

    //
    //Clearing the server address with bzero function
    //
    bzero((char *) &serv_addr, sizeof(serv_addr));

    //Coverts the character value to integer for the portno
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

//Converts the int to Network format
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
      error("ERROR on binding");
    }

    //The second arg is the no of clients it can handel.
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    //
    //The new socket for the client informations
    //
    if(newsockfd<1)
    {
      sleep(1);
    }
    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);


    if (newsockfd < 0)
      {
          error("ERROR on accept");
      }
    bzero(buffer,256); //Clears the buffer

    n = read(newsockfd,buffer,255);

    if (n < 0)
    {
        error("ERROR reading from socket");
    }

    //Buffer Stores the msg sent by the client
    printf("Here is the entered bash command: %s\n",buffer);

    n = write(newsockfd,"I got your message",18);

    if (n < 0)
    {
        error("ERROR writing to socket");
    }


    char *prog;
    strcpy(prog, buffer);
      //printf("HHHHHHHHHHHHHHHH\n");
      //printf("buffer = %s \n", buffer);
      //exit(1);
  	char *args[100];

  	int child_pid;

    //Running the Bash Commands
    if(readAndParseCmdLine(&prog, args)) {
  		child_pid =fork();

  		if(child_pid == 0){ //child part
        printf("\n");
  			execvp(prog, args);  // create and run the new process and close the child process
        printf("\n");
			prog = NULL;
  			printf("Error in excuting the command- please make sure you type the right syntax.\n");
  		} else{ //parent part
  			wait(child_pid);
  		}
      void main();
  	}

}

//
//This function reads the linux command form the buffer and parse it
//
  int readAndParseCmdLine(char **prog, char **args){
  int i =0;
  char cmd[100]; //user command
	char * temp;
	temp = *prog;
  //printf(" HHHHHHHHHHHHhh -- %s\n", temp);
        //sscanf(*prog,"%s",cmd);
      	//printf("%s",cmd);




    	 if(strcmp(temp,"exit")==0){return 0;} //end program if user type exit.

	     char *tok;
    	tok = strtok(temp," \n");

    	while(tok != NULL){
    		if(i==0){
    			prog[0] = tok;
    		}
    		args[i] = tok;
        printf("\n");
    		i=i+1;
    		tok = strtok(NULL, " \n");
    	}
	//printf("tok == %s", tok);
    	args[i]=NULL;
    	return 1;
    }
