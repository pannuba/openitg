#ifndef FFMPEG_HELPER_COMMON
#define FFMPEG_HELPER_COMMON

#include "global.h"
#include "RageDisplay.h"
#include "RageUtil.h"

namespace avcodec
{
#if defined(_WIN32)
	extern "C"
	{
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libavutil/pixdesc.h>
	}

#if defined(_MSC_VER)
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")
#endif

#else
	extern "C"
	{
/*  Moved the local imports of ffpmeg 3.1.11 to the block outside HAVE_LEGACY_FFMPEG, bc it's not really legacy.
    "legacy" version in src/ffmpeg is 0.4.9-pre1. Version in extern/ is 3.X added in 2017, but Windows only.
    avcodec_decode_video is only in 0.4.9, so I need to use the non-legacy .h .cpp files.
    (Why can't I just use the legacy ffmpeg with the bundled library? Pretty sure I tried already)
*/
		/*#if defined(HAVE_LEGACY_FFMPEG)
			#include "ffmpeg/include/ffmpeg/avformat.h"
			#include "ffmpeg/include/ffmpeg/avcodec.h"
		#else
			#include <libavformat/avformat.h>
			#include <libswscale/swscale.h>
			#include <libavutil/avutil.h>
			#include <libavutil/pixdesc.h>
			#include <libavcodec/avcodec.h> // Doesn't work because avcodec_decode_video2 was removed in newer FFMpeg builds (5.0+)
		#endif*/
		#if defined(HAVE_LEGACY_FFMPEG)

		#else
			#include "ffmpeg/include/ffmpeg/avformat.h"
			#include "ffmpeg/include/ffmpeg/avcodec.h"
			#include "ffmpeg/include/ffmpeg/swscale.h"
			#include "ffmpeg/include/ffmpeg/avutil.h"
			#include "ffmpeg/include/ffmpeg/pixdesc.h"
		#endif
	}
	#endif
	
	#if !defined (AV_VERSION_INT)
		#define AV_VERSION_INT(a, b, c) (a<<16 | b<<8 | c)
	#endif
};


struct AVPixelFormat_t
{
	int bpp;
	unsigned masks[4];
	/*Must #include "FFMpeg_Helper_Legacy.h here or just force the macro */	
	//OITG_AV_PIXFMT_NAME pf;
	enum avcodec::AVPixelFormat pf;
	bool HighColor;
	bool ByteSwapOnLittleEndian;
};

extern AVPixelFormat_t AVPixelFormats[5];

static void FixLilEndian()
{
#if defined(ENDIAN_LITTLE)
	static bool Initialized = false;
	if( Initialized )
		return; 
	Initialized = true;

	for( int i = 0; i < AVPixelFormats[i].bpp; ++i )
	{
		AVPixelFormat_t &pf = AVPixelFormats[i];

		if( !pf.ByteSwapOnLittleEndian )
			continue;

		for( int mask = 0; mask < 4; ++mask)
		{
			int m = pf.masks[mask];
			switch( pf.bpp )
			{
				case 24: m = Swap24(m); break;
				case 32: m = Swap32(m); break;
				default: ASSERT(0);
			}
			pf.masks[mask] = m;
		}
	}
#endif
}

static int FindCompatibleAVFormat( RageDisplay::RagePixelFormat &pixfmt, bool HighColor )
{
	for( int i = 0; AVPixelFormats[i].bpp; ++i )
	{
		AVPixelFormat_t &fmt = AVPixelFormats[i];
		if( fmt.HighColor != HighColor )
			continue;

		pixfmt = DISPLAY->FindPixelFormat( fmt.bpp,
				fmt.masks[0],
				fmt.masks[1],
				fmt.masks[2],
				fmt.masks[3],
				true /* realtime */
				);

		if( pixfmt == RageDisplay::NUM_PIX_FORMATS )
			continue;

		return i;
	}

	return -1;
}
#endif // FFMPEG_HELPER_COMMON
