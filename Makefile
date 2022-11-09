tcc:
	tcc test.c -o build/test.tcc.exe
	build/test.tcc.exe

gcc:
	gcc -Wall -Wextra -Os test.c -o build/test.gcc.exe

win:
	powershell "Measure-Command { make | Out-Default }"
