#! /bin/bash

name=$(basename ${BASH_SOURCE:-$0})
path=$(dirname $(realpath ${name}))

export COMPONENTS_PATH_ENV=$path/components