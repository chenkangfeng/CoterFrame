// Test01.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "cfprecompiled.h"
#include "interface/cfinetdns.h"
#include "network/cfcnetdns.h"
#include "network/cfcnetaddrinfo.h"
#include "network/cfcnetaddr.h"

NS_CF_USING

int _tmain(int argc, _TCHAR* argv[])
{
    CFINetDNS::setupComponent<CFCNetDNS>();
    CFINetAddrInfo::setupComponent<CFCNetAddrInfo>();
    CFINetAddr::setupComponent<CFCNetAddr>();

    CFINetDNS::SharedPtr dns = CFINetDNS::createComponent();
    if (dns) {
        dns->parse(CFINetDNS::kTCP, "192.168.1.101", [](CFINetAddrInfo::SharedPtr&& addr_info){
            for (int i = 0; i < addr_info->size(); ++i) {
                printf("%s\n", addr_info->at(0)->ip().c_str());
            }
        });
    }

    system("PAUSE");

    return 0;
}
