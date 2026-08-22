AC_DEFUN([SM_FFMPEG], [

AC_ARG_WITH(ffmpeg, AS_HELP_STRING([--without-ffmpeg],[Disable ffmpeg support]), with_ffmpeg=$withval, with_ffmpeg=yes)

# Since we're always using the bundled ffmpeg 3.1.11, there's no reason to check for system libs
# For reference, the previous logic was "if the system doesn't have the libraries we want at a certain minimum version,
# Use the legacy bundled ffmpeg (0.4.9-pre1), otherwise use the system/shared version"
# In 2026, ffmpeg has changed so much that many functions used by OITG have been changed, moved or straight up removed,
# so the simplest solution that doesn't require rewriting a lot of the game's code is to use the newest compatible version, 3.1.11.

have_ffmpeg=yes

CFLAGS="-I$PWD/src/ffmpeg/include/ffmpeg $CFLAGS"
CXXFLAGS="-I$PWD/src/ffmpeg/include/ffmpeg $CXXFLAGS"
LIBS="-L$PWD/src/ffmpeg/lib -lavformat -lavcodec -lavutil -lswscale -lswresample -lva -lva-drm -lva-x11 -lz -lbz2 -lpng -ljpeg -lpthread"
AC_DEFINE(HAVE_FFMPEG, 1, [FFMPEG support available])

AM_CONDITIONAL(HAVE_FFMPEG, test "$have_ffmpeg" = "yes")

])