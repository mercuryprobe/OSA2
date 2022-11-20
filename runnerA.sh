cd kernel1build/linux-5.19.81/linux-5.19.8
pwd
make mrproper
cd ..
cp .config linux-5.19.81/linux-5.19.8
cd linux-5.19.81/linux-5.19.8
make -j2