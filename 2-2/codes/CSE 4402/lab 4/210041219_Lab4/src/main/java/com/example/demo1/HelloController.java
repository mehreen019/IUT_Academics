package com.example.demo1;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloController {
    int cnt=0;
    public Parent root;
    private Scene scene;
    private Stage stage;
    public void submit(ActionEvent e) throws IOException {
        if(cnt==3){
            System.out.println("submitted");
            this.switchToWin(e);
        }
        else {
            cnt = 0;
            System.out.println("reset");
            this.switchToSecond(e);
        }
    }

    public void switchToWin(ActionEvent e) throws IOException {
        root = FXMLLoader.load(getClass().getResource("win.fxml"));
        stage = (Stage)((Node)e.getSource()).getScene().getWindow();
        scene =  new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    public void switchToFirst(ActionEvent e) throws IOException {
        root = FXMLLoader.load(getClass().getResource("hello-view.fxml"));
        stage = (Stage)((Node)e.getSource()).getScene().getWindow();
        scene =  new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    public void switchToSecond(ActionEvent e) throws IOException{
        root = FXMLLoader.load(getClass().getResource("endCredits.fxml"));
        stage = (Stage)((Node)e.getSource()).getScene().getWindow();
        scene =  new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    public void exit(ActionEvent e) throws IOException{
        Platform.exit();
    }

    public void onCclick(ActionEvent e){
        if(cnt==0){
            cnt++;
            System.out.println("c");
        }
        else cnt=0;
    }

    public void onAclick(ActionEvent e){
        if(cnt==1){
            cnt++;
            System.out.println("a");
        }
        else cnt=0;
    }
   public void onRclick(ActionEvent e){
        if(cnt==2){
            cnt++;
            System.out.println("r");
        }
        else cnt=0;
    }


}