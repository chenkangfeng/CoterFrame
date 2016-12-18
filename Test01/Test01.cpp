// Test01.cpp : �������̨Ӧ�ó������ڵ㡣
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
        dns->parse(CFINetDNS::kTCP, "www.baidu.com", [](CFINetAddrInfo::SharedPtr&& addr_info){
            if (addr_info && addr_info->size() > 0) {
                for (int i = 0; i < addr_info->size(); ++i) {
                    printf("%s\n", addr_info->at(0)->ip().c_str());
                }
            }
        });
    }

    system("PAUSE");

    return 0;
}
