コンパイル方法について
Makefileを用意して全ソースファイルをコンパイルできるようにしている。
シェルで"make"とタイプして実行すればすべてのファイルがコンパイルされ、
実行ファイル"textformat"が作成される。


実行方法について
EUC-JPやASCIIによって構成されたファイルで、Cプログラムのファイルはオプション[-c]を
指定して実行ファイルtextformatを用いる

[例]
$./textformat filename.txt
$./textformat filenamce.c -c

ソースコードファイルとモジュールの対応関係
　ソースコード名     モジュール名
　    main.c      　メインモジュール
   　 htab.c　　　　 水平タブモジュール
　stm.l stm.c      STMモジュール
    filter.c	   フィルタモジュール
  linefeed.c       改行モジュール
  pagefeed.c      改ページモジュール  
    header.c        ヘッダモジュール
 postscript.c      ポストスクリプトモジュール
