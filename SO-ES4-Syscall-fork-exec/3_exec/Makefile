all: cp_exe ls_exe

cp_exe: main_cp.c
	gcc -o cp_exe main_cp.c

ls_exe: main_ls.c
	gcc -o ls_exe main_ls.c

clean:
	rm -rf cp_exe
	rm -rf ls_exe
	rm -rf *.o
