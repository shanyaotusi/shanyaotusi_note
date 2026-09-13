参考：
https://www.cnblogs.com/suntroop/articles/18398934
https://blog.csdn.net/LostUnravel/article/details/127076377

源码解压目录：D:/boost_1_92_0
最终输出目录：D:/boost

使用MinGW构建时遇到模块的.cmake缺失的情况：
boost构建过程选择了全部类型，导致其同时构建了32位版本，但是由于安装的MinGW没有包含32位，运行时被跳过了模块的.cmake，导致后续cmake找不到子模块的'<modulel-name>-congfig.cmake'文件
解决方法：指定只构建64位，添加"address-model=64"参数

依赖MPI未安装：
解决方法：
构建前下载好MPI
这里选择下载MSMPI，具体步骤:
访问MS官网：https://learn.microsoft.com/zh-cn/message-passing-interface/microsoft-mpi
下载.msi和.exe后缀的文件，两个都要；
运行.msi下载好SDK，运行.exe下载MPI，
下载好后注意SDK的目录默认在Program Files (x86)下，而MPI在Program Files下；
然后在系统用户目录下，如C:/users/<username>/下修改或增加user-config.jam，注意';'前要留一个空格:
```user-config.jam
using mpi ;
```

安装1.92版本boost时遇到已知的系统构建错误：
关键错误信息：
```powershell
no match: <local-visibility>hidden
```
解决方法：
找到"D:\boost_1_92_0\libs\histogram\build.jam"中第28行：
删除："<local-visibility>hidden"行后重新运行b2构建
参数中去除--build-type=complete，并明确指定 link=static
```powershell
.\b2.exe install --build-dir="D:/boost_1_92_0/build" --prefix="D:/boost"  toolset=gcc address-model=64 link=static runtime-link=shared threading=multi
```