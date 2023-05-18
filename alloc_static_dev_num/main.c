#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>


#define DRIVER_AUTHOR "Nguyen Thanh Lam"
#define DRIVER_DESC "Allocate statically dev_num for device file"



struct _vchar_drv{			//Struct of character device
	dev_t dev_num;
}vchar_drv;


static int __init vchar_driver_init(void)
{
	int ret = 0;
	vchar_drv.dev_num = MKDEV(238,0);
	
	ret = register_chrdev_region(vchar_drv.dev_num,1,"vchar_driver"); //Allocate dev_num statically by register_chrdev_region
	if(ret < 0){
		printk("Failed to register dev_num statically\n");    
		goto Failed_register_dev;
	}
	printk("Initialize successfully dev_num statically\n");
	return 0;
	Failed_register_dev:
		return ret;
}
static void __exit vchar_driver_exit(void)
{
	unregister_chrdev_region(vchar_drv.dev_num,1);
	printk("Exit vchar driver");

}
module_init(vchar_driver_init);
module_exit(vchar_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);




