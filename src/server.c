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

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;

  printf("Creating socket\n");
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Error: %s\n", strerror(errno));
    exit(errno);
  }
  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
  
  printf("Binding socket\n");
  if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    printf("Error: %s\n", strerror(errno));
    close(sockfd);
    exit(errno);
  }

  printf("Listening to socket\n");
  int max_queue_len = 100;
  if (listen(sockfd, max_queue_len) == -1) {
    printf("Error: %s\n", strerror(errno));
    close(sockfd);
    exit(errno);
  }

  socklen_t addr_len = sizeof(addr);
  printf("Accepting connection\n");
  int new_sock = accept(sockfd, (struct sockaddr *) &addr, &addr_len);
  if (new_sock == -1) {
    printf("Error: Could not accept connection");
    exit(errno);
  }

  printf("Accepted connection\n");

  printf("Reading request\n");
  char buffer[1024];
  ssize_t bytes_returned = read(new_sock, buffer, sizeof(buffer));
  if (bytes_returned == -1) {
    printf("Error: %s\n", strerror(errno));
    exit(errno);
  }

  printf("Message received: %s\n", buffer);

  return 0;
}
