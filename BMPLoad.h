//
//  BMPLoad.h
//  BMPLoad
//
//  Created by Y on 2015/12/24.
//  Copyright © 2015年 Yutaka Yasuda. All rights reserved.
//


#ifndef BMPLoad_h
#define BMPLoad_h

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdarg.h>

#define BMP_DEBUG 1

/* Windows Bitmap ヘッダ情報
 https://ja.wikipedia.org/wiki/Windows_bitmap
 https://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx
 https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx
 などを参照（メンバ名などは後者からの引き写し）
 */

#pragma pack(push, 2) // アライメントを 2 バイト単位に指定

// ファイルヘッダ 14 バイト
typedef struct tagBITMAPFILEHEADER {
    uint16_t bfType; // 特にここが 16bit 幅なので 32bit アライメントされるとヘッダサイズが 14 でなく 16 バイトになってしまう
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

#define BITMAPFILEHEADER_SIZE 14 // アライメントに失敗していないことを強引に確認

// Windows Bitmap ヘッダ 40 バイト
typedef struct tagBITMAPINFOHEADER{
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPixPerMeter;
    int32_t  biYPixPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImporant;
} BITMAPINFOHEADER;

#define BITMAPINFOHEADER_SIZE 40 // アライメントに失敗していないことを強引に確認

#pragma pack(pop)

// prototypes

unsigned char *BmpLoad(char *FileName, int *imageWidth, int *imageHeight, int *imageBits);
int RgbDump(unsigned char *Data, int width, int height, int imageBits);


#endif /* BMPLoad_h */
