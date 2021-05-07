#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <time.h>
#include <sensors.h>

#define PROTOCOL_PAYLOAD_SIZE   1024
#define DEVICE_NAME             16

typedef struct 
{
    uint8_t id;
    Sensors sensor;
    char device[DEVICE_NAME];
    time_t data;
    uint32_t size;
} Header;

typedef struct 
{
    Header header;
    char payload[PROTOCOL_PAYLOAD_SIZE];
} Protocol;

#endif /* PROTOCOL_H */
