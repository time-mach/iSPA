#ifndef _COMMON_H_
#define _COMMON_H_

#include <string.h>

#define HEX_DATA_LEN 500
#define BIT_DATA_LEN HEX_DATA_LEN*4
#define PARENT_SERVICE_NAME_LEN 10
#define PARAMS_COUNT 4

extern void Help();

//从文件中读取16进制字符串
void read16(char HEXArray[], char *data);

//16进制字符串转二进制字符串
void Hex2Bit(char HEXArray[], char BITArray[], int len);

//二进制串转10进制    待修改为自己
int Bit2Dec(char *ps, char *pe, char temp[]);

#endif
