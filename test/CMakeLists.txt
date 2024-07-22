# a.outという名前の実行可能ファイルを作成する
add_executable(a.out main.cpp)

# a.outをコンパイルする際にgreetingsをリンクする
# これにより、a.outがgreetingsライブラリの機能を利用できるようになる
target_link_libraries(a.out greetings)
