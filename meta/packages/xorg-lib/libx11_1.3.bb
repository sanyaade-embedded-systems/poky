require libx11.inc

PE = "1"
PR = "r2"

SRC_URI += "file://x11_disable_makekeys.patch;patch=1 \
            file://nodolt.patch;patch=1 \
            file://include_fix.patch;patch=1"

DEPENDS += "bigreqsproto xproto xextproto xtrans libxau xcmiscproto \
            libxdmcp xf86bigfontproto kbproto inputproto xproto-native gettext"

EXTRA_OECONF += "--without-xcb"

BBCLASSEXTEND = "native nativesdk"