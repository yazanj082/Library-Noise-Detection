package com.retroportalstudio.www.background_service;
import android.media.RingtoneManager;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import java.io.BufferedReader;
import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;
import android.net.Uri;
import android.media.Ringtone;
public class MyService extends Service {

    @Override
    public void onCreate() {
        super.onCreate();}
        @Override
    public int onStartCommand(Intent intent, int flags, int startId){
    String str = intent.getStringExtra("str");
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            NotificationCompat.Builder builder = new NotificationCompat.Builder(this,"messages")
                    .setContentText(str)
                    .setContentTitle("ازعاج من الطاولة")
                    .setSmallIcon(R.drawable.ic_android_black_24dp);
                   
            
            
            startForeground(101,builder.build());
            Uri alarm = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
         Ringtone ringtone = RingtoneManager.getRingtone(getApplicationContext(), alarm);
         if(!str.equals("انتظار")){
         ringtone.play();}
        }
return START_STICKY;
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}

