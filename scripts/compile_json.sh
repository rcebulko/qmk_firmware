#!/bin/bash
layout_path=../keyboards/$1/keymaps/rcebulko;
qmk json2c $layout_path/layout.json > $layout_path/keymap.c;
qmk compile --keyboard $1;
