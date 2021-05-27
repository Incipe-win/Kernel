/*
 * @Author: incipe
 * @Date: 2021-05-20 15:32:00
 * @Description: The story has just begun!
 */
#include <cfg_type.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/types.h>

#define DEVICE_NAME "Car"
#define CAR_MAGIC 'h'
#define CAR_MAX_NR 5
#define CAR_NUM 4
#define CAR_GO _IO(CAR_MAGIC, 1)
#define CAR_BACK _IO(CAR_MAGIC, 2)
#define CAR_STOP _IO(CAR_MAGIC, 3)
#define CAR_LEFT _IO(CAR_MAGIC, 4)
#define CAR_RIGHT _IO(CAR_MAGIC, 5)
#define MAJOR_NUM 202

struct car {
    int gpio;
    char *name;
};

static struct car car_gpios[] = {
    {PAD_GPIO_C + 7, "left1"},
    {PAD_GPIO_C + 8, "left2"},
    {PAD_GPIO_C + 24, "right1"},
    {PAD_GPIO_C + 25, "right2"},
};

static int car_open(struct inode *inode, struct file *filp) {
    printk(DEVICE_NAME ":open\n");
    return 0;
}

static long car_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    printk("car_num = %d \n", CAR_NUM);
    if (_IOC_TYPE(cmd) != CAR_MAGIC)
        return -EINVAL;
    if (_IOC_NR(cmd) > CAR_MAX_NR)
        return -EINVAL;

    switch (cmd) {
    case CAR_GO:
        printk("CAR_GO\n");
        gpio_set_value(car_gpios[0].gpio, 1);
        gpio_set_value(car_gpios[1].gpio, 0);
        gpio_set_value(car_gpios[2].gpio, 1);
        gpio_set_value(car_gpios[3].gpio, 0);
        break;
    case CAR_BACK:
        gpio_set_value(car_gpios[0].gpio, 0);
        gpio_set_value(car_gpios[1].gpio, 1);
        gpio_set_value(car_gpios[2].gpio, 0);
        gpio_set_value(car_gpios[3].gpio, 1);
        break;
    case CAR_STOP:
        gpio_set_value(car_gpios[0].gpio, 0);
        gpio_set_value(car_gpios[1].gpio, 0);
        gpio_set_value(car_gpios[2].gpio, 0);
        gpio_set_value(car_gpios[3].gpio, 0);
        break;
    case CAR_LEFT:
        gpio_set_value(car_gpios[0].gpio, 1);
        gpio_set_value(car_gpios[1].gpio, 0);
        gpio_set_value(car_gpios[2].gpio, 0);
        gpio_set_value(car_gpios[3].gpio, 0);
        break;
    case CAR_RIGHT:
        gpio_set_value(car_gpios[0].gpio, 0);
        gpio_set_value(car_gpios[1].gpio, 0);
        gpio_set_value(car_gpios[2].gpio, 1);
        gpio_set_value(car_gpios[3].gpio, 0);
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

static struct file_operations car_fops = {
    .owner = THIS_MODULE,
    .open = car_open,
    .unlocked_ioctl = car_ioctl,
};

static int __init car_dev_init(void) {
    int ret, i;
    gpio_free(PAD_GPIO_C + 7);
    gpio_free(PAD_GPIO_C + 8);
    gpio_free(PAD_GPIO_C + 24);
    gpio_free(PAD_GPIO_C + 25);
    for (i = 0; i < CAR_NUM; ++i) {
        ret = gpio_request(car_gpios[i].gpio, car_gpios[i].name);
        if (ret) {
            printk("%s: request GPIO %d for CAR failed, ret = %d\n",
                   car_gpios[i].name, car_gpios[i].gpio, ret);
            return ret;
        }
        gpio_direction_output(car_gpios[i].gpio, 0);
    }
    if ((ret = register_chrdev(MAJOR_NUM, DEVICE_NAME, &car_fops))) {
        printk(DEVICE_NAME "register failure\n");
    } else {
        printk(DEVICE_NAME "register success\n");
    }
    return ret;
}

static void __exit car_dev_exit(void) {
    int i;
    for (i = 0; i < CAR_NUM; i++) {
        gpio_free(car_gpios[i].gpio);
    }
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}

module_init(car_dev_init);
module_exit(car_dev_exit);
MODULE_AUTHOR("incipe");
MODULE_DESCRIPTION("the CAR of driver");
MODULE_LICENSE("GPL");
