package com.ckcks12.hw3;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.EditText;

public class MyWebBrowser extends AppCompatActivity implements View.OnClickListener
{
    private WebView webview;
    private Button btn1;
    private EditText txt1;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_web_browser);

        webview = (WebView)findViewById(R.id.webview);
        webview.setWebViewClient(new WebViewClient());
        WebSettings set = webview.getSettings();
        set.setJavaScriptEnabled(true);
        set.setBuiltInZoomControls(true);

        btn1 = (Button) findViewById(R.id.btn1);
        btn1.setOnClickListener(this);
        txt1 = (EditText) findViewById(R.id.txt1);
    }

    @Override
    protected void onStart()
    {
        super.onStart();

        Intent intent = getIntent();
        if( intent.getAction().equals(Intent.ACTION_VIEW) )
        {
            String url = intent.getData().toString();
            txt1.setText(url);
            webview.loadUrl(url);
        }
    }

    @Override
    public void onClick(View view)
    {
        switch(view.getId())
        {
            case R.id.btn1:
                webview.loadUrl(txt1.getText().toString());
        }
    }
}
