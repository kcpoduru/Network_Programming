#include "ip_maths.h"



static void parseIpToArr(char * ipAddress , unsigned char *ipArr)
{
    unsigned char lenOfIp = 0;
    unsigned char currentLoc = 0;
    char * locOfSubString = NULL;
    char * ipAddr;
    check(strlen(ipAddress) < 17 | ipAddress != NULL , "wrong ipAddr Length");
    lenOfIp = strlen(ipAddress) + 1;
    ipAddr = (char *)malloc(lenOfIp);
    checkMem(ipArr!=NULL);
    strcpy(ipAddr, (const char *)ipAddress);
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
    free(ipAddr);
    return;
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

void getAbcdIpFormat(unsigned int ipAddress , char *outputBuf)
{
  char oct = 0;
  char outBuf[4] = {0};
  for(int i = 3; i >= 0; i--)
  {
    oct = ipAddress/(pow(256,i));
    ipAddress = ipAddress - (oct* pow(256,i));
    outBuf[3-i] = oct;
  }
  sprintf(outputBuf,"%hu%c%hu%c%hu%c%hu",outBuf[0],'.',outBuf[1],'.',outBuf[2],'.',outBuf[3]);
}


void getNetworkId(char * ipAddr , unsigned char mask , unsigned char *outputBuf)
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
  maskArr[0] = (maskInt >> 24) & 0xFF;
  maskArr[1] = (maskInt >> 16) & 0xFF;
  maskArr[2] = (maskInt >> 8) & 0xFF;
  maskArr[3] = (maskInt >> 0) & 0xFF;
  *((uint32_t *)outputBuf) = *((uint32_t *)outputBuf) & *((uint32_t *)maskArr);
  return;
  error:
    return;
}

unsigned char getSubnetCardinality(char mask)
{
  check(mask < 33, "wrong mask value");
  unsigned int maskInt = 0;
  for(int i = mask ; i >=0 ; i--)
  {
    maskInt = maskInt + pow(2,i);
  }
  maskInt = maskInt << (IP_V4_MAX_SIZE_IN_BITS - mask);
  maskInt = ~maskInt;
  if(maskInt == 0) return 0;
  return((unsigned char)maskInt - NETWORK_ID_PLUS_BROADCAST_ID);

  error:
    return 0;
}


int checkIpSubnetMembership( char * networkId , char mask , char *checkIp)
{
  unsigned char outputBuf[17] = {0};
  char tempBuf[17] = {0};
  check(networkId !=NULL | mask < 33 | checkIp !=NULL , "invalid input");
  getNetworkId(checkIp , mask , outputBuf);
  sprintf(tempBuf,"%hu%c%hu%c%hu%c%hu",outputBuf[0],'.',outputBuf[1],'.',outputBuf[2],'.',outputBuf[3]);
  if(strcmp(networkId, (const char *)tempBuf)!=0) return -1;
  else return 0;
  error:
    return -1;

}
