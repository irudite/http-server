#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Error: Could not establish a socket");
    exit(1);
  }
  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    printf("Error: Socket could not be bound to address");
    close(sockfd);
    exit(1);
  }

  int max_queue_len = 100;
  if (listen(sockfd, max_queue_len) == -1) {
    printf("Error: Could not listen to any connection");
    close(sockfd);
    exit(1);
  }

  printf("Listening for requests...");

  socklen_t addr_len = sizeof(addr);
  int new_sock = accept(sockfd, (struct sockaddr *) &addr, &addr_len);
  if (new_sock == -1) {
    printf("Error; Could not accept connection");
    exit(1);
  }

  return 0;
}
