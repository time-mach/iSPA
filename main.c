#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Common.h"
#include "EBS.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {//iSPA 业务名 子协议名 字段数据文件路径
	int flag = 0;
	char HEXArray[HEX_DATA_LEN] = {'\0'};
	char BITArray[BIT_DATA_LEN] = {'\0'};
		
	if (PARAMS_COUNT != argc)//如果输入参数个数有误 
	{
		Help();
		return 0;
	}
	
	printf("第一个参数是: %s, 第二个参数是: %s, 第三个参数是: %s\n", argv[1], argv[2], argv[3]);
	//1、读取协议数据
	read16(HEXArray, argv[3]);
	//printf("16进制字符串：%s\n", HEXArray);
	//2、转换为二进制串  技术点
	Hex2Bit(HEXArray, BITArray, strlen(HEXArray));
	//printf("二进制串长度：%d,二进制串：",strlen(BITArray));
	//puts(BITArray);
	//3、按照协议分析，这里以应急广播管理配置表为例   技术点
	if( 0 == strcmp(argv[1], "EBS") )
	{
		flag = 1;
	}
	else
	{
		//扩充 
	}
	
	switch(flag){
        case 1:
		    EBS(BITArray, argv[2]);
		    break;
        default: 
		    break;
    }
    
	puts("欢迎使用, 再见!");
	system("pause");

	return 0;
}
