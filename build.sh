#!/usr/bin/env bash

sudo apt-get install -y dwarves pahole dpkg-dev libbabeltrace-dev libpfm4-dev systemtap-sdt-dev clang
sudo apt-get build-dep -y linux-image-unsigned-6.8.0-31-generic

dpkg-buildpackage -nc 2>&1 | tee build.log

