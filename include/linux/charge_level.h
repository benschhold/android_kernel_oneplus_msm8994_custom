/*
 * Author: andip71, 11.03.2016
 *
 * Version 1.2
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

extern int ac_level;
extern int usb_level;
extern int charge_level;
extern int charge_info_level_cur;
extern int charge_info_level_req;
extern int charger_type;

#define AC_CHARGE_LEVEL_DEFAULT 2000	// 0 = stock charging logic will apply
#define AC_CHARGE_LEVEL_MIN 240
#define AC_CHARGE_LEVEL_MAX 2000

#define USB_CHARGE_LEVEL_DEFAULT 1500	// 0 = stock charging logic will apply
#define USB_CHARGE_LEVEL_MIN 200
#define USB_CHARGE_LEVEL_MAX 2000

#define BK_CHARGER_NONE		0
#define BK_CHARGER_AC		1
#define BK_CHARGER_USB		2
#define BK_CHARGER_UNKNOWN	3

