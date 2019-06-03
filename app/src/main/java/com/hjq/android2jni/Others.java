package com.hjq.android2jni;

import android.util.Log;

/**
 * Created by Administrator on 2019/5/29.
 */
public class Others {
    private String name="";
    private int num=0;
    private int phone=0;

    public Others(){
        Log.i("android2jni","Others");
    }

    public Others(String string){
        Log.i("android2jni",string);
    }

    public void fun_(String string){
        Log.i("android2jni",string+" fun_");
    }

    public String getName() {
        return name;
    }

    public int getNum() {
        return num;
    }

    public int getPhone() {
        return phone;
    }

    public void fun_2(String string){
        Log.i("android2jni",string+" fun_2");
    }

}
