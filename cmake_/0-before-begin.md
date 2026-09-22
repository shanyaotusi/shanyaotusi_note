1 下载官方的教程练习
2 下载cmake，并添加到环境变量path

3 cmake生成器
    cmake本身只是配置程序，不负责运行构建命令，需要用户配置各种信息；
    需要下载支持的构建系统如makefiles, Ninja, Visual Studio
    运行 'cmake --help' 可以在 'Generators' 专题找到当前平台下支持的构建系统（生成器）：
```sh
Generators

The following generators are available on this platform (* marks default):
  Visual Studio 18 2026        = Generates Visual Studio 2026 project files.
                                 Use -A option to specify architecture.
  Visual Studio 17 2022        = Generates Visual Studio 2022 project files.
                                 Use -A option to specify architecture.
...
```
所使用的生成器可以通过 CMAKE_GENERATOR 环境变量或 cmake -G 选项进行控制。比如：
```sh
# 使用Mingw
cmake -G "MinGW32 Makefiles"
# 使用Ninja
cmake -G Ninja
```
运行cmake完成配置后就可以根据使用的构建系统运行相应的构建命令了，如：
```sh
# 使用Mingw
Mingw32-make
# 使用Ninja
ninja
```
或者使用 'cmake --build <dir>'，在指定的目录下运行构建命令，具体用法见下方
构建类型的设置
```sh
cmake --DCMAKE_BUILD_TYPE=<config> # 使用单配置生成器时，指定构建类型
cmake --build --config # 使用多配置构建器时，指定构建配置
```
其他命令
```sh
cmake -S <dir> # 指定项目根目录
cmake -B <dir> # 指定构建目录，在该目录下输出构建系统的文件和构建产物
cmake --build <dir> # 在该目录中运行构建系统，适配所有生成器，多配置生成器需要加上 --config <cfg> 选项
```

不同的生成器之间不能重用构建目录，需要切换不同的生成器之前需要删除之前的构建目录