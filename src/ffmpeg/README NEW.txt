The version of FFmpeg bundled here is a Linux x64 build of FFmpeg 3.11.1 *
This folder is supposed to contain the legacy build of FFmpeg that's used when the game is compiled with the HAVE_LEGACY_FFMPEG flag.
The previous version that's been removed was 0.4.9-pre1.
I'm doing this because the newest versions of FFMpeg are missing some functions that OITG uses, so
bundling an older-but-not-too-old build is the least painful solution.

(see FFMpeg_Helper_Legacy.h and FFMpeg_Helper_Common.h)


* With a few minor changes copied from later commits to make the compiling process work:
https://git.ffmpeg.org/gitweb/ffmpeg.git/commitdiff/effadce6c756247ea8bae32dc13bb3e6f464f0eb
https://stackoverflow.com/questions/36990257/build-error-caused-by-missing-library-arc4random