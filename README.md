[ Languages: [English](README.md), [日本語](README-ja.md) ]

# BMPLoad

Simple and Independent C Library for loading Windows Bitmap format data

### What is this?

If you need RGB / RGBA type image data as array of char on your C program, this will help you. BMPLoad loads Microsoft Windows Bitmap format data, then converts it's image to the standard RGB / RGBA char array. 

The functionality is represented as BmpLoad( ). See main( ) in main.c to see how does it works.

### Usage

<pre><code>unsigned char *Data;
int width, height, bits;
Data = BmpLoad("sample.bmp", &width, &height, &bits);
.......
free(Data);
</code></pre>

BmpLoad( ) open specified file then set the attribute information. _width_ and _height_ represent the size of image. _bits_ means number of bits of single pixel, should be 24 or 32.
This function also allocates memory and store the image body as RGB or RGBA char array. You can get the array address as the return value. NULL will be returned when severe error occur. 

### Test Run 

Here is the typical output of main.c program.
It loads 6x6_24.bmp and dump the contents in hexdec form. 
The image is basically white, except a RED (0xff0000) dot on the top-left corner and a YELLOW (0xffff00) dot on the bottom-right.

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

You can try other included images.
15x15_24_dots.bmp is 24bit image.
15x15_32_dots_alpha.bmp is 32bit (8bit RGB color + 8bit Alpha) image.

##### NOTE : negative value of the height

If you see the negative value as **height**, the image was scanned from top to down. Usually, Bitmap image scanned from bottom to up.
BmpLoad( ) function always stores the image to top-down ordering on the array.

For more detail of this issue, see [_biHeight_](https://msdn.microsoft.com/en-us/library/dd183376.aspx) specification.

### Limitation

BMPLoad can recognize 24 or 32bit color format as basic Windows Bitmap data only. Under technical term, the code only recognizes BITMAPINFOHEADER with full color (no compression and color palette technique).
For more detail, see following info;
https://wikipedia.org/wiki/Windows_bitmap#BITMAPINFOHEADER

Usually case, this conditions are fulfilled on your Bitmap file. 

### Why did I wrote this?

When I encouraged to develop more advanced program in their programming class, I was realized it was relatively difficult to get the bitmap RGB data from usual image data such as PNG or BMP file. 
Actually, one of my students tried to use OpenGL and tried to handle the bitmap image not only the wire-frame. OpenGL is quite general and popular library, but it does not include any standard way to handle the bitmap image. (And it is natual.)
On the other side, there are many ways to manage the graphics image format by various languages such as libpng. But for the student in the beginners' class, it is too complicated to understand what they are doing. 

Thus I started to write code to do such task in simple, easy to understand and independent manner. 
BMPLoad library is written in C. It runs on just general C environment. And it does not rely any other library.

##### NOTE : for Macintosh users

I am Macinotsh user, so here are some tips for Mac users.

**How can i create BMP file?**

'sips' command on MacOSX will help you to convert to BMP format from PNG file as follows;

<code>
$ sips -s format bmp example.png --out example.bmp
</code>

**Preview app does not handle Alpha value (transparency)**

Could not recognise 15x15_32_dots_alpha.bmp file as 'Alpha' image? Yes, Preview app of MacOSX does not handle Alpha, at least on my Yosemite (10.10) enviroment.
Use the other image utilities to see the Alpha image correctly.
I use GraphicConverter app on my Mac.

### References

* [Windows Bitmap](https://ja.wikipedia.org/wiki/Windows_bitmap) (Wikipedia)
* [BITMAPFILEHEADER structure](https://msdn.microsoft.com/en-us/library/dd183374.aspx) (Microsoft Bitmap Structures)
* [BITMAPINFOHEADER structure](https://msdn.microsoft.com/en-us/library/dd183376.aspx) (Microsoft Bitmap Structures)

### Copyright disclaimer 

I do not claim any Copyright about all codes under this BMPLoad repository.

Yutaka Yasuda


