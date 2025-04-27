package com.example.demo;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;

import java.util.Stack;

import java.io.IOException;

public class HelloController {

    @FXML
    private Label txt= new Label("Enter a number");

    String msg = "";

    Stack<Integer> st = new Stack<Integer>();
    Stack<Character> holdOp = new Stack<Character>();
    Stack<Integer> holdNum = new Stack<Integer>();

    public void makeNum(){
        Integer num = 0, t=0 , mul=1;
        while( !st.empty() ){
            t=st.peek();
            t = t*mul;
            num = num + t;
            mul = mul * 10;

            st.pop();
        }
        holdNum.push(num);
        System.out.println(num);
    }

    public void on1click(ActionEvent e) throws IOException{

        st.push(1);
        msg = msg + "1";
        txt.setText(msg);
    }

    public void on2click(ActionEvent e) throws IOException{
        st.push(2);
        msg = msg + "2";
        txt.setText(msg);
    }

    public void on3click(ActionEvent e) throws IOException{
        st.push(3);
        msg = msg + "3";
        txt.setText(msg);
    }

    public void on4click(ActionEvent e) throws IOException{
        st.push(4);
        msg = msg + "4";
        txt.setText(msg);
    }

    public void on5click(ActionEvent e) throws IOException{
        st.push(5);
        msg = msg + "5";
        txt.setText(msg);
    }

    public void on6click(ActionEvent e) throws IOException{
        st.push(6);
        msg = msg + "6";
        txt.setText(msg);
    }

    public void on7click(ActionEvent e) throws IOException{
        st.push(7);
        msg = msg + "7";
        txt.setText(msg);
    }

    public void on8click(ActionEvent e) throws IOException{
        st.push(8);
        msg = msg + "8";
        txt.setText(msg);
    }

    public void on9click(ActionEvent e) throws IOException{
        st.push(9);
        msg = msg + "9";
        txt.setText(msg);
    }

    public void on0click(ActionEvent e) throws IOException{
        st.push(0);
        msg = msg + "0";
        txt.setText(msg);
    }

    public void onPlusclick(ActionEvent e) throws IOException{
        if(!st.empty()) makeNum();
        holdOp.push('+');
        msg = msg + " + ";
        txt.setText(msg);
    }//5*6+9+7

    public void onMinusclick(ActionEvent e) throws IOException{
        if(!st.empty()) makeNum();
        holdOp.push('-');
        msg = msg + " - ";
        txt.setText(msg);
    }

    public void onMultiplyclick(ActionEvent e) throws IOException{
        if(!st.empty()) makeNum();
        holdOp.push('*');
        msg = msg + " X ";
        txt.setText(msg);
    }

    public void onDivideclick(ActionEvent e) throws IOException{
        if(!st.empty()) makeNum();
        holdOp.push('/');
        msg = msg + " / ";
        txt.setText(msg);
    }

    public void onEqualclick(ActionEvent e) throws IOException{
        if(!st.empty()) makeNum();
        Stack<Character> helper = new Stack<Character>();
        Stack<Integer> helpnum = new Stack<Integer>();

        while (!holdOp.empty()){

            while(true) {
                Character c1=holdOp.pop();
                //System.out.println(holdOp.peek() + " " + c1);
                if( !holdOp.empty() && !hasPrecedence(holdOp.peek(), c1)) {
                    helper.push(c1);
                    helpnum.push(holdNum.pop());
                }
                else{
                    holdOp.push(c1);
                    break;
                }
            }

            holdNum.push(applyOp(holdOp.pop(), holdNum.pop(), holdNum.pop()));

            while(!helper.empty()){
                holdOp.push(helper.pop());
                holdNum.push(helpnum.pop());
            }

        }

        System.out.println(holdNum.peek());
        msg= holdNum.peek().toString();
        txt.setText(msg);
        //st.push(holdNum.peek());
            //values.push(applyOp(ops.pop(), values.pop(), values.pop()))
    }

    public void onClearclick(ActionEvent e) throws IOException{
        makeNum();

        while (!holdNum.empty()) holdNum.pop();
        while (!holdOp.empty()) holdNum.pop();
        msg = "";
        txt.setText("0");
    }

    public static int applyOp(char op, int b, int a)
    {
        System.out.println(op + " " + b + " " + a);
        switch (op)
        {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                if (b == 0)
                    throw new
                            UnsupportedOperationException("Cannot divide by zero");
                return a / b;
        }
        return 0;
    }
    public static boolean hasPrecedence(char op1, char op2)
    {
        if (op2 == '(' || op2 == ')')
            return false;
        if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
            return false;
        else
            return true;
    }


}