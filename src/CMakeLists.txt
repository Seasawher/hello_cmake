# greetingsという名前の共有ライブラリ（SHARED）を作成する
# 共有ライブラリにはhello.cppとgood_morning.cppが含まれる
add_library(greetings
  SHARED
    hello.cpp
    good_morning.cpp
  )

# greetingsライブラリに対してインクルードディレクトリを設定する
# PUBLIC指定により、このライブラリを利用するターゲットにも同じインクルードディレクトリが適用される
# ${PROJECT_SOURCE_DIR}/includeは、プロジェクトのルートディレクトリからの相対パスでインクルードディレクトリを指定している
target_include_directories(greetings
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
