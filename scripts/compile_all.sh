#!/bin/bash
node ./convert_layout.js;
./compile_json.sh redox;
./compile_json.sh minidox;
