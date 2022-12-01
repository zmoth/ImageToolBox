cmake_minimum_required(VERSION 3.5)

# 添加版本号
set(PROJECT_VERSION_MAJOR 0) # 主版本号
set(PROJECT_VERSION_MINOR 1) # 子版本号
set(PROJECT_VERSION_PATCH 0) # 阶段版本号
string(TIMESTAMP PROJECT_VERSION_TIME %y%m%d) # 日期版本号
set(PROJECT_VERSION_ALPHABET "alpha")# 希腊字母版本号
set(PROJECT_VERSION  ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TIME})

# 工程名称
project(CXX_DEMO VERSION ${PROJECT_VERSION})
message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}")

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )


#设置输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 静态库的文件夹位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 动态库的文件夹位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 可执行软件的文件夹位置

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)

#这个就是定义各个版本对应的后缀，例如d，debug版本后缀，当然你想定义为其他，	#自己修改这块就可以了。
SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

if(MSVC)
    # 设置MSVC编译编码
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
endif()

include_directories(${PROJECT_BINARY_DIR}) # config.h

# add_subdirectory(3rdparty) # 添加第三方库

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets) # 识别是Qt6还是Qt5
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
message(STATUS "QT_VERSION_MAJOR: ${QT_VERSION_MAJOR}; QT_DIR: ${QT_DIR}")

file(GLOB_RECURSE SRCS  src/*.cpp src/*.cxx src/*.cc)
file(GLOB_RECURSE INCS  src/*.hpp src/*.h)
file(GLOB_RECURSE RES  src/*.qrc src/*.rc src/*.ui)

set(PROJECT_SOURCES ${SRCS} ${INCS} ${RES})

add_executable(${PROJECT_NAME}
    WIN32
    ${PROJECT_SOURCES}
)

# 设置头文件路径
target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
)

# Qt设置
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY
    LIBRARY DESTINATION CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ARCHIVE DESTINATION CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    BUNDLE  DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY
)

# PUBLIC    在public后面的库会被Link到你的target中，并且里面的符号也会被导出，提供给第三方使用。
# PRIVATE   在private后面的库仅被link到你的target中，并且终结掉，第三方不能感知你调了啥库
# INTERFACE 在interface后面引入的库不会被链接到你的target中，只会导出符号。
