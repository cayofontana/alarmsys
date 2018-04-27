package com.rafael.firebaseteste;

import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.Intent;
import android.os.*;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;

import static java.security.AccessController.getContext;

public class MyFirebaseMessagingService extends FirebaseMessagingService {

    private LocalBroadcastManager broadcaster;

    @Override
    public void onCreate(){
        broadcaster = LocalBroadcastManager.getInstance(this);
    }

    @Override
    public void onMessageReceived(RemoteMessage remoteMessage) {
        //Log.d("FirebaseMessaging", "Message Received: " + remoteMessage.getNotification().getBody());

        Intent intent = new Intent("Firebase");
        intent.putExtra("msg", remoteMessage.getNotification().getBody());
        broadcaster.sendBroadcast(intent);
    }
}
