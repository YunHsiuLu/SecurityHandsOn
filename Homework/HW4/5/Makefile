all:
	sudo sysctl -w kernel.randomize_va_space=0
	gcc -m32 -fno-stack-protector -z noexecstack -o stack_rop stack_rop.c
	sudo chown root stack_rop && sudo chmod 4755 stack_rop
clean:

