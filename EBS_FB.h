#ifndef _EBS_FB_H_
#define _EBS_FB_H_

#include <stdlib.h>
#include <string.h> 
#include "Common.h"

#define TER_ADDR_LEN 100
#define RES_CODE_LEN 100
#define CON_CMD_TAG 2
#define TEMP_LEN 100

typedef struct EB_configure_section {
	int table_id;
	int section_syntax_indicator;
	int section_length;
	int table_id_extension;
	int version_number;
	int current_next_indicator;
	int section_number;
	int last_section_number;
	int configure_cmd_number;
	int configure_cmd_tag;
	int configure_cmd_length;
	int terminal_address_length;
	char terminal_address[TER_ADDR_LEN];
	char resource_code[RES_CODE_LEN];
} EBCS;

extern void EBS_FB(char BITArray[], EBCS *pEbcs);
extern void Bit2TA(char *ps, char *pe, char terminal_address[], char temp[]);

#endif
