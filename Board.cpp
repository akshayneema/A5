#include "Board.h"

Board::Board ( )
{
    this->size = 0;
    this->myringout = 0;
    this->oppringout = 0;
    this->eval=0;
}

Board::Board (int size)
{
    this->myringout = 0;
    this->oppringout = 0;
    this->eval=0;
    this->size = size;
    initialize(size);
}

void Board::initialize(int size)
{
    int r = 2*size+1;
    int c = 2*size+1; 
    this->b = (int **)malloc(r * sizeof(int *)); 
    for (int i=0; i<r; i++) 
         b[i] = (int *)malloc(c * sizeof(int)); 
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            b[i][j]=0;
        }
    }
    for(int i=0;i<size;i++){
        for(int j=size+1+i;j<2*size+1;j++){
            b[i][j]=3;
        }
    }
    for(int i=size+1;i<2*size+1;i++){
        for(int j=0;j<i-size;j++){
            b[i][j]=3;
        }
    }
    b[0][0]=3;
    b[size][2*size]=3;
    b[0][size]=3;
    b[size][0]=3;
    b[2*size][size]=3;
    b[2*size][2*size]=3;
}

Board* Board::copyBoard()
{
    Board* newb = new Board(size);
    newb->size = this->size;
    newb->eval= this->eval;
    newb->oppringout=this->oppringout;
    newb->myringout=this->myringout;
    for(int i=0;i<this->oppringpos.size();i++)
    {
        newb->oppringpos.push_back(this->oppringpos[i]);
    }
    for(int i=0;i<this->myringpos.size();i++)
    {
        newb->myringpos.push_back(this->myringpos[i]);
    }
    int r = 2*size+1;
    int c = 2*size+1; 
    newb->b = (int **)malloc(r * sizeof(int *)); 
    for (int i=0; i<r; i++) 
         newb->b[i] = (int *)malloc(c * sizeof(int));
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            newb->b[i][j]=this->b[i][j];
        }
    }
    return newb;
}

Board* Board::flipBoard()
{
    Board* newb = new Board(size);
    newb->size = this->size;
    newb->eval= this->eval;
    newb->myringout=this->oppringout;
    newb->oppringout=this->myringout;
    for(int i=0;i<this->oppringpos.size();i++)
    {
        newb->myringpos.push_back(this->oppringpos[i]);
    }
    for(int i=0;i<this->myringpos.size();i++)
    {
        newb->oppringpos.push_back(this->myringpos[i]);
    }
    int r = 2*size+1;
    int c = 2*size+1; 
    newb->b = (int **)malloc(r * sizeof(int *)); 
    for (int i=0; i<r; i++) 
         newb->b[i] = (int *)malloc(c * sizeof(int));
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            if(this->b[i][j]!=3)
            {
                if(this->b[i][j]!=0)
                    newb->b[i][j]=-1*this->b[i][j];
                else
                    newb->b[i][j]=0;
            }
            else
                newb->b[i][j]=3;
        }
    }
    return newb;
}

void Board::setMyRing(int x,int y)
{
    b[x][y]=1;
}

void Board::setMyMarker(int x,int y)
{
    b[x][y]=2;
}

void Board::setOppRing(int x,int y)
{
    b[x][y]=-1;
}

void Board::setOppMarker(int x,int y)
{
    b[x][y]=-2;
}

int Board::remove(int x,int y)
{
    int ans=b[x][y];
    b[x][y]=0;
    return ans;
}

int Board::getValue(int x, int y)
{
    return b[x][y];
}

double Board::getEval()
{
    return this->eval;
}

void Board::setEval(double eval)
{
    this->eval=eval;
}

// void Board::printBoard(){
//     vector<vector<char> > matrix(2*size-1);
//     for(int i=0;i<2*size-1;i++){
//         matrix[i].resize(2*size+1, ' ');
//     }


//     cerr<<"  ";
//     // for(int i=0;i<2*size+1;i++){
//     //     cerr<<i<<" ";
//     // }
//     cerr<<"\n";

//     for(int x=0;x<4*size+1;x++)
//     {
//     // cerr<<i<<" ";
//         for(int y=0;y<2*size+1;y++)
//         {
//             char a=' ';
//             switch(b[x][y])
//             {
//                 case 3:
//                 a=' ';
//                 break;
//                 case 2:
//                 a='o';
//                 break;
//                 case 1:
//                 a='0';
//                 break;
//                 case 0:
//                 a='.';
//                 break;
//                 case -1:
//                 a='#';
//                 break;
//                 case -2:
//                 a='x';
//                 break;
//             }
//             // cerr<<x<<y<<endl;
//             if(a == ' '){
//                 // cerr<<'n';
//                 // matrix[y-2*x+14][y] = a;
//             }
//             else
//             {
//                 matrix[y-2*x+3*size-1][y] = a;
                
//                 // cerr<<a;
//             }
//         }
        
//         // cerr<<"init done";
//     }
//     for(int i=0;i<4*size-1;i++){
//             for(int j=0;j<2*size+1;j++){
//                 cerr<<matrix[i][j]<<"  ";
//             }
//             cerr<<endl;
//         }
// }


void Board::printBoard(){
    
    vector<vector<char> > matrix(4*size-1);
    for(int i=0;i<4*size-1;i++){
        matrix[i].resize(2*size+1, ' ');
    }

    cerr<<"  ";
    // for(int i=0;i<2*size+1;i++){
    //     cerr<<i<<" ";
    // }
    cerr<<"\n";
    for(int x=0;x<2*size+1;x++)
    {
    // cerr<<i<<" ";
        for(int y=0;y<2*size+1;y++)
        {
            char a=' ';
            switch(b[x][y])
            {
                case 3:
                a=' ';
                break;
                case 2:
                a='o';
                break;
                case 1:
                a='0';
                break;
                case 0:
                a='.';
                break;
                case -1:
                a='#';
                break;
                case -2:
                a='x';
                break;
            }
            // cerr<<x<<y<<endl;
            if(a == ' '){
                // cerr<<'n';
                // matrix[y-2*x+14][y] = a;
            }
            else
            {
                // cerr<<size;
                if(size==5)
                    matrix[y-2*x+14][y] = a;
                else
                    matrix[y-2*x+17][y] = a;
                
                // cerr<<a;
            }
        }        
        // cerr<<"init done";
    }
    for(int i=0;i<4*size-1;i++){
        for(int j=0;j<2*size+1;j++){
            cerr<<matrix[i][j]<<"  ";
        }
        cerr<<endl;
    }

}
