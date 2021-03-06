/*
 * arch/arm/mach-k3v2/common.c
 *
 * Copyright (C) 2011 Hisilicon Co. Ltd.
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <mach/mmc.h>
#include <mach/boardid.h>
#include <hsad/config_mgr.h>

boardid_parameter boardid_source = {
	.chip_id = CS_CHIP_ID,
	.pmu_id = 0,
	.board_id = 0 ,
};

/**
 * parse boaridid cmdline which is passed from fastoot. *
 * Format : BoardID=chip_id,pmu_id,board_id             *
 */
static int __init early_parse_boardid_cmdline(char *p)
{
	char board[HEX_STRING_MAX + 1];
	char chip [HEX_STRING_MAX + 1];
	char pmu  [HEX_STRING_MAX + 1];
	char *endptr = NULL;

	memset(board, 0, HEX_STRING_MAX + 1);
	memcpy(board, p + (HEX_STRING_MAX + 1)*2, HEX_STRING_MAX);
	board[HEX_STRING_MAX] = '\0';

	boardid_source.board_id = simple_strtoull(board, &endptr, TRANSFER_BASE);
	printk(KERN_INFO "[bdid]boardid = 0x%x.\n", boardid_source.board_id);

	/* create hw attribute config data base on boardid */
	if(select_hw_config(boardid_source.board_id))
            printk(KERN_ERR "select_hw_config error\n");
	return 0;
}
early_param("boardid", early_parse_boardid_cmdline);

unsigned int get_boardid(void)
{
	return boardid_source.board_id;
}
EXPORT_SYMBOL(get_boardid);

void set_boardid(unsigned int id)
{
	boardid_source.board_id = id;
}
EXPORT_SYMBOL(set_boardid);


unsigned int get_chipid(void)
{
	return boardid_source.chip_id;
}
EXPORT_SYMBOL(get_chipid);

unsigned int get_pmuid(void)
{
	return boardid_source.pmu_id;
}
EXPORT_SYMBOL(get_pmuid);
#if 0
int get_iomux_type(void)
{
	return 0;
}
EXPORT_SYMBOL(get_iomux_type);

int get_hsd_invert(void)
{
    return 0;
}
EXPORT_SYMBOL(get_hsd_invert);

int get_hs_keys(void)
{
    return 1;
}
EXPORT_SYMBOL(get_hs_keys);
#endif
