SRCS = cursor.c input.c main.c misc.c node.c pager.c row.c table.c vm.c

db: $(SRCS)
	cc -o db $(SRCS)
