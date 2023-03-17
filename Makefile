#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := IoT_base

ifdef CONFIG_PATH
SDKCONFIG := $(abspath ./$(CONFIG_PATH))
CONFIG_NAME := $(notdir $(patsubst %.config,%,$(CONFIG_PATH)))
BUILD_DIR_BASE := $(abspath ./build/$(CONFIG_NAME))
else
$(error "Specify a configuration file, e.g. CONFIG_PATH=proj.config")
endif

include $(IDF_PATH)/make/project.mk

