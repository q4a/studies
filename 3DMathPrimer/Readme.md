3D 数学基础：图形与游戏开发 译者 史银雪 陈洪 王荣静 (2005.7)  
<https://book.douban.com/subject/1400419/>  
3D Math Primer for Graphics and Game Development, by Fletcher Dunn, Ian Parberry (2002.6)  
<https://www.amazon.com/dp/1556229119/>

配书网站 [Video Game Math](http://gamemath.com/)  
包含 勘误表、示例代码（一个小型 3D Toolkit 和一个 3D Viewer）、示例所用的 S3D 模型格式说明，以及 3ds Max 4 的 S3D 模型导出插件

示例练习代码

对原示例代码的修改：

1. 将公共代码改为 DLL 程序 MyEngine

2. MyEngine 涉及本书的主要内容，即 3D Math 功能：  
   矩阵变换、欧拉角、四元数和 AABB 外接体等  
   功能类似于 D3DXMath (DX7+)、XNAMath (DX11+)、DirectXMath (DX in Win8 SDK) 等数学库  
   MyEngine 基于 D3D8 进行图形渲染

3. MyViewer 是一个基于 MyEngine 的简单模型查看器，附带一个沙发的 S3D 模型  
   将其改为窗口模式，以及从命令行指定 S3D 模型：  
   MyViewer AR_COUCH.s3d
