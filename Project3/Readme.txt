The program is a customized shell that receives the input from the user until they type in "quit". The shell has 2 customized internal commands called "cd" and "path". Since this shell is not using the default path, the user has to manually add different directories by using "path +" or remove directories by using "path -". After finishing adding directory, the user can then use any linux command. The program will look into the stored directories libraries to search for the corresponding commands and try to execute it. The single.c file is a single link list used to store all the directories added by path +. Using single linklist allows the implementation of path + and path - become more simpler.  

Files are included in the submission folder:
	main.c makefile shell.c shell.h single.c

COMPILING INSTRUCTION:
	In the terminal, change directory to Group_D directory then type make.

RUNNING INSTRUCTIONS:
	./main

NEXT: right after the sign $, type in path + then to add directories. After finishing adding directories, user can input any linux commands. Type path - to remove paths, type quit to quit the shell.

SAMPLE TEST RUN:

EXISTING BUGS: 
	none
	
