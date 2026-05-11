% Colouring Australia using nc colours
int: nc = 3;

var 1..3: wa;   
var 1..3: nt;  
var 1..3: sa;   
var 1..3: q;
var 1..3: nsw;  
var 1..3: v;   
var 1..3: t;

constraint wa != nt;
constraint wa != sa;
constraint nt != sa;
constraint nt != q;
constraint sa != q;
constraint sa != nsw;
constraint sa != v;
constraint q != nsw;
constraint nsw != v;

solve satisfy;

output ["wa=\(wa)\t nt=\(nt)\t sa=\(sa)\n",
        "q=\(q)\t nsw=\(nsw)\t v=\(v)\n",
         "t=", show(t),  "\n"];
