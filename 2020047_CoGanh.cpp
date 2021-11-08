#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;
int** init_board()
{
    int** t = new int*[5];
    for(int i = 0; i < 5; i++)
    {
        t[i] = new int[5];
        if(i == 0)
        {
            for(int j = 0; j < 5; j++)
                t[i][j] = 1;
        }
        if(i == 4)
        {
            for(int j = 0; j < 5; j++)
                t[i][j] = -1;
        }
    }
    t[1][0] = 1; t[1][4] = 1; t[2][0] = 1;
    t[2][4] = -1; t[3][0] = -1; t[3][4] = -1;

    return t;
}

int** copy_board(int** board)
{
    int** n_b = new int*[5];
    for(int i = 0; i < 5; i++)
    {
        n_b[i] = new int[5];
        for(int j = 0; j < 5; j++)
        {
            n_b[i][j] = board[i][j];
        }
    }
    return n_b;
}

void print_board(int** board)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(board[4-i][j] == 1)
                cout << "X ";
            else if(board[4-i][j] == -1)
                cout << "O ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

struct Position
{
    int x; int y;
    Position(){x = y = 0;}
    Position(int a, int b)
    {
        x = a; y = b;
    }
};

struct Move
{
    Position pos_start, pos_end;
    Move(Position s, Position e)
    {
        pos_start = s; pos_end = e;
    }
};
vector<Move>MoveCo;
bool ConditionMove(int** board,Move m)
{
    if((m.pos_start.x>=0 && m.pos_start.x<5)&&(m.pos_start.y>=0 && m.pos_start.y<5)&&(m.pos_end.x>=0 && m.pos_end.x<5)&&(m.pos_end.y>=0 && m.pos_end.y<5))
    {
        if(board[m.pos_end.x][m.pos_end.y]!=0)
        return false;
        if((m.pos_start.x-m.pos_end.x)>1||(m.pos_start.x-m.pos_end.x)<-1||(m.pos_start.y-m.pos_end.y)>1||(m.pos_start.y-m.pos_end.y)<-1)
        {
            return false;
        }
        if((m.pos_start.x%2==1)&&(m.pos_start.y%2==0))
        {
            if((m.pos_end.x%2==0)&&(m.pos_end.y%2==1))
            {
                return false;
            }
        }
        if((m.pos_start.x%2==0)&&(m.pos_start.y%2==1))
        {
            if((m.pos_end.x%2==1)&&(m.pos_end.y%2==0))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
bool ConditionPosition(int** board,Position m)
{

    Position n1(m.x+1,m.y);Move k1(m,n1);
    Position n2(m.x,m.y+1);Move k2(m,n2);
    Position n3(m.x-1,m.y);Move k3(m,n3);
    Position n4(m.x,m.y-1);Move k4(m,n4);
    Position n5(m.x+1,m.y+1);Move k5(m,n5);
    Position n6(m.x+1,m.y-1);Move k6(m,n6);
    Position n7(m.x-1,m.y+1);Move k7(m,n7);
    Position n8(m.x-1,m.y-1);Move k8(m,n8);
    if(ConditionMove(board,k1)||ConditionMove(board,k2)||ConditionMove(board,k3)||ConditionMove(board,k4)||
    ConditionMove(board,k5)||ConditionMove(board,k6)||ConditionMove(board,k7)||ConditionMove(board,k8))
    return true;
    return false;


}
vector<Position> addr_ganh(int**board,Position m,int player)
{
    vector<Position>re;
    Position kq;
    if(m.x+2<5)
    {
        if(board[m.x][m.y]==player && board[m.x+1][m.y]==0 && board[m.x+2][m.y]==player)
        {
            kq.x=m.x+1;
            kq.y=m.y;
            re.push_back(kq);
        }
    }
    if(m.x-2>=0)
    {
        if(board[m.x][m.y]==player && board[m.x-1][m.y]==0 && board[m.x-2][m.y]==player)
        {
            kq.x=m.x-1;
            kq.y=m.y;
            re.push_back(kq);
        }
    }
    if(m.y+2<5)
    {
        if(board[m.x][m.y]==player && board[m.x][m.y+1]==0 && board[m.x][m.y+2]==player)
        {
            kq.x=m.x;
            kq.y=m.y+1;
            re.push_back(kq);
        }
    }
    if(m.y-2>=0)
    {
        if(board[m.x][m.y]==player && board[m.x][m.y-1]==0 && board[m.x][m.y-2]==player)
        {
            kq.x=m.x;
            kq.y=m.y-1;
            re.push_back(kq);
        }
    }
    if(m.x+2<5 && m.y+2<5)
    {
        if(board[m.x][m.y]==player && board[m.x+1][m.y+1]==0 && board[m.x+2][m.y+2]==player)
        {
            kq.x=m.x+1;
            kq.y=m.y+1;
            re.push_back(kq);
        }
    }
    if(m.x+2<5 && m.y-2>=0)
    {
        if(board[m.x][m.y]==player && board[m.x+1][m.y-1]==0 && board[m.x+2][m.y-2]==player)
        {
            kq.x=m.x+1;
            kq.y=m.y-1;
            re.push_back(kq);
        }
    }
    if(m.x-2>=0 && m.y-2>=0)
    {
        if(board[m.x][m.y]==player && board[m.x-1][m.y-1]==0 && board[m.x-2][m.y-2]==player)
        {
            kq.x=m.x-1;
            kq.y=m.y-1;
            re.push_back(kq);
        }
    }
    if(m.x-2>=0 && m.y+2<5)
    {
        if(board[m.x][m.y]==player && board[m.x-1][m.y+1]==0 && board[m.x-2][m.y+2]==player)
        {
            kq.x=m.x-1;
            kq.y=m.y+1;
            re.push_back(kq);
        }
    }
    if (re.size()==0)
    {
        re.clear();
    }
    return re;
    
}

vector<Position> ganh(int** board, Move m, int player)
{
    vector<Position>vitri;
    if(m.pos_end.x-1>=0 && m.pos_end.x+1<5)
    {
    if((board[m.pos_end.x-1][m.pos_end.y]==-player)&&(board[m.pos_end.x+1][m.pos_end.y]==-player))
    {
        Position trc(m.pos_end.x-1,m.pos_end.y);
        Position sau(m.pos_end.x+1,m.pos_end.y);
        vitri.push_back(trc);
        vitri.push_back(sau);
    }}
    if(m.pos_end.y-1>=0 && m.pos_end.y+1<5)
    {
    if((board[m.pos_end.x][m.pos_end.y-1]==-player)&&(board[m.pos_end.x][m.pos_end.y+1]==-player))
    {
        Position tren(m.pos_end.x,m.pos_end.y-1);
        Position duoi(m.pos_end.x,m.pos_end.y+1);
        vitri.push_back(tren);
        vitri.push_back(duoi);

    }}
    if(m.pos_end.x-1 >=0 && m.pos_end.y-1>=0 && m.pos_end.x+1<5 && m.pos_end.y+1<5)
    {
    if((board[m.pos_end.x-1][m.pos_end.y-1]==-player)&&(board[m.pos_end.x+1][m.pos_end.y+1]==-player))
    {
        Position cheotren1(m.pos_end.x-1,m.pos_end.y-1);
        Position cheoduoi1(m.pos_end.x+1,m.pos_end.y+1);
        vitri.push_back(cheotren1);
        vitri.push_back(cheoduoi1);
 
    }}
    if(m.pos_end.x+1 <5 && m.pos_end.y-1>=0 && m.pos_end.x-1>=0 && m.pos_end.y+1<5)
    {
    if((board[m.pos_end.x+1][m.pos_end.y-1]==-player)&&(board[m.pos_end.x-1][m.pos_end.y+1]==-player))
    {
        Position cheotren2(m.pos_end.x+1,m.pos_end.y-1);
        Position cheoduoi2(m.pos_end.x-1,m.pos_end.y+1);
        vitri.push_back(cheotren2);
        vitri.push_back(cheoduoi2);

    }}
    return vitri;
}

vector<Position>vay(int** board, Move m, int player)
{
    vector<Position>A;
    vector<Position>B;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(board[i][j]==-player)
            {
                Position a(i,j);
                if(ConditionPosition(board,a)==false)
                {
                    A.push_back(a);
                }
            }
        }
    }
    
    B.push_back(m.pos_end);

    for(int i=0;i<(int)B.size();i++)
    {
        for(int j=0;j<(int)A.size();j++)
        {
            if(B[i].x+1<5)
            {
                Position a(B[i].x+1,B[i].y);
                if(a.x==A[j].x && a.y==A[j].y)
                {
                    B.push_back(a);
                    A.erase(A.begin()+j);
                    i=0;
                    j=0;
                    break;
                }
            }
            if(B[i].x-1>=0)
            {
                Position a(B[i].x-1,B[i].y);
                if(a.x==A[j].x && a.y==A[j].y)
                {
                    B.push_back(a);
                    A.erase(A.begin()+j);
                    i=0;
                    j=0;
                    break;
                }
            }
            if(B[i].y+1<5)
            {
                Position a(B[i].x,B[i].y+1);
                if(a.x==A[j].x && a.y==A[j].y)
                {
                    B.push_back(a);
                    A.erase(A.begin()+j);
                    i=0;
                    j=0;
                    break;
                }
            }
            if(B[i].y-1>=0)
            {
                Position a(B[i].x,B[i].y-1);
                if(a.x==A[j].x && a.y==A[j].y)
                {
                    B.push_back(a);
                    A.erase(A.begin()+j);
                    i=0;
                    j=0;
                    break;
                }
            }
            if(B[i].x+1<5 && B[i].y+1<5)
            {
                Position a(B[i].x+1,B[i].y+1);
                if(a.x==A[j].x && a.y==A[j].y)
                {
                    B.push_back(a);
                    A.erase(A.begin()+j);
                    i=0;
                    j=0;
                    break;
                }
            }
            if(B[i].x+1<5 && B[i].y-1>=0)
            {
                Position a(B[i].x+1,B[i].y-1);
                if(a.x==A[j].x && a.y==A[j].y)
                {
                    B.push_back(a);
                    A.erase(A.begin()+j);
                    i=0;
                    j=0;
                    break;
                }
            }
            if(B[i].x-1>=0 && B[i].y+1<5)
            {
                Position a(B[i].x-1,B[i].y+1);
                if(a.x==A[j].x && a.y==A[j].y)
                {
                    B.push_back(a);
                    A.erase(A.begin()+j);
                    i=0;
                    j=0;
                    break;
                }
            }
            if(B[i].x-1>=0 && B[i].y-1>=0)
            {
                Position a(B[i].x-1,B[i].y-1);
                if(a.x==A[j].x && a.y==A[j].y)
                {
                    B.push_back(a);
                    A.erase(A.begin()+j);
                    i=0;
                    j=0;
                    break;
                }
            }
        }
    }
    B.erase(B.begin()+0);
    for(int i=0;i<(int)B.size();i++)
    {
        if(B[i].x+1<5)
        {
            if(board[B[i].x+1][B[i].y]==-player)
            {
                Position a(B[i].x+1,B[i].y);
                if(ConditionPosition(board,a))
                {
                    board[a.x][a.y]=0;
                    Move move(B[i],a);
                    if(ConditionMove(board,move))
                    {
                        B.clear();
                        board[a.x][a.y]=-player;
                        break;
                    }
                    board[a.x][a.y]=-player;
                }
            }
        }
        if(B[i].x-1>=0)
        {
            if(board[B[i].x-1][B[i].y]==-player)
            {
                Position a(B[i].x-1,B[i].y);
                if(ConditionPosition(board,a))
                {
                    board[a.x][a.y]=0;
                    Move move(B[i],a);
                    if(ConditionMove(board,move))
                    {
                        B.clear();
                        board[a.x][a.y]=-player;
                        break;
                    }
                    board[a.x][a.y]=-player;
                }
            }
        }
        if(B[i].y-1>=0)
        {
            if(board[B[i].x][B[i].y-1]==-player)
            {
                Position a(B[i].x,B[i].y-1);
                if(ConditionPosition(board,a))
                {
                    board[a.x][a.y]=0;
                    Move move(B[i],a);
                    if(ConditionMove(board,move))
                    {
                        B.clear();
                        board[a.x][a.y]=-player;
                        break;
                    }
                    board[a.x][a.y]=-player;
                }
            }
        }
        if(B[i].y+1<5)
        {
            if(board[B[i].x][B[i].y+1]==-player)
            {
                Position a(B[i].x,B[i].y+1);
                if(ConditionPosition(board,a))
                {
                    board[a.x][a.y]=0;
                    Move move(B[i],a);
                    if(ConditionMove(board,move))
                    {
                        B.clear();
                        board[a.x][a.y]=-player;
                        break;
                    }
                    board[a.x][a.y]=-player;
                }
            }
        }
        if(B[i].x+1<5 && B[i].y+1<5)
        {
            if(board[B[i].x+1][B[i].y+1]==-player)
            {
                Position a(B[i].x+1,B[i].y+1);
                if(ConditionPosition(board,a))
                {
                    board[a.x][a.y]=0;
                    Move move(B[i],a);
                    if(ConditionMove(board,move))
                    {
                        B.clear();
                        board[a.x][a.y]=-player;
                        break;
                    }
                    board[a.x][a.y]=-player;
                }
            }
        }
        if(B[i].x+1<5 && B[i].y-1>=0)
        {
            if(board[B[i].x+1][B[i].y-1]==-player)
            {
                Position a(B[i].x+1,B[i].y-1);
                if(ConditionPosition(board,a))
                {
                    board[a.x][a.y]=0;
                    Move move(B[i],a);
                    if(ConditionMove(board,move))
                    {
                        B.clear();
                        board[a.x][a.y]=-player;
                        break;
                    }
                    board[a.x][a.y]=-player;
                }
            }
        }
        if(B[i].x-1>=0 && B[i].y-1>=0)
        {
            if(board[B[i].x-1][B[i].y-1]==-player)
            {
                Position a(B[i].x-1,B[i].y-1);
                if(ConditionPosition(board,a))
                {
                    board[a.x][a.y]=0;
                    Move move(B[i],a);
                    if(ConditionMove(board,move))
                    {
                        B.clear();
                        board[a.x][a.y]=-player;
                        break;
                    }
                    board[a.x][a.y]=-player;
                }
            }
        }
        if(B[i].x-1>=0 && B[i].y+1<5)
        {
            if(board[B[i].x-1][B[i].y+1]==-player)
            {
                Position a(B[i].x-1,B[i].y+1);
                if(ConditionPosition(board,a))
                {
                    board[a.x][a.y]=0;
                    Move move(B[i],a);
                    if(ConditionMove(board,move))
                    {
                        B.clear();
                        board[a.x][a.y]=-player;
                        break;
                    }
                    board[a.x][a.y]=-player;
                }
            }
        }
    }
    return B;

}

vector<Move> bay_or_mo(int** current_board, int** previous_board, int player)
{
    vector<Move>kq;
    int PrePlayer=0,CurPlayer=0;
    Position newP;
    for(int i=0;i<5;i++)
    {
        for (int j=0;j<5;j++)
        {
            if(previous_board[i][j]==-player)
            {
                PrePlayer++;
            }
            if(current_board[i][j]==-player)
            {
                CurPlayer++;
            }
            if(previous_board[i][j]==0 && current_board[i][j]==-player)
            {
                newP.x=i;
                newP.y=j;
            }

        }
    }
    if(PrePlayer==CurPlayer)
    {
        
        vector<Position> sau=addr_ganh(current_board,newP,-player);
        if (sau.size()==0)
        {
            kq.clear();
            return kq;
        }
        for(int i=0;i<5;i++)
        {
            
            for (int j=0;j<5;j++)
            {
                if(current_board[i][j]==player)
                {
                    Position trc(i,j);
                    for(int k=0;k<sau.size();k++)
                    {
                    Move pos(trc,sau[k]);
                    
                    
                    if(ConditionMove(current_board,pos))
                    {
                        kq.push_back(pos);
                    }
                    }

                }
            }
        }

    }

    return kq;
}

vector<Move> get_valid_moves(int** current_board, int** previous_board, int player)
{
    vector<Move>kq;
    if(bay_or_mo(current_board,previous_board,player).size()>=1)
    {
        
        kq=bay_or_mo(current_board,previous_board,player);

    }
    else
    {
    for (int i=0;i<5;i++)
        {
        for (int j=0;j<5;j++)
        {
            if(current_board[i][j]==player)
            {
                
                Position trc(i,j);
                if(i+1<5 && ConditionPosition(current_board,trc))
                {
                    Position sau(i+1,j);
                    Move k (trc,sau);
                    if(ConditionMove(current_board,k))
                    {
                        kq.push_back(k);
                    }

                }
                if(i-1>=0 && ConditionPosition(current_board,trc))
                {
                    Position sau(i-1,j);
                    Move k (trc,sau);
                    if(ConditionMove(current_board,k))
                    {
                        kq.push_back(k);
                    }

                }
                if(j+1<5 && ConditionPosition(current_board,trc))
                {
                    Position sau(i,j+1);
                    Move k (trc,sau);
                    if(ConditionMove(current_board,k))
                    {
                        kq.push_back(k);
                    }

                }
                if(j-1>=0 && ConditionPosition(current_board,trc))
                {
                    Position sau(i,j-1);
                    Move k (trc,sau);
                    if(ConditionMove(current_board,k))
                    {
                        kq.push_back(k);
                    }

                }
                if(i+1<5 && j+1<5 && ConditionPosition(current_board,trc))
                {
                    Position sau(i+1,j+1);
                    Move k (trc,sau);
                    if(ConditionMove(current_board,k))
                    {
                        kq.push_back(k);
                    }

                }
                if(i+1<5 && j-1>=0 && ConditionPosition(current_board,trc))
                {
                    Position sau(i+1,j-1);
                    Move k (trc,sau);
                    if(ConditionMove(current_board,k))
                    {
                        kq.push_back(k);
                    }

                }
                if(i-1>=0 && j+1<5 && ConditionPosition(current_board,trc))
                {
                    Position sau(i-1,j+1);
                    Move k (trc,sau);
                    if(ConditionMove(current_board,k))
                    {
                        kq.push_back(k);
                    }

                }
                if(i-1>=0 && j-1>=0 && ConditionPosition(current_board,trc))
                {
                    Position sau(i-1,j-1);
                    Move k (trc,sau);
                    if(ConditionMove(current_board,k))
                    {
                        kq.push_back(k);
                    }

                }
            }
        }
    }
    }
    return kq;
}
void act_move(int** current_board, Move m, int player)
{

current_board[m.pos_start.x][m.pos_start.y]=0;
current_board[m.pos_end.x][m.pos_end.y]=player;
if(ganh(current_board,m,player).size()>0)
{
    int k=ganh(current_board,m,player).size();
    vector<Position>a=ganh(current_board,m,player);
    for(int i=0;i<(int)k;i++ )
    {
        current_board[a[i].x][a[i].y]=player;
    }
}
if(vay(current_board,m,player).size()>0)
{
    int k=vay(current_board,m,player).size();
    vector<Position>a=vay(current_board,m,player);
    for(int i=0;i<(int)k;i++ )
    {
        current_board[a[i].x][a[i].y]=player;
    }
}

}
int Diem(int**board)
{
    int kq=0;
    int X=0;
    int Y=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(board[i][j]==1)
            X=X+1;
            if(board[i][j]==0)
            Y=Y+1;
        }
    }
    kq=X-Y;
    return kq;
}
Move Player(int**current_board,int**previous,int player)
{
    int vitri=0;
vector<Move>valid_move=get_valid_moves(current_board,previous,player);
if(player==1)
{   int diem5=20;
    int diem3=20;
    int diem1=20;
    int diem4=-20;
    int diem2=-20;
    int diem=-20;

for(int i=0;i<valid_move.size();i++)
{
    int** cop_pre=copy_board(current_board);
    int** cop_cur=copy_board(current_board);
    act_move(cop_cur,valid_move[i],player);
    vector<Move>valid_move1=get_valid_moves(cop_cur,cop_pre,-player);
    for(int j=0;j<valid_move1.size();j++)
    {
        int** cop_pre1=copy_board(cop_cur);
        int** cop_cur1=copy_board(cop_cur);
        act_move(cop_cur1,valid_move1[j],-player);
        vector<Move>valid_move2=get_valid_moves(cop_cur1,cop_pre1,player);
        for(int m=0;m<valid_move2.size();m++)
        {
            int**cop_pre2=copy_board(cop_cur1);
            int**cop_cur2=copy_board(cop_cur1);
            act_move(cop_cur2,valid_move2[m],player);
            vector<Move>valid_move3=get_valid_moves(cop_cur2,cop_pre2,-player);
            for(int n=0;n<valid_move3.size();n++)
            {
                int**cop_pre3=copy_board(cop_cur2);
                int**cop_cur3=copy_board(cop_cur2);
                act_move(cop_cur3,valid_move3[n],-player);
                vector<Move>valid_move4=get_valid_moves(cop_cur3,cop_pre3,player);
                for(int a=0;a<valid_move4.size();a++)
                {
                    int**cop_pre4=copy_board(cop_cur3);
                    int**cop_cur4=copy_board(cop_cur3);
                    act_move(cop_cur4,valid_move4[a],player);
                    
                    if(diem4<=Diem(cop_cur4))
                    {
                        diem4=Diem(cop_cur4);
                    }

                }
                if(diem3>=diem4)
                {
                    diem3=diem4;
                }

            }
            if(diem2<=diem3)
            {
                diem2=diem3;
            }
        }
        if(diem1>=diem2)
        {
            diem1=diem2;
        }
    }
    if(diem<=diem1)
    {
        diem=diem1;
        vitri=i;
    }
}
}
else
{
    int diem5=-20;
    int diem3=-20;
    int diem1=-20;
    int diem4=20;
    int diem2=20;
    int diem=20;

    for(int i=0;i<valid_move.size();i++)
{
    int** cop_pre=copy_board(current_board);
    int** cop_cur=copy_board(current_board);
    act_move(cop_cur,valid_move[i],player);
    vector<Move>valid_move1=get_valid_moves(cop_cur,cop_pre,-player);
    for(int j=0;j<valid_move1.size();j++)
    {
        int** cop_pre1=copy_board(cop_cur);
        int** cop_cur1=copy_board(cop_cur);
        act_move(cop_cur1,valid_move1[j],-player);
        vector<Move>valid_move2=get_valid_moves(cop_cur1,cop_pre1,player);
        for(int m=0;m<valid_move2.size();m++)
        {
            int**cop_pre2=copy_board(cop_cur1);
            int**cop_cur2=copy_board(cop_cur1);
            act_move(cop_cur2,valid_move2[m],player);
            vector<Move>valid_move3=get_valid_moves(cop_cur2,cop_pre2,-player);
            for(int n=0;n<valid_move3.size();n++)
            {
                int**cop_pre3=copy_board(cop_cur2);
                int**cop_cur3=copy_board(cop_cur2);
                act_move(cop_cur3,valid_move3[n],-player);
                vector<Move>valid_move4=get_valid_moves(cop_cur3,cop_pre3,player);
                for(int a=0;a<valid_move4.size();a++)
                {
                    int**cop_pre4=copy_board(cop_cur3);
                    int**cop_cur4=copy_board(cop_cur3);
                    act_move(cop_cur4,valid_move4[a],player);
                    
                    if(diem4>=Diem(cop_cur4))
                    {
                        diem4=diem5;
                    }

                }
                if(diem3<=diem4)
                {
                    diem3=diem4;
                }

            }
            if(diem2>=diem3)
            {
                diem2=diem3;
            }
        }
        if(diem1<=diem2)
        {
            diem1=diem2;
        }
    }
    if(diem>=diem1)
    {
        diem=diem1;
        vitri=i;
    }
}
}
return valid_move[vitri];
}
Move select_move(int** current_board, int** previous_board, int player)
{
vector<Move>valid_move=get_valid_moves(current_board,previous_board,player);
int max=0;
int nuoc_an=0;
int stt=0;
for(int i=0;i<valid_move.size();i++)
{
    int**cop_current=copy_board(current_board);
    cop_current[valid_move[i].pos_start.x][valid_move[i].pos_start.y]=0;
    cop_current[valid_move[i].pos_end.x][valid_move[i].pos_end.y]=player;
    nuoc_an=ganh(cop_current,valid_move[i],player).size()+vay(cop_current,valid_move[i],player).size();
    if(max<nuoc_an)
    {
        max=nuoc_an;
        stt=i;
    }
}
if(max==0)
{srand(time(NULL));
    int ran=rand()%valid_move.size();
return valid_move[ran];}
return valid_move[stt];
//return Player(current_board,previous_board,player);
}






void play(int first)
{
    int count = 0, limit = 70;
    int player;
    if(first == 1)
        player = 1;
    else
        player = -1;

    int** board = init_board();
    int** pre_board = init_board();
    print_board(board);
    while(count < limit)
    {
        if(player==1)
        cout<<"Luot di của X"<<endl;
        else cout<<"Luot di của O"<<endl;
        
        vector<Move> valid_moves = get_valid_moves(board, pre_board, player);
        if(valid_moves.size()>0)
        {
        // if(bay_or_mo(board,pre_board,player).size()>0)
        // {
        //     for(int i=0;i<valid_moves.size();i++)
        //     {
        //         cout<<valid_moves[i].pos_start.x<<" "<<valid_moves[i].pos_start.y<<" "<<valid_moves[i].pos_end.x<<" "<<valid_moves[i].pos_end.y<<endl;
        //     }
        // }
        pre_board = copy_board(board);
        cout<<endl;
        if(player==1)
        {
            Move new_move=select_move(board,pre_board,player);
            cout<<"Nuoc di mà bạn muốn"<<endl;
            cout<<new_move.pos_start.x<<" "<<new_move.pos_start.y<<" "<<new_move.pos_end.x<<" "<<new_move.pos_end.y<<endl;
            cout<<"Before"<<endl;
            print_board(pre_board);
            act_move(board, new_move, player);

        }
        else 
        {
           srand(time(NULL)); 
            Move new_move=valid_moves[rand()%valid_moves.size()];
        cout<<"Nuoc di mà bạn muốn"<<endl;
        cout<<new_move.pos_start.x<<" "<<new_move.pos_start.y<<" "<<new_move.pos_end.x<<" "<<new_move.pos_end.y<<endl;
        cout<<"Before"<<endl;
        print_board(pre_board);
        act_move(board, new_move, player);
        }
        
        }
        else
        break;
        
        player *= -1;
        count++;
    }
    int X=0;
    int O=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(board[i][j]==1)
            {
                X=X+1;
            }
            if(board[i][j]==-1)
            {
                O=O+1;
            }
        }
    }
    if(X>O)
    {
        cout<<"X win";
    }else if(O>X)
    {
        cout<<"O Win";
    }else cout<<"due";
 }

int main()
{
    play(1);



    return 0;
}