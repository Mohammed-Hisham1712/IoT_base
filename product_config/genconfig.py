#! /usr/bin/python3

import os
import stat
import argparse
import sys

"""
Generate a header file with #defines from configuration file.

By default the configuration is generated from .config file. A different
file can be specified using --config-file <config_file> argument.

The generated file is saved as config.h by default. A different file name
can be specified using --header-file <header_file> argument.

"""

def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=__doc__)
    
    parser.add_argument(
        "--header-file",
        metavar="HEADER_FILE",
        help="""
        Path to write the generated header file to. If not specified, it 
        defaults to config.h""")

    parser.add_argument(
        "--config-file",
        metavar="CONFIG_FILE",
        help="""
        The configuration header is generated from this file. If not specified it
        defaults to .config
        """)

    args = parser.parse_args()

    if args.header_file is not None:
        header_file = args.header_file
    else:
        header_file = 'config.h'
    
    if args.config_file is not None:
        config_file = args.config_file
    else:
        config_file = '.config'
    
    if os.path.isfile(config_file) is False:
        print('Error: %s no such file' %(header_file))
        return
    
    fstat = os.stat(config_file)
    if bool(fstat.st_mode & stat.S_IRUSR) is not True:
        print('Error: Cannot read %s. Permission denied' %(config_file))
        return
    
    if os.path.isfile(header_file) is True:
        fstat = os.stat(header_file)
        if bool(fstat.st_mode & stat.S_IWUSR) is not True:
            print('Error: Cannot write to %s. Permission denied' %(header_file))
            return
    else:
        full_path = os.path.realpath(header_file)
        dir = os.path.dirname(full_path)
        fstat = os.stat(dir)
        if bool(fstat.st_mode & stat.S_IWUSR) is not True:
            print('Error: Cannot create %s. Permission denied' %(header_file))
            return
    
    with open(config_file, 'r') as rfile:
        with open(header_file, 'w') as wfile:
            pass

if __name__ == "__main__":
    main()