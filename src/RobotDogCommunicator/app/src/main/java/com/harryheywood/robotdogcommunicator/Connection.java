package com.harryheywood.robotdogcommunicator;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.NonNull;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class Connection {

    static BluetoothAdapter bluetoothAdapter;
    static BluetoothDevice bluetoothDevice;
    static BluetoothSocket bluetoothSocket;

    static InputStream in;
    static OutputStream out;

    static boolean connected = false;

    public static BroadcastReceiver BTReciever = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            switch (intent.getAction()) {
                case BluetoothAdapter.ACTION_DISCOVERY_FINISHED:
                    break;
                case BluetoothDevice.ACTION_ACL_DISCONNECTED:
                    break;
            }
        }
    };

    static void sendMessage(String message) {
        try {
            System.out.println(message);
            out.write((message).getBytes());
        } catch (Exception e) {
            System.out.println("ERROR SENDING MESSAGE");
        }
    }
}
