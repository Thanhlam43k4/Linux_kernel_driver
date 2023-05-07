#include<linux/module.h>
#include<linux/kernel.h>

#define DRIVER_AUTHOR "Nguyenthanhlam <nguyenthanhlam71204@gmail.com>"
#define DRIVER_DESC "A sample character device"
#define DRIVER_ADD "hi"

static int __init hello_world_init(void)   //Initialize module

{
	printk("Hello wolrd!\n");
	return 0;

}
static void __exit hello_world_exit(void)  //Exiting Module
{
	printk("Exit program!\n");

}



module_init(hello_world_init);
module_exit(hello_world_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);		//Function to describe about your module
MODULE_DESCRIPTION(DRIVER_DESC);


