#ifndef PACKET_STR_H
#define PACKET_STR_H

#endif // PACKET_STR_H

#include <stdint.h>

typedef struct
{
    uint8_t d_mac[6];
    uint8_t s_mac[6];
    uint16_t e_type;
}Ethernet;

typedef struct
{
    uint8_t VHL;
    uint8_t TOS;
    uint16_t total_len;
    uint16_t id;
    uint16_t fragment;
    uint8_t TTL;
    uint8_t protocol;
    uint16_t checksum;
    uint8_t src[4];
    uint8_t dest[4];
}Ip;

typedef struct
{
    uint8_t s_port[2];
    uint8_t d_port[2];
    uint32_t seq;
    uint32_t ack;
    uint8_t HLR;
    uint8_t flags;
    uint16_t win_size;
    uint16_t checksum;
    uint16_t urg_pointer;
}Tcp;

