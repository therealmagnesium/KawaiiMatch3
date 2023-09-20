#!/bin/bash
cd build

if [ "$1" == "clean" ]; then
    make clean

    echo -n "Would you like to remove config files too? (y/n): "
    read removeConfig
    if [ $removeConfig == 'y' ]; then
        rm Makefile
    fi

    cd ..
elif [ "$1" == "run" ]; then
    cd KawaiiMatch3
    ./KawaiiMatch3
    cd ../..
else
    if [ "$1" == "debug" ]; then
        cmake -DCMAKE_BUILD_TYPE=Debug ..
    elif [ "$1" == "release" ]; then
        cmake -DCMAKE_BUILD_TYPE=Release ..
    fi

    mv compile_commands.json ..
    cp -r ../assets .

    make all -j7

    #    echo -n "Would you like to run the project? (y/n): "
    #    read execute
    #    if [ $execute == 'y' ]; then
    #       ./KawaiiMatch3
    #   fi

    cd ../..
fi
