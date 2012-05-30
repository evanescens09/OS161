#!/bin/bash

cd src
./configure --ostree=$HOME/CSCC69/root
cd kern/conf/
./config ASST1
cd ../compile/ASST1
bmake depend
bmake
bmake install
cd ../../..
bmake
bmake install
cd $HOME/CSCC69
cp src/sys161.conf root
cd root

