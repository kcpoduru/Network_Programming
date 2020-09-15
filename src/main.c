#include "ip_maths.h"
#include "stdio.h"



int main(int argc, char *argv[])
{
  check(argc == 3, "wrong number of arguments");
  unsigned char buff[4];
  getBroadCastAddress(argv[1] , (unsigned char)atoi(argv[2]), buff);
  for(int i = 0; i < 4 ; i++) logInfo("val is %d " , buff[i]);

  logInfo("ip equivalent = %ld", getIpIntegerEquivalent(argv[1]));

  return 0;
  error:
    return -1;
}
