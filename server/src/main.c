#include <server/server_tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int receive(char *buffer, int size);
static int send(char *buffer, int *size);

int main()
{

  Server_t s = {
    .socket = -1,
    .port = "3404",
    .cb.recv = receive,
    .cb.send = send
  };

  Server_init(&s);

  while(true)
    Server_exec(&s);
}

static int receive(char *buffer, int size)
{
  printf("%s\n", buffer);
  return 0;
}

static int send(char *buffer, int *size)
{
  memset(buffer, 0, MAX_BUFFER_SEND_RECV);
  snprintf(buffer, MAX_BUFFER_SEND_RECV, "Eita");
  *size = strlen("Eita");
  return 0;
}