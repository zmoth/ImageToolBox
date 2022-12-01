<h1 align="center">CXX DEMO</h1>

[**中文**](./README.md) | [**English**](./README_EN.md)<br/>

<!-- 目录 -->
# Content
- [Content](#content)
- [Build \& Install](#build--install)
  - [Dependencies](#dependencies)
  - [Build](#build)
- [Example](#example)
- [Origin \& References](#origin--references)

# Build & Install
## Dependencies

Qt 5.15.2

## Build

```bash
git clone --recurse-submodules git@github.com:QianMoth/qt-cmake-project.git
cd nodeeditor-p
mkdir build

# Release
cmake -S . -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Debug
cmake -S . -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```
# Example


# Origin & References
