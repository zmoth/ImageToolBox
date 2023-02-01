<h1 align="center">IMAGE TOOLBOX</h1>

<!-- 目录 -->
# Content
- [Content](#content)
- [Introduction](#introduction)
- [Build \& Install](#build--install)
  - [Dependencies](#dependencies)
  - [Build](#build)
- [Example](#example)

# Introduction

ImageToolBox的目标是图像显示界面库，为其它软件提供基本的图像显示界面，包括但不限于放大缩小、像素信息。

# Build & Install
## Dependencies

Qt >= 5.15.2

## Build

```bash
git clone --recurse-submodules https://github.com/QianMoth/ImageToolBox.git
cd ImageToolBox
mkdir build

# Release
cmake -S . -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Debug
cmake -S . -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

# Example

