#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Common.h"

void Help() {
	printf("====================================\n");
	printf("��ӭʹ�� ҵ��Э��������\n");
	printf("Usage: iSPA ҵ����[EBS|...] ��ҵ����[FB|...] ��Э������·�� \n");
	printf("====================================\n");
}

//���ļ��ж�ȡ16�����ַ���
void read16(char HEXArray[], char *data) {
	int index = 0;
	char valChar = '\0';
	FILE *pFile = NULL;
	if( NULL == (pFile = fopen(data, "r")) ) {
		printf("��16�����ļ�ʧ��!\n");
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
//16�����ַ���ת�������ַ���
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

//�����ƴ�ת10����    ���޸�Ϊ�Լ�
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


