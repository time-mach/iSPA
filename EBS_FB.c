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
	// ��ʼ��
	int index1 = 0, index2 = 0;
	char *ps = BITArray + 40;//ָ��psָ��FB�ĵ�һ�������ƴ�
	char *pe = ps + 7;//ָ��peָ��FB�����һ�������ƴ�
	char temp[TEMP_LEN] = {'\0'}; //�洢��ʱ�Ķ����ƴ�

	//1������ table_id
	pEbcs->table_id = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//2������ section_syntax_indicator
	pe = pe + 1;
	ps = pe;
	pEbcs->section_syntax_indicator = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//3������ section_length
	pe = pe + 4;
	ps = pe; // psָ��section_length�����ƴ���һλ
	pe = ps + 11;// psָ��section_length�����ƴ����һλ
	pEbcs->section_length = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//4������ table_id_extension
	pe = pe + 1;
	ps = pe; // psָ��table_id_extension�����ƴ���һλ
	pe = ps + 15;// psָ��table_id_extension�����ƴ����һλ
	pEbcs->table_id_extension = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//5������ version_number
	pe = pe + 3;
	ps = pe; // psָ��version_number �����ƴ���һλ
	pe = ps + 4;// psָ��version_number �����ƴ����һλ
	pEbcs->version_number = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//6������ current_next_indicator
	pe = pe + 1;
	ps = pe; // psָ��current_next_indicator �����ƴ���һλ
	pEbcs->current_next_indicator = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//7������ section_number
	pe = pe + 1;
	ps = pe; // psָ��section_number �����ƴ���һλ
	pe = ps + 7;// psָ�� section_number�����ƴ����һλ
	pEbcs->section_number = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//8������ last_section_number
	pe = pe + 1;
	ps = pe; // psָ��last_section_number �����ƴ���һλ
	pe = ps + 7;// psָ�� last_section_number�����ƴ����һλ
	pEbcs->last_section_number = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//9������ configure_cmd_number
	pe = pe + 1;
	ps = pe; // psָ��configure_cmd_number �����ƴ���һλ
	pe = ps + 7;// psָ�� configure_cmd_number�����ƴ����һλ
	pEbcs->configure_cmd_number = Bit2Dec(ps, pe, temp);
	memset(temp, 0, TEMP_LEN);

	//10��ѭ������ configure_cmd_tag��configure_cmd_length��terminal_address_length��terminal_address�� resource_code
	for(index1 = 0; index1 < pEbcs->configure_cmd_number; index1++) {
		//11������  configure_cmd_tag
		pe = pe + 1;
		ps = pe; // psָ��configure_cmd_tag �����ƴ���һλ
		pe = ps + 7;// psָ�� configure_cmd_tag�����ƴ����һλ
		pEbcs->configure_cmd_tag = Bit2Dec(ps, pe, temp);
		memset(temp, 0, TEMP_LEN);

		//12������  configure_cmd_length
		pe = pe + 1;
		ps = pe; // psָ��configure_cmd_length�����ƴ���һλ
		pe = ps + 15;// psָ�� configure_cmd_length �����ƴ����һλ
		pEbcs->configure_cmd_length = Bit2Dec(ps, pe, temp);
		memset(temp, 0, TEMP_LEN);

		switch(pEbcs->configure_cmd_tag) {
			case 2:
				//13������  terminal_address_length
				pe = pe + 1;
				ps = pe; // psָ��terminal_address_length�����ƴ���һλ
				pe = ps + 7;// psָ�� terminal_address_length �����ƴ����һλ
				pEbcs->terminal_address_length = Bit2Dec(ps, pe, temp);
				memset(temp, 0, TEMP_LEN);

				//14������  terminal_address
				pe = pe + 1;
				ps = pe; // psָ��terminal_address�����ƴ���һλ
				pe = ps + pEbcs->terminal_address_length * 8 - 1;// psָ�� terminal_address �����ƴ����һλ
				int index3 = 0;
				for(index3 = 0; ps + index3 <= pe; index3++) {
					temp[index3] = *(ps + index3);
				}
				Bit2TA(ps, pe, pEbcs->terminal_address, temp);
				memset(temp, 0, TEMP_LEN);

				//15������  resource_code
				pe = pe + 5;
				ps = pe; // psָ��resource_code�����ƴ���һλ
				pe = ps + 91;// psָ�� resource_code �����ƴ����һλ
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

	//16������ǩ����CRCУ��ʡ��
}
