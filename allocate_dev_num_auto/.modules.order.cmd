cmd_/home/thanhlam/Linux_kernel_device/allocate_dev_num_auto/modules.order := {   echo /home/thanhlam/Linux_kernel_device/allocate_dev_num_auto/main.ko; :; } | awk '!x[$$0]++' - > /home/thanhlam/Linux_kernel_device/allocate_dev_num_auto/modules.order
