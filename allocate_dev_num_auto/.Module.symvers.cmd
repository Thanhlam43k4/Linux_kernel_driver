cmd_/home/thanhlam/Linux_kernel_device/allocate_dev_num_auto/Module.symvers := sed 's/ko$$/o/' /home/thanhlam/Linux_kernel_device/allocate_dev_num_auto/modules.order | scripts/mod/modpost -m -a  -o /home/thanhlam/Linux_kernel_device/allocate_dev_num_auto/Module.symvers -e -i Module.symvers   -T -