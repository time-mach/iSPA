#include <stdio.h>
#include "EBS_FB.h"

void Bit2TA(char *ps, char *pe, char terminal_address[], char temp[]) {
	int index = 0, val = 0, len = strlen(temp) / 4;
	char array[TER_ADDR_LEN] = {'\0'};

	for(index = 0; index < len; index++) {
		val  =8 * (temp[index * 4] - '0');
		val += 4 * (temp[index * 4 + 1] - '0');
		val += 2 * (temp[index * 4 + 2] - '0');
		val += temp[index * 4 + 3] - '0';
		sprintf(array + index, "%1x", val);
	}
	memcpy(terminal_address, array, strlen(array));
}

void EBS_FB(char BITArray[], EBCS *pEbcs)
{
	// 初始化
	int index1 = 0, index2 = 0;
	char *ps = BITArray + 40;//指针ps指向FB的第一个二进制串
	char *pe = ps + 7;//指针pe指向FB的最后一个二进制串
	char temp[TEMP_LEN] = {'\0'}; //存储临时的二进制串

	//1、计算 table_id
	pEbcs->table_id = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//2、计算 section_syntax_indicator
	pe = pe + 1;
	ps = pe;
	pEbcs->section_syntax_indicator = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//3、计算 section_length
	pe = pe + 4;
	ps = pe; // ps指向section_length二进制串第一位
	pe = ps + 11;// ps指向section_length二进制串最后一位
	pEbcs->section_length = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//4、计算 table_id_extension
	pe = pe + 1;
	ps = pe; // ps指向table_id_extension二进制串第一位
	pe = ps + 15;// ps指向table_id_extension二进制串最后一位
	pEbcs->table_id_extension = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//5、计算 version_number
	pe = pe + 3;
	ps = pe; // ps指向version_number 二进制串第一位
	pe = ps + 4;// ps指向version_number 二进制串最后一位
	pEbcs->version_number = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//6、计算 current_next_indicator
	pe = pe + 1;
	ps = pe; // ps指向current_next_indicator 二进制串第一位
	pEbcs->current_next_indicator = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//7、计算 section_number
	pe = pe + 1;
	ps = pe; // ps指向section_number 二进制串第一位
	pe = ps + 7;// ps指向 section_number二进制串最后一位
	pEbcs->section_number = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//8、计算 last_section_number
	pe = pe + 1;
	ps = pe; // ps指向last_section_number 二进制串第一位
	pe = ps + 7;// ps指向 last_section_number二进制串最后一位
	pEbcs->last_section_number = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//9、计算 configure_cmd_number
	pe = pe + 1;
	ps = pe; // ps指向configure_cmd_number 二进制串第一位
	pe = ps + 7;// ps指向 configure_cmd_number二进制串最后一位
	pEbcs->configure_cmd_number = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//10、循环计算 configure_cmd_tag，configure_cmd_length，terminal_address_length，terminal_address， resource_code
	for(index1 = 0; index1 < pEbcs->configure_cmd_number; index1++) {
		//11、计算  configure_cmd_tag
		pe = pe + 1;
		ps = pe; // ps指向configure_cmd_tag 二进制串第一位
		pe = ps + 7;// ps指向 configure_cmd_tag二进制串最后一位
		pEbcs->configure_cmd_tag = Bit2Dec(ps, pe, temp);
		memset(temp, 0, TEMP_LEN);

		//12、计算  configure_cmd_length
		pe = pe + 1;
		ps = pe; // ps指向configure_cmd_length二进制串第一位
		pe = ps + 15;// ps指向 configure_cmd_length 二进制串最后一位
		pEbcs->configure_cmd_length = Bit2Dec(ps, pe, temp);
		memset(temp, 0, TEMP_LEN);

		switch(pEbcs->configure_cmd_tag) {
			case 2:
				//13、计算  terminal_address_length
				pe = pe + 1;
				ps = pe; // ps指向terminal_address_length二进制串第一位
				pe = ps + 7;// ps指向 terminal_address_length 二进制串最后一位
				pEbcs->terminal_address_length = Bit2Dec(ps, pe, temp);
				memset(temp, 0, TEMP_LEN);

				//14、计算  terminal_address
				pe = pe + 1;
				ps = pe; // ps指向terminal_address二进制串第一位
				pe = ps + pEbcs->terminal_address_length * 8 - 1;// ps指向 terminal_address 二进制串最后一位
				int index3 = 0;
				for(index3 = 0; ps + index3 <= pe; index3++) {
					temp[index3] = *(ps + index3);
				}
				Bit2TA(ps, pe, pEbcs->terminal_address, temp);
				memset(temp, 0, TEMP_LEN);

				//15、计算  resource_code
				pe = pe + 5;
				ps = pe; // ps指向resource_code二进制串第一位
				pe = ps + 91;// ps指向 resource_code 二进制串最后一位
				index3 = 0;
				for(index3 = 0; ps + index3 <= pe; index3++) {
					temp[index3] = *(ps + index3);
				}
				Bit2TA(ps, pe, pEbcs->resource_code, temp);
				memset(temp, 0, TEMP_LEN);
				break;
			default:
				break;
		}

	}

	//16、数据签名与CRC校验省略
}
