/*	$Surreal: xkblayout.c,v 1.4 2010/09/28 11:49:47 mitya Exp $	*/

/*
 * Copyright (c) 2008, 2009, 2010 Dmitry Alenichev <mitya@sdf.lonestar.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * xkblayout -- display current xkb keyboard layout
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>

#include "strlcpy.h"

#if defined(__GNUC__)
# ifndef __dead
#  define __dead __attribute__((__noreturn__))
# endif
#endif

void		init(char *);
void		print_layout(int, int);
__dead void	usage(void);

Display		*dpy;
XkbDescPtr	kb;

int
main(int argc, char **argv)
{
	int		lflag, ch;
	char		*display;
	XkbStateRec	state;

	lflag = 0;
	display = getenv("DISPLAY");

	while ((ch = getopt(argc, argv, "d:l")) != -1)
		switch (ch) {
		case 'd':
			display = optarg;
			break;
		case 'l':
			lflag = 1;
			break;
		default:
			usage();
			/* NOTREACHED */
		}

	init(display);

	if (XkbGetNames(dpy, XkbGroupNamesMask, kb) != Success)
		err(1, "Error from XkbGroupNamesMask");

	if (XkbGetState(dpy, XkbUseCoreKbd, &state) != Success)
		err(1, "Error from XkbGetState");
	print_layout(state.group, lflag);

	(void)XkbFreeNames(kb, XkbGroupNamesMask, True);

	return (0);
}

void
init(char *display)
{
	int return_code;

	dpy = XkbOpenDisplay(display, NULL, NULL, NULL, NULL, &return_code);
	if (!dpy) {
		(void)printf("Can't connect to X server: %s\n", display);
		switch (return_code) {
		case XkbOD_BadLibraryVersion:
			(void)printf("Incompatible extension versions\n");
			break;
		case XkbOD_ConnectionRefused:
			(void)printf("Connection refused\n");
			break;
		case XkbOD_NonXkbServer:
			(void)printf("XKB extension not present\n");
			break;
		case XkbOD_BadServerVersion:
			(void)printf("Incompatible extension versions\n");
			break;
		default:
			(void)printf("Error %d from XkbOpenDisplay\n",
			    return_code);
		}
		exit(1);
	}

	if (!(kb = XkbAllocKeyboard()))
		err(1, "Error from XkbAllocKeyboard");
}

void
print_layout(int group, int long_format)
{
	char layout[80];

	(void)strlcpy(layout, XGetAtomName(dpy, kb->names->groups[group]), 80);

	if (long_format)
		(void)printf("%s\n", layout);
	else {
		(void)printf("%.2s\n", layout);
	}
}

void
usage(void)
{
	extern char *__progname;

	(void)fprintf(stderr, "usage: %s [-d display] [-l]\n", __progname);
	exit(1);
}
