
================================================
  ＰＳＰ開発幼稚園  http://ameblo.jp/pspdevblog/  （本館）（ブログ）
  ＰＳＰ開発幼稚園  http://psp.nukenin.jp/        （別館）（ＨＰ）
================================================

■「ＰＳＰＤＳＫ」をインストールしないで、該当部分を盗んできた。
「pspsdk_1.0-beta2.tar.gz」735kbだよ。

その中の「Cube」ってサンプルを移植し、「改造ー」したもの。

□１６ビット色。ＲＧＢＡ＝５５５１にした。
□データーにシェーディング。入れた。
□その他。

（単なる３Ｄのサンプルです）

ＧｕはいいからＧｅって人向け。

それか、理屈は解からんからポリゴンって人向け。
（２００６−０５／０９、１６：３５、polygon0.zip）
================================================
■遊び方（？）。

Ｌ加  減Ｒ  （Ｌ＋Ｒで初期位置に戻る。）

  加↑
ｙ減↓         ┌加減ｚ
               △  ｜
←  →     □      ○
加ｘ減     ｜  ×
           加減┘

[HOME]終了      [SELECT]再開[START]停止
================================================
盗み方が足りない部分は、「my_gu.h」や（ＧＵ）
「pspgum.c」（ＧＵｍ）に追加しちゃえ。
「pspgum_vfpu.c」はＶＦＰＵの使い方。参考になる。（vfpuは音楽用途に使えるかも）
================================================
ＧＵ：「ＤｉｒｅｃｔＸ」で言えば「ＲＭ」のよーなもの。（但し完全ソース公開）
Ｇｅ：「ＤｉｒｅｃｔＸ」で言えば「ＩＭ」のよーなもの。（Execute-Buffer）
ＧＵｍ：「座標変換」等の３Ｄ演算計算ライブラリ。（ＧＵの内部にある）
================================================
ビルト方法。ＰＳＰ用ＧＣＣ４．０．０で、（ＰＳＰＳＤＫは要らない）
make maketree↓で、objディレクトリを作成し（初めの一回のみ）
make↓です。
================================================
私は現在、コンパイル／ＧＣＣ４．０．０環境です。
（toolchain.shを動かしてないので、ＰＳＰＳＤＫではないです）

現在の主流はＧＣＣ４．０．２の様です。が、４．０．２にする為には、
最低でもtoolchain.shを動かさないと駄目みたい。
toolchain.shの中身は、（ネット経由の）ＳＶＮで自動更新。
サーバーがトロイと（多分ね）果てしなく時間がかかる模様。
下記のような便利なＺＩＰがあると、初心者には楽なんだけどな。

  ■ＰＳＰのＧＣＣ達（ＳＤＫ）
  以下の一連のページはサーバーの都合で落としてきた
  ファイル名が変わっちゃうので逐一修正する事。
  落としてきても（名前を直しておかないと）後で
  訳が判らなくなります。
  http://psp-dev.org/pukiwiki/index.php?ToolChain
    （ツールチェインのページ）
  １．（ＧＣＣ）「psp-gcc-4.0.0.tar.bz2」
  http://psp-dev.org/files/psp-gcc-4.0.0.tar.bz2
     (約１２ＭＢ 12,511,957[bytes])
  ２．（ライブラリ）「psp-newlib-1.13.0-compiled-with-gcc-4.0.0.tar.bz2」
http://psp-dev.org/files/psp-newlib-1.13.0-compiled-with-gcc-4.0.0.tar.bz2
     (約０．８ＭＢ  856,717[bytes])
  ３．（ユーティリティー）「psp-binutils-2.16.tar.bz2」
  http://psp-dev.org/files/psp-binutils-2.16.tar.bz2
  (約４ＭＢ    4,225,299[bytes])
  これらは既に「toolchain」のパッチが当たっています。
  ◇これらのＧＣＣセットはバージョンがどんどん新しく
  なる筈です。組み合わせが悪くなければ最新版の方が
  （初心者には）問題が少ないと思うのでガンガン最新版に
  してもＯＫです。

「toolchain.sh」を動かして、最新の４．０．２にしたい方は、
多分ここ、http://www.oopo.net/consoledev/
Toolchain Files
[02-22-2006] newtoolchain-20060222.tgz - The new, experimental toolchain autobuild script.
訳：最新の奴でちゅ。
[01-20-2006] psptoolchain-20060120.tgz - The famous pspdev toolchain autobuild script.
訳：有名な奴でちゅ。


■cygwin      （unix互換の環境なら何でもいい）
  注意：ＯＳがlinuxな人には既に関係ない話です。
  注意：Macな人も関係あるらしいです。
  http://cygwin.com/    (Cygwin Projectのページ)
  http://cygwin.com/setup.exe

Ｗ９８な人へ：
うちはＷ９８ＳＥの純正ＩＥ５なので（ボッツだと決め付けられて）跳ねられちゃいます。
ＩＥなら６にしてください。アップデートが嫌ならＯｐｅｒａ辺りがお勧めかも。
  http://www.vector.co.jp/vpack/filearea/win/net/www/index.html
     (ブラウザＩＮＤＥＸ)
  http://www.vector.co.jp/soft/win95/net/se379091.html
    （Ｏｐｅｒａ８．５）
ＩＥ６は標準かどうか知らないが、私は使いにくい。

■補足情報（２００６−０１／１９）
Ｃｙｇｗｉｎでなくても、

ＭｉｎＧＷでも、出来るそうです。（試してないので知らない）
オフィシャルサイトはこちら、
http://www.mingw.org/
================================================
