# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

# プロジェクト名と使用する言語を設定
project(test_cmake CXX)

# GREETINGS_BUILD_SHARED_LIBSというオプションを作成。デフォルトをOFFに設定。
option(GREETINGS_BUILD_SHARED_LIBS "build greetings as a shared library" OFF)

# hello.cppとgood_morning.cppをコンパイルしてライブラリlibgreetings.aを作成
if (GREETINGS_BUILD_SHARED_LIBS)
  add_library(greetings SHARED hello.cpp good_morning.cpp)
else()
  add_library(greetings STATIC hello.cpp good_morning.cpp)
endif()

# a.outという実行ファイルをmain.cppとhello.cppから作成
add_executable(a.out main.cpp hello.cpp)

# a.outを作成する際にlibgreetings.aをリンク
target_link_libraries(a.out greetings)