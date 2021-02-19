#include <stdio.h>
#include <string.h>
#include "EBS.h"

void EBS(char BITArray[], char *pCName) {
	int flag = 0;
	EBCS ebcs;
	if( 0 == strcmp(pCName, "FB") )
	{
		flag = 1;
	}
	else
	{
		//扩充 
	}
	switch(flag){
        case 1: 
			ebcs.table_id = 0;
			ebcs.section_syntax_indicator = 0;
			ebcs.section_length = 0;
			ebcs.table_id_extension = 0;
			ebcs.version_number = 0;
			ebcs.current_next_indicator = 0;
			ebcs.section_number = 0;
			ebcs.last_section_number = 0;
			ebcs.configure_cmd_number = 0;
			ebcs.configure_cmd_tag = 0;
			ebcs.configure_cmd_length = 0;
			ebcs.terminal_address_length = 0;
			memset(ebcs.terminal_address, 0, TER_ADDR_LEN);
			memset(ebcs.resource_code, 0, RES_CODE_LEN);
			EBS_FB(BITArray, &ebcs);
		
			printf("应急广播配置表字段输出如下: \n");
			printf("table_id: %d\n", ebcs.table_id);
			printf("section_syntax_indicator: %d\n", ebcs.section_syntax_indicator);
			printf("section_length: %d\n", ebcs.section_length);
			printf("table_id_extension: %d\n", ebcs.table_id_extension);
			printf("version_number: %d\n", ebcs.version_number);
			printf("current_next_indicator: %d\n", ebcs.current_next_indicator);
			printf("section_number: %d\n", ebcs.section_number);
			printf("last_section_number: %d\n", ebcs.last_section_number);
			printf("configure_cmd_number: %d\n", ebcs.configure_cmd_number);
			printf("configure_cmd_tag: %d\n", ebcs.configure_cmd_tag);
			printf("configure_cmd_length: %d\n", ebcs.configure_cmd_length);
			printf("terminal_address_length: %d\n", ebcs.terminal_address_length);
			printf("terminal_address: %s\n", ebcs.terminal_address);
			printf("resource_code: %s\n", ebcs.resource_code);
		    break;
        default:
		    break;
    }
	
}
