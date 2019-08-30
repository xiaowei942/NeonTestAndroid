#include <jni.h>
#include <string>

#include "FirstNeonTest.h"

extern "C" JNIEXPORT jstring
JNICALL
Java_com_finalreality_neontestandroid_MainActivity_stringFromJNI(
	JNIEnv *env,
	jobject /* this */) {
	std::string hello = "Hello from C++";
	return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void
JNICALL
Java_com_finalreality_neontestandroid_MainActivity_addTest(
	JNIEnv *env,
	jobject /* this */) {
	addTest();
}