#ifndef _COMMON_H_
#define _COMMON_H_

#include <string.h>

#define HEX_DATA_LEN 500
#define BIT_DATA_LEN HEX_DATA_LEN*4
#define PARENT_SERVICE_NAME_LEN 10
#define PARAMS_COUNT 4

extern void Help();

//���ļ��ж�ȡ16�����ַ���
void read16(char HEXArray[], char *data);

//16�����ַ���ת�������ַ���
void Hex2Bit(char HEXArray[], char BITArray[], int len);

//�����ƴ�ת10����    ���޸�Ϊ�Լ�
int Bit2Dec(char *ps, char *pe, char temp[]);

#endif
