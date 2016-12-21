package com.ckcks12.idiotmusicplayer;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.media.Image;
import android.os.Bundle;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    public static final String IntentFilter = "a";
    public static final String PlayToPause = "1";
    public static final String PauseToPlay = "2";
    public static final String MusicEnd = "3";

    private BroadcastReceiver br1 = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            switch (intent.getStringExtra("data"))
            {
                case PlayToPause:
                    break;
                case PauseToPlay:
                    break;
                case MusicEnd:
                    isPlaying = false;
                    updateImageView3();
                    break;
            }
        }
    };

    public void play()
    {
        if( isPlaying )
        {
            if(myService != null) {
                myService.unpause();
            }
            isPlaying = true;
        }
        else {
            startService(myMusicIntent);
            bindService(myMusicIntent, musicConnection, BIND_AUTO_CREATE);
            isPlaying = true;
        }
    }

    public void rewind()
    {
        if(myService == null ) {
            bindService(myMusicIntent, musicConnection, BIND_AUTO_CREATE);
        }
        myService.rewind();
    }

    public void pause()
    {
        if(myService == null ) {
            bindService(myMusicIntent, musicConnection, BIND_AUTO_CREATE);
//            bindService(myMusicIntent, musicConnection, )
        }
        myService.pause();
        isPlaying = false;
    }

    public void unpause()
    {
        if(myService == null ) {
            bindService(myMusicIntent, musicConnection, BIND_AUTO_CREATE);
        }
        myService.unpause();
        isPlaying = true;
    }

    public void stop()
    {
        stopService(myMusicIntent);
        unbindService(musicConnection);
        isPlaying = false;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ImageView play = (ImageView)findViewById(R.id.imageView);
        ImageView rewinder = (ImageView) findViewById(R.id.imageView2);
        ImageView play2 = (ImageView) findViewById(R.id.imageView3);
        ImageView stop = (ImageView) findViewById(R.id.imageView4);
        TextView title = (TextView) findViewById(R.id.textView);

        play.setOnClickListener(this);
        rewinder.setOnClickListener(this);
        play2.setOnClickListener(this);
        stop.setOnClickListener(this);

        play2.setImageDrawable(getDrawable(R.drawable.ic_action_av_play_arrow));

        title.setText("mymusic.mp3");
        myMusicIntent = new Intent(this, MyService.class);

        registerReceiver(br1, new IntentFilter(IntentFilter));
    }

    private MyService myService;
    private boolean myBound = false;
    private Intent myMusicIntent;
    private boolean isPlaying = false;

    private ServiceConnection musicConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            MyService.MyBinder binder = (MyService.MyBinder)service;
            myService = binder.getService();
            myBound = true;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            myBound = false;
        }
    };


    public void updateImageView3() {
        if( isPlaying ){
            ((ImageView)findViewById(R.id.imageView3)).setImageDrawable(getDrawable(R.drawable.ic_action_av_pause));
        }
        else{
            ((ImageView)findViewById(R.id.imageView3)).setImageDrawable(getDrawable(R.drawable.ic_action_av_play_arrow));
        }
    }

    @Override
    public void onClick(View v) {
        switch(v.getId())
        {
            case R.id.imageView:
                play();
                break;
            case R.id.imageView2:
                rewind();
                break;
            case R.id.imageView3:
                if(isPlaying)
                {
                    pause();
                }
                else{
                    unpause();
                }
                break;
            case R.id.imageView4:
                stop();
                break;
        }
        updateImageView3();
    }
}
