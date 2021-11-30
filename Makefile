SRCS = cursor.c input.c main.c misc.c pager.c row.c table.c vm.c

db:
	cc -o db $(SRCS)
