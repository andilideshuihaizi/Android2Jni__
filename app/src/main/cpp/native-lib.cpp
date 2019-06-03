#include <jni.h>
#include <string>

#include<android/log.h>
#include <sstream>
#include <utility>
#include <iostream>


#define TAG "android2jni"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型

std::string Numeric2string(jbyte a);

extern "C" JNIEXPORT jstring JNICALL
Java_com_hjq_android2jni_MainActivity_stringFromJNI(

        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());

}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_hjq_android2jni_MainActivity_arr_1int(JNIEnv *env, jobject instance, jintArray source_,
                                               jint len) {
    jint *source = env->GetIntArrayElements(source_, NULL);
    jsize length = env->GetArrayLength(source_);

    for (int i = 0; i < length; ++i) {//需要先修改java传下来的数组
        source[i] = i * 6 + 20;
        LOGD("source[%d] = %d",i,source[i]);
    }

    jintArray  array;//定义数组对象
    array = env->NewIntArray(len);
    jint *target = env->GetIntArrayElements(array,NULL);

    for (int i = 0; i < len; ++i) {
        if (i<length)
            target[i] = source[i] + 2;
        else
            target[i] = i * 6 + 20;

        LOGD("target[%d] = %d",i,target[i]);
    }

    env->ReleaseIntArrayElements(array,target,0);
    env->ReleaseIntArrayElements(source_, source, 0);

    return array;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_hjq_android2jni_MainActivity_arr_1str(JNIEnv *env, jobject instance, jbyteArray value_,
                                               jchar title, jstring ending_) {
    using namespace std;

    //java的char转换c/c++的char
    const jchar org = title;
    const jchar *p = &org;
    jstring j_org = env->NewString(p, sizeof(char));
    const char *c_org = env->GetStringUTFChars(j_org,0);

    LOGD("title = %s",c_org);

    jbyte *value = env->GetByteArrayElements(value_, NULL);
    const char *ending = env->GetStringUTFChars(ending_, 0);

    //java字节数组转换c/c++的字符串数组，操作后并返回，byte[]{0x30,0x50}----->string[]{"30","50"}
    jsize lenth = env->GetArrayLength(value_);
    jclass objclass = env->FindClass("java/lang/String");
    jobjectArray target = env->NewObjectArray(lenth,objclass,0);


    for (int i = 0; i < lenth; ++i) {
        string str = Numeric2string(value[i]);
        const jstring jstr = env->NewStringUTF(str.c_str());
        env->SetObjectArrayElement(target,i,jstr);
    }

    string str_org = c_org;

    if (str_org.compare("黄") == 0){
        LOGD("str_org.compare(\"黄\") == 0 %d",str_org.length());
        LOGD("%s ",ending);
    } else{
        LOGD("str_org.compare(\"黄\") != 0  %d",str_org.length());
    }

    env->ReleaseByteArrayElements(value_, value, 0);
    env->ReleaseStringUTFChars(ending_, ending);
    env->ReleaseStringUTFChars(j_org,c_org);

    return target;
}


//字节转字符串
std::string Numeric2string(jbyte a){
    using namespace std;

//    double a = 123.32;

//    string res;
//    stringstream ss;          //定义流ss
//    ss << a;                      // 将数字a转化成流ss
//    ss >> res;                    //将流ss转化成字符串


    string res;

    int v = a/16;	//取除数（前面一位）
    int m = a%16;	//取模（后面一位）

    //前面一位转char
    if(v>=0&&v<=9)	{
        v+=48;	//数字转ASCII
    }else if( v>=97&&v<=122){
        v=v+87;	//小写字母转ASCII
    }else {
        v=v+55;	//大写字母转ASCII
    }
    char vChar = (char)v;	//ASCII码转为char类型

    //后面一位转char
    if(m>=0&&m<=9) {
        m+=48;
    }else if(m>=97&&m<=122) {
        m=m+87;
    }else {
        m=m+55;
    }
    char mChar = (char)m;
    //两位char合并为一个字符串
    char strKVCTmp[3]={vChar,mChar};	//char字符合并成string

    //字符数组换为字符串
    res = strKVCTmp;

    return res;
}

//字符串转数字
int string2Numeric(){

    using namespace std;
    double a ;
    string res= "123.32";
    stringstream ss;
    ss << res;
    ss >> a;
    return 0;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_hjq_android2jni_MainActivity_arr_1str2(JNIEnv *env, jobject instance, jcharArray value_) {
    jchar *value = env->GetCharArrayElements(value_, NULL);

    jsize lenth = env->GetArrayLength(value_);
    using namespace std;
    string *str = new string[lenth];
    //java的char转换c/c++的char
    for (int i = 0; i < lenth; ++i) {
        jstring j_org = env->NewString(&value[i], sizeof(char));
        const char *c_org = env->GetStringUTFChars(j_org,0);
        str[i] = c_org;
        str[i].append(" i");
        env->ReleaseStringUTFChars(j_org,c_org);
        LOGD("%s ",c_org);
    }

    jclass jclass1 = env->FindClass("java/lang/String");
    jobjectArray target = env->NewObjectArray(lenth,jclass1,0);

    for (int i = 0; i < lenth; ++i) {
        env->SetObjectArrayElement(target,i,env->NewStringUTF(str[i].c_str()));
    }

    env->ReleaseCharArrayElements(value_, value, 0);
    delete(str);
    str = NULL;

    return target;
}

extern "C"
JNIEXPORT jcharArray JNICALL
Java_com_hjq_android2jni_MainActivity_arr_1ch(JNIEnv *env, jobject instance, jcharArray value_) {
    jchar *value = env->GetCharArrayElements(value_, NULL);

    jsize lenth = env->GetArrayLength(value_);
    jcharArray jcharArray1 = env->NewCharArray(lenth);
    jchar *p = env->GetCharArrayElements(jcharArray1,NULL);

    using namespace std;
    string *str = new string[lenth];

    for (int i = 0; i < lenth; ++i) {
        jstring j_org = env->NewString(&value[i], sizeof(char));//jchar--->jstring
        const char *c_org = env->GetStringUTFChars(j_org,0);//jstring--->char
        str[i] = c_org;//char--->string
        jstring jstring1 = env->NewStringUTF(str[i].c_str());//string--->jstring
        const jchar* p2= env->GetStringChars(jstring1,0);//jstring--->jchar
        p[i] = *p2;
        env->ReleaseStringChars(jstring1,p2);
        env->ReleaseStringUTFChars(j_org,c_org);
        LOGD("%s ",c_org);
    }


    env->ReleaseCharArrayElements(value_, value, 0);
    env->ReleaseCharArrayElements(jcharArray1,p,0);
    delete(str);
    str = NULL;

    return jcharArray1;
}

