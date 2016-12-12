// TestServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Network/CFDNS.h"
#include "Network/CFNetServer.h"
#include <list>

NS_CF_USING

int _tmain(int argc, _TCHAR* argv[])
{
    CFNetAddrInfo addrInfo;
    CFDNS::parse(CFDNS::TCP, "127.0.0.1", addrInfo);

    CFNetAddr addr = addrInfo[0];
    printf("%s\n", addrInfo[0].ip().c_str());
    addr.setPort(1234);

    std::list<CFNetObject::SharePtr> listObject;
    CFNetServer server(8);
    server.setAcceptor([&](CFNetObject::SharePtr&& netObject){
        printf("accept %s %d\n", netObject->netAddr().ip().c_str(), listObject.size());
        listObject.push_back(netObject);
        netObject->setReader([&](CFNetMessage&& message){
            printf("recv %s\n", message.getMessage().c_str());
        });
        netObject->sendMessage("thanks!");
    });
    server.startServer(addr);

    while (true) {
        server.mainLoop();
        Sleep(100);
    }

	return 0;
}
