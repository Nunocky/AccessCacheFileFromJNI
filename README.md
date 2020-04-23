# AccessCacheFileFromJNI

rawディレクトリ下にあるリソースをキャッシュにコピーし、JNIでアクセスする実験

## ざっくりした解説

MyApplicationの onCreateでコピー処理を行い、そのパスを記憶。

ネイティブメソッド helloにそのパスを渡す。

helloのネイティブ実装の中で、CのファイルアクセスAPI(fopen, freadなど)でファイルが読めることを確かめる。
