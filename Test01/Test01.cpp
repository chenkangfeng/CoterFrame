// Test01.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "cfprecompiled.h"
#include "interface/cfinetdns.h"
#include "network/cfcnetdns.h"
#include "network/cfcnetaddrinfo.h"
#include "network/cfcnetaddr.h"
#include "interface/cfinetclient.h"
#include "network/cfcnetclient.h"
#include "interface/cfinetserver.h"
#include "network/cfcnetserver.h"

NS_CF_USING

int _tmain(int argc, _TCHAR* argv[])
{
    CFINetDNS::setupComponent<CFCNetDNS>();
    CFINetAddrInfo::setupComponent<CFCNetAddrInfo>();
    CFINetAddr::setupComponent<CFCNetAddr>();
    CFINetClient::setupComponent<CFCNetClient>();
    CFINetServer::setupComponent<CFCNetServer>();

    CFINetDNS::SharedPtr dns = CFINetDNS::createComponent();
    if (dns) {
        dns->parse(CFINetDNS::kTCP, "127.0.0.1", [](CFINetAddrInfo::SharedPtr&& addr_info){
            if (addr_info && addr_info->size() > 0) {
                for (int i = 0; i < addr_info->size(); ++i) {
                    printf("%s\n", addr_info->at(i)->ip().c_str());
                    CFINetClient::SharedPtr client = CFINetClient::createComponent();
                    if (client) {
                        client->start(addr_info->at(i), [](void){
                        });
                    }
                    CFINetServer::SharedPtr server = CFINetServer::createComponent(8);
                    if (server) {
                        server->start(addr_info->at(i), [](void){

                        });
                    }
                }
            }
        });
    }

    system("PAUSE");

    return 0;
}
