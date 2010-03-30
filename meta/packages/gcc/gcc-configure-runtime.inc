require gcc-configure-common.inc

EXTRA_OECONF_PATHS = " \
    --with-local-prefix=${STAGING_DIR_TARGET}${prefix} \
    --with-gxx-include-dir=${includedir}/c++/"

RUNTIMETARGET = "libgcc libssp libstdc++-v3"
#  ?
# libiberty
# libmudflap
# libgfortran

do_configure () {
	cp ${CROSS_DIR}/include/gcc-build-internal/* ${S}/gcc
	for d in ${RUNTIMETARGET}; do
		echo "Configuring $d"
		mkdir -p ${B}/$d/
		cd ${B}/$d/
		chmod a+x ${S}/$d/configure
		${S}/$d/configure ${CONFIGUREOPTS} ${EXTRA_OECONF_PATHS}
	done
}

do_compile () {
	for d in ${RUNTIMETARGET}; do
		cd ${B}/$d/
		oe_runmake
	done
}

do_install () {
	for d in ${RUNTIMETARGET}; do
		cd ${B}/$d/
		oe_runmake 'DESTDIR=${D}' install
	done

	# Move libgcc_s into /lib
	mkdir -p ${D}${base_libdir}
	if [ -f ${D}${libdir}/nof/libgcc_s.so ]; then
		mv ${D}${libdir}/nof/libgcc* ${D}${base_libdir}
	else
		mv ${D}${libdir}/libgcc* ${D}${base_libdir} || true
	fi
}

INHIBIT_DEFAULT_DEPS = "1"
DEPENDS = "virtual/${TARGET_PREFIX}gcc virtual/${TARGET_PREFIX}g++"
PROVIDES = "virtual/${TARGET_PREFIX}compilerlibs"

BBCLASSEXTEND = "nativesdk"
