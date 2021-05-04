#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <time.h>

#define PROTOCOL_PAYLOAD_SIZE   1024

typedef struct 
{
    uint8_t id;
    time_t data;
    uint32_t size;
    uint8_t payload[PROTOCOL_PAYLOAD_SIZE];
} Protocol;

#endif /* PROTOCOL_H */
