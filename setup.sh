#! /bin/bash

# This script is used to run instead of make CONFIG_PATH=product_config/*.config menuconfig
# Usage: ./setup.sh <config_file>   -> e.g., ./setup.sh product_config/ESP8266_GPIO.config

script_name=$(basename ${BASH_SOURCE:-$0})
script_path=$(dirname $(realpath ${script_name}))
config_name=$(basename $1)
out_header=components/Common/include/config/${config_name%.*}_config.h

export COMPONENTS_PATH_ENV=$script_path/components

make CONFIG_PATH=$1 menuconfig

./product_config/genconfig.py --config-file $1 --header-file ${out_header}