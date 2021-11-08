all:
	gcc -m32 -fno-stack-protector -z noexecstack -o stack stack.c
	gcc -m32 -fno-stack-protector -z noexecstack -g -o stack-dbg stack.c
	gcc -m32 env.c -o env55
	gcc -m32 -g env.c -o env55-dbg
	sudo sysctl -w kernel.randomize_va_space=0
	sudo chown root stack && sudo chmod 4755 stack
	sudo chown root stack-dbg && sudo chmod 4755 stack-dbg
clean:
