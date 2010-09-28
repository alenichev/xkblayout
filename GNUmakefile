LDADD=		-lX11

CFLAGS+=        -Wall -Werror -Wstrict-prototypes
CFLAGS+=        -Wmissing-prototypes -Wmissing-declarations
CFLAGS+=        -Wshadow -Wpointer-arith -Wcast-qual
CFLAGS+=        -Wsign-compare

SRCS=		xkblayout.c strlcpy.c
OBJS=		$(SRCS:.c=.o)

all:		xkblayout

xkblayout:	$(OBJS)
	$(CC) -o xkblayout $(OBJS) $(LDADD)

clean cleandir:
	rm -f *.o xkblayout *.core core
