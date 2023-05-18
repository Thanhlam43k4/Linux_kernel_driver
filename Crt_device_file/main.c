#include<linux/module.h>
#include<linux/fs.h>
#include<linux/device.h>


#define DRIVER_AUTHOR "Nguyen Thanh Lam <nguyenthanhlam71204@gmail.com>"
#define DRIVER_DESC "A sample character device"



struct _vchar_drv{
	dev_t dev_num;
	struct class *dev_class;
	struct device *dev;

}vchar_drv;

static int  __init vchar_driver_init(void)
{	
	int ret =0;
	ret = alloc_chrdev_region(&vchar_drv.dev_num,0,1,"Lam's device");
	if(ret < 0){
		goto failed_register_devnum;
	}

	printk("Allocated device number (%d,%d)\n",MAJOR(vchar_drv.dev_num),MINOR(vchar_drv.dev_num));
	
	vchar_drv.dev_class = class_create(THIS_MODULE,"class_vchar_dev");
	if(vchar_drv.dev_class == NULL){
		printk("Failed to create a device class\n");
		goto failed_create_class;

	}
	vchar_drv.dev = device_create(vchar_drv.dev_class,NULL,vchar_drv.dev_num,NULL,"vchar_dev");
	if(IS_ERR(vchar_drv.dev)){
		printk("Failed to create a device\n");
		goto failed_create_device;

	}
	printk("Initialize vchar driver successfully\n");
	return 0;
	failed_create_device:
		class_destroy(vchar_drv.dev_class);
	failed_create_class:
		unregister_chrdev_region(vchar_drv.dev_num,1);
	failed_register_devnum:
		return ret;


}
static void __exit vchar_driver_exit(void)
{	
	device_destroy(vchar_drv.dev_class,vchar_drv.dev_num);
	class_destroy(vchar_drv.dev_class);



	unregister_chrdev_region(vchar_drv.dev_num,1);
}


module_init(vchar_driver_init);
module_exit(vchar_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

