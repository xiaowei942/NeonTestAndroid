//
// Created by finalreality on 2019/8/29.
//

#ifndef NEONTEST_LOG_H
#define NEONTEST_LOG_H

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "NeonTest", __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "NeonTest", __VA_ARGS__);

#endif //NEONTEST_LOG_H
