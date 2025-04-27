package com.example.lab_6_210041219;

import java.util.ArrayList;

public class Submarine extends Ships{
    int start_x;
    int start_y;
    int count=0;
    String align = new String();
    Submarine(int x,int y, String a){
        start_x=x;
        start_y=y;
        align=a;
        coords = new ArrayList<Pair>();
        destroyed=false;
        scoreCounted=false;
        if(align=="horizontal"){
            coords.add(new Pair(x,y));
        }
    }

    @Override
    Boolean checkHit(int x, int y){
        for(Pair p : coords){
            if(p.x==x && p.y==y){
                count++; p.x=-1; p.y=-1;
                if(count==1) destroyed=true;
                return true;}
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