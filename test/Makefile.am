AUTOMAKE_OPTIONS = subdir-objects

MANUAL_TESTS = \
	manual/download_url_file

ALL_TESTCASES = ${MANUAL_TESTS}

TESTCASES = ${ALL_TESTCASES}

check_PROGRAMS = ${TESTCASES}

AM_CFLAGS = -I$(top_srcdir)/src/ -I${top_srcdir}/deps/tap/
AM_LDFLAGS = -no-install
LDADD = 																						\
	${top_builddir}/src/libcre-downloader.la         	\
	${top_builddir}/deps/tap/libtap.la

check-%: 	BASE=$(subst -,_,$(subst check-,,$@))
check-%:	${TESTCASES}
					$(AM_V_GEN) srcdir=${srcdir} prove -e "${PROVE_ENV}" ${PROVE_OPTIONS} ${TESTCASES}

check: ${TESTCASES}
				$(AM_V_GEN) srcdir=${srcdir} prove -e "${PROVE_ENV}" ${PROVE_OPTIONS} ${TESTCASES}

.PHONY: check
