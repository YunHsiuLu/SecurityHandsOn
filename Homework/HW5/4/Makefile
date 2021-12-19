all:
	gcc -D BUFSIZE=5000 -m32 fmtvul.c
	sudo sysctl -w kernel.randomize_va_space=0
