MAX_ASSEMBLED_SIZE = 2048

registers = {
    "r0": 0b000,
    "r1": 0b001,
    "r2": 0b010,
    "r3": 0b011,
    "r4": 0b100,
    "r5": 0b101,
    "r6": 0b110,
    "sys": 0b111,
}

opcodes = {
    # add r1 r2 r3
    "add": 0b00,
    
    # not r1 r2
    "not": 0b01,
    
    # set r1 imm
    "set": 0b10,
    
    # jmpz r1 imm/label
    "jmpz": 0b11
}

# in writing pseudo instructions, you may overwrite the sys register but
# otherwise may not write to other registers unless noted as part of the
# operation.
#
# note that the name of the pseduo instruction is stripped from args.
# thus you should expect arg[0] to be the first argument to the instruction.
pseudo = {
    # halt
    # 4 bytes, 2 instructions
    # stop processing
    "halt": lambda args: [
        "set sys 0",
        "jmpz sys 255"],
    
    # twos r1 r2
    # 6 bytes, 3 instructions
    # convert r1's contents to twos complement and store it in r2
    # twos complement for a byte can store values between -128 and +127
    # note that twos(twos(r1)) is an identity function
    "twos": lambda args: [
        "not %s %s" % (args[0], args[1]),
        "set sys 1",
        "add sys %s %s" % (args[1], arg[1])],
    
    # sub r1 r2 r3
    # 8 bytes, 4 instructions
    # r3 <- r2 - r1
    # subtract r1 from r2 using twos complement
    "sub": lambda args: [
        # invert the number to subtract by
        # this is just rewritten twos complement logic
        "not %s %s" % (args[0], args[2]),
        "set sys 1",
        "add sys %s sys" % (args[2]),
        # add the inverted number
        "add sys %s %s" % (args[1], args[2])],
    
    # mov r1 r2
    # 4 bytes, 2 instructions
    # r2 <- r1
    # copy one register to another
    "mov": lambda args: [
        "set sys 0",
        "add sys %s %s" % (args[0], args[1])]
}
