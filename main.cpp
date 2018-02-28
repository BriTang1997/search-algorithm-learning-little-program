#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <queue>
using namespace std;

int stx,sty;
int n;
int aix=0,aiy=0;
struct node{
    int x;int y;
    node(int a = -1,int b = -1){
        x=a;y=b;
    }

};
bool operator < (const node &a,const node& b) {
        return (aix-a.x)*(aix-a.x)+(aiy-a.y)*(aiy-a.y) > (aix-b.x)*(aix-b.x)+(aiy-b.y)*(aiy-b.y) ;
    }
int go[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
char grond[101][101];
bool flag[101][101];
void output(int lll){
    if(lll==1) printf("dfs,just like a mouse in a hole\n");
    else if(lll== 2) printf("bfs,just like pouring water on the grond\n");
    else if (lll==3) printf("two-way bfs,just like pouring water on the grond in different position\n");
    else  printf("prioritybfs,the grond is deciling\n");
    grond[stx][sty]='s';
    grond[aix][aiy]='e';
    for(int i =0 ;i<n;i++){
        for(int j = 0 ;j<n;j++){
            cout<<grond[i][j];
        }
        cout<<endl;
    }
    cout<<"Made in china"<<endl;
}
void bfs(){		//简单广搜
    memset(flag,false,sizeof(flag));
    queue<node> q;
    q.push(node(stx,sty));
    flag[stx][sty]=true;
    while(!q.empty()){
        node tem = q.front();
        q.pop();
        if(grond[tem.x][tem.y]=='e')
            break;
        grond[tem.x][tem.y]='a';
        _sleep(5);
        system("cls");
        output(2);
        for(int i = 0 ;i<4;i++){
            int x = tem.x+go[i][0];
            int y = tem.y+go[i][1];
            if(x>=0 && x<n && y >=0 && y<n){
                if(!flag[x][y] && grond[x][y]!='*')
                {
                    q.push(node(x,y));
                    flag[x][y]=1;
                }
            }
        }
    }
    while(!q.empty())
        q.pop();
}
void prioritybfs(){//优先队列BFS
    memset(flag,false,sizeof(flag));
    priority_queue<node> q;
    q.push(node(stx,sty));
    flag[stx][sty]=true;
    while(!q.empty()){
        node tem = q.top();
        q.pop();
        if(grond[tem.x][tem.y]=='e')
            break;
        grond[tem.x][tem.y]='a';
        _sleep(5);
        system("cls");
        output(4);
        for(int i = 0 ;i<4;i++){
            int x = tem.x+go[i][0];
            int y = tem.y+go[i][1];
            if(x>=0 && x<n && y >=0 && y<n){
                if(!flag[x][y] && grond[x][y]!='*')
                {
                    q.push(node(x,y));
                    flag[x][y]=1;
                }
            }
        }
    }
    while(!q.empty())
        q.pop();
}
void twobfs(){//双向广搜
    memset(flag,false,sizeof(flag));
    queue<node> q1;
    queue<node> q2;
    q1.push(node(stx,sty));
    q2.push(node(aix,aiy));
    flag[stx][sty]=true;
    flag[aix][aiy]=true;
    while(!q1.empty() && !q2.empty()){
        node tem1 = q1.front();
        q1.pop();
        node tem2 = q2.front();
        q2.pop();
        if(grond[tem1.x][tem1.y]=='b')
            break;
        grond[tem1.x][tem1.y]='a';
        if(grond[tem2.x][tem2.y]=='a')
            break;
        grond[tem2.x][tem2.y]='b';
        _sleep(5);
        system("cls");
        output(3);
        for(int i = 0 ;i<4;i++){
            int x = tem1.x+go[i][0];
            int y = tem1.y+go[i][1];
            if(x>=0 && x<n && y >=0 && y<n){
                if(!flag[x][y] && grond[x][y]!='*')
                {
                    q1.push(node(x,y));
                    flag[x][y]=1;
                }
                else if(flag[x][y] && grond[x][y]=='b')//注意与另外一支汇合
                    q1.push(node(x,y));
            }
        }
        for(int i = 0 ;i<4;i++){
            int x = tem2.x+go[i][0];
            int y = tem2.y+go[i][1];
            if(x>=0 && x<n && y >=0 && y<n){
                if(!flag[x][y] && grond[x][y]!='*')
                {
                    q2.push(node(x,y));
                    flag[x][y]=1;
                }
                else if(flag[x][y] && grond[x][y]=='a') //注意与另外一支汇合
                    q1.push(node(x,y));
            }
        }
    }
    while(!q1.empty())
        q1.pop();
    while(!q2.empty())
        q2.pop();
}
int yes;
void showmessage(){
cout<<"I know there is input error,but donot believe that I will solve this problem for you"<<endl;
}
void dfs(int x,int y){	//普通深搜

    if(x==aix && y == aiy){
        yes =1;
        return;
    }
    grond[x][y]='a';
    _sleep(5);
    system("cls");
    output(1);
    for(int i = 0 ;i<4;i++){
        int a = x+go[i][0];
        int b = y+go[i][1];
        if(a>=0 && a<n && b >=0 && b<n){
            if(!flag[a][b] && grond[a][b]!='*')
            {
                flag[a][b]=1;
                dfs(a,b);
                if(yes)
                    return;
            }
        }
    }
}
void init(){
    grond[stx][sty]='b';
    grond[aix][aiy]='e';
    for(int i =0 ; i <n;i++)
        for(int j=0;j<n;j++)
        {
            grond[i][j]='.';
        }
    for(int i  = 0;i<n-3;i++)
        grond[n/2][i]='*';
}
int main(){
    printf("please input the size:(0<n<100)");
    cin>>n;
    printf("start point x,y:");
    cin>>stx>>sty;
    printf("end point x,y:");
    cin>>aix>>aiy;
    if(stx<0 || sty < 0 || sty>=n || stx >=n ){
        showmessage();
        _sleep(1000);
    }
    init();
    printf("now I will show you dfs,bfs,Two-waybfs and priority_bfs,press 'a' to continue;\n");
    char c;
    while(cin>>c){
        if(c!='a')
            break;
        init();
        yes = 0;
        memset(flag,0,sizeof(flag));
        dfs(stx,sty);
        _sleep(500);
        init();
        bfs();
        _sleep(500);
        init();
        prioritybfs();
        _sleep(500);
         init();
        twobfs();
        printf("press 'a' to once again,or any other char to exit\n");
    }
    return 0;
}
/*
输入数据
13 0 7 12 1
10 0 5 9 5
*/
