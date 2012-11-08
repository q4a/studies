// COMSimulate.cpp
//

#include "StdAfx.h"
#include "interface.h"

int _tmain(int argc, _TCHAR* argv[])
{
    TRACE("Entering client main\n");
    IUnknown* pUnk; // if you declare these void*, you lose type-safety
    IMotion* pMot;
    IVisual* pVis;
    IClassFactory* pClf;

    // 得到全局厂对象 CSpaceshipFactory g_factory 的 IClassFactory 接口，这个操作完成后，
    // 对g_factory 的引用数为 2，这是因为全局对象g_factory在程序初始化时，就已经
    // 存在，即已经执行过它的构造函数，那时它的引用数已经是1
    GetClassObject(CLSID_CSpaceship, IID_IClassFactory, (void**) &pClf);

    pClf->CreateInstance(IID_IUnknown, (void**) &pUnk);
    pUnk->QueryInterface(IID_IMotion, (void**) &pMot);
    pMot->QueryInterface(IID_IVisual, (void**) &pVis);

    TRACE("main: pUnk=%p, pMot=%p, pDis=%p\n", pUnk, pMot, pVis);

    // test all the interface virtual functions
    pMot->Fly();
    int nPos = pMot->GetPosition();
    TRACE("nPos = %d\n", nPos);
    pVis->Display();

    // 执行完这个操作后，全局厂对象 g_factory 的引用数恢复到程序初始化时候的1
    pClf->Release();

    // 执行完这3个操作后，由 g_factory 产生的 CSpaceship对象的引用数变为0，并将这个对象析构
    pUnk->Release();
    pMot->Release();
    pVis->Release();

    return 0;
}
