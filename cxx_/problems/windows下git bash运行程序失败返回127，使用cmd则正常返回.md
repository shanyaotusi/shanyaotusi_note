# windows下git bash运行程序失败返回127，使用cmd则正常返回

在测试一个需要输入参数的cpp时，运行输入参数无论数量正常还是异常都显示异常退出，编译期也无报错：

```bash
rm -f cm.exe &&
g++ compress.cpp -o cm.exe -g -Wall -std=c++17 &&
./cm.exe in.txt out.huf; echo EXIT:$?
EXIT:127
```

但是使用clang++编译后就可以正常运行：
```bash
clang++ compress.cpp -o cmp -g -Wall -std=c++17

# normal output
./cmp in.txt out
argc=3
compress file: in.txt to out
0
0
...
```

ai的解释是
```
在 cmd 里，cm.exe 直接被 Windows PE loader 执行，通常能跑起来
在 bash 里，cm.exe 需要先由 MSYS/Git Bash 做一层路径/环境翻译
如果当前目录、PATH、文件名或可执行权限没有对上，就会直接返回 127
127 在 shell 语义里通常表示“命令没找到/不能执行”，不是 C++ 程序自己 return 127;

最常见的原因有两种：

clang++ 生成的是原生 Windows exe

这种情况下，Git Bash 也通常能直接启动
只要当前目录和路径正确，./a.exe 之类都能跑
但你的 g++ 生成的程序，或者你当前用的 bash 解析/调用方式，存在兼容性问题

例如：
产物不是标准 Windows PE 可执行文件
依赖 MSYS runtime / MinGW runtime 的加载方式不同
bash 不能正确加载它
这时候就会出现：
./xxx.exe 直接失败
但在 cmd 里能跑
```
