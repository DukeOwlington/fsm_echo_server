#include "server_routine.h"

int recv_len;
int master_sock;
char buf[BUFLEN];
unsigned int slen;
struct sockaddr_in sender;

int InitializeServer(void) {
  struct sockaddr_in serv_addr;

  /* create a UDP socket */
  if ((master_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    perror("socket");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* bind socket to port */
  if (bind(master_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
    perror("bind");
    return EXIT_FAILURE;
  }

  printf("I live...again...\n");
  return 0;
}

int ReceiveMessage(void) {
  slen = sizeof(sender);
  /* try to receive some data, this is a blocking call */
  if ((recv_len = recvfrom(master_sock, buf, BUFLEN, 0, (struct sockaddr *) &sender,
                           &slen)) == -1) {
      perror("recvfrom");
      return -1;
  }

  /* print details of the client/peer and the data received */
  printf("Received packet from %s:%d\n", inet_ntoa(sender.sin_addr),
          ntohs(sender.sin_port));
  printf("Data: %s\n", buf);

  return 0;
}

int SendMessage(void) {
  /* now reply the client with the same data */
  if (sendto(master_sock, buf, recv_len, 0, (struct sockaddr*) &sender, slen) == -1) {
    perror("sendto");
    return -1;
  }

  printf("Message lock and loaded!\n");
  return 0;
}

int TurnOff(void) {
  close(master_sock);
  return 0;
}
