#!/bin/sh
# copy binary to SD, sync and unmount
cp ../Output/fip.bin /run/media/ericb/22A5-5645/
sync
umount /dev/sdd1
