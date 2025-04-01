# LevelGenerator
毕业设计程序。生成roguelike地下城式关卡。

# Env

IDE: Microsoft Visual Studio 2022

OS: Windows 10

language: c++17

# vendor

## GGL

url: https://www.tbi.univie.ac.at/software/GGL/

### debug

不知道是因为开发环境不同还是什么原因，我在使用GGL的时候出了一些bug.

#### 丢失const-volatile

bug描述: MSVC编译错误，C3848, 丢失const-volatile.

debug: 在发生错误的模板匹配处加`const`.

#### minus unsigned

bug描述: 对size_t类型的变量使用`-`操作符

debug: 把相关类型从`size_t`改为`int`.

#### end_iter ++

bug描述: 如果应用(apply)的规则(rule)导致要删除边(edge)，抛出end迭代器`++`的异常。

debug: `MR_ApplyRule.cc` line590 处遍历并删除边(edge)，添加逻辑：找到并删除`edge`后，`break`跳出循环。

#### vector iterator incompatible

bug描述: 调用`Graph_Interface`的`==`重载的时候(具体来说是调用`edge descriptors`的`!=`)，抛异常(`vector iterator incompatible`)。该bug使相关类的`==`和`!=`调用异常。我则是在`Pattern_Interface`上调用异常。

debug: 修改`Graph_Interface::operator==()`中，对于边(edge)的检测。file:Graph_Interface.hh line 50

## opencv

url: https://opencv.org/

将opencv的头文件放在 `./Dependence/include` 目录下。

将`opencv_worldxxxx.lib`和`opencv_worldxxxxd.lib`放在`./Dependence/bin/opencv2`目录下。

将`opencv_worldxxxx.dll`放在`.\Bin\Release\x64`.

将`opencv_worldxxxxd.dll`放在`.\Bin\Release\x64`.

## boost

url: https://www.boost.org/

每个项目为boost配置include路径

