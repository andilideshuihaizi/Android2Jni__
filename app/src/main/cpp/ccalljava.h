//
// Created by Administrator on 2019/5/28.
//

#ifndef ANDROID2JNI_CCALLJAVA_H
#define ANDROID2JNI_CCALLJAVA_H

#include<android/log.h>
#define TAG "android2jni"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)

namespace ccall{
    jobject jobject1;
}

class ccalljava {

};


#endif //ANDROID2JNI_CCALLJAVA_H
