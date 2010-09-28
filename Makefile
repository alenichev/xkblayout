# $Surreal: Makefile,v 1.1.1.1 2009/08/26 06:04:47 mitya Exp $

.include <bsd.xconf.mk>

PROG=		xkblayout
MAN=		xkblayout.1

CPPFLAGS+=	-I${X11BASE}/include
LDADD+=		-L${X11BASE}/lib -lX11

CFLAGS+=	-Wall -Werror -Wstrict-prototypes
CFLAGS+=	-Wmissing-prototypes -Wmissing-declarations
CFLAGS+=	-Wshadow -Wpointer-arith -Wcast-qual
CFLAGS+=	-Wsign-compare -Wbounded
CLEANFILES+=	xkblayout.cat1

BINDIR?=	/usr/local/bin

.include <bsd.prog.mk>
