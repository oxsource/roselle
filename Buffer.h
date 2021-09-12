//
// Created by peng on 2021/9/12.
//

#ifndef LCT_BUFFER_H
#define LCT_BUFFER_H

#include <cstdlib>
#include <cstring>
#include <cstdio>
//#include <android/log.h>

//#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "LOGCAT_BUFFER", __VA_ARGS__)
//#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "LOGCAT_BUFFER", __VA_ARGS__)

#define LOGW(...) printf(__VA_ARGS__)
#define LOGD(...) printf(__VA_ARGS__)

class Buffer {
protected:
    char *value;
    long seek;
public:
    Buffer *next;

    Buffer();

    ~Buffer();

    virtual long sizes();

    virtual long frees();

    virtual int sink(const char *ins);

    virtual int flush(char *outs, long length);

    virtual int flush(Buffer *buf);
};


#endif //LCT_BUFFER_H
