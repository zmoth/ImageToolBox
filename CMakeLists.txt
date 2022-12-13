cmake_minimum_required(VERSION 3.5)

# 添加版本号
set(PROJECT_VERSION_MAJOR 0) # 主版本号
set(PROJECT_VERSION_MINOR 0) # 子版本号
set(PROJECT_VERSION_PATCH 1) # 阶段版本号
string(TIMESTAMP PROJECT_VERSION_TIME %y%m%d) # 日期版本号
set(PROJECT_VERSION_ALPHABET "alpha") # 希腊字母版本号
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TIME})

# 工程名称
project(imagetoolbox VERSION ${PROJECT_VERSION})
message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}")

get_directory_property(_has_parent PARENT_DIRECTORY)

if(_has_parent)
  set(is_root_project OFF)
else()
  set(is_root_project ON)
endif()

set(PROJECT_DEVELOPER_DEFAULTS "${is_root_project}" CACHE BOOL "Turns on default settings for development")

option(BUILD_TESTING "Build tests" "${PROJECT_DEVELOPER_DEFAULTS}")
option(BUILD_EXAMPLES "Build Examples" "${PROJECT_DEVELOPER_DEFAULTS}")
option(BUILD_DOCS "Build Documentation" "${PROJECT_DEVELOPER_DEFAULTS}")

if(MSVC)
  # 设置MSVC编译编码
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
endif()

if(is_root_project)
  # 加入一个配置头文件，用于处理 CMake 对源码的设置
  configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
  )

  # 设置输出路径
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 静态库的文件夹位置
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 动态库的文件夹位置
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 可执行软件的文件夹位置

  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)

  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)

  # 这个就是定义各个版本对应的后缀，例如d，debug版本后缀，当然你想定义为其他，	#自己修改这块就可以了。
  SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
  SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
  SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
  SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

  include_directories(${PROJECT_BINARY_DIR}) # config.h
endif()

# add_subdirectory(3rdparty) # 添加第三方库
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets) # 识别是Qt6还是Qt5
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
message(STATUS "QT_VERSION_MAJOR: ${QT_VERSION_MAJOR}; QT_DIR: ${QT_DIR}")

file(GLOB_RECURSE CPP_SOURCE_FILES src/*.cpp src/*.cxx src/*.cc)
file(GLOB_RECURSE CPP_INCLUDE_FILES include/*.hpp include/*.h)
file(GLOB_RECURSE RESOURCES src/*.qrc src/*.rc)

set(PROJECT_SOURCES ${CPP_SOURCE_FILES} ${CPP_INCLUDE_FILES} ${RESOURCES})

# 制作动态库
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

# 支持动态库和静态库同时存在
set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 设置头文件路径
target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/toolbox/internal>
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
)

# 编译选项
target_compile_definitions(${PROJECT_NAME}
  PUBLIC
  PROJECT_DLL_SHARED
  PRIVATE
  PROJECT_DLL_EXPORTS
)

if(is_root_project)
  INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY
    LIBRARY DESTINATION CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ARCHIVE DESTINATION CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    BUNDLE DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY
  )
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
