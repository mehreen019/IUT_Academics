package com.example.lab_6_210041219;

import java.util.ArrayList;

public class Fleet {
    ArrayList<Ships> allShips = new ArrayList<>();
    public int battle;
    public int dest;
    public int sub;

    Fleet(){
        battle=0;
        sub=0;
        dest=0;
    }

    void inputShip(int x, int y){
        if(battle<1){
            System.out.println("in fleet, adding battleship at: "+x+y);
            allShips.add(new Battleship(x,y,"horizontal"));
            battle++;
        }
        else if(dest<2){
            allShips.add(new Destroyer(x,y,"horizontal"));
            dest++;
        }
        else if(sub<3){
            allShips.add(new Submarine(x,y,"horizontal"));
            sub++;
        }
    }

    Boolean checkOccupied(int x, int y){
        Boolean ans=false;
        for(Ships ship: allShips) {
            ans = ship.checkOcc(x, y);
            if(ans==true) return true;
        }
        return false;
    }
}
