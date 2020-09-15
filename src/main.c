#include "ip_maths.h"
#include "stdio.h"



int main(int argc, char *argv[])
{
  check(argc == 4, "wrong number of arguments");
  unsigned char buff[17];
  // getNetworkId(argv[1] , (unsigned char)atoi(argv[2]), buff);
  // for(int i = 0; i < 4 ; i++) logInfo("val is %d " , buff[i]);
  // unsigned char card  = getSubnetCardinality(atoi(argv[2]));
  // logInfo("cardinality is = %u ", card);
  //logInfo("ip equivalent = %ld", getIpIntegerEquivalent(argv[1]));
  //getAbcdIpFormat(getIpIntegerEquivalent(argv[1]) , buff);
  //logInfo("ip addr %s" , buff);
  int ret = checkIpSubnetMembership(argv[1] , atoi(argv[2]) , argv[3]);
  logInfo("membership = %d", ret);
  return 0;
  error:
    return -1;
}
