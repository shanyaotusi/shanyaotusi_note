1 cmake_minimum_require(VERSION 3.20) 根CML的第一个命令；
2 project() 参数是项目名称；
3 add_executable() 用于创建目标文件的文件名称；
4 target_source(<target-name>
    PRIVATE
        main.cxx
)
    将需要构建和链接的源文件与目标关联，
    第二各参数是作用域关键字，描述属性如何由目标的依赖项继承,
    此处描述main.cxx只属于本项目，不可继承；

5 add_library() 创建库，与add_executable()类比；
6 
```CMakeLists.txt
target_source(<library-name>
    PRIVATE
        library_implement.cxx

    PUBLIC
        FLIE_SET myHeaders
        TYPE HEADERS
        BASE_DIRS
            include
        FILES
            include/library_headers.h
)
```

    FLIE_SET <name> 这个名字用于在其他上下文中描述该集合
    TYPE <type> 描述的文件的类型
    BASE_DIRS 文件的基础位置
    FILES 文件列表，与源文件列表相同

    如果FLIE_SET名称与类型相同，就不需要提供TYPE字段，

```CMakeLists.txt
    FILE_SET myHeaders
    TYPE HEADERS
    #可以替换为：
    FILE_SET HEADERS
```

7 add_subdirectory() 添加子目录




