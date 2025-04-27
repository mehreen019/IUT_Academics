package com.example.lab_6_210041219;

import java.util.ArrayList;

public abstract class Ships {
    Boolean destroyed;
    Boolean scoreCounted;
    public ArrayList<Pair> coords;
    abstract Boolean checkHit(int x, int y);
    abstract Boolean checkOcc(int x,int y);
    class Pair{
        int x;
        int y;

        Pair(int X, int Y){
            x=X;
            y=Y;
        }
    }

}

