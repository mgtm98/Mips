#!/usr/bin/env python3
import sys


def is_instruction(word):
    instructions = (
        'add', 'sub', 'and', 'or', 'xor', 'nor', 'slt', 'sll', 'sra', 'srl', 'jr', 'j', 'jal', 'addi', 'andi', 'ori',
        'xori', 'slti', 'lui', 'lw', 'lh', 'lb', 'sw', 'sh', 'sb', 'beq', 'bne', 'nop')
    if word in instructions:
        return True
    else:
        return False


def is_register(word):
    registerss = (
        '$zero', '$at', '$v0', '$v1', '$a0', '$a1', '$a2', '$a3', '$t0', '$t1', '$t2', '$t3', '$t4', '$t5', '$t6',
        '$t7',
        '$s0', '$s1', '$s2', '$s3', '$s4', '$s5', '$s6', '$s7', '$t8', '$t9', 'k0', '$k1', '$gp', '$sp', '$fp', '$ra')
    if word in registerss:
        return True
    else:
        return False


def is_r(word):
    instructions = ('add', 'sub', 'and', 'or', 'xor', 'nor', 'slt', 'sll', 'sra', 'srl', 'jr')
    if word in instructions:
        return True
    else:
        return False


def is_r_arithmetic(word):
    instructions = ('add', 'sub', 'and', 'or', 'xor', 'nor', 'slt')
    if word in instructions:
        return True
    else:
        return False


def is_r_shift(word):
    instructions = ('sll', 'sra', 'srl')
    if word in instructions:
        return True
    else:
        return False


def is_r_jump(word):
    return word == "jr"


def is_i_arithmetic_memory(word):
    instructions = ('addi', 'andi', 'ori', 'xori', 'slti', 'lui', 'lw', 'lh', 'lb', 'sw', 'sh', 'sb')
    if word in instructions:
        return True
    else:
        return False


def is_i_branch(word):
    instructions = ('beq', 'bne')
    if word in instructions:
        return True
    else:
        return False


def is_j(word):
    instructions = ('j', 'jal')
    if word in instructions:
        return True
    else:
        return False


def is_jump(word):
    if word[-1] == ":":
        return True
    else:
        return False


def is_number(word):
    return word.isnumeric()


def decimal_to_binary5(decimal):
    return '{0:05b}'.format(int(decimal))


def decimal_to_binary16(decimal):
    result = ('{0:016b}'.format(int(decimal)))
    if int(result) < 0:
        result1 = ""
        result = "0" + result[1:]
        flag = False
        for letter in result[::-1]:
            if letter == "0" and flag == False:
                result1 += letter
            elif letter == "0" and flag == True:
                result1 += "1"
            elif letter == "1" and flag == False:
                result1 += letter
                flag = True
            elif letter == "1" and flag == True:
                result1 += "0"
        return result1[::-1]
    return result


def decimal_to_binary26(decimal):
    return '{0:026b}'.format(int(decimal))


def decimal_to_binary32(decimal):
    return '{0:032b}'.format(int(decimal))


instruction_to_op = {
    'add': "000000",
    'sub': "000000",
    'and': "000000",
    'or': "000000",
    'xor': "000000",
    'nor': "000000",
    'slt': "000000",
    'sll': "000000",
    'sra': "000000",
    'srl': "000000",
    'jr': "000000",
    'nop': "000000",
    'j': "000010",
    'jal': "000011",
    'addi': "001000",
    'andi': "001100",
    'ori': "001101",
    'xori': "001110",
    'slti': "001010",
    'lui': "001111",
    'lw': "100011",
    'lh': "100001",
    'lb': "100000",
    'sw': "101011",
    'sh': "101001",
    'sb': "101000",
    'beq': "000100",
    'bne': "000101",
}

instruction_to_funct = {
    'add': "100000",
    'sub': "100010",
    'and': "100100",
    'or': "100101",
    'xor': "100110",
    'nor': "100111",
    'slt': "101010",
    'sll': "000000",
    'sra': "000011",
    'srl': "000010",
    'jr': "001000"
}

register_to_code = {
    '$zero': '00000',
    '$0': '00000',
    '$at': '00001',
    '$v0': '00010',
    '$v1': '00011',
    '$a0': '00100',
    '$a1': '00101',
    '$a2': '00110',
    '$a3': '00111',
    '$t0': '01000',
    '$t1': '01001',
    '$t2': '01010',
    '$t3': '01011',
    '$t4': '01100',
    '$t5': '01101',
    '$t6': '01110',
    '$t7': '01111',
    '$s0': '10000',
    '$s1': '10001',
    '$s2': '10010',
    '$s3': '10011',
    '$s4': '10100',
    '$s5': '10101',
    '$s6': '10110',
    '$s7': '10111',
    '$t8': '11000',
    '$t9': '11001',
    '$k0': '11010',
    '$k1': '11011',
    '$gp': '11100',
    '$sp': '11101',
    '$fp': '11110',
    '$ra': '11111',
}

instructions_and_jumps = []
jumps = []
registers = []
numbers = []
file_name = ""
if len(sys.argv) > 1:
    file_name = sys.argv[1]
else:
    file_name = "test.txt"
lines = [line.rstrip('\n') for line in open(file_name)]
for line in lines:
    line = line.replace(',', ' ')
    line = line.replace('\n', ' ')
    line = line.replace('(', ' ')
    line = line.replace(')', ' ')
    words = line.split()
    for str in words:
        if is_register(str):
            registers.append(str)
        elif is_number(str):
            numbers.append(str)
        elif is_instruction(str):
            instructions_and_jumps.append(str)
        elif str[-1] == ":":
            instructions_and_jumps.append(str)
        else:
            jumps.append(str)
number_pointer = 0
jump_pointer = 0
register_pointer = 0
full_code = ""
for index, word in enumerate(instructions_and_jumps):
    if is_instruction(word):
        full_code += instruction_to_op[word]
        if word == 'nop':
            full_code += "00000000000000000000000000"
        elif is_r_arithmetic(word):
            full_code += register_to_code[registers[register_pointer + 1]]
            full_code += register_to_code[registers[register_pointer + 2]]
            full_code += register_to_code[registers[register_pointer]]
            full_code += "00000"
            full_code += instruction_to_funct[word]
            register_pointer += 3
        elif is_r_shift(word):
            full_code += "00000"
            full_code += register_to_code[registers[register_pointer + 1]]
            full_code += register_to_code[registers[register_pointer]]
            full_code += decimal_to_binary5(numbers[number_pointer])
            full_code += instruction_to_funct[word]
            register_pointer += 2
            number_pointer += 1
        elif is_r_jump(word):
            full_code += register_to_code[registers[register_pointer]]
            full_code += "00000"
            full_code += "00000"
            full_code += "00000"
            full_code += instruction_to_funct[word]
            register_pointer += 1
        elif word == "lui":
            full_code += "00000"
            full_code += register_to_code[registers[register_pointer]]
            full_code += decimal_to_binary16(numbers[number_pointer])
            register_pointer += 1
            number_pointer += 1
        elif is_i_arithmetic_memory(word):
            full_code += register_to_code[registers[register_pointer + 1]]
            full_code += register_to_code[registers[register_pointer]]
            full_code += decimal_to_binary16(numbers[number_pointer])
            register_pointer += 2
            number_pointer += 1
        elif is_i_branch(word):
            full_code += register_to_code[registers[register_pointer]]
            full_code += register_to_code[registers[register_pointer + 1]]
            jump_position = instructions_and_jumps.index(jumps[jump_pointer] + ":")
            counter = 0
            if index > jump_position:
                for i in range(jump_position, index + 1):
                    if is_instruction(instructions_and_jumps[i]):
                        counter += 1
                counter = -counter
            elif index < jump_position:
                for i in range(index + 1, jump_position + 1):
                    if is_instruction(instructions_and_jumps[i]):
                        counter += 1
            else:
                counter = -1
            full_code += decimal_to_binary16(counter)
            register_pointer += 2
            jump_pointer += 1
        elif is_j(word):
            counter = 0
            jump_position = instructions_and_jumps.index(jumps[jump_pointer] + ":")
            for word in instructions_and_jumps[:jump_position]:
                if is_instruction(word):
                    counter += 1
            counter *= 4
            full_code += decimal_to_binary32(counter)[4:30]
        full_code += "\n"
file_name = ""
if (len(sys.argv) == 3):
    file_name = sys.argv[2]
else:
    file_name = "result.txt"
file = open(file_name, "w")
file.write(full_code)
file.close()
print("Done")
