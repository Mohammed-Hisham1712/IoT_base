#! /bin/bash

# This script is used to run instead of make CONFIG_PATH=product_config/*.config menuconfig
# Usage: ./setup.sh <config_file>   -> e.g., ./setup.sh product_config/ESP8266_GPIO.config

name=$(basename ${BASH_SOURCE:-$0})
path=$(dirname $(realpath ${name}))

export COMPONENTS_PATH_ENV=$path/components

make CONFIG_PATH=$1 menuconfig