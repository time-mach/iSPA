#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Common.h"

void Help() {
	printf("====================================\n");
	printf("欢迎使用 业务协议分析软件\n");
	printf("Usage: iSPA 业务名[EBS|...] 子业务名[FB|...] 子协议数据路径 \n");
	printf("====================================\n");
}

//从文件中读取16进制字符串
void read16(char HEXArray[], char *data) {
	int index = 0;
	char valChar = '\0';
	FILE *pFile = NULL;
	if( NULL == (pFile = fopen(data, "r")) ) {
		printf("打开16进制文件失败!\n");
		exit(1);
	}

	while( EOF!= (valChar=fgetc(pFile)) ) {
		if( (isdigit(valChar)) || (isalpha(valChar)) ) {
			HEXArray[index] = valChar;
			index++;
		}
	}
	fclose(pFile);
}
//16进制字符串转二进制字符串
void Hex2Bit(char HEXArray[], char BITArray[], int len) {
	int index1 = 0, index2 = 0;
	char Bit[16][5] = {"0000", "0001", "0010", "0011","0100", "0101", "0110", "0111", "1000", "1001",
	                   "1010", "1011", "1100", "1101", "1110", "1111"
	                  };
	for(index1 = 0; index1 < len; index1++) {
		if ( (HEXArray[index1] >= 'a') && (HEXArray[index1] <= 'f') ) index2 = HEXArray[index1] - 'a' + 10;
		if ( (HEXArray[index1] >= 'A') && (HEXArray[index1] <= 'F') ) index2 = HEXArray[index1] - 'A' + 10;
		if ( (HEXArray[index1] >= '0') && (HEXArray[index1] <= '9') ) index2 = HEXArray[index1] - '0';

		memcpy(&BITArray[index1 * 4], Bit[index2],4);
	}
}

//二进制串转10进制    待修改为自己
int Bit2Dec(char *ps, char *pe, char temp[]) {
	int dec = 0, index = 0;

	for(index = 0; ps + index <= pe; index++) {
		temp[index] = *(ps + index);
	}

	for (index = 0; index < strlen(temp); index++) {
		dec = dec + ((temp[index] - 48)<< (strlen(temp) - index - 1));
	}

	return dec;
}


