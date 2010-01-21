DESCRIPTION = "U-boot bootloader mkimage tool"
LICENSE = "GPL"
SECTION = "bootloader"

PR = "r1"

SRC_URI = "ftp://ftp.denx.de/pub/u-boot/u-boot-${PV}.tar.bz2"

S = "${WORKDIR}/u-boot-${PV}"

EXTRA_OEMAKE = "CROSS_COMPILE=${TARGET_PREFIX}"

BBCLASSEXTEND = "native nativesdk"

do_compile () {
  oe_runmake smdk2410_config
  oe_runmake tools
}

NATIVE_INSTALL_WORKS = "1"
do_install () {
  install -d ${D}${bindir}
  install -m 0755 tools/mkimage ${D}${bindir}/uboot-mkimage
  ln -sf uboot-mkimage ${D}${bindir}/mkimage
}
