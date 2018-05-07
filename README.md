# Linear-Programming
Using the Simplex Method to solve the Linear Programming Problems

This program is written for MATLAB.

When you want to solve a LP problem, you just need to rewrite the file "init.m".

You need to know that this program can just calculate the Standard Form, so please change the form into standard Form first.

For example, when you are going to solve this one:
min  x1+x2
s.t. x1+2x2<=3
     2x+3x2>=5
     x1,x2>=0
     
You should change it into this form:
max  -x1-x2
s.t. x1+2x2+x3=3
     2x1+3x2-x4=4
     x1,x2,x3,x4>=0

Then you will kown how to rewrite the file "init.m"
c is the coefficient of the subject function, which in this problem is
c=[-1 -1 0 0]

A is the main matrix, which in this problem is
A=[1 2 1 0;2 3 0 -1]

b is the vector in right hand side, which in this problem is
b=[3;5]
//Tips: b is a column vector while c is a row vector

Now you can take look at how to decide the starting basis. Two Phase Method and Big-M method are all good. When you decide how the initializing basis is, please input the NBV and BV.
For example, in the problem we just talked about, we can let the x3 and x4 = 0, then
NBV=[3 4]
BV=[1 2]

When you finished the rewriting on the file "init.m", please do these following steps.
1) Add the path to Matlab Path.
2) Input the following commands
>> clear
>> init
>> clc
>> LP
3) Read the word on the screen which will show you how the simplex method run in this problem and get the answer.

ATTENTION
1) This problem can only run the standard form, which has just equaltion restrictions, all variables are not smaller than 0, also just need the maximun.
2) The BV and NBV you provided must feasible to get the initializing basis. B is Full Rank Please.
3) If the problem is infeasible or unbounded, I don't know what will happened. Maybe I will update it later.

Thank you and Best wishes.
Hope this problem can help you.


------------------------Update 2018.5.7---------------------------

I have updated the file.
First, the matlab program can support the judgement of "unbounded" and "Infeasible".

Secondly, I add the cpp program for you all.

In the cpp program, a file named "LPdata.txt" is needed.

In this LPdata file,you should write in the following order:

!)n m
2)c
3)A
4)b
5)BV
6)NBV

For example, we see the following problem.
max 4x1+3x2+x3
s.t. 2x1-x2-1x3=5
     -4x1+3x2+x3=-1
     x1 x2 x3>=0
BV={2 3}
NBV={1}

In the file "LPdata.txt",you should write:
3 2

4 3 1

2 -1 -1
-4 3 1

5
-1

2 3
1
