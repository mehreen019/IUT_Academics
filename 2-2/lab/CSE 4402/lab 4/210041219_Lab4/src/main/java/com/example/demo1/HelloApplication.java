package com.example.demo1;

import java.io.IOException;
import javafx.application.Application;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.image.ImageView;
import javafx.scene.text.Text;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;

import javafx.scene.Scene;
import javafx.stage.Stage;

public class HelloApplication extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        //Stage stage = new Stage();
        try {
            Parent root = FXMLLoader.load(getClass().getResource("hello-view.fxml"));
            //Group root = new Group();
            Scene scene = new Scene(root, Color.SKYBLUE);

            //String css = this.getClass().getResource("game.css").toExternalForm();
            //scene.getStylesheets().add(css);
        /*Text text = new Text();
        text.setText("ok");
        text.setX(100);
        text.setY(100);
        text.setFill(Color.BLACK);
        text.setVisible(true);

        root.getChildren().add(text);*/
            //Image icon = new Image("/unnamed.png"); //won't work
            //ImageView iconView = new ImageView(icon);

            //stage.getIcons().add(icon);
            stage.setTitle("moushi's first java app!");
            //stage.setHeight(420);
            //stage.setWidth(420);
            //stage.setResizable(false);
            //stage.setX(50);
            //stage.setY(50);

            //stage.setFullScreen(true);
            //stage.setFullScreenExitHint("press q to exit");
            //stage.setFullScreenExitKeyCombination(KeyCombination.valueOf("q"));

            stage.setScene(scene);
            stage.show();
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}