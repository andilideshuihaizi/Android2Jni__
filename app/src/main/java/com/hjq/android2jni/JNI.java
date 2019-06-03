package com.hjq.android2jni;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

/**
 * Created by Administrator on 2019/5/28.
 */
public class JNI {
    private Context context;
    private static final String TAG = "android2jni";

    public JNI(Context context) {
        this.context = context;
    }

    /*
        本地方法
         */
    //C调用java空方法
    public native void callbackmethod();

    //C调用java中的带两个int参数的方法
    public native void callbackIntmethod();

    //C调用java中参数为string的方法
    public native void callbackStringmethod();

    //C调用java中静态方法
    public native void callStaticmethod();

    //C调用java中别的类中的方法（new了后，再使用其方法）
    public native Others callOthersMethod();

    //C调用java中别的类中的方法2
    public native Others callOthersMethod2(Others others);

    //C调用java中别的类中的方法3
    public native Others callOthersMethod3();


    /*
    被C反调的java方法
     */
    //C调用java空方法
    public void helloFromJava(){
        Toast.makeText(context,"C调用了java的空方法",Toast.LENGTH_SHORT).show();
    }

    //C调用java中的带两个int参数的方法
    public int add(int x,int y){
        return x+y;
    }

    //C调用java中参数为string的方法
    public void printString(String s){
        Toast.makeText(context,s,Toast.LENGTH_SHORT).show();
    }

    //C调用java中静态方法
    public static void staticmethod(String s){
        Log.d(TAG,s+",我是被C调用的静态方法");
    }
}
