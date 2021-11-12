// spaceship.h
//

#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

class CSpaceship;

class CSpaceshipFactory : public CSimulatedCmdTarget {
public:
    CSpaceshipFactory() {
        TRACE("Entering CSpaceshipFactory ctor %p\n", this);
    }

    ~CSpaceshipFactory() {
        TRACE("Entering CSpaceshipFactory dtor %p\n", this);
    }

    BOOL ExternalQueryInterface(int nIid, void** ppvObj);

    class XClassFactory : public IClassFactory {
    public:
        XClassFactory() {
            TRACE("Entering XClassFactory ctor %p\n", this);
        }

        virtual BOOL QueryInterface(int nIid, void** ppvObj);
        virtual DWORD Release();
        virtual DWORD AddRef();
        virtual BOOL CreateInstance(int nIid, void** ppvObj);

    } m_xClassFactory;

    friend class XClassFactory;
};

class CSpaceship : public CSimulatedCmdTarget {
private:
    int m_nPosition;
    int m_nAcceleration;
    int m_nColor;

public:
    CSpaceship() {
        TRACE("Entering CSpaceship ctor %p\n", this);
        m_nPosition = 100;
        m_nAcceleration = 101;
        m_nColor = 102;
    }

    ~CSpaceship() {
        TRACE("Entering CSpaceship dtor %p\n", this);
    }

    BOOL ExternalQueryInterface(int nIid, void** ppvObj);

    class XMotion : public IMotion {
    public:
        XMotion() {
            TRACE("Entering XMotion ctor %p\n", this);
        }

        // IUnknown
        virtual BOOL QueryInterface(int nIid, void** ppvObj);
        virtual DWORD Release();
        virtual DWORD AddRef();

        // IMotion
        virtual void Fly();
        virtual int& GetPosition();
    } m_xMotion;

    class XVisual : public IVisual {
    public:
        XVisual() {
            TRACE("Entering XVisual ctor %p\n", this);
        }

        // IUnknown
        virtual BOOL QueryInterface(int nIid, void** ppvObj);
        virtual DWORD Release();
        virtual DWORD AddRef();

        // IVisual
        virtual void Display();
    } m_xVisual;

    friend class XVisual;
    friend class XMotion;
    friend class CSpaceshipFactory::XClassFactory;
};

#endif  // __SPACESHIP_H__
