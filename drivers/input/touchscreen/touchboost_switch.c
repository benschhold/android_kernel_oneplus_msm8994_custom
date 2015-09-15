/*
 * interface to control touch boost (= input boost) on OnePlus One bacon
 *
 * Author: andip71, 22.09.2014
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

#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/stat.h>


/*****************************************/
// Global external variables
/*****************************************/

extern unsigned int input_boost_status;
extern unsigned int input_boost_freq;

void set_touchboost_frequency(void);

/*****************************************/
// sysfs interface functions
/*****************************************/

static ssize_t touchboost_switch_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	// return value of current touchboost status
	return sprintf(buf, "Touchboost status: %d", input_boost_status);
}


static ssize_t touchboost_switch_store(struct device *dev, struct device_attribute *attr,
					const char *buf, size_t count)
{
	unsigned int ret = -EINVAL;
	unsigned int val = 0;

	// read value from input buffer
	ret = sscanf(buf, "%d", &val);

	if (ret != 1)
		return -EINVAL;

	// check if new status is valid and store in external variable
	if ((val == 0) || (val == 1))
		input_boost_status = val;
	else
		pr_err("Touchboost switch : invalid touchboost status.\n");

	return count;
}

static ssize_t touchboost_freq_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	// return value of current touchboost frequency
	return sprintf(buf, "%d - Touchboost frequency\n", input_boost_freq);
}


static ssize_t touchboost_freq_store(struct device *dev, struct device_attribute *attr,
					const char *buf, size_t count)
{
	unsigned int ret = -EINVAL;
	unsigned int input = 0;

	// read value from input buffer
	ret = sscanf(buf, "%d", &input);

	if (ret != 1)
		return -EINVAL;

	if (input == 0) 
	{
		pr_err("Touchboost switch : frequency not allowed");
		return -EINVAL;
	} 
	else 
	{
		input_boost_freq = input;
		set_touchboost_frequency();
		pr_debug("Touchboost switch : frequency for touch boost set");
	}

	return -EINVAL;
}


/*****************************************/
// Initialize touchboost switch sysfs
/*****************************************/

// define objects
static DEVICE_ATTR(touchboost_switch, S_IRUGO | S_IWUGO, touchboost_switch_show, touchboost_switch_store);
static DEVICE_ATTR(touchboost_freq  , S_IRUGO | S_IWUGO, touchboost_freq_show  , touchboost_freq_store  );

// define attributes
static struct attribute *touchboost_switch_attributes[] = {
	&dev_attr_touchboost_switch.attr,
	&dev_attr_touchboost_freq.attr,
	NULL
};

// define attribute group
static struct attribute_group touchboost_switch_control_group = {
	.attrs = touchboost_switch_attributes,
};

// define control device
static struct miscdevice touchboost_switch_control_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "touchboost_switch",
};


/*****************************************/
// Driver init and exit functions
/*****************************************/

static int touchboost_switch_init(void)
{
	// register touchboost switch device
	misc_register(&touchboost_switch_control_device);
	if (sysfs_create_group(&touchboost_switch_control_device.this_device->kobj,
				&touchboost_switch_control_group) < 0) {
		pr_err("Touchboost switch : failed to create touchboost switch sys fs object.\n");
		return 0;
	}

	pr_info("Touchboost switch : device initialized\n");

	return 0;
}


static void touchboost_switch_exit(void)
{
	// remove touchboost switch device
	sysfs_remove_group(&touchboost_switch_control_device.this_device->kobj,
                           &touchboost_switch_control_group);

	pr_info("Touchboost switch : device stopped\n");
}


/* define driver entry points */

module_init(touchboost_switch_init);
module_exit(touchboost_switch_exit);
