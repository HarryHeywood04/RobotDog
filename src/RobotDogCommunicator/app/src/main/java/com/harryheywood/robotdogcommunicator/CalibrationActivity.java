package com.harryheywood.robotdogcommunicator;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.io.InputStream;
import java.io.OutputStream;

public class CalibrationActivity extends AppCompatActivity {
    Button minusButton, plusButton, cancelButton, confirmButton;
    Spinner servoSpinner;

    int servo = 0;
    int[] angles = {90,90,90,90,90,90,90,90};

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_calibration);

        minusButton = findViewById(R.id.minus_button);
        plusButton = findViewById(R.id.plus_button);
        cancelButton = findViewById(R.id.cancel_button);
        confirmButton = findViewById(R.id.confirm_button);
        servoSpinner = findViewById(R.id.servo_spinner);
        Connection.sendMessage("calibrate");

        minusButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("a" + --angles[servo]);
            }
        });

        plusButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("a" + ++angles[servo]);
            }
        });

        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("x");
                finish();
            }
        });

        confirmButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("c");
                finish();
            }
        });

        servoSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                Connection.sendMessage("s" + position);
                servo = position;
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
    }
}
