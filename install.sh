#Number of threads to use for compile
#default : Number of cores
nproc= $(nproc)

# Change prefix to where you want to download sdl source
prefix=~/sdl_source

############ END OF USER SETTINGS ############

sudo apt-get install libxext-dev libfreetype6-dev
if [ ! -d $prefix ]; then
    mkdir $prefix
fi
# SDL2
cd $prefix
if [ ! -e SDL2-2.0.10.tar.gz ]; then
    wget https://www.libsdl.org/release/SDL2-2.0.10.tar.gz
fi 
tar -xf SDL2-2.0.10.tar.gz
cd SDL2-2.0.10/
if [ ! -d build ]; then
    mkdir build
fi
cd build
../configure
make -j$nproc
sudo make install
# SDL2_image
cd $prefix
if [ ! -e SDL2_image-2.0.5.tar.gz ]; then
    wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
fi
tar -xf SDL2_image-2.0.5.tar.gz
cd SDL2_image-2.0.5/
if [ ! -d build ]; then
    mkdir build
fi
cd build
../configure
make -j$nproc
sudo make install
#SDL2_ttf
cd $prefix
if [ ! -e SDL2_ttf-2.0.15.tar.gz ]; then
    wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz
fi 
tar -xf SDL2_ttf-2.0.15.tar.gz
cd SDL2_ttf-2.0.15/
if [ ! -d build ]; then
    mkdir build
fi
cd build
../configure
make -j$nproc
sudo make install