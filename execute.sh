#! /bin/sh
make clean
make
sudo rmmod split_ll_module
if [[ $1 -ne 0 ]]
then
    sudo insmod split_ll_module.ko size=$1
    sudo dmesg
else
    echo "invaild size input"
fi
exit 0;