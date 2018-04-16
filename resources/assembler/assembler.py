#!/usr/bin/env python3
"""
  assembler.py
  
  Created on: Apr 14, 2018
  Author: ben
"""
import os.path
import argparse

# project imports
from constants import *
from parsers import *

def parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file", help="the input file to assemble")
    parser.add_argument("-d", "--debug", default=False, action='store_true')
    return parser.parse_args()

def main(input_file):
    lines = list()
    with open(input_file) as f:
        lines = [x.strip().lower() for x in f]
    
    # strip out all the comments
    lines = [l for l in lines if not l.startswith('#')]
    
    # strip out all empty lines
    lines = [l for l in lines if l]
    
    # parse out the tokens
    lines = [l.split() for l in lines]
    
    # expand all the pseudo instructions
    expanded = list()
    for line in lines:
        if line[0] in pseudo:
            for l in pseudo[line[0]](line[1:]):
                # split the lines to match already split tokens
                expanded.append(l.split())
        else:
            expanded.append(line)
    
    # we are now at the point where one line is one instruction
    # and there is a 1:1 mapping to bytes
    
    # convert all the labels to byte addresses
    current_instruction = 0
    labels = dict()
    instructions = list()
    for line in expanded:
        if line[0].endswith(':'):
            labels[line[0].strip(':')] = current_instruction
        else:
            instructions.append(line)
            current_instruction += 1
        
    # convert all instructions to bytes
    converted = list()
    for instruction in instructions:
        converted.extend(parse_instruction(instruction, labels))
        
    # change the file extension to .o
    path, file = os.path.split(input_file)
    file = file.split('.')[0] + '.o'
    path = os.path.join(path, file)
    
    if len(converted) > MAX_ASSEMBLED_SIZE:
        raise ValueError("program size is %s bytes, max allowed is %s bytes" % (len(converted), MAX_ASSEMBLED_SIZE))
    
    # save the output file
    with open(path, "wb") as f:
        f.write(bytes(converted))
        
        
if __name__ == "__main__":
    args = parse()
    
    # simplify the exception handler if not using debug flag
    if not args.debug:
        import sys
        def exception_handler(exception_type, exception, traceback):
            print("%s" % (exception))
            exc = exception.__cause__
            while exc is not None:
                print("caused by: %s" % (exc))
                exc = exc.__cause__ 
        sys.excepthook = exception_handler
        
    main(args.input_file)
            