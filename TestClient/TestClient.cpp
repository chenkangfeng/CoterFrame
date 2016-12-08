// TestClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Network/CFDNS.h"
#include "Network/CFNetClient.h"

NS_CF_USING

int _tmain(int argc, _TCHAR* argv[])
{
    CFNetAddrInfo addrInfo;
    CFDNS::parse(CFDNS::TCP, "127.0.0.1", addrInfo);

    CFNetAddr addr = addrInfo[0];
    printf("%s\n", addrInfo[0].getIp().c_str());
    addr.setPort(1234);

    CFNetClient client;
    client.initClient(addr);

	return 0;
}
