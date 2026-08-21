This directory is only for Windows.  For other OS's, install it yourself
as usual.

I'm not adding this library source to CVS, because it's still in heavily
active development and there's not yet a stable release, so it's too much
work to keep a copy here, and because it's easier to create diffs to send
upstream if my copy is checked out of the original repository.  Check it
out yourself if you want to recompile it.

Compile with MingW.
Configured with ./configure --enable-shared --enable-mingw32 --enable-small --disable-debug

TODO: Don't compile encoders, audio decoders and unneeded video decoders.



The version of FFmpeg bundled here is a Linux x64 build of FFmpeg 3.11.1 *
This folder is supposed to contain the legacy build of FFmpeg that's used when the game is compiled with the HAVE_LEGACY_FFMPEG flag.
The previous version that's been removed was 0.4.9-pre1.
I'm doing this because the newest versions of FFMpeg are missing some functions that OITG uses, so
bundling an older-but-not-too-old build is the least painful solution.

(see FFMpeg_Helper_Legacy.h and FFMpeg_Helper_Common.h)


* With a few minor changes copied from later commits to make the compiling process work:
https://git.ffmpeg.org/gitweb/ffmpeg.git/commitdiff/effadce6c756247ea8bae32dc13bb3e6f464f0eb
https://stackoverflow.com/questions/36990257/build-error-caused-by-missing-library-arc4random

Update: need to split headers into different folders (/libswscale, /libavcodec) to prevent overlapping as there are some headers with the same name
Also FFmpeg 3.11.1 has a different folder structure than 0.4.9-pre1, so this is required to avoid editing the headers
I'm doing this after trying to compile on a different Linux install, the one where this wasn't needed had an older system-wide FFmpeg which happened to not conflict