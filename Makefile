DESTDIR=
PREFIX=/usr/local
all:
clean:
install:
	mkdir -p $(DESTDIR)$(PREFIX)/include
	cp telluser.h $(DESTDIR)$(PREFIX)/include


## -- manpages --
ifneq ($(PREFIX),)
MAN_3=./telluser.3 
install: install-man3
install-man3: $(MAN_3)
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp $(MAN_3) $(DESTDIR)$(PREFIX)/share/man/man3
endif
## -- manpages --
## -- license --
ifneq ($(PREFIX),)
install: install-license
install-license: LICENSE
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-telluser
	cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-telluser
endif
## -- license --
