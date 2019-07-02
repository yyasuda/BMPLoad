[ Languages: [English](README.md), [日本語](README-ja.md) ]

# BMPLoad

シンプルで他のライブラリに依存せずに Windows Bitmap フォーマットデータを読み込む C ライブラリです。

### What is this?

もしあなたが RGB / RGBA タイプの画像データをあなたの C プログラムに読み込ませたいなら、このプログラムが役に立つでしょう。BMPLoad は Microsoft Windows Bitmap フォーマットのデータをロードし、そのイメージ部分を標準的な RGB / RGBA 並びの文字配列に変換します。

その機能は BmpLoad( ) 関数にあります。どう動くかは main.c の main( ) 関数を見てください。

### Usage

<pre><code>unsigned char *Data;
int width, height, bits;
Data = BmpLoad("sample.bmp", &width, &height, &bits);
.......
free(Data);
</code></pre>

BmpLoad( ) は指定されたファイルをオープンして、その属性情報をセットします。_width_ と _height_ はイメージのサイズを示し、 _bits_ は一画素あたりのビット数（24 あるいは 32）を意味します。
この関数はまたメモリ領域を確保し、そこに画像本体を RGB あるいは RGBA 形式の文字配列として格納します。返り値にはこの配列のアドレスが与えられます。シビアなエラーがあった場合は NULL が返されます。

### Test Run 

main.c プログラムの典型的な出力を以下に示します。
これは 6x6_24.bmp ファイルをロードし、その内容を 16 進ダンプしたものです。
画像は左上端の画素が赤（0xff0000）、右下端の画素が黄色（0xff0000）で、それ以外はすべて白です。

<pre><code>$ cc BMPLoad.c main.c
$ ./a.out 6x6_24.bmp 
filename = 6x6_24.bmp
width = 6, height = 6
planes = 1
bits/pixel = 24
Data 0x7fc312500000 (108 bytes allocated)
dump (6 x 6) format="RGB"
000 ff0000 ffffff ffffff ffffff ffffff ffffff
001 ffffff ffffff ffffff ffffff ffffff ffffff
002 ffffff ffffff ffffff ffffff ffffff ffffff
003 ffffff ffffff ffffff ffffff ffffff ffffff
004 ffffff ffffff ffffff ffffff ffffff ffffff
005 ffffff ffffff ffffff ffffff ffffff ffff00
PROGRAM normarly ended.
$
</code></pre>

このリポジトリにある他の画像データでも試してみてください。
15x15_24_dots.bmp は 24bit 画像です。
15x15_32_dots_alpha.bmp は 32bit つまり 8bit RGB カラー と 8bit アルファ値をもつ画像です。

##### NOTE : _height_ の値が負である場合

もし **height** が負の値だった場合、その画像は「上から下」にスキャンされています。通常は「下から上」にスキャンされています。
BmpLoad( ) 関数は常に画像データを「上から下」順で配列に格納します。

詳細は [_biHeight_](https://msdn.microsoft.com/en-us/library/dd183376.aspx) の仕様を参照してください。

### 機能的な制限（限界）

BMPLoad は Windows Bitmap データの基本的なものである 24 あるいは 32bit カラーフォーマットだけを認識できます。技術的な言い方をすれば、コードはフルカラーの（つまり圧縮やカラーパレット処理のない） [BITMAPINFOHEADER](https://wikipedia.org/wiki/Windows_bitmap#BITMAPINFOHEADER) だけに対応しています。

多くの場合、あなたのビットマップファイルはこの条件を満たしています。

### なぜ作ったか？

プログラミングの初級クラスで頑張っている学生に、もっと先へ進んだプログラムを作ってみるように勧めたとき、PNG や BMP といったよくある画像ファイルから RGB ビットマップデータを取り出すことが比較的難しいことに気がつきました。
実際に、学生の一人は OpenGL を試しており、ワイヤーフレームだけではなくビットマップを扱おうとしていました。OpenGL はとても一般的でよく使われるライブラリですが、ビットマップ画像を扱う標準的な方法は用意されていません。（まあ当然でもあります）
その一方で、libpng のような画像フォーマットを処理するための多くの手段が多種の言語で用意されています。ただそれらは初級クラスの学生たちが何をやってるのか理解するにはちょっとややこしい。

そんなわけで私はこのタスクをシンプルに、理解しやすく、他のライブラリへの依存性がない方法で実現するコードを書いたわけです。
BMPLoad ライブラリは C で書かれています。普通の C 言語の環境でさえあれば動くでしょう。そして他のライブラリには依存していません。

##### NOTE : Macinotsh ユーザ向けに

私は Macintosh ユーザなので、幾らかそのあたりの Tips を。。

**BMP ファイルってどうやって作れば？**

以下のようにして、MacOSX 標準の sips コマンドで PNG ファイルから BMP フォーマットへの変換ができます。

<code>
$ sips -s format bmp example.png --out example.bmp
</code>

**「プレビュー」アプリがアルファ値（透明度）を処理してくれない**

「プレビュー」で 15x15_32_dots_alpha.bmp を見たけど、Alpha っぽく出てこなかった？はい、MacOSX のプレビュー・アプリは Alpha を処理できません。少なくとも私の Yosemite (10.10) 環境では。
何か他の Alpha つきイメージを正しく処理できる画像処理ツールを使ってください。
私は GraphicConverter アプリを使っています。

### 参考資料

* [Windows Bitmap](https://ja.wikipedia.org/wiki/Windows_bitmap) (Wikipedia)
* [BITMAPFILEHEADER structure](https://msdn.microsoft.com/en-us/library/dd183374.aspx) (Microsoft Bitmap Structures)
* [BITMAPINFOHEADER structure](https://msdn.microsoft.com/en-us/library/dd183376.aspx) (Microsoft Bitmap Structures)

### 権利について

誰でもこの BMPLoad リポジトリにあるあるすべてのファイルを自由に利用、改変、再配布することができます。再配布する場合も著作権情報を含める必要はなく、改変し、再配布するものの利用ライセンスも自由に設定できます。

These codes are licensed under CC0.
[![CC0](http://i.creativecommons.org/p/zero/1.0/88x31.png "CC0")](http://creativecommons.org/publicdomain/zero/1.0/deed.ja)

Yutaka Yasuda


