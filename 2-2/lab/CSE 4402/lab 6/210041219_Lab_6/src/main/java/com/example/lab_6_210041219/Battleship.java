package com.example.lab_6_210041219;

import java.util.ArrayList;
import java.util.Vector;

public class Battleship extends Ships{
    int start_x;
    int start_y;
    int count=0;
    String align = new String();
    Battleship(int x,int y, String a){
        start_x=x;
        start_y=y;
        align=a;
        destroyed=false;
        scoreCounted=false;
        coords = new ArrayList<Pair>();
        if(align=="horizontal"){
            coords.add(new Pair(x,y));
            coords.add(new Pair(x,(y+1) ));
            coords.add(new Pair(x,(y+2) ));
        }
        for(Pair p : coords){
            System.out.println("Battleship positioned at: "+p.x+p.y);
        }
    }

    @Override
    Boolean checkHit(int x, int y){
        for(Pair p : coords){
            System.out.println("Battleship found at: "+p.x+p.y);
            if(p.x==x && p.y==y){
                count++; p.x=-1; p.y=-1;
                if(count==3) destroyed=true;
                return true;
            }
        }
        return false;
    }

    @Override
    Boolean checkOcc(int x,int y){
        for(Pair p : coords){
            if(p.x==x && p.y==y){
                return true;
            }
        }
        return false;
    }
}
