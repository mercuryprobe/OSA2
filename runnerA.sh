#!/bin/bash
cd kernelbuild/linux-5.19.81/linux-5.19.8 && make mrproper
cp .config linux-5.19.81/linux-5.19.8
cd linux-5.19.81/linux-5.19.8 && make -j2