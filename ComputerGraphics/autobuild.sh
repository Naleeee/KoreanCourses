#!/bin/bash

NoColor="\033[0m"
CyanColor="\033[0;36m"

args=""

if [[ "$*" == *"re"* ]] ; then
    echo -e "${CyanColor}Recompiling all the project${NoColor}"
    rm -rf build
fi

mkdir -p ./build && cd ./build

if [[ "$*" == *"cc"* ]] ; then
    echo -e "${CyanColor}Creating compile_commands.json file${NoColor}"
    args="$args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
fi

if [[ "$*" == *"debug"* ]] ; then
    echo -e "${CyanColor}Compiling project in debug mode${NoColor}"
    cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ $args
elif [[ "$*" == *"release"* ]] ; then
    echo -e "${CyanColor}Compiling project in release mode${NoColor}"
    cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++ $args
else
    cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++ $args
fi

cmake --build .

if [[ "$*" == *"cc"* ]] ; then
    mv compile_commands.json ..
fi

