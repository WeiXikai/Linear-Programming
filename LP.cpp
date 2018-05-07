#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int maxn=501;
const int maxm=251;
const string spareline="----------------\n";

const int main_stack=16;
char my_stack[128<<20];

ifstream fin;

int swap(double &a,double &b){
    double c;
    c=a;
    a=b;
    b=c;
    return 0;
}

int swap(int &a,int &b){
    int c;
    c=a;
    a=b;
    b=c;
    return 0;
}

struct matrix{
    int n;
    int m;
    double data[maxn][maxm];
    matrix(){
    	n=0;
    	m=0;
		for (int i = 0; i < maxn; i++){
			for (int j = 0; j < maxm; j++){
				data[i][j] = 0;
			}
		}
	}
	matrix Trans(){
        matrix B;
        B.n=m;
        B.m=n;
        for (int i=1;i<=n; i++){
            for (int j=1; j<=m; j++){
                B.data[j][i]=data[i][j];
            }
        }
        return B;
    }//转置
    int exrow(int a,int b){
        for (int i=1;i<=m;i++){
            swap(data[a][i],data[b][i]);
        }
        return 0;
    }//交换两行
    int excol(int a,int b){
        for (int i=1;i<=n;i++){
            swap(data[i][a],data[i][b]);
        }
        return 0;
    }//交换两列
    int addcol(int a,int b){
        for (int i=1;i<=n;i++){
            data[i][a]+=data[i][b];
        }
        return 0;
    }//在第a列加上第b列的值
    int addrow(int a,int b){
        for (int i=1;i<=m;i++){
            data[a][i]+=data[b][i];
        }
        return 0;
    }//在第a行加上第b行的值
    int multrow(int a,double k){
        for (int i=1;i<=m;i++){
            data[a][i]*=k;
        }
        return 0;
    }//第a行乘上k
    int multcol(int a,double k){
        for (int i=1;i<=n;i++){
            data[i][a]*=k;
        }
        return 0;
    }//第a列乘上k
    int output(){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=m;j++){
                cout<<"\t"<<setprecision(5)<<data[i][j]<<"\t";
            }
            cout<<endl;
        }
        return 0;
    }//输出调试
    int input(int N,int M){
        n=N;
        m=M;
        for (int i=1;i<=n;i++){
            for (int j=1;j<=m;j++){
                fin>>data[i][j];
            }
        }
        return 0;
    }
    matrix getcol(int x[maxn],int size){
        matrix B;
        B.n=n;
        B.m=size;
        for (int i=1;i<=n;i++){
            for (int j=1;j<=size;j++){
                B.data[i][j]=data[i][x[j]];
            }
        }
        return B;
    }//返回B的若干列
    matrix getrow(int x[maxn],int size){
        matrix B;
        B.n=size;
        B.m=m;
        for (int i=1;i<=size;i++){
            for (int j=1;j<=m;j++){
                B.data[i][j]=data[x[i]][j];
            }
        }
        return B;
    }//返回B的若干行
    matrix inverse(){
        if (n!=m){
            printf("Fuck you! It is not a square matrix!\n");
            matrix B;
            return B;
        }
        matrix A;
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                A.data[i][j]=data[i][j];
            }
        }
        for (int i=1;i<=n;i++){
            A.data[i][n+i]=1;
        }
        A.n=n;
        A.m=m*2;
        for (int i=1;i<=n;i++){
            if (A.data[i][i]==0){
                int flag=0;
                for (int j=i;j<=n;j++){
                    if (A.data[j][i]!=0){
                        flag=j;
                        break;
                    }
                }
                if (flag==0){
                    printf("Fuck you! It is a noninvertible matrix!\n");
                    matrix B;
                    return B;
                }
                A.exrow(i,flag);
            }
            A.multrow(i,1/A.data[i][i]);
            for (int j=1;j<i;j++){
                if (A.data[j][i]!=0){
                    A.multrow(j,-A.data[i][i]/A.data[j][i]);
                    A.addrow(j,i);
                    A.multrow(j,1/A.data[j][j]);
                }
            }
            for (int j=i+1;j<=n;j++){
                if (A.data[j][i]!=0){
                    A.multrow(j,-A.data[i][i]/A.data[j][i]);
                    A.addrow(j,i);
                }
            }
        }
        matrix B;
        B.n=n;
        B.m=n;
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                B.data[i][j]=A.data[i][j+n];
            }
        }
        return B;
    }//高斯消元求逆矩阵
    int rank(){
        matrix A;
        for (int i=1;i<=n;i++){
            for (int j=1;j<=m;j++){
                A.data[i][j]=data[i][j];
            }
        }
        A.n=n;
        A.m=m;
        int i=1;
        for (int j=1;j<=n;j++){
            if (i>m){
                return j-1;
            }
            if (A.data[j][i]==0){
                int flag=0;
                for (int k=j;k<=n;k++){
                    if (A.data[k][i]!=0){
                        flag=k;
                        break;
                    }
                }
                if (flag==0){
                    i++;
                    continue;
                }
                A.exrow(j,flag);
            }
            for (int k=j+1;k<=n;k++){
                if (A.data[k][i]!=0){
                    A.multrow(k,-A.data[j][i]/A.data[k][i]);
                    A.addrow(j,k);
                }
            }
            i++;
        }
        return n;
    }
};

matrix operator *(matrix A,matrix B){
	matrix C;
	if (A.m!=B.n){
        printf("Fuck you! These two matrix cannot multiply together!\n");
        return C;
    }
    C.n=A.n;
    C.m=B.m;
    for (int i=1;i<=A.n;i++){
        for (int j=1;j<=B.m;j++){
            for (int k=1;k<=A.m;k++){
                C.data[i][j]+=A.data[i][k]*B.data[k][j];
            }
        }
    }
	return C;
}//矩阵乘法

matrix operator +(matrix A,matrix B){
    matrix C;
    if ((A.n!=B.n)||(A.m!=B.m)){
        printf("Fuck you! These two matrix cannot plus together!\n");
        return C;
    }
    C.n=A.n;
    C.m=A.m;
    for (int i=1;i<=A.n;i++){
        for (int j=1;j<=A.m;j++){
            C.data[i][j]=A.data[i][j]+B.data[i][j];
        }
    }
    return C;
}//矩阵加法

matrix operator -(matrix A,matrix B){
    matrix C;
    if ((A.n!=B.n)||(A.m!=B.m)){
        printf("Fuck you! These two matrix cannot plus together!\n");
        return C;
    }
    C.n=A.n;
    C.m=A.m;
    for (int i=1;i<=A.n;i++){
        for (int j=1;j<=A.m;j++){
            C.data[i][j]=A.data[i][j]-B.data[i][j];
        }
    }
    return C;
}//矩阵减法

matrix operator ^(matrix A,int n){
    matrix C;
    if (n==-1){
        C=A.inverse();
    }else{
        C=A;
        for (int i=1;i<n;i++){
            C=C*A;
        }
    }
    return C;
}//矩阵求逆与乘方

int n;//变量数量
int m;//限制数量
matrix c;//目标函数的系数(1*n矩阵)
matrix A;//限制的系数阵(m*n矩阵)
matrix b;//限制的值矩阵(m*1矩阵)
int BV[maxn];//BV的编号数列
int NBV[maxn];//NBV的编号数列

int init(){
    fin.open("LPdata.txt",ios::in);
    fin>>n>>m;
    c.input(1,n);
    A.input(m,n);
    b.input(m,1);
    for (int i=1;i<=m;i++){
        fin>>BV[i];
    }
    for (int i=1;i<=n-m;i++){
        fin>>NBV[i];
    }
    fin.close();
    printf("init:\n");
    printf("c=\n");
    c.output();
    printf("\n");
    printf("A=\n");
    A.output();
    printf("\n");
    printf("b=\n");
    b.output();
    printf("\n");
    return 0;
}

int LP(){
    int flag=0;
    matrix B;
    matrix cB;
    matrix N;
    matrix cN;
    matrix xB;
    matrix rN;
    while (flag==0){
        cout<<spareline;
        printf(" BV: \n");
        for (int i=1;i<=m;i++){
            cout<<"\t"<<"x"<<BV[i];
        }
        cout<<endl;
        printf("NBV: \n");
        for (int i=1;i<=n-m;i++){
            cout<<"\t"<<"x"<<NBV[i];
        }
        cout<<endl;
        cout<<endl;
        B=A.getcol(BV,m);
        cB=c.getcol(BV,m);
        N=A.getcol(NBV,n-m);
        cN=c.getcol(NBV,n-m);
        printf("B=\n");
        B.output();
        printf("\n");
        printf("N=\n");
        N.output();
        printf("\n");
        printf("cB=\n");
        cB.output();
        printf("\n");
        printf("cN=\n");
        cN.output();
        printf("\n");
        printf("B^(-1)=\n");
        B.inverse().output();
        printf("\n");
        if (B.rank()<m){
            printf("Fuck you! It is infeasiable!\n");
            return 1;
        }
        xB=(B^(-1))*b;
        printf("xB=\n");
        xB.output();
        cout<<endl;
        rN=cN-cB*(B^(-1))*N;
        printf("rN=\n");
        rN.output();
        cout<<endl;
        flag=1;
        int EV=0;
        for (int i=1;i<=n-m;i++){
            if (rN.data[1][i]>0){
                flag=0;
                EV=i;
                printf("Entering Variable:\n");
                cout<<"\t"<<"x"<<NBV[EV]<<endl;
                break;
            }
        }
        if (flag==1){
            break;
        }
        matrix bak1=(B^(-1))*b;
        int _EV[maxn];
        _EV[1]=EV;
        matrix bak2=(B^(-1))*N.getcol(_EV,1);
        double compare[maxn];
        for (int i=1;i<=m;i++){
            compare[i]=bak1.data[i][1]/bak2.data[i][1];
        }
        double min=1e100;
        int LV=0;
        for (int i=1;i<=m;i++){
            if (compare[i]>0){
                if (compare[i]<min){
                    min=compare[i];
                    LV=i;
                }
            }
        }
        if (LV==0){
            printf("Fuck you! It is unbounded!\n");
            return 2;
        }
        printf("Leaving Variable:\n");
        cout<<"\t"<<"x"<<BV[LV]<<endl<<endl;
        swap(BV[LV],NBV[EV]);
        for (int i=1;i<=m-1;i++){
            for (int j=i+1;j<=m;j++){
                if (BV[i]>BV[j]){
                    swap(BV[i],BV[j]);
                }
            }
        }
        for (int i=1;i<=n-m-1;i++){
            for (int j=i+1;j<=n-m;j++){
                if (NBV[i]>NBV[j]){
                    swap(NBV[i],NBV[j]);
                }
            }
        }
        cout<<endl;
    }
    cout<<spareline;
    printf("FINISHED!\n");
    xB=(B^(-1))*b;
    matrix x;
    x.n=n;
    x.m=1;
    for (int i=1;i<=m;i++){
        x.data[BV[i]][1]=xB.data[i][1];
    }
    printf("x=\n");
    x.output();
    matrix ans=c*x;
    printf("ans=\n");
    cout<<"\t"<<ans.data[1][1]<<endl;
    return 0;
}

int main(){
	init();
    __asm__("movl %%esp, (%%eax);\n"::"a"(my_stack):"memory");
    __asm__("movl %%eax, %%esp;\n"::"a"(my_stack+sizeof(my_stack)-main_stack):"%esp");
    LP();
    __asm__("movl (%%eax), %%esp;\n"::"a"(my_stack):"%esp");
    return 0;
}
