////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��  ��: Spinlock.h
// ˵  ��:
//   ������
//   ���� x86, x64 �������� _InterlockedExchange ԭ�Ӳ���
//
// ��  ��: 1.0
// ��  ��: Breaker Zhao <breakerzhao@qq.com>
// ��  ��: 2011.10
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class Spinlock
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Spinlock
{
private:
    volatile long*  m_SpinSlot;

public:
    enum SPIN_STATE
    {
        SPIN_FREE   = 0,    // ������ 0, �Ա� Lock() �е� _InterlockedExchange ���� 0
        SPIN_HOLD   = 1
    };

private:
    // ��ֹ����
    Spinlock(const Spinlock&);
    Spinlock& operator=(const Spinlock&);

public:
    // CAUTION:
    // �û������ڵ��߳������׶ν� *slot ��ʼ��Ϊ SPIN_FREE (0)
    static void InitSpinSlot(_Inout_ volatile long* slot)
    {
        _ASSERTE(slot != NULL);
        *slot = SPIN_FREE;
    }

    // ����
    // slot     �û��ṩ�� SpinSlot
    // owner    �Ƿ��ڹ��� Spinlock ����ʱ����
    Spinlock(_Inout_ volatile long* slot, bool owner = true) : m_SpinSlot(slot)
    {
        _ASSERTE(slot != NULL);
        if (owner)
            Lock();
    }

    ~Spinlock()
    {
        if (!m_SpinSlot)
            Unlock();
    }

public:
    void Lock()
    {
        while (_InterlockedExchange(m_SpinSlot, SPIN_HOLD))
            YieldProcessor();
    }

    void Unlock()
    {
        _InterlockedExchange(m_SpinSlot, SPIN_FREE);
    }
};
