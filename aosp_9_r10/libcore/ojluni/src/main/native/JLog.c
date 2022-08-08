#include <log/log.h>
#include <utils/Log.h>
#include <jni.h>
#include <nativehelper/JNIHelp.h>
//#include <process.h>
#include <unistd.h>

static jint java_lang_JLog_println_native(JNIEnv* env, jclass clazz,
        jint bufID, jint priority, jstring tagObj, jstring msgObj)
{
    const char* tag = NULL;
    const char* msg = NULL;

    if (msgObj == NULL) {
        //JNU_ThrowNullPointerException(env, "println needs a message");
        return -1;
    }

    if (bufID < 0 || bufID >= LOG_ID_MAX) {
        //JNU_ThrowNullPointerException(env, "bad bufID");
        return -1;
    }

    if (tagObj != NULL)
        tag = (*env)->GetStringUTFChars(env,tagObj, NULL);
    msg = (*env)->GetStringUTFChars(env,msgObj, NULL);

    int res = __android_log_buf_write(bufID, (android_LogPriority)priority, tag, msg);

    if (tag != NULL)
        (*env)->ReleaseStringUTFChars(env,tagObj, tag);
    (*env)->ReleaseStringUTFChars(env,msgObj, msg);

    return res;
}


static jint java_lang_JLog_getpid(JNIEnv* env, jclass clazz){
    return getpid();
}


static const JNINativeMethod gMethods[] = {
    /* name, signature, funcPtr */
    { "println_native",  "(IILjava/lang/String;Ljava/lang/String;)I", (void*) java_lang_JLog_println_native },
    { "getpid",  "()I", (void*) java_lang_JLog_getpid }
};

void register_java_lang_JLog(JNIEnv* env) {
  jniRegisterNativeMethods(env, "java/lang/JLog", gMethods, NELEM(gMethods));
}