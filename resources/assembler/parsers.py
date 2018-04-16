# project imports
from constants import *

class ImmediateParseError(ValueError):
    pass

def parse_immediate(token):
    value = None
    try:
        if token.strip("'").isalpha():
            value = ord(token.strip("'"))
        elif token.startswith("0x"):
            value = int(token, 16)
        elif token.startswith("0b"):
            value = int(token, 2)
        elif token.startswith("-"):
            value = int(token, 10) + 256
        else:
            value = int(token, 10)       
            
        if value > 255:
            raise ImmediateParseError() 
        return value
    
    except ImmediateParseError as e:
        raise ValueError("immediate token %s value of %s is out of range (<= 255)" % (token, value))
    except ValueError as e:
        raise ValueError("invalid immediate %s") from e

def parse_opcode(token):
    try:
        return opcodes[token]
    except:
        raise ValueError("No such instruction: %s" % (token))

def parse_register(token):
    try:
        return registers[token]
    except:
        raise ValueError("No such register: %s" % (token))
    
def parse_immediate_or_label(token, labels):
    if token in labels:
        return labels[token]
    return parse_immediate(token)

def parse_add(instruction):
    opcode = parse_opcode(instruction[0])
    rx = parse_register(instruction[1])
    ry = parse_register(instruction[2])
    rz = parse_register(instruction[3])
    byte1 = (opcode << 6) | (rx << 3) | ry
    byte2 = (rz << 5)
    return (byte1, byte2)

def parse_not(instruction):
    opcode = parse_opcode(instruction[0])
    rx = parse_register(instruction[1])
    ry = parse_register(instruction[2])
    byte1 = (opcode << 6) | (rx << 3) | ry
    return (byte1, 0)

def parse_loadi(instruction):
    opcode = parse_opcode(instruction[0])
    rx = parse_register(instruction[1])
    byte1 = (opcode << 6) | (rx << 3)
    byte2 = parse_immediate(instruction[2])
    return (byte1, byte2)

def parse_jmpz(instruction, labels):
    opcode = parse_opcode(instruction[0])
    rx = parse_register(instruction[1])
    byte1 = (opcode << 6) | (rx << 3)
    byte2 = parse_immediate_or_label(instruction[2], labels)
    return (byte1, byte2)
    
def parse_instruction(instruction, labels):
    try:
        if instruction[0] == "add":
            return parse_add(instruction)
        if instruction[0] == "not":
            return parse_not(instruction)
        if instruction[0] == "set":
            return parse_loadi(instruction);
        if instruction[0] == "jmpz":
            return parse_jmpz(instruction, labels)
        raise ValueError("Unknown instruction %s" % (' '.join(instruction)))
    except ValueError as e:
        raise ValueError("Failed to parse instruction %s" % (' '.join(instruction))) from e
