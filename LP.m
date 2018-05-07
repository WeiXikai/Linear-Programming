[m,n]=size(A);
flag=0;
maxnumber=100000000;
while flag==0
    fprintf("------------------------------------\n");
    B=zeros(m,m);
    N=zeros(m,n-m);
    cB=zeros(m,1);
    cN=zeros(n-m,1);
    for i=1:m
        B(:,i)=A(:,BV(i));
        cB(i)=c(BV(i));
    end
    for i=1:(n-m)
        N(:,i)=A(:,NBV(i));
        cN(i)=c(NBV(i));
    end
    B
    N
    cB
    cN
    inverseB=B^(-1)
    if rank(B)<m
        fprintf("Infeasible");
        return ;
    end;
    xB=B^(-1)*b
    rN=cN'-cB'*B^(-1)*N
    flag=1;
    for i=1:(n-m)
        if rN(i)>0
            flag=0;
            EV=i;
            fprintf("Entering Variable:");
            NBV(EV)
            break;
        end
    end
    if flag==1
        break
    end
    bak=zeros(m,3);
    bak(:,1)=B^(-1)*b;
    bak(:,2)=B^(-1)*N(:,EV);
    bak(:,3)=bak(:,1)./bak(:,2);
    compare=bak(:,3)'
    min=maxnumber;
    LV=0;
    for i=1:m
        if bak(i,3)>0
            if bak(i,3)<min
                min=bak(i,3);
                LV=i;
            end
        end
    end
    if LV==0
        fprintf("unbounded");
        return ;
    end
    fprintf("Leaving Variable:");
    BV(LV)
    temp=BV(LV);
    BV(LV)=NBV(EV);
    NBV(EV)=temp;
    fprintf("Now:\n");
    BV=sort(BV)
    NBV=sort(NBV)
end
fprintf("------------------------------------\n");
fprintf("Finished!")
BV
NBV
xB=B^(-1)*b;
x=zeros(n,1);
for i=1:m
    x(BV(i))=xB(i);
end
x
c*x