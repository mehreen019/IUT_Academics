package com.example.lab_6_210041219;

import javafx.event.ActionEvent;
import javafx.animation.PauseTransition;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.IOException;

import static java.lang.Math.abs;

public class HelloController {

    public Parent root;
    private Scene scene;
    private Stage stage;

    private Fleet p1 = new Fleet();
    Node[][] allNodesp1 = new Node[10][10];
    Node[][] p1attacks = new Node[10][10];

    int p1score=0;
    int loc_x=-1;
    int loc_y=-1;
    Boolean thisturn=true;


    Boolean fs=false;
    private Button btn = new Button();
    @FXML
    public GridPane p1ShipPlace;
    @FXML
    public GridPane p1Attack;

    @FXML
    public Label scorecard;
    @FXML
    public Label instruction;

    @FXML
    protected void onButtonClick(ActionEvent e) {
        //btn00.setText("X");
        this.btn = (Button) e.getSource();
        String st[] = btn.getId().split("");
        System.out.println(st[1]+st[2]);
        int row = Integer.parseInt(st[1]);
        int col = Integer.parseInt(st[2]);

        if(st[0]=="p"){
            Alert a = new Alert(Alert.AlertType.WARNING);
            a.show();
        }
        else{
            Boolean ans=false;
            for(Ships ship: SceneManager.SceneSwitcher.p2fleet.allShips){
                ans = ship.checkHit(row,col);
                if(ans==true){
                    if(ship.destroyed==true && ship.scoreCounted==false){


                        String cn = ship.getClass().getSimpleName();

                        if(cn.equals("Battleship")){ p1score= p1score+3; instruction.setText("Battleship destroyed!");}
                        else if(cn.equals("Destroyer")){ p1score= p1score+2; instruction.setText("Destroyer destroyed!");}
                        else if(cn.equals("Submarine")){ p1score= p1score+1; instruction.setText("Submarine destroyed!");}

                        ship.scoreCounted=true;
                        System.out.println("Ship destroyed: "+cn+" "+ p1score);
                        scorecard.setText("Score: "+p1score);

                        if(p1score==10){

                        }
                    }
                    break;
                }
            }

            if(ans==true){
                btn.setText("X");
                btn.setTextFill(Color.WHITE);
                btn.setStyle("-fx-background-color: #e30303; ");
                ((Button) p1attacks[row][col]).setText("X");
            }
            else{
                btn.setText("O");
                btn.setStyle("-fx-background-color: #6198e1; ");
                ((Button) p1attacks[row][col]).setText("O");
            }

            this.startPauseAndAction(e, ans);
        }
    }

    private void startPauseAndAction(ActionEvent e, Boolean ans) {
        // Create a PauseTransition with a duration of 2 seconds
        PauseTransition pause = new PauseTransition(Duration.seconds(0.5));

        // Set the action to be performed after the pause
        pause.setOnFinished(event -> {
            // Perform your next action here after the 2-second delay
            try{
                this.switchToSecond(e, ans);
            }
            catch(Exception ex){
                ex.printStackTrace();
            }
        });

        // Start the pause transition
        pause.play();
    }

    public void switchToSecond(ActionEvent e, Boolean ans) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("hello-view-2.fxml"));
        //loader.setController(this);
        root = loader.load();
        root.setStyle("-fx-background-color: lightblue;");
        scene2controller newc = loader.getController();
        if(fs==false){
            newc.initGrid("attack", newc.p2Attack);
            newc.initGrid("place",  newc.p2ShipPlace);
            fs=true;
        }
        else{
            newc.initialize(SceneManager.SceneSwitcher.p2fleet, SceneManager.SceneSwitcher.p2Nodes, SceneManager.SceneSwitcher.p2Attacks, ans);
        }
        SceneManager.SceneSwitcher.p1fleet = p1;
        SceneManager.SceneSwitcher.p1Nodes = allNodesp1;
        SceneManager.SceneSwitcher.p1Attacks = p1attacks;
        SceneManager.SceneSwitcher.p1SCORE = p1score;
        SceneManager.SceneSwitcher.p2hit = ans;
        stage = (Stage)((Node)e.getSource()).getScene().getWindow();
        scene =  new Scene(root);
        //scene.setFill(Color.AQUAMARINE);
        stage.setScene(scene);
        stage.show();
    }

    protected void moveShip(ActionEvent e){
        Button bt = (Button) e.getSource();
        String[] st = bt.getId().split("");
        System.out.println(st[1]+st[2]);
        int row = Integer.parseInt(st[1]);
        int col = Integer.parseInt(st[2]);

        if(loc_x==-1 && loc_y==-1 && thisturn==true){
            loc_x=row;
            loc_y=col;
            this.btn = bt;
            instruction.setText("Choose where to move");
        }
        else if(thisturn==true){
            if(abs(loc_y-col)>1 || loc_x!=row){
                Alert a = new Alert(Alert.AlertType.WARNING);
                a.show();
                return;
            }

            Boolean ans=false;


            if(loc_y<col) {
                for (Ships ship : p1.allShips) {
                    String cn = ship.getClass().getSimpleName();
                    int tempy = 0;
                    if (cn.equals("Battleship")) {
                        tempy = loc_y - 2;
                    } else if (cn.equals("Destroyer")) {
                        tempy = loc_y - 1;
                    } else if (cn.equals("Submarine")) {
                        tempy = loc_y;
                    }

                    for (Ships.Pair p : ship.coords) {
                        if (p.x == loc_x && p.y == tempy && ship.destroyed == false) {
                            btn = (Button) allNodesp1[p.x][p.y];
                            System.out.println("deleting: "+ btn.getId());
                            btn.setStyle(" {-fx-background-color: #ffffff};");
                            for(Node child: p1ShipPlace.getChildren()){
                                Integer gridcol = GridPane.getColumnIndex(child);
                                Integer gridrow = GridPane.getRowIndex(child);
                                if(gridcol==null) gridcol =0;
                                if(gridrow==null) gridrow=0;

                                if(gridcol==p.y && gridrow==p.x){
                                    ((Button) child).setStyle("{-fx-background-color: #ffffff !important; }");
                                }
                            }
                            ((Button) allNodesp1[p.x][p.y]).setText("");
                            //System.out.println("deleting: "+p.x+p.y);

                            p.x = row;
                            p.y = col;
                            bt.setStyle("-fx-background-color: #000000; ");
                            ((Button) allNodesp1[p.x][p.y]).setText("occupied");
                            System.out.println("adding: "+p.x+p.y);

                            instruction.setText("Moved to new location. Now Attack!");
                            loc_x=-1; loc_y=-1; thisturn=false;

                            return;
                            //ans = true;
                            //break;
                        }
                        else if(p.x == loc_x && p.y == tempy && ship.destroyed == true){
                            instruction.setText("This is already destroyed");
                            return;
                        }
                    }
                    if(ans==true) break;
                }
                instruction.setText("Failed to move");
                loc_x=-1; loc_y=-1; thisturn=false;
            }
            else{
                for(Ships ship: p1.allShips) {
                        String cn = ship.getClass().getSimpleName();
                        int tempy=0;
                        if(cn.equals("Battleship")){ tempy= loc_y+2;}
                        else if(cn.equals("Destroyer")){ tempy= loc_y+1;}
                        else if(cn.equals("Submarine")){ tempy=loc_y;}

                        for (Ships.Pair p : ship.coords) {
                            if (p.x == loc_x && p.y == tempy && ship.destroyed == false) {
                                btn = (Button) allNodesp1[p.x][p.y];
                                System.out.println("deleting: "+ btn.getId());
                                btn.setStyle("{-fx-background-color: #ffffff !important; }");

                                for(Node child: p1ShipPlace.getChildren()){
                                    Integer gridcol = GridPane.getColumnIndex(child);
                                    Integer gridrow = GridPane.getRowIndex(child);
                                    if(gridcol==null) gridcol =0;
                                    if(gridrow==null) gridrow=0;

                                    if(gridcol==p.y && gridrow==p.x){
                                        ((Button) child).setStyle("{-fx-background-color: #ffffff !important; }");
                                    }
                                }
                                ((Button) allNodesp1[p.x][p.y]).setText("");
                                //System.out.println("deleting: "+p.x+p.y);


                                p.x=row; p.y=col;
                                bt.setStyle("-fx-background-color: #000000; ");
                                System.out.println("adding: "+p.x+p.y);
                                ((Button) allNodesp1[p.x][p.y]).setText("occupied");

                                instruction.setText("Moved to new location. Now Attack!");
                                loc_x=-1; loc_y=-1; thisturn=false;

                                return;
                                //ans=true;
                                //break;
                            }
                            else if(p.x == loc_x && p.y == tempy && ship.destroyed == true){
                                instruction.setText("This is already destroyed");
                                return;
                            }
                        }

                        if(ans==true) break;
                }
            }


        }
        else{
            Alert a = new Alert(Alert.AlertType.WARNING);
            a.show();
        }
    }

    protected void toPlaceAll(ActionEvent e){
        this.btn = (Button) e.getSource();
        String[] st = btn.getId().split("");
        System.out.println(st[1]+st[2]);
        int row = Integer.parseInt(st[1]);
        int col = Integer.parseInt(st[2]);

            if(p1.sub<3) {
                Boolean ans=false;

                if(p1.dest<2){
                    if(p1.battle<1){
                        ans=false;
                    }
                    else{
                        ans= p1.checkOccupied(row, col+1);
                        if(ans==true){
                            Alert a = new Alert(Alert.AlertType.WARNING);
                            a.show();
                            return;
                        }
                    }
                }
                else{
                    ans= p1.checkOccupied(row, col);
                    if(ans==true){
                        Alert a = new Alert(Alert.AlertType.WARNING);
                        a.show();
                        return;
                    }
                }

                btn.setStyle("-fx-background-color: #000000; ");
                ((Button) allNodesp1[row][col]).setText("occupied");

                if (p1.dest < 2) {
                    btn = (Button) allNodesp1[row][col + 1];
                    btn.setStyle("-fx-background-color: #000000; ");
                    ((Button) allNodesp1[row][col + 1]).setText("occupied");
                }
                if (p1.battle < 1) {
                    btn = (Button) allNodesp1[row][col + 2];
                    btn.setStyle("-fx-background-color: #000000; ");
                    ((Button) allNodesp1[row][col + 2]).setText("occupied");
                }
                p1.inputShip(row, col);

                if(p1.sub==3){
                    try{
                        this.switchToSecond(e, false);
                    }
                    catch(Exception ex){
                        ex.printStackTrace();
                    }
                }
            }
            else{
                Alert a = new Alert(Alert.AlertType.WARNING);
                a.show();
            }
    }

    void initialize(Fleet f, Node[][] n, Node[][] a, Boolean hit){
        p1=f; allNodesp1=n; fs=true; p1attacks=a; p1score= SceneManager.SceneSwitcher.p1SCORE;
        this.loc_x=-1; this.loc_y=-1; this.thisturn= hit;

        for(Node child: p1ShipPlace.getChildren()){
            Integer column = GridPane.getColumnIndex(child);
            Integer row = GridPane.getRowIndex(child);
            if(column==null) column =0;
            if(row==null) row=0;
            child.setId("p"+ row + column);
            //if(allNodesp1[row][column] instanceof Button){
            Button btn = (Button) allNodesp1[row][column];
            if(btn.getText()=="occupied"){
                    child.setStyle("-fx-background-color: #000000; ");
                    System.out.println("ok");
            }

            if (child instanceof Button) {
                this.btn = (Button) child;
                ((Button)child).setOnAction(this::moveShip);
            }
        }

        for(Node child: p1Attack.getChildren()){
            Integer column = GridPane.getColumnIndex(child);
            Integer row = GridPane.getRowIndex(child);
            if(column==null) column =0;
            if(row==null) row=0;
            child.setId("a"+ row + column);
            //if(allNodesp1[row][column] instanceof Button){
            Button btn = (Button) p1attacks[row][column];

            if (child instanceof Button) {
                if(btn.getText()=="X"){
                    ((Button)child).setText("X");
                    child.setStyle("-fx-background-color: #e30303; ");
                    System.out.println("ok");
                }
                else if(btn.getText()=="O"){
                    ((Button)child).setText("O");
                    child.setStyle("-fx-background-color: #6198e1; ");
                }

                this.btn = (Button) child;
                //System.out.println("reached action setting");
                /*btn.setOnAction(event ->{
                    this.onButtonClick(event);
                } );*/
                ((Button)child).setOnAction(this::onButtonClick);
            }
        }

        scorecard.setText("Score: "+p1score);
        instruction.setText("Attack!");

    }

    protected void initGrid(String action, GridPane g){

        for (Node child : g.getChildren()) {
            Integer column = GridPane.getColumnIndex(child);
            Integer row = GridPane.getRowIndex(child);
            if(column==null) column =0;
            if(row==null) row=0;
            if (child instanceof Button) {
                if(action=="place")
                    allNodesp1[row][column] = (Button) child;
                else
                    p1attacks[row][column]= (Button) child;
            }


            if (child instanceof Button) {
                this.btn = (Button) child;
                // Now you can safely work with btn
            }
            if(action=="attack"){
                child.setId("a"+ row + column);
                btn.setOnAction(event ->{
                    this.onButtonClick(event);

                    PauseTransition pause = new PauseTransition(Duration.seconds(1));

                    // Set the action to be performed after the pause
                    //pause.setOnFinished(e -> {
                        // Perform your next action here after the 2-second delay
                        try{
                            this.switchToSecond(event, false);
                        }
                        catch(Exception ex){
                            ex.printStackTrace();
                        }

                    //});

                    // Start the pause transition
                    //pause.play();
                } );
            }
            else {
                child.setId("p"+ row + column);
                btn.setOnAction(event -> this.toPlaceAll(event));
            }
        }
        //return g;
    }

}