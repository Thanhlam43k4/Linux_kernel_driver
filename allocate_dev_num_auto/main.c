#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>

#define DRIVER_AUTHOR "Nguyenthanhlam <nguyenthanhlam71204@gmail.com>"
#define DRIVER_DESC "Allocate automatically device number"



struct _vchar_drv{  //Struct of character device
	dev_t dev_num;

}vchar_drv;

static int __init vchar_driver_init(void) //Function to init vchar driver
{
	int ret =0;
	vchar_drv.dev_num = 0;
	ret = alloc_chrdev_region(&vchar_drv.dev_num,0,1,"Lam's device");   //Allocate device number dynamically by fucn(alloc_chrdev_reigon)
	if(ret < 0){
		printk("failed to register device number dynamically\n");
		goto failed_register_devnum;

	}
	printk("Allocated device number (%d,%d)\n",MAJOR(vchar_drv.dev_num),MINOR(vchar_drv.dev_num));
	printk("Initialize vchar driver successfully\n");
	return 0;

	failed_register_devnum:
		return ret;

}


static void __exit vchar_driver_exit(void) //Function to exit vchar driver
{
	unregister_chrdev_region(vchar_drv.dev_num,1);
	printk("Exit vchar driver\n");

}
module_init(vchar_driver_init);
module_exit(vchar_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

