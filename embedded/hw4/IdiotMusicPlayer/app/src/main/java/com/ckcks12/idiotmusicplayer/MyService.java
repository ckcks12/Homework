package com.ckcks12.idiotmusicplayer;

import android.app.Service;
import android.content.Intent;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.Environment;
import android.os.IBinder;
import android.os.PowerManager;
import android.util.Log;
import android.widget.Toast;

import java.io.IOException;

public class MyService extends Service implements MediaPlayer.OnPreparedListener, MediaPlayer.OnErrorListener, MediaPlayer.OnCompletionListener {
    public MyService() {
    }

    private MediaPlayer player;
    private final IBinder myBinder = new MyBinder();

    public class MyBinder extends Binder
    {
        MyService getService()
        {
            return MyService.this;
        }
    }

    @Override
    public void onCreate() {
        super.onCreate();

        player = new MediaPlayer();
        player.setWakeMode(getApplicationContext(), PowerManager.PARTIAL_WAKE_LOCK);
        player.setAudioStreamType(AudioManager.STREAM_MUSIC);
        player.setOnPreparedListener(this);
        player.setOnErrorListener(this);
        player.setOnCompletionListener(this);
    }

    public void rewind()
    {
        int c = player.getCurrentPosition();
        c = c < 10000 ? c = 0 : c - 10000;
        player.seekTo(c);
    }

    public void pause()
    {
        player.pause();
    }

    public void unpause()
    {
        player.start();
    }

    @Override
    public void onDestroy() {
        Log.d("eunchan", "stopService() : hi~");
        try {
            player.stop();
            player.release();
        }catch(Exception e) {

        }
        super.onDestroy();
    }

    @Override
    public boolean stopService(Intent name) {
        Log.d("eunchan", "stopService() : hi~");
        player.stop();
        player.release();
        return super.stopService(name);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d("eunchan", "onStartCommand() : hi~~~~");
        player.reset();
        try {
            player.setDataSource("/sdcard/mymusic.mp3");
        } catch (IOException e) {
            e.printStackTrace();
        }
        player.prepareAsync();

        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public boolean onUnbind(Intent intent) {
        player.stop();
        player.release();
        return false;
//        return super.onUnbind(intent);
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
//        throw new UnsupportedOperationException("Not yet implemented");
        return myBinder;
    }

    @Override
    public void onCompletion(MediaPlayer mp) {
//        Toast.makeText(this, "Music done!", Toast.LENGTH_SHORT).show();
        Intent intent = new Intent(MainActivity.IntentFilter);
        intent.putExtra("data", MainActivity.MusicEnd);
        sendBroadcast(intent);
    }

    @Override
    public boolean onError(MediaPlayer mp, int what, int extra) {
        return false;
    }

    @Override
    public void onPrepared(MediaPlayer mp) {
        mp.start();
        Log.d("eunchan", "onPrepared() : mp.start!!!");
    }
}
