/*
 * Author: andip71, 03.01.2016
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

#include <linux/cpu.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
//#include <linux/sched.h>
//#include <linux/mutex.h>

//static int boeffla_config_mode = 0;

//static DEFINE_MUTEX(bk_helper_mutex);

//static struct work_struct bk_hotplug_work;


//static void __ref bk_handle_hotplug(struct work_struct *work)
//{
//	if (boeffla_config_mode == 1)
//	{
		//pr_info("Boeffla-Kernel: cpu up\n");
		//mutex_lock(&bk_helper_mutex);
		//put_online_cpus();
		//cpu_hotplug_driver_lock();
		//cpu_up(0);
		//cpu_up(4);
		//get_online_cpus();
		//cpu_hotplug_driver_unlock();
		//mutex_unlock(&bk_helper_mutex);
//	}
//	else
//	{
//		pr_info("Boeffla-Kernel: cpu down\n");
/*		mutex_lock(&bk_helper_mutex);
		put_online_cpus();
		cpu_hotplug_driver_lock();
		cpu_down(0);
		cpu_down(4);
		get_online_cpus();
		cpu_hotplug_driver_unlock();
		mutex_unlock(&bk_helper_mutex); */
//	}
//}


static ssize_t show_boeffla_config_mode(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", get_boeffla_config_mode());
}


static ssize_t store_boeffla_config_mode(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	unsigned int ret = -EINVAL;
	int val;

	ret = sscanf(buf, "%d", &val);

	if (ret != 1)
		return -EINVAL;

	// check for valid input (only 0 and 1)
	if ((val < 0) || (val > 1))
		return -EINVAL;

	// send new value to kernel driver
	set_boeffla_config_mode(val);

	return count;
}


/* Initialize boeffla_config_mode sysfs folder */

static struct kobj_attribute boeffla_config_mode_attribute =
__ATTR(enabled, 0666, show_boeffla_config_mode, store_boeffla_config_mode);

static struct attribute *boeffla_config_mode_attrs[] = {
	&boeffla_config_mode_attribute.attr,
	NULL,
};

static struct attribute_group boeffla_config_mode_attr_group = {
	.attrs = boeffla_config_mode_attrs,
};

static struct kobject *boeffla_config_mode_kobj;


int boeffla_config_mode_init(void)
{
	int boeffla_config_mode_retval;

//	INIT_WORK(&bk_hotplug_work, bk_handle_hotplug);

	boeffla_config_mode_kobj = kobject_create_and_add("boeffla_config_mode", kernel_kobj);

	if (!boeffla_config_mode_kobj)
		return -ENOMEM;

	boeffla_config_mode_retval = sysfs_create_group(boeffla_config_mode_kobj, &boeffla_config_mode_attr_group);

	if (boeffla_config_mode_retval)
		kobject_put(boeffla_config_mode_kobj);

    return (boeffla_config_mode_retval);
}


void boeffla_config_mode_exit(void)
{
	kobject_put(boeffla_config_mode_kobj);
}


/* define driver entry points */
module_init(boeffla_config_mode_init);
module_exit(boeffla_config_mode_exit);
