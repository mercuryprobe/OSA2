#!/bin/bash
cd /home/mercury/osAssignment/osAssignment2/OSA2/kernelbuild/linux-5.19.82/linux-5.19.8 && make mrproper
cp /home/mercury/osAssignment/osAssignment2/OSA2/kernelbuild/.config /home/mercury/osAssignment/osAssignment2/OSA2/kernelbuild/linux-5.19.82/linux-5.19.8
cd /home/mercury/osAssignment/osAssignment2/OSA2/kernelbuild/linux-5.19.82/linux-5.19.8 && make -j2