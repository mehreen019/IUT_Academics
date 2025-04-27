package com.example.lab_6_210041219;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        try{
            /*FXMLLoader loader2 = new FXMLLoader(getClass().getResource("hello-view-2.fxml"));
            Parent root = loader2.load();
            scene2controller controller2 = loader2.getController();
            controller2.initGrid("attack", controller2.p2Attack);
            controller2.initGrid("place",  controller2.p2ShipPlace);*/

            FXMLLoader loader1 = new FXMLLoader(getClass().getResource("hello-view.fxml"));
            Parent root = loader1.load();
            root.setStyle("-fx-background-color: lightblue;");
            HelloController controller1 = loader1.getController();
            controller1.initGrid("attack", controller1.p1Attack);
            controller1.initGrid("place",  controller1.p1ShipPlace);

            Scene scene = new Scene(root);
            //scene.setFill(Color.AQUAMARINE);
            stage.setTitle("Battleship");
            stage.setScene(scene);
            stage.show();
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch();
    }
}