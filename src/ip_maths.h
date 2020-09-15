#ifndef IP_MATHS_HEADER
#define IP_MATHS_HEADER

#include "dbg.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define IP_V4_MAX_SIZE_IN_BITS                32
#define NETWORK_ID_PLUS_BROADCAST_ID          ((unsigned int)2)

void getBroadCastAddress(char * ipAddr , unsigned char mask , unsigned char *outputBuf);
long int getIpIntegerEquivalent(char * ipAddr);
void getAbcdIpFormat(unsigned int ipAddress , char *outputBuf);
void getNetworkId(char * ipAddr , unsigned char mask , unsigned char *outputBuf);
unsigned char getSubnetCardinality(char mask);
int checkIpSubnetMembership( char * networkId , char mask , char *checkIp);


#endif
