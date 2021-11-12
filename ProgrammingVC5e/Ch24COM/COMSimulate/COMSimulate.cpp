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

    // �õ�ȫ�ֳ����� CSpaceshipFactory g_factory �� IClassFactory �ӿڣ����������ɺ�
    // ��g_factory ��������Ϊ 2��������Ϊȫ�ֶ���g_factory�ڳ����ʼ��ʱ�����Ѿ�
    // ���ڣ����Ѿ�ִ�й����Ĺ��캯������ʱ�����������Ѿ���1
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

    // ִ�������������ȫ�ֳ����� g_factory ���������ָ��������ʼ��ʱ���1
    pClf->Release();

    // ִ������3���������� g_factory ������ CSpaceship�������������Ϊ0�����������������
    pUnk->Release();
    pMot->Release();
    pVis->Release();

    return 0;
}
