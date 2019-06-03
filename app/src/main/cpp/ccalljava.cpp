//
// Created by Administrator on 2019/5/28.
//
#include <jni.h>
#include <cstddef>
#include "ccalljava.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_hjq_android2jni_JNI_callbackmethod(JNIEnv *env, jobject instance) { /**C函数反射调用java中的空方法 */

    // TODO
    jclass jclazz = env->FindClass("com/hjq/android2jni/JNI");
    jmethodID jmethodID1 = env->GetMethodID(jclazz,"helloFromJava","()V");

    env->CallVoidMethod(instance,jmethodID1);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hjq_android2jni_JNI_callbackIntmethod(JNIEnv *env, jobject instance) {/**调用java中Int方法*/

    // TODO
    jclass jclass1 = env->FindClass("com/hjq/android2jni/JNI");
    jmethodID jmethodID1 = env->GetMethodID(jclass1,"add","(II)I");
    int result = env->CallIntMethod(instance,jmethodID1,5,6);

    LOGD("RESLUT = %d",result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hjq_android2jni_JNI_callbackStringmethod(JNIEnv *env, jobject instance) {/**调用java中String方法     */

    // TODO
    jclass jclass1 = env->FindClass("com/hjq/android2jni/JNI");
    jmethodID jmethodID1 = env->GetMethodID(jclass1,"printString","(Ljava/lang/String;)V");
    jstring jstr = env->NewStringUTF("123 456 789 ");//将要传递的字符串先转换成jstring类型 ，然后在传递给java方法
    env->CallVoidMethod(instance,jmethodID1,jstr);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_hjq_android2jni_JNI_callStaticmethod(JNIEnv *env, jobject instance) {/**调用Java中的静态方法*/

    // TODO
    jclass jclass1 = env->FindClass("com/hjq/android2jni/JNI");
    jmethodID jmethodID1 = env->GetStaticMethodID(jclass1,"staticmethod","(Ljava/lang/String;)V");
    jstring jstr = env->NewStringUTF("C调用java 静态方法");
    env->CallStaticVoidMethod(jclass1,jmethodID1,jstr);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_hjq_android2jni_JNI_callOthersMethod(JNIEnv *env, jobject instance) {

    // TODO
    jclass jclass1 = env->FindClass("com/hjq/android2jni/Others");
    jmethodID jmethodID1 = env->GetMethodID(jclass1,"<init>","()V");//调用类的构造方法，方法名都是<init>
//    using namespace ccall;
    jobject jobject1 = env->NewObject(jclass1,jmethodID1);

    if (jobject1==NULL) {
        LOGD("callOthersMethod jobject1==NULL");
        return NULL;
    }else
        LOGD("callOthersMethod new jobject1 success");

    jmethodID jmethodID2 = env->GetMethodID(jclass1,"fun_","(Ljava/lang/String;)V");

    if (jmethodID2 == NULL){
        LOGD("callOthersMethod jmethodID2==NULL");
        return NULL;
    } else{
        jstring jstr = env->NewStringUTF("JNI_callOthersMethod");
        env->CallVoidMethod(jobject1,jmethodID2,jstr);//java的方法中的参数，需要的是jstring类型，或者jint等，不能是C/C++的字符 字符串等类型
    }

//    env->DeleteLocalRef(jobject1);//不需要时释放内存

    return jobject1;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_hjq_android2jni_JNI_callOthersMethod2(JNIEnv *env, jobject instance, jobject others) {

    // TODO
    jclass jclass1 = env->GetObjectClass(others);
    jmethodID jmethodID_others = env->GetMethodID(jclass1,"<init>","()V");
    jmethodID jmethodID_fun_ = env->GetMethodID(jclass1,"fun_","(Ljava/lang/String;)V");
    jmethodID jmethodID_fun_2 = env->GetMethodID(jclass1,"fun_2","(Ljava/lang/String;)V");

    jfieldID jfieldID_String = env->GetFieldID(jclass1,"name","Ljava/lang/String;");
    jfieldID jfieldID_num = env->GetFieldID(jclass1,"num","I");
    jfieldID jfieldID_phone = env->GetFieldID(jclass1,"phone","I");

//    jobject jobject1 = env->NewObject(jclass1,jmethodID_others);
    if (others==NULL) {
        LOGD("callOthersMethod2 others==NULL");
        return NULL;
    }else
        LOGD("callOthersMethod2 others success");

    env->SetObjectField(others,jfieldID_String,env->NewStringUTF("xiao hua"));
    env->SetIntField(others,jfieldID_num,50);
    env->SetIntField(others,jfieldID_phone,195346);

    env->CallVoidMethod(others,jmethodID_fun_,env->NewStringUTF("second method"));
    env->CallVoidMethod(others,jmethodID_fun_2,env->NewStringUTF("second method"));

    return others;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_hjq_android2jni_JNI_callOthersMethod3(JNIEnv *env, jobject instance) {

    // TODO
    jclass jclass1 = env->FindClass("com/hjq/android2jni/Others");
    jmethodID jmethodID1 = env->GetMethodID(jclass1,"<init>","(Ljava/lang/String;)V");
    jobject jobject1 = env->NewObject(jclass1,jmethodID1,env->NewStringUTF("有参函数"));

    if (jobject1==NULL) {
        LOGD("callOthersMethod jobject1==NULL");
        return NULL;
    }else
        return jobject1;
}

/*
 * JNIEnv类型代表Java环境。通过这个JNIEnv*指针，就可以对Java端的代码进行操作。如，创建Java类得对象，调用Java对象的方法，获取Java对象的属性等。
 * JNIEnv的指针会被JNI传送到本地方法的实现函数中来对Java端的代码进行操作
 */

/*
 *  JNIEnv类中的函数：
 *  NewObject/NewString/New<TYPE>Array  ：new新对象
 *  Get/Set<TYPE>Field：获取属性
 *  Get/SetStatic<TYPE>Field ：获取静态属性
 *  Call<TYPE>Method/CallStatic<TYPE>Method：调用方法
 */

/*
类型           相应的签名
boolean        Z
byte           B
char           C
short          S
int            I
long           J
float          F
double         D
void           V
object         L用/分隔包的完整类名：   Ljava/lang/String;
Array          [签名          [I      [Ljava/lang/Object;
Method         (参数1类型签名 参数2类型签名···)返回值类型签名

 Java类型      别名　　           C++本地类型　　        字节(bit)
boolean      jboolean            unsigned char　　     8, unsigned
byte         jbyte               signed char　　　　   8
char         jchar               unsigned short　　    16, unsigned
short        jshort              short　　　           16
int          jint                long　　　　          32
long         jlong               __int64　　　　       64
float        jfloat              float　　　           32
double       jdouble             double　　　          64
void         void        　　　　                      n/a　　
 */


/*
void f1()                         ()V
int f2(int, long)                 (IJ)I
boolean f3(int[])                 ([I)Z
double f4(String, int)            (Ljava/lang/String;I)D
void f5(int, String [], char)    (I[Ljava/lang/String;C)V
 */

/*
 * 获取jclass
 *  JNIEnv类中有如下几个简单的函数可以取得jclass
 *  ---jclass FindClass(const char* clsName)  根据类名来查找一个类，完整类名。
 *  ---jclass GetObjectClass(jobject obj)   根据一个对象，获取该对象的类
 *  ---jclass GetSuperClass(jclass obj)     获取一个类的父类
 *
 *  FindClass 会在classpath系统环境变量下寻找类，需要传入完整的类名，注意包与包之间是用"/"而不是"."来分割
 *  如：jclass cls_string= env->FindClass("java/lang/String");
 */

/*
 * 如何获取属性： 在访问或设置Java属性的时候，首先就要现在本地代码中取得代表Java属性的jfieldID，然后才能在本地代码中进行Java属性操作。
 * 如何调用java的方法：调用Java端的方法时，需要取得代表方法的jmethodID才能进行Java方法调用
 *
 * JNIEnv获取相应的fieldID和jmethodID的方法：
 * GetFieldID / GetMethodID
 * GetStaticFieldID / GetStaticMethodID
 *
 * **GetMethodID也可以取得"构造函数"的jmethodID。创建Java对象时调用指定的构造函数。
 *  (*jniEnv)->GetMethodID(jniEnv, Clazz,"<init>", "()V"); 这个比较特殊，这个是默认构造函数的方法，一般用这个来初始化对象，但是再实际过程中，为了快速生成一个实例，一般通过工厂方法类创建jobject
 *
 */

/*
 * 注意 GetXXXMethodID  和 CallXXXMethod 。
第一个XXX 表示的是映射方法的类型，如： 静态 跟非静态
第二个 XXX 表示 调用方法的返回值 ，如：Void,Object,等等。（调用静态方法的时候Call后面要加Static）
 */