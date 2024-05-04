#!/usr/bin/env bash

# bash build.sh 2>/dev/null | grep " changed from " | awk '{print $2,$5$7}' | tr ':' ' ' | sort -k 2 | grep -E "m-|-m|n-|-n|-y|y-" | tee a.txt
# g++ -o annotation annotation.cc; ./annotation a.txt debian.master/config/annotations debian.master/config/annotations
sudo apt-get install -y dwarves pahole dpkg-dev libbabeltrace-dev libpfm4-dev systemtap-sdt-dev clang libperl-dev binutils-dev binutils-multiarch-dev python3-libfdt llvm
sudo apt-get build-dep -y linux-image-unsigned-6.8.0-31-generic

dpkg-buildpackage -nc 2>&1 | tee build.log

