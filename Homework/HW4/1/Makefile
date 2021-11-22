all:
	gcc -m32 -fno-stack-protector -z noexecstack -o retlib retlib.c
	sudo chown root retlib && sudo chmod 4755 retlib
	gcc -m32 -fno-stack-protector -z noexecstack -o prtenv prtenv.c
	sudo chown root prtenv && sudo chmod 4755 prtenv
clean:

