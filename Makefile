DESTDIR=
PREFIX=/usr/local
all:
	@true
clean:
	@true
install:
	@echo 'I include/telluser.h'
	@mkdir -p $(DESTDIR)$(PREFIX)/include
	@cp telluser.h $(DESTDIR)$(PREFIX)/include

## -- manpages --
install: install-man3
install-man3:
	@echo 'I share/man/man3/'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/telluser.3'
	@cp ./telluser.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- manpages --
## -- license --
install: install-license
install-license: LICENSE
	@echo 'I share/doc/c-telluser/LICENSE'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-telluser
	@cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-telluser
## -- license --
