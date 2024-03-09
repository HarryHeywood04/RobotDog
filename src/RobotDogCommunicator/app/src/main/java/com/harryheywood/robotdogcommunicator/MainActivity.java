package com.harryheywood.robotdogcommunicator;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.net.ipsec.ike.TunnelModeChildSessionParams;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.Console;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.List;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {
    Button ScanButton, ConnectButton, ControlButton, CalibrateButton;

    IntentFilter intentFilter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ConnectButton = findViewById(R.id.connect_button);
        ControlButton = findViewById(R.id.controller_button);
        CalibrateButton = findViewById(R.id.calibrate_button);

        Connection.bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        intentFilter.addAction(BluetoothDevice.ACTION_ACL_DISCONNECTED);

        registerReceiver(Connection.BTReciever, intentFilter);
        ConnectButton.setEnabled(false);
        ControlButton.setEnabled(false);
        CalibrateButton.setEnabled(false);

        if (ActivityCompat.checkSelfPermission(getApplicationContext(), android.Manifest.permission.BLUETOOTH_CONNECT) == PackageManager.PERMISSION_GRANTED) {
            Set<BluetoothDevice> devices = Connection.bluetoothAdapter.getBondedDevices();
            for (BluetoothDevice dev : devices) {
                if (dev.getName().equals("HC-05")) {
                    Connection.bluetoothDevice = dev;
                    ConnectButton.setEnabled(true);
                    break;
                }
            }
        }

        ConnectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    ConnectButton.setText("Connect");
                    ControlButton.setEnabled(false);
                    CalibrateButton.setEnabled(false);
                    Connection.connected = false;
                    if (ActivityCompat.checkSelfPermission(getApplicationContext(), android.Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                        return;
                    }
                    Connection.bluetoothSocket = Connection.bluetoothDevice.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
                    Connection.bluetoothSocket.connect();
                    Connection.in = Connection.bluetoothSocket.getInputStream();
                    Connection.out = Connection.bluetoothSocket.getOutputStream();
                    ControlButton.setEnabled(true);
                    CalibrateButton.setEnabled(true);
                    ConnectButton.setText("Disconnect");
                    Toast.makeText(getApplicationContext(), "CONNECTED", Toast.LENGTH_SHORT).show();
                } catch (Exception e) {}
            }
        });

        ControlButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, ControllerActivity.class);
                startActivity(intent);
            }
        });

        CalibrateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, CalibrationActivity.class);
                startActivity(intent);
            }
        });
    }
}