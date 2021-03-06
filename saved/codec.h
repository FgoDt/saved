#ifndef __CODEC_H__
#define __CODEC_H__

#include "saved.h"
#include "format.h"
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include "videoscale.h"
#include "audioresample.h"
#include <libavutil/audio_fifo.h>




typedef struct SAVEDDecoderContext {
    int use_hw;
    char *hw_name;
    AVBufferRef *hw_bufferref;

    AVCodecContext *actx; //audio
    AVCodecContext *vctx; //video
    AVCodecContext *vdctx; //video default context
    AVCodecContext *sctx; //sub

    AVRational a_time_base;
    AVRational v_time_base;
    AVRational s_time_base;

    AVFrame *idst_frame; // internal swsscale frame
    AVFrame *isrc_frame; // internal avcodec decode frame
    AVFrame *ihw_frame;  // internal hard ware decode frame

    AVPacket *ipkt;  // internal packet
    double decpts;

    AVFrame *iadst_frame; //audio dst frame;

    int use_default_codec;

	SAVEDVideoPar force_video_par;
	SAVEDAudioPar force_audio_par;

    SAVEDVideoScaleCtx *video_scale_ctx;
    SAVEDAudioResampleCtx *audio_resample_ctx;

}SAVEDDecoderContext;


typedef struct SAVEDEncoderContext {
    int use_hw;
    char *hw_name;
    AVBufferRef *hw_bufferref;

    AVCodecContext *actx; //audio
    AVCodecContext *vctx; //video
    AVCodecContext *sctx; //sub

    AVRational a_time_base;
    AVRational v_time_base;
    AVRational s_time_base;

    AVFrame *ivdst_frame; // video scale frame
    AVFrame *iadst_frame; // audio resample frame

    AVPacket *ipkt;  // internal packet

    SAVEDVideoScaleCtx *videoScaleCtx;
    SAVEDAudioResampleCtx *audioResampleCtx;

	SAVEDVideoPar *force_video_par;
	SAVEDAudioPar *force_audio_par;

    AVAudioFifo *fifo;
    double aenpts;
    double venpts;

}SAVEDEncoderContext;



typedef struct SAVEDCodecContext{
    SAVEDDecoderContext *decoder_ctx;
    SAVEDEncoderContext *encoder_ctx;
    int isencoder;
}SAVEDCodecContext;

SAVEDCodecContext* saved_codec_alloc(void);

int saved_codec_open(SAVEDCodecContext *savctx, SAVEDFormat *fmt);

int saved_codec_open_with_par(SAVEDCodecContext *savctx, int vh, int vw, int vfmt,int vbit_rate,
								int asample_rate, int afmt, int ach, int abit_rate );

int saved_codec_open_with_option(SAVEDCodecContext *savctx, AVDictionary *options);

int saved_codec_close(SAVEDCodecContext *savctx);
int saved_codec_send_pkt(SAVEDCodecContext *ictx, SAVEDPkt *pkt);
int saved_codec_get_pkt(SAVEDCodecContext *ictx, SAVEDPkt *pkt);
int saved_codec_send_frame(SAVEDCodecContext *ictx, SAVEDFrame *f);
int saved_codec_get_frame(SAVEDCodecContext *ictx, SAVEDFrame *f);

int saved_codec_set_force_video_par(SAVEDCodecContext *ictx, SAVEDVideoPar *par);

int saved_codec_set_force_audio_par(SAVEDCodecContext *ictx, SAVEDAudioPar *par);

int saved_codec_get_video_par(SAVEDCodecContext *ictx, SAVEDVideoPar *par);

int saved_codec_get_audio_par(SAVEDCodecContext *ictx, SAVEDAudioPar *par);

#endif // !__CODEC_H__
