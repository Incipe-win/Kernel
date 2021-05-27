#include <cfg_type.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/types.h>

static int __init lkm_init(void) {
  printk("Hello World\n");
  return 0;
}

static void __exit lkm_exit(void) { printk("GoodBye\n"); }

module_init(lkm_init);
module_exit(lkm_exit);
MODULE_LICENSE("GPL");
