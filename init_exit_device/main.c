#include<Linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>

#define DRIVER_AUTHOR "Nguyen Thanh Lam"
#define DRIVER_DESC "A Init Exit function of device file"


static int __init init_program(void)
{
	printk("Initialize driver successfully");
	return 0;

}
static void __exit exit_program(void)
{
	printk("Exit driver");

}
module_init(init_program);
module_exit(exit_program);


MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);



