# README

元ネタの記事：[Qiita/CMakeの使い方(その１)](https://qiita.com/shohirose/items/45fb49c6b429e8b204ac)

## ステップ１：実行ファイルを作成

`g++` はC++のプログラムをコンパイルするためのツール。`g++` は次の仕事をやってくれる。

* コードのコンパイル：コードを機械が実行可能な形に変えて実行ファイルを作る。
* リンク：ソースファイル同士をつなげて、必要なライブラリと結びつける。オブジェクトファイルを結合したり、ライブラリと結合したり、関数や変数の名前解決を行ったりする。

### コマンドラインからビルド

オブジェクトファイルを生成する場合は以下のようになる。

```bash
g++ -c main.cpp hello.cpp # ソースファイルをコンパイルしてオブジェクトファイル（main.o, hello.o）を生成
g++ -o a.out main.o hello.o # オブジェクトファイルをリンクしてa.outという実行ファイルを生成
```

オブジェクトファイルを経由しない場合は次のようになる。

```bash
# オブジェクトファイルは生成されず、直接実行ファイルが作られる
# 実行ファイルの名前は特に指定しなければ `a.out` になる
g++ main.cpp hello.cpp
```

```bash
# 実行ファイルの名前を指定したい場合は `-o` オプションを使う
g++ -o a.out main.cpp hello.cpp
```

### CMakeを使ってみる

```bash
# -S はソースディレクトリを指すオプション
# -B はビルドディレクトリを指すオプション
# このコマンドにより `build` ディレクトリの中にビルド設定を生成する
cmake -S . -B build

# build ディレクトリの設定に基づいて実際にビルドを行う
cmake --build build
```

## ステップ２：静的・共有ライブラリを作成

* 静的ライブラリ：プログラムを作るときに、その中にコードを「くっつける」ものが静的ライブラリと呼ばれる。`.a` や `.lib` という名前がついている。
* 共有ライブラリ：プログラムが実行されるときに、自動で読み込まれるもの。`.so` や `.dll` という名前がついている。

### コマンドラインからビルド

コマンドなし

#### 静的ライブラリを作成

```bash
# オブジェクトファイル(hello.o, good_morning.o)の作成
g++ -c hello.cpp good_morning.cpp

# ar コマンドを使って、hello.o と good_morning.o のオブジェクトファイルを libgreetings.a という名前の静的ライブラリにまとめる
# -r オプションはファイルを追加または置き換え、-v は詳細な出力を表示、-s はインデックスを作成する
# ar コマンドは、アーカイブファイルを作ったり操作したりするためのツール。
# アーカイブファイルとは、複数のファイルをひとつにまとめたもので静的ライブラリとして扱われる。
ar rvs libgreetings.a hello.o good_morning.o

# main.cppをコンパイルしてlibgreetings.aとリンクし実行ファイルa.outを作成
g++ main.cpp libgreetings.a
```

#### 共有ライブラリを作成

```bash
# オブジェクトファイル(hello.o, good_morning.o)の作成
# -fPIC オプション: Position Independent Code（位置独立コード）を生成するためのオプション。共有ライブラリを作るときに必要
g++ -fPIC -c hello.cpp good_morning.cpp

# 共有ライブラリ（libgreetings.so）の作成
# -o オプション: 出力ファイルの名前を指定する。ここでは `libgreetings.so` という名前にしている。
# -shared オプション:
#   共有ライブラリを作るためのオプション。
#   これで `hello.o` と `good_morning.o` をまとめて共有ライブラリ `libgreetings.so` にする
g++ -shared hello.o good_morning.o -o libgreetings.so

# main.cppをコンパイルしてlibgreetings.soとリンクし実行ファイルa.outを作成
# -L. オプション: ライブラリを探すディレクトリを指定する。ここではカレントディレクトリ（.）を指定している。
# -lgreetings オプション: `libgreetings.so` というライブラリをリンクする
# -Xlinker -rpath -Xlinker . オプション:
#   ランタイムパス（ライブラリを探す場所）を指定する。
#   ここではカレントディレクトリ（.）に設定している。
g++ main.cpp -L. -lgreetings -Xlinker -rpath -Xlinker .
```

以下で実行結果を確認できる。

```bash
$ ./a.out
Hello!
Good morning!
```

### CMakeを使ってみる

静的ライブラリと共有ライブラリを作るときのコマンドは同一で、`CMakelists.txt` の内容が異なるだけ

```bash
cmake -S . -B build;
cmake --build build
```

### 静的・共有ライブラリの指定について

以下のように `CMakeLists` に条件分岐を記載することができる。

```cmake
# GREETINGS_BUILD_SHARED_LIBSというオプションを作成。デフォルトをOFFに設定。
option(GREETINGS_BUILD_SHARED_LIBS "build greetings as a shared library" OFF)

if (GREETINGS_BUILD_SHARED_LIBS)
  add_library(greetings SHARED hello.cpp good_morning.cpp)
else()
  add_library(greetings STATIC hello.cpp good_morning.cpp)
endif()
```

コマンドラインから次のようにオプションを与えることができます。

```bash
# -D という prefix は Define の頭文字で、オプション名にこれをつけて指定する
cmake -S . -B build -DGREETINGS_BUILD_SHARED_LIBS=ON

cmake --build build
```

## ステップ３：サブディレクトリにソースが分散している場合

ディレクトリ構成を以下のように変更する：

```txt
---/
 |
 |--include/
 |  |--hello.hpp
 |  |--good_morning.hpp
 |
 |--src/
 |  |--hello.cpp
 |  |--good_morning.cpp
 |
 |--test/
    |--main.cpp
```