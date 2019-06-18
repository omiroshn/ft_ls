# ft_ls
System function ls is recoded on this git repository.

From BSD General Commands Manual:
	
	NAME
		ls -- list directory contents

	SYNOPSIS
		ls [-ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1] [file ...]

	DESCRIPTION
		For each operand that names a file of a type other than directory, ls displays its name as well as any requested,
		associated information.  For each operand that names a file of type directory, ls displays the names of files con-
		tained within that directory, as well as any requested, associated information.

	 	If no operands are given, the contents of the current directory are displayed.  If more than one operand is given,
	 	non-directory operands are displayed first; directory and non-directory operands are sorted separately and in lexico-
		graphical order.

for more information search in BSD General Commands Manual.

However the synopsis of my ls is:
```
./ft_ls [-lRartufgds1] [file ...]
```

**To compile a binary that will list directories** you should do **`make`**. After what you can watch through any directory (if you have such permisions of course).
**To inititalise ft_ls** you should write:
```
./ft_ls
```
That's it!
Every option (such as -l or -a) is implemented due to the option of original ls, so u can watch how it works and compare with my function!

Images of original ls and ft_ls:

<img src="https://github.com/omiroshn/ft_ls/blob/master/img/Screen%20Shot%202019-06-18%20at%204.45.06%20PM.png">

<img src="https://github.com/omiroshn/ft_ls/blob/master/img/Screen%20Shot%202019-06-18%20at%204.45.12%20PM.png">

<img src="https://github.com/omiroshn/ft_ls/blob/master/img/Screen%20Shot%202019-06-18%20at%204.46.19%20PM.png">

<img src="https://github.com/omiroshn/ft_ls/blob/master/img/Screen%20Shot%202019-06-18%20at%204.46.59%20PM.png">

Additional info:

Makefile functions:
- `make/make all` - compiles a binary named `ft_ls`;
- `make clean` - removes every object file from `obj` directory;
- `make fclean` - the same as `make clean` + removes binary file `ft_ls`;
- `make re` - the same as `make fclean` + `make`.
