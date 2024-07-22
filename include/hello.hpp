#ifndef HELLO_H // ヘッダーガードの開始: HELLO_Hが定義されていない場合に以下のコードを実行する
#define HELLO_H // HELLO_Hを定義する

void hello(); // hello関数のプロトタイプ宣言

#endif // ヘッダーガードの終了: ここまでのコードが一度だけインクルードされるようにする

/* 補足: C++のヘッダーガード（include guard）は、
同じヘッダーファイルが複数回インクルードされることによって発生する重複定義エラーを防ぐための仕組みです。 */