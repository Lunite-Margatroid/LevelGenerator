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

不知道是因为开发环境不同还是什么，我在使用的时候出了一些bug.

#### 丢失const-volatile

在发生错误的模板匹配处加`const`.

#### minus unsigned

把相关类型从`size_t`改为`int`.

#### end_iter ++

`MR_ApplyRule.cc`。如果应用的规则中含有删除边的规则时，抛异常。

此处遍历特定顶点的`out edge`。

添加逻辑：找到并删除`edge`后，`break`跳出循环。

## opencv

url: https://opencv.org/

将opencv的头文件放在 `./Dependence/include` 目录下。

将`opencv_worldxxxx.lib`和`opencv_worldxxxxd.lib`放在`./Dependence/bin/opencv2`目录下。

将`opencv_worldxxxx.dll`放在`.\Bin\Release\x64`.

将`opencv_worldxxxxd.dll`放在`.\Bin\Release\x64`.

## boost

url: https://www.boost.org/

每个项目为boost配置include路径

