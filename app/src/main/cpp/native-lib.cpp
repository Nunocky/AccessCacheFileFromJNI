#include <jni.h>
#include <android/log.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <malloc.h>

extern "C" JNIEXPORT
void Java_org_nunocky_accesscachefilefromjni_MainActivity_hello(JNIEnv *env, jobject thiz,
                                                                jstring strPath) {
    const char *filename = env->GetStringUTFChars(strPath, NULL);

    __android_log_print(ANDROID_LOG_INFO, "Native", "%s", filename);

    struct stat st;
    if (stat(filename, &st) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "Native", "%s stat failed", filename);
        return;
    }


    FILE *fr = NULL;
    uint8_t *buf = NULL;


    fr = fopen(filename, "r");
    if (!fr) {
        __android_log_print(ANDROID_LOG_ERROR, "Native", "%s open failed", filename);
        goto done;
    }

    buf = (uint8_t *) malloc(st.st_size + 1);
    fread(buf, 1, st.st_size, fr);
    buf[st.st_size] = 0;
    __android_log_print(ANDROID_LOG_INFO, "Native", "%s", buf);

    done:
    if (buf) {
        free(buf);
    }

    if (fr) {
        fclose(fr);
    }
}