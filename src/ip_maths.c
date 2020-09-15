#include "ip_maths.h"



static void parseIpToArr(char * ipAddr , unsigned char *ipArr)
{
    unsigned char lenOfIp = 0;
    unsigned char currentLoc = 0;
    char * locOfSubString = NULL;
    check(strlen(ipAddr) < 17 | ipArr != NULL , "wrong ipAddr Length");
    lenOfIp = strlen(ipAddr) + 1;
    locOfSubString = ipAddr;
    for(int i = 0; i < lenOfIp; i++)
    {
      if(ipAddr[i] == '.' || ipAddr[i] == '\0')
      {
          ipAddr[i] = '\0';
          ipArr[currentLoc] = atoi(locOfSubString);
          currentLoc++;
          locOfSubString = &ipAddr[i+1];
      }
    }
error:
  return;
}


void getBroadCastAddress(char * ipAddr , unsigned char mask , unsigned char *outputBuf)
{
  check(mask < 33, "wrong mask value");
  unsigned int maskInt = 0;
  unsigned char maskArr[4] = {0};
  parseIpToArr(ipAddr , outputBuf);
  for(int i = mask ; i >=0 ; i--)
  {
    maskInt = maskInt + pow(2,i);
  }
  maskInt = maskInt << (IP_V4_MAX_SIZE_IN_BITS - mask);
  maskInt = ~maskInt;
  memcpy(maskArr, &maskInt , 4);
  maskArr[0] = (maskInt >> 24) & 0xFF;
  maskArr[1] = (maskInt >> 16) & 0xFF;
  maskArr[2] = (maskInt >> 8) & 0xFF;
  maskArr[3] = (maskInt >> 0) & 0xFF;
  *((uint32_t *)outputBuf) = *((uint32_t *)outputBuf) | *((uint32_t *)maskArr);

  error:
    return;
}


long int getIpIntegerEquivalent(char * ipAddr)
{
  check(ipAddr != NULL , "no ip address provided");
  unsigned char ipArr[4] = {0};
  parseIpToArr(ipAddr , ipArr);
  long int ipDec = (ipArr[0] * pow(256,3)) + (ipArr[1] * pow(256,2)) + (ipArr[2] * pow(256,1)) + (ipArr[3]);
  return(ipDec);

  error:
    return -1;
}
