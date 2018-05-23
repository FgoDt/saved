// saved.cpp: 定义应用程序的入口点。
//

#include "saved.h"
#include "log.h"
#include "define.h"

#include<libavformat/avformat.h>
#include<libavcodec/avcodec.h>
#include<libswresample/swresample.h>
#include<libswscale/swscale.h>
#include<libavutil/time.h>
#include<libavutil/avutil.h>


void test2(char *h) {
    printf("%s", h);
}

typedef struct SAVEDCodec {
    AVCodec *codec;
    AVCodecContext *avctx;
    AVFormatContext *pfmt;
}SAVEDCodec;


void test(void)
{
    saved_set_log_level(SAVEDLOG_LEVEL_W);
    SAVEDLOG1(NULL, 1, "nihao %d", 102);
    SAVLOGD("keyi keyi");
    SAVLOGE("E keyi");
    SAVLOGW("W keyi");
    printf("hello\n");
}

SAVEDContext* saved_create_context() {
    SAVEDContext *ctx = (SAVEDContext*)malloc(sizeof(SAVEDContext));
    ctx->codec = NULL;
    ctx->openmark = OPENMARK;
    ctx->isencoder = 0;
    SAVLOGD("create context done");
    return ctx;
}

int saved_open(SAVEDContext *ctx, const char *path, const char *options, int isencoder) {

    RETIFCTXNULL(ctx);

    ctx->isencoder = isencoder;

    ctx->codec = malloc(sizeof(SAVEDCodec));

    SAVEDCodec *codec = (SAVEDCodec*)ctx->codec;
    
    if (path == NULL && !isencoder)
    {

        return SAVED_E_USE_NULL;
    }
}

