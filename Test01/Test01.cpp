// Test01.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "cfprecompiled.h"
#include "interface/cfinetaddr.h"
#include "network/cfcnetaddr.h"

NS_CF_USING

int _tmain(int argc, _TCHAR* argv[])
{
    CFINetAddr::registerComponent<CFCNetAddr>();
    CF_SHARED_PTR<CFINetAddr> addr = CFINetAddr::createComponent();
    if (addr)
    {
        addr->set_family(AF_INET);
        addr->set_ip("127.0.0.1");
        printf("%s\n", addr->ip().c_str());
    }

    system("PAUSE");

    return 0;
}
