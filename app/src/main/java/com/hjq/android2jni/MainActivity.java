package com.hjq.android2jni;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.TextView;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.Charset;

public class MainActivity extends Activity {

    private static final String TAG = "android2jni";

    private Handler mHandle = new Handler();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i("OtaApplication", "onCreate");
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        //type int
        int[] target = arr_int(new int[6],10);

        if (target!=null)
            for (int it : target){
                Log.i(TAG,Integer.toString(it));
            }

        String[] out = arr_str(new byte[]{0x30,0x50,0x7f,0x66,0x77},'黄',"---------------------------");

        if (out!=null)
            for (String it : out){
                Log.i(TAG,it);
            }

        char[] a={'5','换','7'};
        String[] out2 = arr_str2(a);
        if (out2!=null)
            for (String it : out2){
                Log.i(TAG,it);
            }

        Log.i(TAG,"********************************");
        char[] out3 = arr_ch(a);
        if (out3!=null)
            for (char it : out3){
                Log.i(TAG,String.valueOf(it));
            }

        Log.i(TAG,"********************************");

        JNI jni = new JNI(this);

        jni.callbackmethod();

        jni.callbackIntmethod();

        jni.callbackStringmethod();

        jni.callStaticmethod();

        Others others = jni.callOthersMethod();

        if (others == null){
            Log.e(TAG,"others == null");
        }else {
            others.fun_("MainActivity");
        }

        Others others1 = new Others();
        Others others2 = jni.callOthersMethod2(others1);
        if (others2 == null){
            Log.e(TAG,"others == null");
        }else {
            Log.i(TAG,others2.getName());
            Log.i(TAG,Integer.toString(others2.getNum()));
            Log.i(TAG,Integer.toString(others2.getPhone()));
            others2.fun_("MainActivity");
            others2.fun_2("MainActivity");
        }

        Others others5 = jni.callOthersMethod3();

        if (others5 == null){
            Log.e(TAG,"others == null");
        }else {
            others5.fun_("others5 MainActivity");
        }

    }

//    Runnable runnable = new Runnable() {
//        @Override
//        public void run() {
//            Activity activity = ApplicationUtils.getCurrentActivity();
//
//            if (activity!=null) {
////                Log.i("OtaApplication", activity.getLocalClassName());
//                Class jclass = activity.getClass();
//
//                if (!activity.getLocalClassName().equals("Second"))
//                    return;
//
//                try {
//                    Field strField1 = jclass.getDeclaredField("aa");
//                    boolean access = strField1.isAccessible();
//                    if(!access)
//                        strField1.setAccessible(true);
//
//                    int result = strField1.getInt(activity);
//                    Log.i("OtaApplication", Integer.toString(result));
//
//                    //***************************************************************
//
//                    Field strField2 = jclass.getDeclaredField("textView");
//                    boolean access2 = strField2.isAccessible();
//                    if(!access2)
//                        strField2.setAccessible(true);
//
//                    TextView result2 = (TextView) strField2.get(activity);
//                    if (result2!=null)
//                        Log.i("OtaApplication", result2.getText().toString());
//                    else
//                        Log.i("OtaApplication", "error2");
//                } catch (NoSuchFieldException e) {
//                    Log.i("OtaApplication", "NoSuchFieldException:"+e.toString());
//                } catch (IllegalAccessException e) {
//                    Log.i("OtaApplication", "IllegalAccessException:"+e.toString());
//                }
//            } else {
//                Log.i("OtaApplication", "error");
//                mHandle.postDelayed(runnable,100);
//            }
//        }
//    };

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int[] arr_int(int[] source ,int len);

    public native String[] arr_str(byte[] value,char title ,String ending);

    public native String[] arr_str2(char[] value);

    public native char[] arr_ch(char[] value);

    // byte转char
    private char[] getChars (byte[] bytes) {
        Charset cs = Charset.forName ("UTF-8");
        ByteBuffer bb = ByteBuffer.allocate (bytes.length);
        bb.put (bytes);
        bb.flip ();
        CharBuffer cb = cs.decode (bb);

        return cb.array();
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i("OtaApplication", "onResume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.i("OtaApplication", "onPause");
//        mHandle.postDelayed(runnable,100);
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.i("OtaApplication", "onRestart");
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.i("OtaApplication", "onStart");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i("OtaApplication", "onDestroy");
    }
}
