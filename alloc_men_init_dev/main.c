#include<linux/device.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include "main.h"


#define DRIVER_AUTHOR "Nguyen Thanh Lam <ngueynthanhlam71204@gmail.com>"
#define DRIVER_DESC "Allocate memory and Init Device"

typedef struct vchar_dev{
	unsigned char *control_regs;
	unsigned char *status_regs;
	unsigned char *data_regs;


}vchar_dev_t;

struct _vchar_drv{
	dev_t dev_num;
	struct class *dev_class;
	struct device *dev;
	vchar_dev_t *vchar_hw;
	
}vchar_drv;

/******************* device  specific - Start ***********************/
/* Ham khoi tao thiet bi */

int vchar_hw_init(vchar_dev_t *hw)
{
	char *buf;
	buf = kzalloc(NUM_DEV_REGS * REG_SIZE,GFP_KERNEL);
	if(!buf){
		return -ENOMEM;

	}
	hw->control_regs = buf;
	hw->status_regs = hw->control_regs + NUM_CTRL_REGS;
	hw->data_regs = hw->status_regs + NUM_STS_REGS;
	//Khoi tao cac gia tri ban dau cho cac thanh ghi
	hw->control_regs[CONTROL_ACCESS_REG] = 0x03;
	hw->status_regs[DEVICE_STATUS_REG] = 0x03;


	return 0;

}
void vchar_hw_exit(vchar_dev_t *hw)
{
	kfree(hw->control_regs);
}
static int __init vchar_driver_init(void)
{
	int ret = 0;
	vchar_drv.vchar_hw = kzalloc(sizeof(vchar_dev_t),GFP_KERNEL);
	if(!vchar_drv.vchar_hw){
		printk("Failed to allocate data structure of the driver\n");
		ret = -ENOMEM;
		goto failed_allocate_structure;
	}
	ret =vchar_hw_init(vchar_drv.vchar_hw);
	if(ret < 0){
		printk("failed to initialize a virtual character device\n");
		goto failed_init_hw;
	}

	

	printk("Initialize vchar driver  successfully\n");
	
	failed_init_hw:
		kfree(vchar_drv.vchar_hw);
	failed_allocate_structure:
		device_destroy(vchar_drv.dev_class,vchar_drv.dev_num);

		return 0;	
}
static void __exit vchar_driver_exit(void)
{
	/* Giai phong thiet bi vat ly */
	vchar_hw_exit(vchar_drv.vchar_hw);

	/*Giai phong bo nho da cap nhat cau truc du lieu cua driver ! */
	kfree(vchar_drv.vchar_hw);


	/*xoa bo device file */

	device_destroy(vchar_drv.dev_class, vchar_drv.dev_num);

}
module_init(vchar_driver_init);
module_exit(vchar_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
