////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文  件: Spinlock.h
// 说  明:
//   自旋锁
//   基于 x86, x64 处理器的 _InterlockedExchange 原子操作
//
// 版  本: 1.0
// 作  者: Breaker Zhao <breakerzhao@qq.com>
// 日  期: 2011.10
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
        SPIN_FREE   = 0,    // 必须是 0, 以便 Lock() 中的 _InterlockedExchange 返回 0
        SPIN_HOLD   = 1
    };

private:
    // 禁止拷贝
    Spinlock(const Spinlock&);
    Spinlock& operator=(const Spinlock&);

public:
    // CAUTION:
    // 用户负责在单线程启动阶段将 *slot 初始化为 SPIN_FREE (0)
    static void InitSpinSlot(_Inout_ volatile long* slot)
    {
        _ASSERTE(slot != NULL);
        *slot = SPIN_FREE;
    }

    // 参数
    // slot     用户提供的 SpinSlot
    // owner    是否在构造 Spinlock 对象时加锁
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
