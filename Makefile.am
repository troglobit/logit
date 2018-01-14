EXTRA_DIST      = README.md LICENSE
bin_PROGRAMS    = logit
logit_CFLAGS    = -W -Wall -Wextra -Wno-unused-result -std=gnu99
logit_SOURCES   = logit.c

## Target to run when building a release
release: distcheck
	@for file in $(DIST_ARCHIVES); do	\
		md5sum $$file > ../$$file.md5;	\
	done
	@mv $(DIST_ARCHIVES) ../
	@echo
	@echo "Resulting release files in ../"
	@echo "================================================================="
	@for file in $(DIST_ARCHIVES); do					\
		printf "%-32s Distribution tarball\n" $$file;			\
		printf "%-32s " $$file.md5; cat ../$$file.md5 | cut -f1 -d' ';	\
	done
