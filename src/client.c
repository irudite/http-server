#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

int main (int argc, char **argv) {
  (void) argc;
  (void) argv;

  printf("Creating socket\n");
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Error: %s\n", strerror(errno));
    exit(errno);
  }

  struct sockaddr_in addr = {AF_INET, htons(PORT), INADDR_ANY};

  printf("Connecting to server\n");
  if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    printf("Error: %s\n", strerror(errno));
    close(sockfd);
    exit(errno);
  }

  char *message = "Fuck me in the ass!";
  if (send(sockfd, message, sizeof(message), 0) == -1) {
    printf("Error: %s\n", strerror(errno));
  }

  close(sockfd);
}
