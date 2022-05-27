#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/un.h>
#include "poll.h"
#include "server_answer.h"
#define POLL_SIZE 10000

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  int sockFD, newSockFD, portNumber, pid;
  socklen_t clientLen;
  struct sockaddr_in servAddr, clientAddr;
  ServerAnswer server;
  struct pollfd pollSet[POLL_SIZE];
  int numFDs = 0;

  sockFD = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFD < 0)
  {
    error("ERROR opening socket");
  }
  fcntl(sockFD, F_SETFL, O_NONBLOCK);
  bzero((char *) &servAddr, sizeof(servAddr));
  portNumber = 45000;
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(portNumber);
  if (bind(sockFD, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
  {
    error("ERROR on binding");
  }
  listen(sockFD,5);
  memset(pollSet, '\0', sizeof(pollSet));
  pollSet[0].fd = sockFD;
  pollSet[0].events = POLLIN;
  numFDs++;

  int64_t socketsCounter = 0;
  while(1)
  {
    int fd_index;
    int readResult;

    poll(pollSet, numFDs, 1);
    for(fd_index = 0; fd_index < numFDs; fd_index++)
    {
      if( pollSet[fd_index].revents & POLLIN ) 
      {
        if(pollSet[fd_index].fd == sockFD)
        {
          clientLen = sizeof(clientAddr);
          int clientSockFD = accept(sockFD, (struct sockaddr *)&clientAddr, (socklen_t *)&clientLen);
          pollSet[numFDs].fd = clientSockFD;
          pollSet[numFDs].events = POLLIN;
          numFDs++;
        }
        else 
        {
          ioctl(pollSet[fd_index].fd, FIONREAD, &readResult);
          if( readResult == 0 )
          {
            close(pollSet[fd_index].fd);
            pollSet[fd_index].events = 0;
            int i = fd_index;
            pollSet[i] = pollSet[i + 1];
            numFDs--;
          }
          else 
          {
            server.HandleRequest(pollSet[fd_index].fd);
          }
        }
      }
    }
  }
  close(sockFD);
  return 0;
}
