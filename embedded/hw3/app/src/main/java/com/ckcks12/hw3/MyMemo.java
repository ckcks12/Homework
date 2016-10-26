package com.ckcks12.hw3;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MyMemo extends AppCompatActivity
{

    private TextView txt2;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_memo);

        txt2 = (TextView) findViewById(R.id.txt2);
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        Intent intent = getIntent();
        if( intent == null )
            return;

        if( intent.getAction().equals(Intent.ACTION_SEND) )
        {
            String sms_body = intent.getStringExtra(Intent.EXTRA_TEXT);
            txt2.setText(sms_body);
        }
    }
}
