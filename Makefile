# Make sex

PROG=sex
PREFIX?=/usr/local
BINDIR=${PREFIX}/bin
MANDIR=${PREFIX}/man/man
MAN6=sex.6

.include <bsd.prog.mk>
