# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

# プロジェクト名と使用する言語を設定
project(test_cmake CXX)

# サブディレクトリを登録
add_subdirectory(src)
add_subdirectory(test)
