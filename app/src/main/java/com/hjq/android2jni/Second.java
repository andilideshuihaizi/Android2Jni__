package com.hjq.android2jni;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.widget.TextView;

/**
 * Created by Administrator on 2019/4/11.
 */
public class Second extends Activity {

    private int aa = 0;

    private int bb = 0;

    private TextView textView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.second);

        aa = 1;
        bb = 2;

        textView = findViewById(R.id.textView);

        Log.i("OtaApplication", "onCreate exit " +"aa "+Integer.toString(aa)+" bb "+Integer.toString(bb));
    }

    public Second(){
        Log.i("OtaApplication", "Second()"+" aa "+Integer.toString(aa)+" bb "+Integer.toString(bb));
    }

}
