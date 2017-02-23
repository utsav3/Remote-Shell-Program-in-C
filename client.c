
#include "header.h"

void error(char *msg)
{
perror(msg);
exit(0);
}

int main(int argc, char *argv[])

{
    int sockfd, portno, n;
     struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    //We have to use 3 args while running client code.
    if (argc < 3)
    {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
    }

    //Gets the portno form the argument
    portno = atoi(argv[2]);


    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd<0)
    {
      error("Error opening socket");
    }
  //  if (sockfd h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);


    //gets the hostname
    server = gethostbyname(argv[1]);

      if(server==NULL)
      {
        fprintf(stderr,"Error,no such host\n");
        exit(0);
      }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0)
    {
      error("ERROR connecting");
    }

    printf("Please enter the linux command: ");
    bzero(buffer,256); //clears the buffer content
    fgets(buffer,255,stdin);


//For iterating the execution of the code loope needs to be here.
    n = write(sockfd,buffer,strlen(buffer)); //returns -1 if the write on the buffer was sucessful.


    if (n < 0)
    {
      error("ERROR writing to socket");
    }

    bzero(buffer,256);


    n = read(sockfd,buffer,255);

    if (n < 0)
    {
      error("ERROR reading from socket");
    }
    printf("\n%s\n",buffer);

    return 0;
}
