// Test01.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "cfprecompiled.h"

NS_CF_USING

class Test01 : public CFSharedPtr<Test01>, public CFObject
{
public:
    Test01(int a) {
        printf("%d\n", a);
    }
};

class Test02 : public CFSharedPtr<Test02>
{
public:
    Test02(int b) {
        printf("%d\n", b);
    }
};

CF_INTERFACE(Test03, int)
{
public:
    Test03(int a) {
        printf("Test03 %d\n", a);
    }
};

CF_COMPONENT(Test03, Test04, int)
{
public:
    Test04(int a) : CFComponent(a) {
        printf("Test04\n");
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Test01::SharedPtr a = CFGlobal::create<CFObject, Test01>(1);
    Test02::SharedPtr b = CFGlobal::create<CFObject, Test02>(2);

    Test03::registerComponent<Test04>();
    CF_SHARED_PTR<Test03> c = Test03::createComponent(10);

    system("PAUSE");

    return 0;
}
