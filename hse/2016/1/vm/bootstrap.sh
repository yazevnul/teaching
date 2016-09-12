#!/bin/bash

apt-get update
apt-get install -y software-properties-common

# for those who love GCC
add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-get update
apt-get install -y gcc-6 g++-6 gdb
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6

# for those who are a fans of Clang and LLVM
wget -O - http://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
apt-add-repository 'deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.9 main'
apt-get update
apt-get install -y clang-3.9 lldb-3.9
update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.9 60 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-3.9
update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-3.9 60
update-alternatives --install /usr/bin/lldb-server lldb-server /usr/bin/lldb-server-3.9 60

# those are better than a regular libstdc++, but requires `--stdlib=libc++` when compiling
apt-get install -y libc++-dev libc++abi-dev

# Installing linux "perf" tool
# See https://perf.wiki.kernel.org/index.php/Tutorial
apt-get install -y "linux-tools-$(uname -r)"
sh -c 'echo 0 > /proc/sys/kernel/kptr_restrict'
sh -c 'echo -1 > /proc/sys/kernel/perf_event_paranoid'
