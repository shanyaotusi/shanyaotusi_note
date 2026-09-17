# cmake 学习笔记
参考官方教程：https://cmake.com.cn/cmake/help/latest/guide/tutorial

官方练习：
./cmake-4.3.0-tutorial-source

cmake cl 参数：
```sh
# 0
cmake -G <generator> # 指定生成器
cmake --DCMAKE_BUILD_TYPE=<config> # 使用单配置生成器时，指定构建类型
cmake --build --config # 使用多配置构建器时，指定构建配置

cmake -S <dir> # 指定项目根目录
cmake -B <dir> # 指定构建目录，在该目录下输出构建系统的文件和构建产物
cmake --build <dir> # 在该目录中运行构建系统，多配置生成器需要加上 --config <cfg> 选项
```