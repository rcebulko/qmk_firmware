#!/usr/bin/bash

cd keyboards/maple_computing/minidox/keymaps/rcebulko
./convert_json.sh
cd ../../../../..
make maple_computing/minidox/rev1:rcebulko:flash
