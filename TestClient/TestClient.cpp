// TestClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Network/CFDNS.h"
#include "Network/CFNetClient.h"
#include <thread>
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

    std::thread threadPool[500];

    for (int i = 0; i < 500; ++i) {
        threadPool[i] = std::thread([&](const CFNetAddr& addr){
            CFNetClient client;
            client.setConnector([&](CFNetObject::SharePtr&& netObject){
                printf("connect\n");
                listObject.push_back(netObject);
                netObject->setReader([&](CFNetMessage&& message){
                    printf("recv %s\n", message.getMessage().c_str());
                });
                netObject->sendMessage("hello world!");
            });
            client.startClient(addr);
            while (true) {
                client.mainLoop();
                Sleep(100);
            }

        }, addr);
    }
    for (int i = 0; i < 500; ++i){
        threadPool[i].join();
    }

	return 0;
}
