#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <syslog.h>
#include <server/udp.h>
#include <protocol.h>

#define BUFFER_SIZE 1024

void on_receive_message(const char *buffer, size_t buffer_size, void *data);

int main(int argc, char *argv[])
{   
    char server_buffer[BUFFER_SIZE];

    UDP_Server server = 
    {
        .buffer = server_buffer,
        .buffer_size = BUFFER_SIZE,
        .port = 1234,
        .on_receive_message = on_receive_message
    };

    UDP_Server_Init(&server);

    while(true)
	{
		UDP_Server_Run(&server, NULL);
	}
    
    return 0;
}

bool Init(void *object)
{
    (void)object; 
    return true;
}

void on_receive_message(const char *buffer, size_t buffer_size, void *data)
{
  // Protocol protocol;
  // memset(&protocol, 0, sizeof(protocol));

  // memcpy(&protocol, buffer, sizeof(protocol));

  
  // printf("ID: %d\n", protocol.header.id);
  // printf("Device: %s\n", protocol.header.device);
  // printf("Sensor: %d\n", protocol.header.sensor);
  // printf("Epoch: %d\n", protocol.header.data);
  // printf("Size: %d\n", protocol.header.size);
  // printf("Payload: %s\n", protocol.payload);  

  printf("%s\n", buffer);
}