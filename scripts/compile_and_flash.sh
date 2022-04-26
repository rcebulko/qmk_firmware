#!/bin/bash
qmk json2c ./layout.json > ./keymap.c && qmk flash
