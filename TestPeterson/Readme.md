# TestPeterson

测试并发线程 Peterson 同步算法

**测试平台**  
处理器 Intel Core i5-7200  
Core x 2  
CPU x 4  
Windows 10 x64 (64bit)  

**编译环境**  
MSVC 9.0

**构建配置**  
x86 Release  
x64 Release  
Optimization: /O2  

## 测试结论

在支持乱序执行技术 (OoOE: Out-of-Order Execution) 的现代 Intel 处理器, 以及支持指令重排优化 (Instruction Reordering Optimization) 的 MSVC 编译器环境下  
想要使用 Peterson 无锁算法进行并发线程同步是一件很困难的事情  
即使测试中使用了 MemoryBarrier 也没有达成同步目标  

这可能有两方面原因:
1. volatile 修饰符的使用有缺失
2. MemoryBarrier 的调用时机有缺失

**Peterson 算法的替代方法**

1. 用处理器提供的原子操作如 Interlock Intrinsic 完成序列化操作 (比如累加)  
   处理器原子操作的效率是最高的, 用户程序无需进入内核态, 序列化过程由处理器实现

2. 用 Critical Section (临界区: 一种内核同步对象) 完成序列化  
   Critical Section 通常比其它内核同步对象 Event, Mutex, Semaphore 的效率高  
   Critical Section 使用 SpinLock + Event on Demand (WinXP+) 的方式实现  
   Critical Section 只限于同一进程内使用, 而 Event, Mutex, Semaphore 可用于多进程间同步

3. 如果自己实现同步锁, 可用 InterlockedExchange Intrinsic 实现 SpinLock (自旋锁)

## 测试结果

**运行参数**  
THREAD_COUNT = 4  
MAX_TEST_ROUND = 500  

x86, x64 的测试结果相同

测试用例 TestThreadAccBaseline

| SyncMode              | Data Race |
| --------------------- | --------- |
| SYNC_NOLOCK           | 高频率    |
| SYNC_CRITICALSECTION  | 从未发生  |
| SYNC_ATOMIC           | 从未发生  |
| SYNC_SPINLOCK         | 从未发生  |

测试用例 TestThreadAccPeterson2

| UseMemoryBarrier      | Data Race |
| --------------------- | --------- |
| false                 | 高频率    |
| true                  | 低频率    |

测试用例 TestThreadAccPetersonN

| UseMemoryBarrier      | Data Race |
| --------------------- | --------- |
| false                 | 高频率    |
| true                  | 中频率    |
