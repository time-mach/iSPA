#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Common.h"
#include "EBS.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {//iSPA ҵ���� ��Э���� �ֶ������ļ�·��
	int flag = 0;
	char HEXArray[HEX_DATA_LEN] = {'\0'};
	char BITArray[BIT_DATA_LEN] = {'\0'};
		
	if (PARAMS_COUNT != argc)//������������������ 
	{
		Help();
		return 0;
	}
	
	printf("��һ��������: %s, �ڶ���������: %s, ������������: %s\n", argv[1], argv[2], argv[3]);
	//1����ȡЭ������
	read16(HEXArray, argv[3]);
	//printf("16�����ַ�����%s\n", HEXArray);
	//2��ת��Ϊ�����ƴ�  ������
	Hex2Bit(HEXArray, BITArray, strlen(HEXArray));
	//printf("�����ƴ����ȣ�%d,�����ƴ���",strlen(BITArray));
	//puts(BITArray);
	//3������Э�������������Ӧ���㲥�������ñ�Ϊ��   ������
	if( 0 == strcmp(argv[1], "EBS") )
	{
		flag = 1;
	}
	else
	{
		//���� 
	}
	
	switch(flag){
        case 1:
		    EBS(BITArray, argv[2]);
		    break;
        default: 
		    break;
    }
    
	puts("��ӭʹ��, �ټ�!");
	system("pause");

	return 0;
}
