package com.example.lab_6_210041219;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

import java.io.IOException;

public class SceneManager {
    public Parent root;
    private Scene scene;
    private Stage stage;
    void initialize() {}
    void initData(GridPane p1p, GridPane p2p) {
        //p1ship = p1p;
        //p2ship = p2p;
    }

    public static class SceneSwitcher{

        public static Fleet p1fleet;
        public static Node[][] p1Nodes;
        public static Node[][] p1Attacks;

        public static int p1SCORE;

        public static Boolean p1hit;

        public static Fleet p2fleet;
        public static Node[][] p2Nodes;
        public static Node[][] p2Attacks;
        public static int p2SCORE;

        public static Boolean p2hit;

    }
}
