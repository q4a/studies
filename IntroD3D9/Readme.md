DirectX 9.0 3D 游戏开发编程基础 译者 段菲 (2007.4)  
<https://book.douban.com/subject/2111771/>  
Introduction to 3D Game Programming with DirectX 9.0c: A Shader Approach, by Frank D. Luna (2006.6)  
<https://www.amazon.com/dp/1598220160/>

作者 Frank D. Luna 维护的配书网站 [d3dcoder.net](https://d3dcoder.net/)

示例练习代码

对原示例代码的修改：

1. 将配书代码的 Win32 程序改为 MFC 程序

2. 将原公共代码 d3dUtility.h/.cpp 改为 OOD 的 DLL 程序 SGL  
   SGL 对 MFC/ATL 的依赖是 Header-only 的，即不依赖 MFC DLL/LIB，所以用户程序可以不是 MFC 程序
