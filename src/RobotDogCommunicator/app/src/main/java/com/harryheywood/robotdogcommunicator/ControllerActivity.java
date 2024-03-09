package com.harryheywood.robotdogcommunicator;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class ControllerActivity extends AppCompatActivity {

    Button forwardButton,rightButton,backButton,leftButton,menuButton;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controller);

        forwardButton = findViewById(R.id.btn_fwd);
        rightButton = findViewById(R.id.btn_rgt);
        backButton = findViewById(R.id.btn_bac);
        leftButton = findViewById(R.id.btn_lft);
        menuButton = findViewById(R.id.btn_menu);
        Connection.sendMessage("control");

        forwardButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("fwd");
            }
        });

        rightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("rgt");
            }
        });

        backButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("bck");
            }
        });

        leftButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("lft");
            }
        });

        menuButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Connection.sendMessage("menu");
                finish();
            }
        });
    }
}
