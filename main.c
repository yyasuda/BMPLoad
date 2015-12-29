//
//  main.c
//  BMPLoad
//
//  Created by Y on 2015/12/24.
//  I do not claim any copyright of this code. Yutaka Yasuda.


#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "BMPLoad.h"

void usage(char *message)
{
    if(strlen(message)!=0) {
        printf("ERROR %s\n", message);
        printf("\n");
    }
    printf("Usage: ./a.out filename\n");
    
    exit(0);
}



int main(int argc, const char * argv[]) {
    unsigned char *Data;
    int width, height, bits;
    
    // 引数チェック
    if(argc != 2) usage("NO FILENAME SPECIFIED");
    
    char fname[128];
    strcpy(fname, argv[1]);
    
    printf("filename = %s\n", fname);
    
    // 読み出し
    if( (Data = BmpLoad(fname, &width, &height, &bits)) == NULL) {
        printf("PROGRAM TERMINATED with ERROR\n");
        exit(1);
    }
    
    // 内容確認
    RgbDump(Data, width, height, bits);
    
    // メモリ解放
    free(Data);
    
    printf("PROGRAM normarly ended.\n");
    
    return 0;
}
