 /* 
 * File:   GamePlay.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "GamePlay.h"


GamePlay::GamePlay ( )
{
    MAX_DEPTH = 5;
    size=0;
    processingTimeInMinutes=0;
}

GamePlay::GamePlay (int size, int contmarker)
{
    this->size=size;
    this->startring=size;
    this->contmarker = contmarker;
    this->curboard = new Board (size);
}

pair<int, int> GamePlay::coordinatebackConversion(int x, int y){
    int sign = (x-size)*(y-size);
    int h,p;
    if(sign>=0){
        h = max(abs(x-size), abs(y-size));
    }
    else {
        h = abs(x-size) + abs(y-size);
    }
    if(x-size==h)
    {
        p=y-size;
    } 
    else if(y-size==h)
        p=2*(y-size)-(x-size);
    else if(x-size==-h)
        p=3*abs(x-size)+abs(y-size);
    else if(y-size==-h)
        p=5*abs(y-size)-abs(x-size);
    else if(x-size<0)
        p=3*h-(y-size);
    else if(y-size<0)
        p=5*h+(x-size);
    return make_pair(h, p);
}
pair<int,int> GamePlay::coordinateConversion(int h, int p)
{
    int x=h;
    int y=0;
    int i=0;
    while(i<p)
    {
        if(i/h==0)
        {
            y++;
            i++;
        }
        else if(i/h==1)
        {
            x--;
            i++;
        }
        else if(i/h==2)
        {
            x--;
            y--;
            i++;
        }
        else if(i/h==3)
        {
            y--;
            i++;
        }
        else if(i/h==4)
        {
            x++;
            i++;
        }
        else if(i/h==5)
        {
            x++;
            y++;
            i++;
        }


    }
    return make_pair(x,y);
}



vector<string> GamePlay::moveVector(string move)
{
    vector<string> v(0);
    for(int i=0;i<move.length();i++)
    {
        string s="";
        while(move[i]!=' ' && i<move.length())
        {
            s=s+move[i];
            i++;
        }
        v.push_back(s);
    }
    return v;
}

void GamePlay::oppMove (Board* board, vector<string> v)
{
    //changes board configuration according to opponent's moveS
    // cerr<<"----------Entered Opp Move"<<endl;
    if(v.size()==0)
    {
        // cerr<<"--------Returning frm opp move"<<endl;
        return;
    }
    else
    {
        if(v[0]=="P")
        {
            // cerr<<"---------------Placing ring"<<endl;
            int h=stoi(v[1]);
            int p=stoi(v[2]);
            pair<int,int> c= coordinateConversion(h,p);
            int x=c.first;
            int y=c.second;
            board->b[x+size][y+size]=-1;
            vector<string> newv;
            for(int i=3;i<v.size();i++)
            {
                newv.push_back(v[i]);
            }
            board->oppringpos.push_back(make_pair(x+size,y+size));
            oppMove(board, newv);
        }
        else if(v[0]=="S")
        {
            // cerr<<"----------------------selecting and moveing"<<endl;
            int h1=stoi(v[1]);
            int p1=stoi(v[2]);
            pair<int,int> c1= coordinateConversion(h1,p1);
            int x1=c1.first;
            int y1=c1.second;
            int h2=stoi(v[4]);
            int p2=stoi(v[5]);
            pair<int,int> c2= coordinateConversion(h2,p2);
            int x2=c2.first;
            int y2=c2.second;
            if(x1==x2)//slope=0
            {
                if(y2>y1)
                {
                    for(int i=y1+1;i<y2;i++)
                    {
                        if(board->b[x1+size][i+size]==-2)
                            board->b[x1+size][i+size]=2;
                        else if(board->b[x1+size][i+size]==2)
                            board->b[x1+size][i+size]=-2;
                    }
                }
                else if(y1>y2)
                {
                    for(int i=y2+1;i<y1;i++)
                    {
                        if(board->b[x1+size][i+size]==-2)
                            board->b[x1+size][i+size]=2;
                        else if(board->b[x1+size][i+size]==2)
                            board->b[x1+size][i+size]=-2;
                    }
                }
            }
            else if(y1==y2)//slope=infi
            {
                if(x2>x1)
                {
                    for(int i=x1+1;i<x2;i++)
                    {
                        if(board->b[i+size][y1+size]==-2)
                            board->b[i+size][y1+size]=2;
                        else if(board->b[i+size][y1+size]==2)
                            board->b[i+size][y1+size]=-2;
                    }
                }
                else if(x1>x2)
                {
                    for(int i=x2+1;i<x1;i++)
                    {
                        if(board->b[i+size][y1+size]==-2)
                            board->b[i+size][y1+size]=2;
                        else if(board->b[i+size][y1+size]==2)
                            board->b[i+size][y1+size]=-2;
                    }
                }
            }
            else if(x2-x1==y2-y1 || x2-x1==-y2+y1)//slope=+-1
            {
                if(x2>x1 && y2>y1)
                {
                    for(int i=1;i<x2-x1;i++)
                    {
                        if(board->b[x1+i+size][y1+i+size]==-2)
                            board->b[x1+i+size][y1+i+size]=2;
                        else if(board->b[x1+i+size][y1+i+size]==2)
                            board->b[x1+i+size][y1+i+size]=-2;
                    }
                }
                else if(x2>x1 && y1>y2)
                {
                    for(int i=1;i<x2-x1;i++)
                    {
                        if(board->b[x1+i+size][y1-i+size]==-2)
                            board->b[x1+i+size][y1-i+size]=2;
                        else if(board->b[x1+i+size][y1-i+size]==2)
                            board->b[x1+i+size][y1-i+size]=-2;
                    }
                }
                else if(x1>x2 && y2>y1)
                {
                    for(int i=1;i<x1-x2;i++)
                    {
                        if(board->b[x1-i+size][y1+i+size]==-2)
                            board->b[x1-i+size][y1+i+size]=2;
                        else if(board->b[x1-i+size][y1+i+size]==2)
                            board->b[x1-i+size][y1+i+size]=-2;
                    }
                }
                else if(x1>x2 && y1>y2)
                {
                    for(int i=1;i<x1-x2;i++)
                    {
                        if(board->b[x1-i+size][y1-i+size]==-2)
                            {
                            board->b[x1-i+size][y1-i+size]=2;}
                        else if(board->b[x1-i+size][y1-i+size]==2)
                            board->b[x1-i+size][y1-i+size]=-2;
                    }
                }
            }
            board->b[x1+size][y1+size]=-2;
            board->b[x2+size][y2+size]=-1;
            vector<string> newv;
            for(int i=6;i<v.size();i++)
            {
                newv.push_back(v[i]);
            }
            for(int i=0;i<board->oppringpos.size();i++)
            {
                if(x1+size==board->oppringpos[i].first && y1+size==board->oppringpos[i].second)
                {
                    board->oppringpos.erase(board->oppringpos.begin()+i);
                    board->oppringpos.push_back(make_pair(x2+size,y2+size));
                    break;
                }
            }
            oppMove(board, newv);
        }
        else if(v[0]=="RS")//remove krenge 
        {
            // cerr<<"----------------------removing"<<endl;
            int h1=stoi(v[1]);
            int p1=stoi(v[2]);
            pair<int,int> c1= coordinateConversion(h1,p1);
            int x1=c1.first;
            int y1=c1.second;
            int h2=stoi(v[4]);
            int p2=stoi(v[5]);
            pair<int,int> c2= coordinateConversion(h2,p2);
            int x2=c2.first;
            int y2=c2.second;
            if(x1==x2)//slope=0
            {
                if(y2>y1)
                {
                    for(int i=y1;i<=y2;i++)
                    {
                        board->b[x1+size][i+size]=0;
                    }
                }
                else if(y1>y2)
                {
                    for(int i=y2;i<=y1;i++)
                    {
                        board->b[x1+size][i+size]=0;
                    }
                }
            }
            else if(y1==y2)//slope=infi
            {
                if(x2>x1)
                {
                    for(int i=x1;i<=x2;i++)
                    {
                        board->b[i+size][y1+size]=0;
                    }
                }
                else if(x1>x2)
                {
                    for(int i=x2;i<=x1;i++)
                    {
                        board->b[i+size][y1+size]=0;
                    }
                }
            }
            else if(x2-x1==y2-y1 || x2-x1==-y2+y1)//slope=+-1
            {
                if(x2>x1 && y2>y1)
                {
                    for(int i=0;i<=x2-x1;i++)
                    {
                        board->b[x1+i+size][y1+i+size]=0;
                    }
                }
                else if(x2>x1 && y1>y2)
                {
                    for(int i=1;i<x2-x1;i++)
                    {
                        board->b[x1+i+size][y1-i+size]=0;
                    }
                }
                else if(x1>x2 && y2>y1)
                {
                    for(int i=1;i<x1-x2;i++)
                    {
                        board->b[x1-i+size][y1+i+size]=0;
                    }
                }
                else if(x1>x2 && y1>y2)
                {
                    for(int i=1;i<x1-x2;i++)
                    {
                        board->b[x1-i+size][y1-i+size]=0;
                    }
                }
            }
            int h3=stoi(v[7]);
            int p3=stoi(v[8]);
            pair<int,int> c3= coordinateConversion(h3,p3);
            int x3=c3.first;
            int y3=c3.second;
            board->b[x3+size][y3+size]=0;
            board->oppringout=board->oppringout+1;
            vector<string> newv;
            for(int i=9;i<v.size();i++)
            {
                newv.push_back(v[i]);
            }
            for(int i=0;i<board->oppringpos.size();i++)
            {
                if(x3+size==board->oppringpos[i].first && y3+size==board->oppringpos[i].second)
                {
                    board->oppringpos.erase(board->oppringpos.begin()+i);
                    break;
                }
            }
            oppMove(board, newv);
        } 
    }
}
void GamePlay::myMove (Board* board, vector<string> v)
{
    //changes board configuration according to opponent's moveS
    // cerr<<"----------Entered My Move"<<endl;
    if(v.size()==0)
    {
        // cerr<<"--------Returning frm my move"<<endl;
        return;
    }
    else
    {
        if(v[0]=="P")
        {
            // cerr<<"---------------Placing ring"<<endl;
            int a = 3*234+13;
            // cerr<<"place hua"<<"\n";
            int h=stoi(v[1]);
            int p=stoi(v[2]);
            pair<int,int> c= coordinateConversion(h,p);
            int x=c.first;
            int y=c.second;
            board->b[x+size][y+size]=1;
            vector<string> newv;
            for(int i=3;i<v.size();i++)
            {
                newv.push_back(v[i]);
            }
            board->myringpos.push_back(make_pair(x+size,y+size));
            myMove(board, newv);
        }
        else if(v[0]=="S")
        {
            // cerr<<"----------------------selecting and moveing"<<endl;
            // int a = 3*234+13;
            int h1=stoi(v[1]);
            int p1=stoi(v[2]);
            pair<int,int> c1= coordinateConversion(h1,p1);
            int x1=c1.first;
            int y1=c1.second;
            int h2=stoi(v[4]);
            int p2=stoi(v[5]);
            pair<int,int> c2= coordinateConversion(h2,p2);
            int x2=c2.first;
            int y2=c2.second;
            if(x1==x2)//slope=0
            {
                if(y2>y1)
                {
                    for(int i=y1+1;i<y2;i++)
                    {
                        if(board->b[x1+size][i+size]==-2)
                            board->b[x1+size][i+size]=2;
                        else if(board->b[x1+size][i+size]==2)
                            board->b[x1+size][i+size]=-2;
                    }
                }
                else if(y1>y2)
                {
                    for(int i=y2+1;i<y1;i++)
                    {
                        if(board->b[x1+size][i+size]==-2)
                            board->b[x1+size][i+size]=2;
                        else if(board->b[x1+size][i+size]==2)
                            board->b[x1+size][i+size]=-2;
                    }
                }
            }
            else if(y1==y2)//slope=infi
            {
                if(x2>x1)
                {
                    for(int i=x1+1;i<x2;i++)
                    {
                        if(board->b[i+size][y1+size]==-2)
                            board->b[i+size][y1+size]=2;
                        else if(board->b[i+size][y1+size]==2)
                            board->b[i+size][y1+size]=-2;
                    }
                }
                else if(x1>x2)
                {
                    for(int i=x2+1;i<x1;i++)
                    {
                        if(board->b[i+size][y1+size]==-2)
                            board->b[i+size][y1+size]=2;
                        else if(board->b[i+size][y1+size]==2)
                            board->b[i+size][y1+size]=-2;
                    }
                }
            }
            else if(x2-x1==y2-y1 || x2-x1==-y2+y1)//slope=+-1
            {
                if(x2>x1 && y2>y1)
                {
                    for(int i=1;i<x2-x1;i++)
                    {
                        if(board->b[x1+i+size][y1+i+size]==-2)
                            board->b[x1+i+size][y1+i+size]=2;
                        else if(board->b[x1+i+size][y1+i+size]==2)
                            board->b[x1+i+size][y1+i+size]=-2;
                    }
                }
                else if(x2>x1 && y1>y2)
                {
                    for(int i=1;i<x2-x1;i++)
                    {
                        if(board->b[x1+i+size][y1-i+size]==-2)
                            board->b[x1+i+size][y1-i+size]=2;
                        else if(board->b[x1+i+size][y1-i+size]==2)
                            board->b[x1+i+size][y1-i+size]=-2;
                    }
                }
                else if(x1>x2 && y2>y1)
                {
                    for(int i=1;i<x1-x2;i++)
                    {
                        if(board->b[x1-i+size][y1+i+size]==-2)
                            board->b[x1-i+size][y1+i+size]=2;
                        else if(board->b[x1-i+size][y1+i+size]==2)
                            board->b[x1-i+size][y1+i+size]=-2;
                    }
                }
                else if(x1>x2 && y1>y2)
                {
                    for(int i=1;i<x1-x2;i++)
                    {
                        if(board->b[x1-i+size][y1-i+size]==-2)
                            {
                            board->b[x1-i+size][y1-i+size]=2;}
                        else if(board->b[x1-i+size][y1-i+size]==2)
                            board->b[x1-i+size][y1-i+size]=-2;
                    }
                }
            }
            board->b[x1+size][y1+size]=2;
            board->b[x2+size][y2+size]=1;
            vector<string> newv;
            for(int i=6;i<v.size();i++)
            {
                newv.push_back(v[i]);
            }
            for(int i=0;i<board->myringpos.size();i++)
            {
                if(x1+size==board->myringpos[i].first && y1+size==board->myringpos[i].second)
                {
                    board->myringpos.erase(board->myringpos.begin()+i);
                    board->myringpos.push_back(make_pair(x2+size,y2+size));
                    break;
                }
            }
            myMove(board, newv);
        }
        else if(v[0]=="RS")//remove krenge 
        {
            // cerr<<"----------------------removing"<<endl;
                        // int a = 3*234+13;
            int h1=stoi(v[1]);
            int p1=stoi(v[2]);
            pair<int,int> c1= coordinateConversion(h1,p1);
            int x1=c1.first;
            int y1=c1.second;
            int h2=stoi(v[4]);
            int p2=stoi(v[5]);
            pair<int,int> c2= coordinateConversion(h2,p2);
            int x2=c2.first;
            int y2=c2.second;
            if(x1==x2)//slope=0
            {
                if(y2>y1)
                {
                    for(int i=y1;i<=y2;i++)
                    {
                        board->b[x1+size][i+size]=0;
                    }
                }
                else if(y1>y2)
                {
                    for(int i=y2;i<=y1;i++)
                    {
                        board->b[x1+size][i+size]=0;
                    }
                }
            }
            else if(y1==y2)//slope=infi
            {
                if(x2>x1)
                {
                    for(int i=x1;i<=x2;i++)
                    {
                        board->b[i+size][y1+size]=0;
                    }
                }
                else if(x1>x2)
                {
                    for(int i=x2;i<=x1;i++)
                    {
                        board->b[i+size][y1+size]=0;
                    }
                }
            }
            else if(x2-x1==y2-y1 || x2-x1==-y2+y1)//slope=+-1
            {
                if(x2>x1 && y2>y1)
                {
                    for(int i=0;i<=x2-x1;i++)
                    {
                        board->b[x1+i+size][y1+i+size]=0;
                    }
                }
                else if(x2>x1 && y1>y2)
                {
                    for(int i=1;i<x2-x1;i++)
                    {
                        board->b[x1+i+size][y1-i+size]=0;
                    }
                }
                else if(x1>x2 && y2>y1)
                {
                    for(int i=1;i<x1-x2;i++)
                    {
                        board->b[x1-i+size][y1+i+size]=0;
                    }
                }
                else if(x1>x2 && y1>y2)
                {
                    for(int i=1;i<x1-x2;i++)
                    {
                        board->b[x1-i+size][y1-i+size]=0;
                    }
                }
            }
            int h3=stoi(v[7]);
            int p3=stoi(v[8]);
            pair<int,int> c3= coordinateConversion(h3,p3);
            int x3=c3.first;
            int y3=c3.second;
            board->b[x3+size][y3+size]=0;
            board->myringout=board->myringout+1;
            vector<string> newv;
            for(int i=9;i<v.size();i++)
            {
                newv.push_back(v[i]);
            }
            for(int i=0;i<board->myringpos.size();i++)
            {
                // cerr<<"shaky : "<<board->myringpos[i].first<<" "<<board->myringpos[i].second<<"\n";
                if(x3+size==board->myringpos[i].first && y3+size==board->myringpos[i].second)
                {
                    board->myringpos.erase(board->myringpos.begin()+i);
                    break;
                }
            }
            myMove(board, newv);
        } 
        else{
            // cerr<<"yaha kabhi nahi aaega";
        }
    }
}


void GamePlay::ChangeBoard(bool ismyturn, Board* board, string move)
{
    vector<string> v=moveVector(move);
    if(ismyturn==true) 
    {
        // cerr<<"-------------------------Going to enter in my move"<<endl;
        myMove(board, v);
    }
    else 
    {
        // cerr<<"------------------------Going to enter in opp move"<<endl;
        oppMove(board, v);
    }
}

vector<pair<pair<int, int>,pair<int, int> > > GamePlay::CheckContMarkerX( bool ismyturn, Board* board)
{   
    int m;
    if(ismyturn==true) m=2;
    else m=-2;
    int count = 0;
    vector<pair<pair<int, int>, pair<int, int> > > goodmarkers;
    int n = 2*size+1;
    int start =0;
    for(int x=0;x<n;x++){
        int y=0;
        start=0;
        count=0;
        while(y<n){
            if(board->b[x][y]!=m){
                if(count>=contmarker){
                    // goodmarkers.push_back(make_pair(make_pair(x,start),make_pair(x, y-1)));
                    goodmarkers.push_back(make_pair(make_pair(x,y-contmarker),make_pair(x, y-1)));
                }
                count=0;
                start=y+1;
            }
            else{
                count++;
            }
        y++;
        }
        if(count>=contmarker){
            // goodmarkers.push_back(make_pair(make_pair(x,start),make_pair(x, y-1)));
                    goodmarkers.push_back(make_pair(make_pair(x,y-contmarker),make_pair(x, y-1)));
            }
    }
    
    return goodmarkers;
}
vector<pair<pair<int, int>,pair<int, int> > > GamePlay::CheckContMarkerY( bool ismyturn, Board* board)
{   
    int m;
    if(ismyturn==true) m=2;
    else m=-2;
    int count = 0;
    vector<pair<pair<int, int>, pair<int, int> > > goodmarkers;
    int n = 2*size+1;
    int start =0;
    
    for(int y=0;y<n;y++){
        int x=0;
        start=0;
        count=0;
        while(x<n){
            if(board->b[x][y]!=m){
                if(count>=contmarker){
                    // goodmarkers.push_back(make_pair(make_pair(start,y),make_pair(x-1, y)));
                    goodmarkers.push_back(make_pair(make_pair(x-contmarker,y),make_pair(x-1, y)));
                }
                count=0;
                start=x+1;
            }
            else{
                count++;
            }
        x++;
        }
        if(count>=contmarker){
            // goodmarkers.push_back(make_pair(make_pair(start,y),make_pair(x-1, y)));
                    goodmarkers.push_back(make_pair(make_pair(x-contmarker,y),make_pair(x-1, y)));

        }
    }
   
    return goodmarkers;
}
vector<pair<pair<int, int>,pair<int, int> > > GamePlay::CheckContMarkerXY( bool ismyturn, Board* board)
{   
    int m;
    if(ismyturn==true) m=2;
    else m=-2;
    int count = 0;
    vector<pair<pair<int, int>, pair<int, int> > > goodmarkers;
    int n = 2*size+1;
    // int start =0;
   
    int startx = 0;
    int starty = 0;
    for(int i=size;i>=0;i--){  
        int x = i;
        int y = 0;
        startx=i;
        starty=0;
        count=0;
        while(x<n&&y<n){
            if(board->b[x][y]!=m){
                if(count>=contmarker){
                    // goodmarkers.push_back(make_pair(make_pair(startx,starty),make_pair(x-1, y-1)));
                    goodmarkers.push_back(make_pair(make_pair(x-contmarker,y-contmarker),make_pair(x-1, y-1)));

                }
                count=0;
                startx=x+1;
                starty=y+1;
            }
            else{
                count++;
            }
            x++;
            y++;
        }
        if(count>=contmarker){
            // goodmarkers.push_back(make_pair(make_pair(startx,starty),make_pair(x-1, y-1)));
                    goodmarkers.push_back(make_pair(make_pair(x-contmarker,y-contmarker),make_pair(x-1, y-1)));
        }
    }
    for(int j=1;j<=size;j++){
        int x = 0;
        int y = j;
        startx=0;
        starty=j;
        count=0;
        while(x<n&&y<n){
            if(board->b[x][y]!=m){
                if(count>=contmarker){
                    // goodmarkers.push_back(make_pair(make_pair(startx,starty),make_pair(x-1, y-1)));
                    goodmarkers.push_back(make_pair(make_pair(x-contmarker,y-contmarker),make_pair(x-1, y-1)));
                }
                count=0;
                startx=x+1;
                starty=y+1;
            }
            else{
                count++;
            }
            x++;
            y++;
        }
        if(count>=contmarker){
            // goodmarkers.push_back(make_pair(make_pair(startx,starty),make_pair(x-1, y-1)));
                    goodmarkers.push_back(make_pair(make_pair(x-contmarker,y-contmarker),make_pair(x-1, y-1)));
        }
    }
    return goodmarkers;
}
vector<pair<pair<int, int>,pair<int, int> > > GamePlay::CheckContMarker( bool ismyturn, Board* board){
    Board *tempboard;
    auto a = CheckContMarkerX(ismyturn, board);
    tempboard=board->copyBoard();
    for(auto move:a){
            pair<int, int> hp1pcl=coordinatebackConversion(move.first.first, move.first.second);
            pair<int, int> hp2pcl=coordinatebackConversion(move.second.first, move.second.second);
            pair<int, int> ptbr;
            if(ismyturn==true)
                ptbr = tempboard->myringpos[0];
            else
                ptbr = tempboard->oppringpos[0];
            pair<int, int> hptbr=coordinatebackConversion(ptbr.first, ptbr.second);
            string str = "RS "+to_string(hp1pcl.first)+" "+to_string(hp1pcl.second)+" RE "+to_string(hp2pcl.first)+" "+to_string(hp2pcl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);  
            ChangeBoard(ismyturn, tempboard, str);
    }
    auto b = CheckContMarkerY(ismyturn, tempboard);
    for(auto move:b){
            pair<int, int> hp1pcl=coordinatebackConversion(move.first.first, move.first.second);
            pair<int, int> hp2pcl=coordinatebackConversion(move.second.first, move.second.second);
            pair<int, int> ptbr;
            if(ismyturn==true)
                ptbr = tempboard->myringpos[0];
            else
                ptbr = tempboard->oppringpos[0];
            pair<int, int> hptbr=coordinatebackConversion(ptbr.first, ptbr.second);
            string str = "RS "+to_string(hp1pcl.first)+" "+to_string(hp1pcl.second)+" RE "+to_string(hp2pcl.first)+" "+to_string(hp2pcl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);  
            ChangeBoard(ismyturn, tempboard, str);
    }
    auto c = CheckContMarkerXY(ismyturn, tempboard);
    a.insert(a.end(), b.begin(), b.end());
    a.insert(a.end(), c.begin(), c.end());

    return a;
    }
vector<string> GamePlay::neighbours(Board* board, bool ismyturn){
    // cerr<<"outloop";
    vector<string> moves(0);
    Board *tempboard;
    // Board *preloopboard;
    string hey;
    auto precontlist = CheckContMarker(ismyturn, board);
    vector<pair<int, int> > ringsabell;
    if(ismyturn)    
        ringsabell = board->myringpos;
    else 
        ringsabell = board->oppringpos;
    // cerr<<"outloop";
    if(precontlist.empty()==true){
        // cerr<<"stilloutloop";
         string initialstring="";
         for (auto r: ringsabell){
            //  cerr<<"loop1";
                    vector<pair<int, int> > list = neighbourPosition(board, r.first, r.second);
                    for(auto mymove : list){
                        // cerr<<"loop2";
                        auto tempboard=board->copyBoard();
                        auto hpr=coordinatebackConversion(r.first, r.second);
                        auto hpmymove=coordinatebackConversion(mymove.first, mymove.second);
                        string mymovestring = "S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                        // string mymovestring = "S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                        ChangeBoard(ismyturn, tempboard, mymovestring);
                        // tempboard->printBoard();
                        auto contlist = CheckContMarker(ismyturn, tempboard);
                        vector<pair<int, int> > tempringsabell;
                            if(ismyturn)    
                                tempringsabell = tempboard->myringpos;
                            else 
                                tempringsabell = tempboard->oppringpos;
                        if(contlist.empty()){
                            hey = initialstring + "S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                            // hey =initialstring+" S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                            //then just add s and p to moves
                            moves.push_back(hey);
                        }
                        else if (contlist.size() == 1){
                            // moves.clear();
                            for(auto cl : contlist){
                                // cerr<<"loop3";
                                for(auto tbr:tempringsabell){
                                    // hey = initialstring+" S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                                    hey = initialstring+ "S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                                    pair<int, int> hp1cl=coordinatebackConversion(cl.first.first, cl.first.second);
                                    pair<int, int> hp2cl=coordinatebackConversion(cl.second.first, cl.second.second);
                                    pair<int, int> hptbr=coordinatebackConversion(tbr.first, tbr.second);
                                    hey = hey + " RS "+to_string(hp1cl.first)+" "+to_string(hp1cl.second)+" RE "+to_string(hp2cl.first)+" "+to_string(hp2cl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);                                    
                                    // hey = hey + " RS "+to_string(cl.first.first)+" "+to_string(cl.first.second)+" RE "+to_string(cl.second.first)+" "+to_string(cl.second.second)+" X "+to_string(tbr.first)+" "+to_string(tbr.second);
                                    // moves.clear();
                                    moves.push_back(hey);
                                    // return moves;
                                }
                            }
                            // return moves;
                        }
                        else{
                            int i =0;
                            hey = initialstring+ "S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                            for(auto cl : contlist){
                                // cerr<<"loop3";
                                    auto tbr = tempringsabell[i];
                                    // hey = initialstring+" S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                                    pair<int, int> hp1cl=coordinatebackConversion(cl.first.first, cl.first.second);
                                    pair<int, int> hp2cl=coordinatebackConversion(cl.second.first, cl.second.second);
                                    pair<int, int> hptbr=coordinatebackConversion(tbr.first, tbr.second);
                                    hey = hey + " RS "+to_string(hp1cl.first)+" "+to_string(hp1cl.second)+" RE "+to_string(hp2cl.first)+" "+to_string(hp2cl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);                                    
                                    // hey = hey + " RS "+to_string(cl.first.first)+" "+to_string(cl.first.second)+" RE "+to_string(cl.second.first)+" "+to_string(cl.second.second)+" X "+to_string(tbr.first)+" "+to_string(tbr.second);
                                    // moves.clear();
                                    // return moves;
                                    i++;
                                }
                            moves.push_back(hey);    
                            }
                        }
                    }
                }
    else if(precontlist.size()==1){
        for(auto pcl : precontlist){
            // cerr<<"a";
            for(auto ptbr:ringsabell){
                for(auto x:ringsabell){
                    // cerr<<x.first<<","<<x.second<<endl;
                }
                // cerr<<"2";
                tempboard=board->copyBoard();    
                pair<int, int> hp1pcl=coordinatebackConversion(pcl.first.first, pcl.first.second);
                pair<int, int> hp2pcl=coordinatebackConversion(pcl.second.first, pcl.second.second);
                pair<int, int> hptbr=coordinatebackConversion(ptbr.first, ptbr.second);
                string initialstring = "RS "+to_string(hp1pcl.first)+" "+to_string(hp1pcl.second)+" RE "+to_string(hp2pcl.first)+" "+to_string(hp2pcl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);  
                ChangeBoard(ismyturn, tempboard, initialstring);
                vector<pair<int, int> > tempringsabell;
                int ringout;
                if(ismyturn)    
                    {tempringsabell = tempboard->myringpos;
                    ringout = tempboard->myringout;}
                else 
                    {tempringsabell = tempboard->oppringpos;
                    ringout = tempboard->oppringout;}
                    
                for (auto r: tempringsabell){
                    // cerr<<"b";
                    if(ringout>=3) break;
                    vector<pair<int, int> > list = neighbourPosition(tempboard, r.first, r.second);
                    for(auto mymove : list){
                        auto temptempboard=tempboard->copyBoard();
                        auto hpr=coordinatebackConversion(r.first, r.second);
                        auto hpmymove=coordinatebackConversion(mymove.first, mymove.second);
                        string mymovestring = "S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                        // string mymovestring = "S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                        ChangeBoard(ismyturn, temptempboard, mymovestring);
                        vector<pair<int, int> > temptempringsabell;
                            if(ismyturn)    
                                tempringsabell = temptempboard->myringpos;
                            else 
                                tempringsabell = temptempboard->oppringpos;
                        auto contlist = CheckContMarker(ismyturn, temptempboard);
                        if(contlist.empty()==true){
                            // cerr<<"c";
                            hey = initialstring + " S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                            // hey =initialstring+" S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                            //then just add s and p to moves
                            moves.push_back(hey);
                        }
                        else{
                            // cerr<<"d";
                            for(auto cl : contlist){
                                for(auto tbr:temptempringsabell){
                                    // hey = initialstring+" S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                                    // cerr<<"e";
                                    hey = initialstring+ " S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                                    pair<int, int> hp1cl=coordinatebackConversion(cl.first.first, cl.first.second);
                                    pair<int, int> hp2cl=coordinatebackConversion(cl.second.first, cl.second.second);
                                    pair<int, int> hptbr=coordinatebackConversion(tbr.first, tbr.second);
                                    hey = hey + " RS "+to_string(hp1cl.first)+" "+to_string(hp1cl.second)+" RE "+to_string(hp2cl.first)+" "+to_string(hp2cl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);
                                    // hey = hey+" RS "+to_string(cl.first.first)+" "+to_string(cl.first.second)+" RE "+to_string(cl.second.first)+" "+to_string(cl.second.second)+" X "+to_string(tbr.first)+" "+to_string(tbr.second);
                                    // moves.clear();
                                    moves.push_back(hey);
                                    // return moves;
                                }
                            }
                        }
                        // cout<<hey<<"\n";
                    }
                }
                // cerr<<initialstring<<"\n";
                moves.push_back(initialstring);
                // board->printBoard();
            }
        }
    }
    else {
        int i =0;
        string initialstring = "";
        for(auto pcl : precontlist){
            vector<pair<int, int> > tempringsabell;    
            int ringout;        
            if(ismyturn)    
                ringout = tempboard->myringout;
            else 
                ringout = tempboard->oppringout;
            if(ringout>=3) {
                break;
            }
                
            // cerr<<"a";
            // for(auto ptbr:ringsabell){

                auto ptbr = ringsabell[i];
                for(auto x:ringsabell){
                    // cerr<<x.first<<","<<x.second<<endl;
                }
                // cerr<<"2";
                tempboard=board->copyBoard();    
                pair<int, int> hp1pcl=coordinatebackConversion(pcl.first.first, pcl.first.second);
                pair<int, int> hp2pcl=coordinatebackConversion(pcl.second.first, pcl.second.second);
                pair<int, int> hptbr=coordinatebackConversion(ptbr.first, ptbr.second);
                if(i==0)                
                    initialstring += "RS "+to_string(hp1pcl.first)+" "+to_string(hp1pcl.second)+" RE "+to_string(hp2pcl.first)+" "+to_string(hp2pcl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);                  
                else         
                    initialstring += " RS "+to_string(hp1pcl.first)+" "+to_string(hp1pcl.second)+" RE "+to_string(hp2pcl.first)+" "+to_string(hp2pcl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);  
                ChangeBoard(ismyturn, tempboard, initialstring);
                i++;
            }
                
                    // cerr<<"b";
            for (auto r:tempboard->myringpos){
                vector<pair<int, int> > list = neighbourPosition(tempboard, r.first, r.second);
                for(auto mymove : list){
                        int ringout;
                        if(ismyturn)    
                            ringout = tempboard->myringout;
                        else 
                            ringout = tempboard->oppringout;
                        if(ringout>=3) {
                            moves.push_back(initialstring);
                            break;
                        }
                        auto temptempboard=tempboard->copyBoard();
                        auto hpr=coordinatebackConversion(r.first, r.second);
                        auto hpmymove=coordinatebackConversion(mymove.first, mymove.second);
                        string mymovestring = "S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                        // string mymovestring = "S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                        ChangeBoard(ismyturn, temptempboard, mymovestring);
                        auto contlist = CheckContMarker(ismyturn, temptempboard);
                        if(contlist.empty()==true){
                            // cerr<<"c";
                            hey = initialstring + " S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                            // hey =initialstring+" S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                            //then just add s and p to moves
                            moves.push_back(hey);
                        }
                        else if (contlist.size() == 1){
                            // cerr<<"d";
                            vector<pair<int, int> > temptempringsabell;
                            if(ismyturn)    
                                temptempringsabell = temptempboard->myringpos;
                            else 
                                temptempringsabell = temptempboard->oppringpos;
                            for(auto cl : contlist){
                                for(auto tbr:temptempringsabell){
                                    // hey = initialstring+" S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                                    // cerr<<"e";
                                    hey = initialstring+ " S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                                    pair<int, int> hp1cl=coordinatebackConversion(cl.first.first, cl.first.second);
                                    pair<int, int> hp2cl=coordinatebackConversion(cl.second.first, cl.second.second);
                                    pair<int, int> hptbr=coordinatebackConversion(tbr.first, tbr.second);
                                    hey = hey + " RS "+to_string(hp1cl.first)+" "+to_string(hp1cl.second)+" RE "+to_string(hp2cl.first)+" "+to_string(hp2cl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);
                                    // hey = hey+" RS "+to_string(cl.first.first)+" "+to_string(cl.first.second)+" RE "+to_string(cl.second.first)+" "+to_string(cl.second.second)+" X "+to_string(tbr.first)+" "+to_string(tbr.second);
                                    // moves.clear();
                                    moves.push_back(hey);
                                    // return moves;
                                }
                            }
                        }
                        else{
                            int i =0;
                            hey = initialstring+ "S "+to_string(hpr.first)+" "+to_string(hpr.second)+" M "+to_string(hpmymove.first)+" "+to_string(hpmymove.second);
                            for(auto cl : contlist){
                                // cerr<<"loop3";
                                    vector<pair<int, int> > tempringsabell;
                                    if(ismyturn)    
                                        tempringsabell = tempboard->myringpos;
                                    else 
                                        tempringsabell = tempboard->oppringpos;        
                                    auto tbr = tempringsabell[i];
                                    // hey = initialstring+" S "+to_string(r.first)+" "+to_string(r.second)+" M "+to_string(mymove.first)+" "+to_string(mymove.second);
                                    pair<int, int> hp1cl=coordinatebackConversion(cl.first.first, cl.first.second);
                                    pair<int, int> hp2cl=coordinatebackConversion(cl.second.first, cl.second.second);
                                    pair<int, int> hptbr=coordinatebackConversion(tbr.first, tbr.second);
                                    hey = hey + " RS "+to_string(hp1cl.first)+" "+to_string(hp1cl.second)+" RE "+to_string(hp2cl.first)+" "+to_string(hp2cl.second)+" X "+to_string(hptbr.first)+" "+to_string(hptbr.second);                                    
                                    // hey = hey + " RS "+to_string(cl.first.first)+" "+to_string(cl.first.second)+" RE "+to_string(cl.second.first)+" "+to_string(cl.second.second)+" X "+to_string(tbr.first)+" "+to_string(tbr.second);
                                    // moves.clear();
                                    // return moves;
                                    i++;
                                }
                            moves.push_back(hey);    
                            }
                        // cout<<hey<<"\n";
                    }
                // moves.push_back(initialstring);
                }
                // cerr<<initialstring<<"\n";
                // board->printBoard();
                
        }
    return moves;
}

// vector<string> GamePlay::neighbourPos(Board* board, int x, int y){
//     string move="";
//     vector<pair<pair<int,int>,pair<int,int>>> contMarker= CheckContMarker(true, board);
//     for(int i=0;i<contMarker.size();i++)
//     {
//         int x1=contMarker[i].first.first;
//         int y1=contMarker[i].first.second;
//         int x2=contMarker[i].second.first;
//         int y2=contMarker[i].second.second;

//     }
// }
int GamePlay::maxoppflip(Board* board,int x,int y)
{
    // vector<pair<int,int> > v;
    int maxi=-10;
    //slope +0
    int count=0;
    for(int i=x+1;i<=2*size;i++)
    {
        // int count=0;
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)//empty space
            {
                if(board->b[i-1][y]==0 || board->b[i-1][y]==-1)
                {

                }
                    // v.push_back(make_pair(i,y));
                else if(board->b[i-1][y]==-2 || board->b[i-1][y]==2)
                {
                    // v.push_back(make_pair(i,y));
                    // if(board->b[i-1][y]==-2)
                    //     count++;
                    // else
                    //     count--;
                    break;
                }
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else
            {
                if(board->b[i][y]==-2)
                        count++;
                    else
                        count--;
            }
        }
    }
    maxi=max(maxi,-count);
    count=0;
    //slope -0
    for(int i=x-1;i>=0;i--)
    {
        // count=0;
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)
            {
                if(board->b[i+1][y]==0 || board->b[i+1][y]==-1)
                {

                }
                    // v.push_back(make_pair(i,y));
                else if(board->b[i+1][y]==-2 || board->b[i+1][y]==2)
                {
                    // v.push_back(make_pair(i,y));
                    // if(board->b[i+1][y]==-2)
                    //     count++;
                    // else
                    //     count--;
                    break;
                }
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else
            {
                if(board->b[i][y]==-2)
                        count++;
                    else
                        count--;
            }

        }
    }
    //slope +infi
    maxi=max(maxi,-count);
    count=0;
    for(int i=y+1;i<=2*size;i++)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                if(board->b[x][i-1]==0 || board->b[x][i-1]==-1)
                {

                }
                    // v.push_back(make_pair(x,i));
                else if(board->b[x][i-1]==-2 || board->b[x][i-1]==2)
                {
                    // v.push_back(make_pair(x,i));
                    // if(board->b[i+1][y]==-2)
                    //     count++;
                    // else
                    //     count--;
                    break;
                }
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else
            {
                if(board->b[x][i]==-2)
                        count++;
                    else
                        count--;
            }
        }
    }
    //slope -infi
    maxi=max(maxi,-count);
    count=0;
    for(int i=y-1;i>=0;i--)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                if(board->b[x][i+1]==0 || board->b[x][i+1]==-1)
                    // v.push_back(make_pair(x,i));
                    {}
                else if(board->b[x][i+1]==-2 || board->b[x][i+1]==2)
                {
                    // v.push_back(make_pair(x,i));
                    // if(board->b[x][i+1]==-2)
                    //     count++;
                    // else
                    //     count--;
                    break;
                }
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else
            {
                if(board->b[x][i]==-2)
                        count++;
                    else
                        count--;
            }
        }
    }
    //slope +1
    maxi=max(maxi,-count);
    count=0;
    int i=x+1;
    int j=y+1;
    while(i<=2*size && j<=2*size)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                if(board->b[i-1][j-1]==0 || board->b[i-1][j-1]==-1)
                    // v.push_back(make_pair(i,j));
                    {}
                else if(board->b[i-1][j-1]==-2 || board->b[i-1][j-1]==2)
                {
                    // v.push_back(make_pair(i,j));
                    // if(board->b[i-1][j-1]==-2)
                    //     count++;
                    // else
                    //     count--;
                    break;
                }
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else
            {
                if(board->b[i][j]==-2)
                        count++;
                    else
                        count--;
            }
        }
        i++;
        j++;
    }
    maxi=max(maxi,-count);
    count=0;
    i=x-1;
    j=y-1;
    while(i>=0 && j>=0)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                if(board->b[i+1][j+1]==0 || board->b[i+1][j+1]==-1)
                    // v.push_back(make_pair(i,j));
                    {

                    }
                else if(board->b[i+1][j+1]==-2 || board->b[i+1][j+1]==2)
                {
                    // v.push_back(make_pair(i,j));
                    // if(board->b[i-1][j-1]==-2)
                    //     count++;
                    // else
                    //     count--;
                    break;
                }
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
             else
            {
                if(board->b[i][j]==-2)
                        count++;
                    else
                        count--;
            }   
        }
        i--;
        j--;
    }
    maxi=max(maxi,-count);
    return maxi;
}
int GamePlay::oppflipsum(Board* board)
{
    int maxi=0;
    for(auto i: board->oppringpos)
    {
        // sum+=oppflip(board,i.first,i.second);
        maxi=max(maxi,maxoppflip(board,i.first,i.second));
    }
    return maxi;
}
vector<int > GamePlay::markerSpaceRing(Board* board, int x, int y) 
{
    vector<int > v(3);
    int ans=0;
    int count=0;
    //slope +0
    for(int i=x+1;i<=2*size;i++)
    {
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)//empty space
            {
                if(board->b[i-1][y]==0 || board->b[i-1][y]==1)
                {

                }
                else if(board->b[i-1][y]==-2 || board->b[i-1][y]==2)
                {
                    // v.push_back(make_pair(i,y));
                    break;
                }
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][y]==2)
            {
                count++;
            }
            else if(board->b[i][y]==-2)
            {
                count=0;
                break;
            }
            
        }
    }
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    //slope -0
    for(int i=x-1;i>=0;i--)
    {
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)
            {
                if(board->b[i+1][y]==0 || board->b[i+1][y]==1)
                {

                }
                else if(board->b[i+1][y]==-2 || board->b[i+1][y]==2)
                {
                    // count=0;
                    break;
                }
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][y]==2)
            {
                count++;
            }
            else if(board->b[i][y]==-2)
            {
                count=0;
                break;
            }
        }
    }
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    //slope +infi
    for(int i=y+1;i<=2*size;i++)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                if(board->b[x][i-1]==0 || board->b[x][i-1]==1)
                {

                }
                else if(board->b[x][i-1]==-2 || board->b[x][i-1]==2)
                {
                    // v.push_back(make_pair(x,i));
                    // count=0;
                    break;
                }
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[x][i]==2)
            {
                count++;
            }
            else if(board->b[x][i]==-2)
            {
                count=0;
                break;
            }
        }
    }
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    //slope -infi
    for(int i=y-1;i>=0;i--)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                if(board->b[x][i+1]==0 || board->b[x][i+1]==1)
                {
                    
                }
                else if(board->b[x][i+1]==-2 || board->b[x][i+1]==2)
                {
                    // v.push_back(make_pair(x,i));
                    // count=0;
                    break;
                }
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[x][i]==2)
            {
                count++;
            }
            else if(board->b[x][i]==-2)
            {
                count=0;
                break;
            }
        }
    }
    //slope +1
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    int i=x+1;
    int j=y+1;
    while(i<=2*size && j<=2*size)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                if(board->b[i-1][j-1]==0 || board->b[i-1][j-1]==1)
                {
                    
                }
                else if(board->b[i-1][j-1]==-2 || board->b[i-1][j-1]==2)
                {
                    // v.push_back(make_pair(i,j));
                    // count=0;
                    break;
                }
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][j]==2)
            {
                count++;
            }
            else if(board->b[i][j]==-2)
            {
                count=0;
                break;
            }
        }
        i++;
        j++;
    }
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    i=x-1;
    j=y-1;
    while(i>=0 && j>=0)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                if(board->b[i+1][j+1]==0 || board->b[i+1][j+1]==1)
                {
                    
                }
                else if(board->b[i+1][j+1]==-2 || board->b[i+1][j+1]==2)
                {
                    // v.push_back(make_pair(i,j));
                    // count=0;
                    break;
                }
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][j]==2)
            {
                count++;
            }
            else if(board->b[i][j]==-2)
            {
                count=0;
                break;
            }
        }
        i--;
        j--;
    }
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    return v;
}
vector<int> GamePlay::totalMarkerSpaceRing(Board* board)
{
    vector<int> maxi(3);
    for(auto i: board->oppringpos)
    {
        // sum+=oppflip(board,i.first,i.second);
        // maxi=max(maxi,maxoppflip(board,i.first,i.second));
        vector<int> v=markerSpaceRing(board,i.first,i.second);
        for(int i=0;i<3;i++)
            maxi[i]+=v[i];
    }
    return maxi;
}
vector<int> GamePlay::ringClash(Board* board,int x,int y)//spacemarkerring
{
    // vector<pair<int,int> > v;
    // int maxi=-10;
    //slope +0
    vector<int> v(3);

    int ans=0;
    int count=0;
    bool clash=true;
    for(int i=x+1;i<=2*size;i++)
    {
        // int count=0;
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)//empty space
            {
                break;
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][y]==2)
            {
                count++;
            }
            else if(board->b[i][y]==-2)
            {
                count=0;
                break;
            }
        }
    }

    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    // maxi=max(maxi,-count);
    // count=0;
    //slope -0
    count=0;
    for(int i=x-1;i>=0;i--)
    {
        // count=0;
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)
            {
                break;
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][y]==-2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
    }
    //slope +infi
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    // maxi=max(maxi,-count);
    // count=0;
    count=0;
    for(int i=y+1;i<=2*size;i++)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                break;
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[x][i]==-2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
    }
    //slope -infi
    // maxi=max(maxi,-count);
    // count=0;
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    for(int i=y-1;i>=0;i--)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                 break;
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[x][i]==-2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
    }
    //slope +1
    // maxi=max(maxi,-count);
    // count=0;
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    int i=x+1;
    int j=y+1;
    while(i<=2*size && j<=2*size)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                break;
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][j]==-2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
        i++;
        j++;
    }
    // maxi=max(maxi,-count);
    // count=0;
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    i=x-1;
    j=y-1;
    while(i>=0 && j>=0)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                break;
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][j]==-2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
        i--;
        j--;
    }
    // maxi=max(maxi,-count);
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    return v;
}
vector<int> GamePlay::totalOppRingClash(Board* board)
{
    vector<int> maxi(3);
    for(auto i: board->oppringpos)
    {
        // sum+=oppflip(board,i.first,i.second);
        // maxi=max(maxi,maxoppflip(board,i.first,i.second));
        vector<int> v=ringClash(board,i.first,i.second);
        for(int i=0;i<3;i++)
            maxi[i]+=v[i];
    }
    return maxi;
}
vector<int> GamePlay::myRingClash(Board* board,int x,int y)
{
    // vector<pair<int,int> > v;
    // int maxi=-10;
    //slope +0
    vector<int> v(3);

    int ans=0;
    int count=0;
    bool clash=true;
    for(int i=x+1;i<=2*size;i++)
    {
        // int count=0;
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)//empty space
            {
                break;
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][y]==-2)
            {
                count++;
            }
            else if(board->b[i][y]==2)
            {
                count=0;
                break;
            }
        }
    }

    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    // maxi=max(maxi,-count);
    // count=0;
    //slope -0
    count=0;
    for(int i=x-1;i>=0;i--)
    {
        // count=0;
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)
            {
                break;
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][y]==2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
    }
    //slope +infi
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    // maxi=max(maxi,-count);
    // count=0;
    count=0;
    for(int i=y+1;i<=2*size;i++)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                break;
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[x][i]==2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
    }
    //slope -infi
    // maxi=max(maxi,-count);
    // count=0;
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    for(int i=y-1;i>=0;i--)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                 break;
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[x][i]==2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
    }
    //slope +1
    // maxi=max(maxi,-count);
    // count=0;
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    int i=x+1;
    int j=y+1;
    while(i<=2*size && j<=2*size)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                break;
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][j]==2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
        i++;
        j++;
    }
    // maxi=max(maxi,-count);
    // count=0;
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    count=0;
    i=x-1;
    j=y-1;
    while(i>=0 && j>=0)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                break;
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][j]==2)
            {
                count=0;
                break;
            }
            else
                count++;
        }
        i--;
        j--;
    }
    // maxi=max(maxi,-count);
    if(count==4)
        v[2]++;
    if(count==3)
        v[1]++;
    if(count==2)
        v[0]++;
    return v;
}
vector<int> GamePlay::totalMyRingClash(Board* board)
{
    vector<int> maxi(3);
    for(auto i: board->myringpos)
    {
        // sum+=oppflip(board,i.first,i.second);
        // maxi=max(maxi,maxoppflip(board,i.first,i.second));
        vector<int> v=myRingClash(board,i.first,i.second);
        for(int i=0;i<3;i++)
            maxi[i]+=v[i];
    }
    return maxi;
}
vector<int> GamePlay::oppMyOpp(Board* board,int x,int y)//spacemarkerring
{
    // vector<pair<int,int> > v;
    // int maxi=-10;
    //slope +0
    vector<int> v(3);

    int ans=0;
    int count=0;
    bool clash=false;
    for(int i=x+1;i<=2*size;i++)
    {
        // int count=0;
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)//empty space
            {
                break;
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][y]==2)
            {
                count++;
            }
            else if(board->b[i][y]==-2)
            {
                // count=0;
                clash=true;
                break;
            }
        }
    }

    if(count==4 && clash==true)
        v[2]++;
    if(count==3 && clash==true)
        v[1]++;
    clash=false;
    // if(count==3)
    //     v[1]++;
    // if(count==2)
    //     v[0]++;
    count=0;
    for(int i=x-1;i>=0;i--)
    {
        // count=0;
        if(board->b[i][y]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][y]==0)
            {
                break;
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][y]==-2)
            {
                // count=0;
                clash=true;
                break;
            }
            else
                count++;
        }
    }
    //slope +infi
    if(count==4 && clash==true)
        v[2]++;
    if(count==3 && clash==true)
        v[1]++;
    clash=false;
    // if(count==3)
    //     v[1]++;
    // if(count==2)
    //     v[0]++;
    count=0;
    for(int i=y+1;i<=2*size;i++)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                break;
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[x][i]==-2)
            {
                // count=0;
                clash=true;
                break;
            }
            else
                count++;
        }
    }
    if(count==4 && clash==true)
        v[2]++;
    if(count==3 && clash==true)
        v[1]++;
    clash=false;
    count=0;
    for(int i=y-1;i>=0;i--)
    {
        if(board->b[x][i]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                 break;
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[x][i]==-2)
            {
                // count=0;
                clash=true;
                break;
            }
            else
                count++;
        }
    }
    if(count==4 && clash==true)
        v[2]++;
    if(count==3 && clash==true)
        v[1]++;
    clash=false;
    //slope +1
    // if(count==3)
    //     v[1]++;
    // if(count==2)
    //     v[0]++;
    count=0;
    int i=x+1;
    int j=y+1;
    while(i<=2*size && j<=2*size)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                break;
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][j]==-2)
            {
                // count=0;
                clash=true;
                break;
            }
            else
                count++;
        }
        i++;
        j++;
    }
    if(count==4 && clash==true)
        v[2]++;
    if(count==3 && clash==true)
        v[1]++;
    clash=false;
    // if(count==3)
    //     v[1]++;
    // if(count==2)
    //     v[0]++;
    count=0;
    i=x-1;
    j=y-1;
    while(i>=0 && j>=0)
    {
        if(board->b[i][j]==3)
        {
            count=0;
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                break;
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
            {
                count=0;
                break;
            }
            else if(board->b[i][j]==-2)
            {
                // count=0;
                clash=true;
                break;
            }
            else
                count++;
        }
        i--;
        j--;
    }
    // maxi=max(maxi,-count);
    if(count==4 && clash==true)
        v[2]++;
    if(count==3 && clash==true)
        v[1]++;
    clash=false;
    // if(count==3)
    //     v[1]++;
    // if(count==2)
    //     v[0]++;
    return v;
}
vector<int> GamePlay::totalOppMyOpp(Board* board)
{
    vector<int> maxi(3);
    for(auto i: board->oppringpos)
    {
        // sum+=oppflip(board,i.first,i.second);
        // maxi=max(maxi,maxoppflip(board,i.first,i.second));
        vector<int> v=oppMyOpp(board,i.first,i.second);
        for(int i=0;i<3;i++)
            maxi[i]+=v[i];
    }
    return maxi;
}
vector<pair<int,int> > GamePlay::neighbourPosition(Board* board, int x, int y) 
{
    vector<pair<int,int> > v;
    //slope +0
    for(int i=x+1;i<=2*size;i++)
    {
        if(board->b[i][y]==3)
        {
            break;
        }
        else
        {
            if(board->b[i][y]==0)//empty space
            {
                if(board->b[i-1][y]==0 || board->b[i-1][y]==1 || board->b[i-1][y]==-1)
                    v.push_back(make_pair(i,y));
                else if(board->b[i-1][y]==-2 || board->b[i-1][y]==2)
                {
                    v.push_back(make_pair(i,y));
                    break;
                }
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
                break;
        }
    }
    //slope -0
    for(int i=x-1;i>=0;i--)
    {
        if(board->b[i][y]==3)
        {
            break;
        }
        else
        {
            if(board->b[i][y]==0)
            {
                if(board->b[i+1][y]==0 || board->b[i+1][y]==1 || board->b[i+1][y]==-1)
                    v.push_back(make_pair(i,y));
                else if(board->b[i+1][y]==-2 || board->b[i+1][y]==2)
                {
                    v.push_back(make_pair(i,y));
                    break;
                }
            }
            else if(board->b[i][y]==1 || board->b[i][y]==-1)//ring encounter
                break;
        }
    }
    //slope +infi
    for(int i=y+1;i<=2*size;i++)
    {
        if(board->b[x][i]==3)
        {
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                if(board->b[x][i-1]==0 || board->b[x][i-1]==1 || board->b[x][i-1]==-1)
                    v.push_back(make_pair(x,i));
                else if(board->b[x][i-1]==-2 || board->b[x][i-1]==2 )
                {
                    v.push_back(make_pair(x,i));
                    break;
                }
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
                break;
        }
    }
    //slope -infi
    for(int i=y-1;i>=0;i--)
    {
        if(board->b[x][i]==3)
        {
            break;
        }
        else
        {
            if(board->b[x][i]==0)
            {
                if(board->b[x][i+1]==0 || board->b[x][i+1]==1 || board->b[x][i+1]==-1)
                    v.push_back(make_pair(x,i));
                else if(board->b[x][i+1]==-2 || board->b[x][i+1]==2)
                {
                    v.push_back(make_pair(x,i));
                    break;
                }
            }
            else if(board->b[x][i]==1 || board->b[x][i]==-1)//ring encounter
                break;
        }
    }
    //slope +1
    int i=x+1;
    int j=y+1;
    while(i<=2*size && j<=2*size)
    {
        if(board->b[i][j]==3)
        {
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                if(board->b[i-1][j-1]==0 || board->b[i-1][j-1]==1 || board->b[i-1][j-1]==-1)
                    v.push_back(make_pair(i,j));
                else if(board->b[i-1][j-1]==-2 || board->b[i-1][j-1]==2)
                {
                    v.push_back(make_pair(i,j));
                    break;
                }
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
                break;
        }
        i++;
        j++;
    }
    i=x-1;
    j=y-1;
    while(i>=0 && j>=0)
    {
        if(board->b[i][j]==3)
        {
            break;
        }
        else
        {
            if(board->b[i][j]==0)
            {
                if(board->b[i+1][j+1]==0 || board->b[i+1][j+1]==1 || board->b[i+1][j+1]==-1)
                    v.push_back(make_pair(i,j));
                else if(board->b[i+1][j+1]==-2 || board->b[i+1][j+1]==2)
                {
                    v.push_back(make_pair(i,j));
                    break;
                }
            }
            else if(board->b[i][j]==1 || board->b[i][j]==-1)//ring encounter
                break;
        }
        i--;
        j--;
    }
    return v;
}

string GamePlay::nextMove()
{

    int x, y;
    if((curboard->myringpos.size()+curboard->myringout)<startring){
         while(true){
            if(curboard->myringpos.size()>3){
                if(curboard->oppringpos.size()==0){
                    x = size-1; y = 2*size-1;
                    if(curboard->b[x][y]==0) break;    
                }
                else{
                    if(curboard->oppringpos.size()>0)
                    {    auto op = curboard->oppringpos[curboard->oppringpos.size()-1];
                        int a = op.first;
                        int b = op.second;
                        x = a-1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a-1; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b+1;
                    }    if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                    if(curboard->oppringpos.size()>1)
                    {   auto op = curboard->oppringpos[curboard->oppringpos.size()-2];
                        int a = op.first;
                        int b = op.second;
                        x = a-1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a-1; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                    }
                    if(curboard->oppringpos.size()>2)
                    {   auto op = curboard->oppringpos[curboard->oppringpos.size()-3];
                        int a = op.first;
                        int b = op.second;
                        x = a-1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a-1; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                    }
                    if(curboard->oppringpos.size()>3)
                    {   auto op = curboard->oppringpos[curboard->oppringpos.size()-4];
                        int a = op.first;
                        int b = op.second;
                        x = a-1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a-1; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                    }
                    if(curboard->oppringpos.size()>4)
                    {   auto op = curboard->oppringpos[curboard->oppringpos.size()-5];
                        int a = op.first;
                        int b = op.second;
                        x = a-1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a-1; y = b-1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                        x = a+1; y = b+1;
                        if(x>=0 && y>=0 && x<=2*size && x<=2*size && curboard->b[x][y]==0) break;
                    }

                }
            }

            else{
             if(curboard->b[size][size]==-1){
                x = size-1; y = 2*size-1;
                if(curboard->b[x][y]==0) break;
                x = size-2; y = 2*size-2;
                if(curboard->b[x][y]==0) break;
                x = size-3; y = 2*size-3;
                if(curboard->b[x][y]==0) break;
                x = size-4; y = 2*size-4;
                if(curboard->b[x][y]==0) break;
                x = size-5; y = 2*size-4;
                if(curboard->b[x][y]==0) break;
                x = 0; y = 3;
                if(curboard->b[x][y]==0) break;
                x = 0; y = 2;
                if(curboard->b[x][y]==0) break;
                x = 0; y = 1;
                if(curboard->b[x][y]==0) break;
                x = 4; y = 5;
                if(curboard->b[x][y]==0) break;
                x = 6; y = 10;
                if(curboard->b[x][y]==0) break;  
             }
             else{
                x = 5; y = 5;
                if(curboard->b[x][y]==0) break;
                x = 6; y = 5;
                if(curboard->b[x][y]==0) break;
                x = 6; y = 6;
                if(curboard->b[x][y]==0) break;
                x = 5; y = 6;
                if(curboard->b[x][y]==0) break;
                x = 4; y = 6;
                if(curboard->b[x][y]==0) break;
                x = 4; y = 5;
                if(curboard->b[x][y]==0) break;
                x = 4; y = 4;
                if(curboard->b[x][y]==0) break;
                x = 5; y = 4;
                if(curboard->b[x][y]==0) break;
                x = 4; y = 5;
                if(curboard->b[x][y]==0) break;
                x = 6; y = 10;
                if(curboard->b[x][y]==0) break;
             }}
         }
         pair<int, int> hp = coordinatebackConversion(x,y);
        //  pair<int, int> hp = make_pair(x,y);        
         return "P "+to_string(hp.first)+" "+ to_string(hp.second);
    }
    else{
        return miniMax(this->curboard, 1);
        // return miniMaxAlt();
    }

}
string GamePlay::miniMaxAlt()
{
    vector<string> list= neighbours(curboard,true);
    int maxeval=-10000;
    string move="";
    // cerr<<"--------------------NEIGHBOURS CALCULATED"<<endl;
    for(auto l:list)
    {
        Board* newb;
        newb=curboard->copyBoard();
        ChangeBoard(true,newb,l);
        int score=calcEval(newb);
        // cerr<<"------------------"<<score<<endl;

        if(score>maxeval)
        {
            maxeval=score;
            move=l;
        }
    }
    // cerr<<"for loop finished ->"<<move<<endl;
    return move;
}
string GamePlay::miniMax(Board* board, int depth){
    // cerr<<"minimax starts"<<"\n";
    pair<int, string> posvalue;

    posvalue = maxValue(board, -INT_MAX, +INT_MAX, depth);
    vector<string> neighbours = GamePlay::neighbours(board, false);
    // for (string n : neighbours) {
    //     cerr<<n<<endl;
    // }
    // cerr<<"-----------------------CHANGE"<<endl;
    // neighbours = GamePlay::neighbours(board, true);
    // for (string n : neighbours) {
    //     cerr<<n<<endl;
    // }
    cerr<<"-----------------------Eval="<<posvalue.first<<endl;
    cerr<<"my ring out"<<board->myringout<<endl;
    cerr<<"opp ring out"<<board->oppringout<<endl;
    return posvalue.second;
}
// pair<int, string> GamePlay::maxValue(Board* board, int alpha, int beta, int depth){
//     // cerr<<"---------------- at level"<<depth<<"\n";
//     if(depth>=4){
//         // Board* newboard = board->flipBoard();
//         string s = "";
//         return make_pair(0, s);
//     }
//     int posValue = -INT_MAX;
//     string move;
//     vector<string> neighbours = GamePlay::neighbours(board, true);
//     int hi=0;
//     for (string n : neighbours) {
//         Board* newboard = board->copyBoard();
//         ChangeBoard(true, newboard, n);
//         newboard = newboard->flipBoard(); 
//         pair<int, string> newValue = maxValue(newboard, alpha, beta, depth+1);
//         // cerr<<n<<"--"<<hi<<"/"<<neighbours.size()<<"-----------"<<newValue.first<<endl;
//         string thismove=newValue.second;
//         if(thismove!="")
//         {
//             cerr<<n<<","<<newValue.second<<endl;
//             ChangeBoard(true,newboard,thismove);
//         }
//         newboard = newboard->flipBoard(); 
//         int ans=calcEval(newboard);
//         if ( ans > posValue ) {
//             posValue = ans;
//             move = n;
//         }                                               
//         hi++;
//     // alpha = max(alpha, newValue.first);
//     // if(alpha>=beta) return make_pair(posValue, move);
//     }
    
//   return make_pair(0, move);
// }
pair<int, string> GamePlay::maxValue(Board* board, int alpha, int beta, int depth){
    // cerr<<"---------------- at level"<<depth<<"\n";
    if(depth>=4){
        // Board* newboard = board->flipBoard();
        string s = "";
        return make_pair(calcEval(board), s);
    }
    float posValue = -INT_MAX;
    string move;
    vector<string> neigh = neighbours(board, true);
    // cerr<<"-----------------------------max"<<endl;
    // board->printBoard();
    int hi=0;
    for (string n : neigh) {
        Board* newboard = board->copyBoard();
        ChangeBoard(true, newboard, n);
        // newboard = newboard->flipBoard(); 
        pair<int, string> newValue = minValue(newboard, alpha, beta, depth+1);
        // cerr<<n<<"--"<<hi<<"/"<<neighbours.size()<<"-----------"<<newValue.first<<endl;
        // string thismove=newValue.second;
        // if(thismove!="")
        //     ChangeBoard(true,newboard,thismove);
        // newboard = newboard->flipBoard(); 
        // int ans=calcEval(newboard);
        // cerr<<"print"<<endl;
        // cerr<<n<<","<<newValue.second<<endl;
        if ( newValue.first > posValue ) {
            posValue = newValue.first;
            move = n;
        }                                               
        hi++;
    alpha = max(alpha, newValue.first);
    if(alpha>=beta) return make_pair(posValue, move);
    }
    
  return make_pair(posValue, move);
}
pair<int, string> GamePlay::minValue(Board* board, int alpha, int beta, int depth){
    // cerr<<"---------------- at level"<<depth<<"\n";
    if(depth>=4){
        string s ="";
        return make_pair(calcEval(board), s);
    }
    int posValue = INT_MAX;
    string move;
    vector<string> neigh = neighbours(board, false);
    // cerr<<"-----------------------------min"<<endl;
    // board->printBoard();
    for (string n : neigh) {
        
        Board* newboard = board->copyBoard();
        ChangeBoard(false, newboard, n);
        pair<int, string> newValue = maxValue(newboard, alpha, beta, depth+1);
        // cerr<<n<<"------         "<<newValue.first<<endl;
        if ( newValue.first < posValue ) {
            posValue = newValue.first;
            move = n;
        }
        beta = min(beta, newValue.first);
        if(alpha>=beta) return make_pair(posValue, move);
    }
  return make_pair(posValue, move);
}
int GamePlay::calcnayaEval(Board* board){
    vector<int> list = calcContinuous(board, true);
    vector<int> list2 = calcContinuous(board, false);
    //0
    int good = 0;

    // vector<float> wt {0,1,3,9,27,81,0.5,1.5,4.5,13.5,40.5};
    vector<float> wt {0,1,3,9,27,81,0.5,1.5,4.5,13.5,40.5};

    vector<float> wt2 (11,0);

    for(int i=0;i<11;i++){
        wt2[i]=wt[i]*20;
    }
    for(int i=0;i<6;i++){
        good+=list[i]*wt[i];
        good-=list2[i]*wt2[i];
    }
    for(int i=6;i<11;i++){
        good-=list[i]*wt[i];
        good+=list2[i]*wt2[i];
    }
    int myrings = board->myringout;
    int oprings = board->oppringout;
    if(myrings<3){
        good+=myrings*2000;
    }
    else good+=myrings*200000;

    if(oprings<3){
        good-=oprings*5000;
    }
    else good-=oprings*50000;
    // good += board->myringout*10000 - board->oppringout*50000;
    return good;
}
//markers weightage 1,3,9,27,81,81,...
//ring weightage 0,1,4,13,40,40,...
int GamePlay::calcEval(Board* board)
{

    int m;
    // m=2;
    int count = 0;
    int block=0;
    int goodness = 0;
    int n = 2*size+1;
    int start =0;
    bool vulner=false;
    // cout<<"B ->"<<goodness<<endl;
    // cerr<<"MY RING AND COUNTERSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<endl;
    for(int x=0;x<n;x++){
        int y=0;
        start=0;
        count=0;
        block=0;
        vulner=false;
        // cerr<<"line eq: x="<<x<<endl;
        while(y<n){
            if(board->b[x][y]==2 || board->b[x][y]==1){
                // cerr<<board->b[x][y]<<" ";
                if(count==0 && y-1>=0)
                {
                    if(board->b[x][y-1]!=0)
                        block++;
                    if(board->b[x][y-1]==-1)
                        vulner=true;
                }
                else if(count==0 && y-1<0)
                    block++;
                
                count++;
                if(board->b[x][y]==2)
                {
                    if(count==1){
                        goodness+=1;
                    }
                    else if(count==2){
                        // goodness+=4;
                        goodness+=5;
                    }
                    else if(count==3){
                        // goodness+=10;
                        goodness+=40;
                    }                
                    else if(count==4){
                        // goodness+=200;
                        goodness+=1000;
                    }
                    else if(count>=5){
                        // goodness+=5000;
                        goodness+=25000;
                    }
                }  
                if(board->b[x][y]==1)
                {
                    if(count==1){
                        goodness+=0;
                    }
                    else if(count==2){
                        goodness+=2;
                    }
                    else if(count==3){
                        // goodness+=5;
                        goodness+=20;
                    }                
                    else if(count==4){
                        // goodness+=100;
                        goodness+=500;
                    }
                    else if(count>=5){
                        // goodness+=2500;
                        goodness+=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness-=1;
                //     else if(count==3)
                //         goodness-=3;
                //     else if(count==4)
                //         goodness-=10;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness-=2;
                //     else if(count==3)
                //         goodness-=7;
                //     else if(count==4)
                //         goodness-=20;
                // }
                // if(board->b[x][y]==-1 && vulner==false)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // else if(vulner=true && board->b[x][y]!=-1)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // cerr<<endl;
                count=0;
                block=0;
                vulner=false;
            }
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness-=1;
        //         else if(count==3)
        //             goodness-=3;
        //         else if(count==4)
        //             goodness-=10;
        //     }
        //     // else if(block==2)//blocking 
        //     // {
        //     //     if(count==2)
        //     //         goodness-=2;
        //     //     else if(count==3)
        //     //         goodness-=7;
        //     //     else if(count==4)
        //     //         goodness-=20;
        //     // }
        // }

    }
    // cout<<"X+"<<goodness<<endl;
    for(int y=0;y<n;y++){
        int x=0;
        start=0;
        count=0;
        block=0;
        vulner=false;
        // cerr<<"line eq: y="<<y<<endl;
        while(x<n){
            if(board->b[x][y]==2 || board->b[x][y]==1){
                // cerr<<board->b[x][y]<<" ";
                if(count==0 && x-1>=0)
                {
                    if(board->b[x-1][y]!=0)
                        block++;
                    if(board->b[x-1][y]==-1)
                        vulner=true;
                }
                else if(count==0 && x-1<0)
                    block++;
                count++;
                if(board->b[x][y]==2)
                {
                    if(count==1){
                        goodness+=1;
                    }
                    else if(count==2){
                        // goodness+=4;
                        goodness+=5;
                    }
                    else if(count==3){
                        // goodness+=10;
                        goodness+=40;
                    }                
                    else if(count==4){
                        // goodness+=200;
                        goodness+=1000;
                    }
                    else if(count>=5){
                        // goodness+=5000;
                        goodness+=25000;
                    }
                }  
                if(board->b[x][y]==1)
                {
                    if(count==1){
                        goodness+=0;
                    }
                    else if(count==2){
                        goodness+=2;
                    }
                    else if(count==3){
                        // goodness+=5;
                        goodness+=20;
                    }                
                    else if(count==4){
                        // goodness+=100;
                        goodness+=500;
                    }
                    else if(count>=5){
                        // goodness+=2500;
                        goodness+=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness-=1;
                //     else if(count==3)
                //         goodness-=3;
                //     else if(count==4)
                //         goodness-=10;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness-=2;
                //     else if(count==3)
                //         goodness-=7;
                //     else if(count==4)
                //         goodness-=20;
                // }
                // if(board->b[x][y]==-1 && vulner==false)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // else if(vulner=true && board->b[x][y]!=-1)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // cerr<<endl;
                count=0;
                block=0;
                vulner=false;
            }
        x++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness-=1;
        //         else if(count==3)
        //             goodness-=3;
        //         else if(count==4)
        //             goodness-=10;
        //     }
        //     // else if(block==2)//blocking 
        //     // {
        //     //     if(count==2)
        //     //         goodness-=2;
        //     //     else if(count==3)
        //     //         goodness-=7;
        //     //     else if(count==4)
        //     //         goodness-=20;
        //     // }
        // }

    }
    // cout<<"Y+ ->"<<goodness<<endl;
    int startx = 1;
    int starty = 0;
    for(int i=size;i>=0;i--){  
        int x = i;
        int y = 0;
        startx=i;
        starty=0;
        count=0;
        block=0;
        vulner=false;
        // cerr<<"line eq: x-y="<<i<<endl;
        while(x<n&&y<n){
            if(board->b[x][y]==2 || board->b[x][y]==1){
                // cerr<<board->b[x][y]<<" ";
                if(count==0 && x-1>=0 && y-1>=0)
                {
                    if(board->b[x-1][y-1]!=0)
                        block++;
                    if(board->b[x-1][y-1]==-1)
                        vulner=true;
                }
                else if(count==0 && (x-1<0 || y-1<0))
                    block++;
                count++;
                if(board->b[x][y]==2)
                {
                    if(count==1){
                        goodness+=1;
                    }
                    else if(count==2){
                        // goodness+=4;
                        goodness+=5;
                    }
                    else if(count==3){
                        // goodness+=10;
                        goodness+=40;
                    }                
                    else if(count==4){
                        // goodness+=200;
                        goodness+=1000;
                    }
                    else if(count>=5){
                        // goodness+=5000;
                        goodness+=25000;
                    }
                }  
                if(board->b[x][y]==1)
                {
                    if(count==1){
                        goodness+=0;
                    }
                    else if(count==2){
                        goodness+=2;
                    }
                    else if(count==3){
                        // goodness+=5;
                        goodness+=20;
                    }                
                    else if(count==4){
                        // goodness+=100;
                        goodness+=500;
                    }
                    else if(count>=5){
                        // goodness+=2500;
                        goodness+=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness-=1;
                //     else if(count==3)
                //         goodness-=3;
                //     else if(count==4)
                //         goodness-=10;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness-=2;
                //     else if(count==3)
                //         goodness-=7;
                //     else if(count==4)
                //         goodness-=20;
                // }
                // if(board->b[x][y]==-1 && vulner==false)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // else if(vulner=true && board->b[x][y]!=-1)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // cerr<<endl;
                count=0;
                block=0;
                vulner=false;
            }
        x++;
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness-=1;
        //         else if(count==3)
        //             goodness-=3;
        //         else if(count==4)
        //             goodness-=10;
        //     }
        //     // else if(block==2)//blocking 
        //     // {
        //     //     if(count==2)
        //     //         goodness-=2;
        //     //     else if(count==3)
        //     //         goodness-=7;
        //     //     else if(count==4)
        //     //         goodness-=20;
        //     // }
        // }
    }
    // cout<<"D+ ->"<<goodness<<endl;
    for(int j=1;j<=size;j++){
        int x = 0;
        int y = j;
        startx=0;
        starty=j;
        count=0;
        block=0;
        vulner=false;
        // cerr<<"line eq: y-x="<<j<<endl;
        while(x<n&&y<n){
            if(board->b[x][y]==2 || board->b[x][y]==1){
                // cerr<<board->b[x][y]<<" ";
                if(count==0 && x-1>=0 && y-1>=0)
                {
                    if(board->b[x-1][y-1]!=0)
                        block++;
                    if(board->b[x-1][y-1]==-1)
                        vulner=true;
                }
                else if(count==0 && (x-1<0 || y-1<0))
                    block++;
                count++;
                if(board->b[x][y]==2)
                {
                    if(count==1){
                        goodness+=1;
                    }
                    else if(count==2){
                        // goodness+=4;
                        goodness+=5;
                    }
                    else if(count==3){
                        // goodness+=10;
                        goodness+=40;
                    }                
                    else if(count==4){
                        // goodness+=200;
                        goodness+=1000;
                    }
                    else if(count>=5){
                        // goodness+=5000;
                        goodness+=25000;
                    }
                }  
                if(board->b[x][y]==1)
                {
                    if(count==1){
                        goodness+=0;
                    }
                    else if(count==2){
                        goodness+=2;
                    }
                    else if(count==3){
                        // goodness+=5;
                        goodness+=20;
                    }                
                    else if(count==4){
                        // goodness+=100;
                        goodness+=500;
                    }
                    else if(count>=5){
                        // goodness+=2500;
                        goodness+=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness-=1;
                //     else if(count==3)
                //         goodness-=3;
                //     else if(count==4)
                //         goodness-=10;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness-=2;
                //     else if(count==3)
                //         goodness-=7;
                //     else if(count==4)
                //         goodness-=20;
                // }
                // if(board->b[x][y]==-1 && vulner==false)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // else if(vulner=true && board->b[x][y]!=-1)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                count=0;
                block=0;
                vulner=false;
                // cerr<<endl;
            }
        x++;
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness-=1;
        //         else if(count==3)
        //             goodness-=3;
        //         else if(count==4)
        //             goodness-=10;
        //     }
        //     // else if(block==2)//blocking 
        //     // {
        //     //     if(count==2)
        //     //         goodness-=2;
        //     //     else if(count==3)
        //     //         goodness-=7;
        //     //     else if(count==4)
        //     //         goodness-=20;
        //     // }
        // }
    }
    // cout<<"D++ ->"<<goodness<<endl;
    
    //// calculate opponents continuity
    // cerr<<"OPP RING AND COUNTERSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<endl;
    m=-2;
    count = 0;
    n = 2*size+1;
    start =0;
    for(int x=0;x<n;x++){
        int y=0;
        start=0;
        count=0;
        block=0;
        // cerr<<"line eq: x="<<x<<endl;
        while(y<n){
            if(board->b[x][y]==-2 || board->b[x][y]==-1){
                // if(count==0 && y-1>=0)
                // {
                //     if(board->b[x][y-1]!=0)
                //         block++;
                // }
                // else if(count==0 && y-1<0)
                //     block++;
                // cerr<<board->b[x][y]<<" ";
                count++;
                if(board->b[x][y]==-2)
                {
                    if(count==1){
                        goodness-=1;
                    }
                    else if(count==2){
                        goodness-=5;
                    }
                    else if(count==3){
                        goodness-=40;
                    }                
                    else if(count==4){
                        goodness-=1000;
                    }
                    else if(count>=5){
                        goodness-=25000;
                    }
                }  
                if(board->b[x][y]==-1)
                {
                    if(count==1){
                        goodness-=0;
                    }
                    else if(count==2){
                        goodness-=2;
                    }
                    else if(count==3){
                        goodness-=20;
                    }                
                    else if(count==4){
                        goodness-=500;
                    }
                    else if(count>=5){
                        goodness-=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness+=2;
                //     else if(count==3)
                //         goodness+=9;
                //     else if(count==4)
                //         goodness+=100;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness+=3;
                //     else if(count==3)
                //         goodness+=18;
                //     else if(count==4)
                //         goodness+=200;
                // }
                count=0;
                // cerr<<endl;
                block=0;
            }
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=2;
        //         else if(count==3)
        //             goodness+=9;
        //         else if(count==4)
        //             goodness+=100;
        //     }
        //     else if(block==2)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=3;
        //         else if(count==3)
        //             goodness+=18;
        //         else if(count==4)
        //             goodness+=200;
        //     }
        // }
    }
    // cout<<"X- ->"<<goodness<<endl;
    for(int y=0;y<n;y++){
        int x=0;
        start=0;
        count=0;
        block=0;
        // cerr<<"line eq: y="<<y<<endl;
        while(x<n){
            if(board->b[x][y]==-2 || board->b[x][y]==-1){
                // if(count==0 && x-1>=0)
                // {
                //     if(board->b[x-1][y]!=0)
                //         block++;
                // }
                // else if(count==0 && x-1<0)
                //     block++;
                // cerr<<board->b[x][y]<<" ";
                count++;
                if(board->b[x][y]==-2)
                {
                    if(count==1){
                        goodness-=1;
                    }
                    else if(count==2){
                        goodness-=5;
                    }
                    else if(count==3){
                        goodness-=40;
                    }                
                    else if(count==4){
                        goodness-=1000;
                    }
                    else if(count>=5){
                        goodness-=25000;
                    }
                }  
                if(board->b[x][y]==-1)
                {
                    if(count==1){
                        goodness-=0;
                    }
                    else if(count==2){
                        goodness-=2;
                    }
                    else if(count==3){
                        goodness-=20;
                    }                
                    else if(count==4){
                        goodness-=500;
                    }
                    else if(count>=5){
                        goodness-=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness+=2;
                //     else if(count==3)
                //         goodness+=9;
                //     else if(count==4)
                //         goodness+=100;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness+=3;
                //     else if(count==3)
                //         goodness+=18;
                //     else if(count==4)
                //         goodness+=200;
                // }
                // cerr<<endl;
                count=0;
                block=0;
            }
        x++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=2;
        //         else if(count==3)
        //             goodness+=9;
        //         else if(count==4)
        //             goodness+=100;
        //     }
        //     else if(block==2)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=3;
        //         else if(count==3)
        //             goodness+=18;
        //         else if(count==4)
        //             goodness+=200;
        //     }
        // }
    }
    // cout<<"Y- ->"<<goodness<<endl;
    startx = 0;
    starty = 0;
    for(int i=size;i>=0;i--){  
        int x = i;
        int y = 0;
        startx=i;
        starty=0;
        count=0;
        block=0;
        // cerr<<"line eq: x-y="<<i<<endl;
        while(x<n&&y<n){
            if(board->b[x][y]==-2 || board->b[x][y]==-1){
                // if(count==0 && x-1>=0 && y-1>=0)
                // {
                //     if(board->b[x-1][y]!=0)
                //         block++;
                // }
                // else if(count==0 && (x-1<0 || y-1<0))
                //     block++;
                // cerr<<board->b[x][y]<<" ";
                count++;
                if(board->b[x][y]==-2)
                {
                    if(count==1){
                        goodness-=1;
                    }
                    else if(count==2){
                        goodness-=5;
                    }
                    else if(count==3){
                        goodness-=40;
                    }                
                    else if(count==4){
                        goodness-=1000;
                    }
                    else if(count>=5){
                        goodness-=25000;
                    }
                }  
                if(board->b[x][y]==-1)
                {
                    if(count==1){
                        goodness-=0;
                    }
                    else if(count==2){
                        goodness-=2;
                    }
                    else if(count==3){
                        goodness-=20;
                    }                
                    else if(count==4){
                        goodness-=500;
                    }
                    else if(count>=5){
                        goodness-=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness+=2;
                //     else if(count==3)
                //         goodness+=9;
                //     else if(count==4)
                //         goodness+=100;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness+=3;
                //     else if(count==3)
                //         goodness+=18;
                //     else if(count==4)
                //         goodness+=200;
                // }
                // cerr<<endl;
                count=0;
                block=0;
            }
        x++;
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=2;
        //         else if(count==3)
        //             goodness+=9;
        //         else if(count==4)
        //             goodness+=100;
        //     }
        //     else if(block==2)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=3;
        //         else if(count==3)
        //             goodness+=18;
        //         else if(count==4)
        //             goodness+=200;
        //     }
        // }
    }
    // cout<<"D- ->"<<goodness<<endl;
    for(int j=1;j<=size;j++){
        int x = 0;
        int y = j;
        startx=0;
        starty=j;
        count=0;
        block=0;
        // cerr<<"line no. y-x="<<j<<endl;
        while(x<n&&y<n){
            if(board->b[x][y]==-2 || board->b[x][y]==-1){
                // if(count==0 && x-1>=0 && y-1>=0)
                // {
                //     if(board->b[x-1][y]!=0)
                //         block++;
                // }
                // else if(count==0 && (x-1<0 || y-1<0))
                //     block++;
                // cerr<<board->b[x][y]<<" ";
                count++;
                if(board->b[x][y]==-2)
                {
                    if(count==1){
                        goodness-=1;
                    }
                    else if(count==2){
                        goodness-=5;
                    }
                    else if(count==3){
                        goodness-=40;
                    }                
                    else if(count==4){
                        goodness-=1000;
                    }
                    else if(count>=5){
                        goodness-=25000;
                    }
                }  
                if(board->b[x][y]==-1)
                {
                    if(count==1){
                        goodness-=0;
                    }
                    else if(count==2){
                        goodness-=2;
                    }
                    else if(count==3){
                        goodness-=20;
                    }                
                    else if(count==4){
                        goodness-=500;
                    }
                    else if(count>=5){
                        goodness-=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness+=2;
                //     else if(count==3)
                //         goodness+=9;
                //     else if(count==4)
                //         goodness+=100;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness+=3;
                //     else if(count==3)
                //         goodness+=18;
                //     else if(count==4)
                //         goodness+=200;
                // }
                // cerr<<endl;
                count=0;
                block=0;
            }
        x++;
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=2;
        //         else if(count==3)
        //             goodness+=9;
        //         else if(count==4)
        //             goodness+=100;
        //     }
        //     else if(block==2)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=3;
        //         else if(count==3)
        //             goodness+=18;
        //         else if(count==4)
        //             goodness+=200;
        //     }
        // }
    }
    // cout<<"D-- ->"<<goodness<<endl;
    // int mof=oppflipsum(board);
    // if(mof==4 || mof==-4)
    //     goodness-=10000;
    // else if(mof==3 || mof==-3)
    //     goodness-=500;
    // else if(mof==2 || mof==-2)
    //     goodness-=100;

    // goodness-=50*oppflipsum(board);
    //// consider for gaining a ring out


    //-------------------------------------------------------------------------------
    // vector<int> v=totalOppRingClash(board);
    // goodness-=v[2]*14000;
    // goodness-=v[1]*700;
    // goodness-=v[0]*35;
    // v=totalMyRingClash(board);
    // goodness+=v[2]*14000;
    // goodness+=v[1]*700;
    // goodness+=v[0]*35;

    //-------------------------------------------------------------------------------

    // v=totalMarkerSpaceRing(board);
    // goodness-=v[2]*800;
    // goodness-=v[1]*40;
    // goodness-=v[0]*2;
    // v=totalOppMyOpp(board);
    // goodness-=v[2]*10000;
    // goodness-=v[1]*100;
    // goodness-=(totalMyRingClash(board)/(5-board->myringout))*400;

    goodness+=board->myringout*200000;
    // cout<<"Ring+ ->"<<goodness<<endl;
    goodness-=board->oppringout*200000;
    // cout<<"Ring- ->"<<goodness<<endl;
    return goodness;
    // return 1; 
}


vector<int> GamePlay::calcContinuous(Board* board, bool ismyturn){
    int m;
    if(ismyturn==true) m=2;
    else m=-2;
    int count = 0;
    vector<int> list(11,0);
    // vector<pair<pair<int, int>, pair<int, int> > > goodmarkers;
    int n = 2*size+1;
    // int start =0;
    int startx = 0;
    int starty = 0;
    int start = 0;
    
    for(int x=0;x<n;x++){
        int y=0;
        start=0;
        count=0;
        while(y<n){
            if(board->b[x][y]==(m/2)){
                count++;
                list[min(5+count,10)]++;
            }
            else if(board->b[x][y]!=m){
                for(int i=1;i<=min(count,5);i++)
                    list[i]++;
                if(count>5){
                    // goodmarkers.push_back(make_pair(make_pair(x,start),make_pair(x, y-1)));
                    // goodmarkers.push_back(make_pair(make_pair(x,y-5),make_pair(x, y-1)));
                    list[5]+=count-5;
                }
                count=0;
                start=y+1;
            }
            else{
                count++;
            }
        y++;
        }
        for(int i=1;i<=min(count,5);i++)
            list[i]++;
        if(count>5){
            // goodmarkers.push_back(make_pair(make_pair(x,start),make_pair(x, y-1)));
                    // goodmarkers.push_back(make_pair(make_pair(x,y-5),make_pair(x, y-1)));
                list[5]+=count-5;
            }
    }

    
    for(int y=0;y<n;y++){
        int x=0;
        start=0;
        count=0;
        while(x<n){
            if(board->b[x][y]==(m/2)){
                count++;
                list[min(5+count,10)]++;
            }
            else if(board->b[x][y]!=m){
                for(int i=1;i<=min(count,5);i++)
                    list[i]++;
                if(count>5){
                    // goodmarkers.push_back(make_pair(make_pair(start,y),make_pair(x-1, y)));
                    // goodmarkers.push_back(make_pair(make_pair(x-5,y),make_pair(x-1, y)));
                    list[5]+=count-5;
                }
                count=0;
                start=x+1;
            }
            else{
                count++;
            }
        x++;
        }
        for(int i=1;i<=min(count,5);i++)
            list[i]++;
        if(count>5){
            // goodmarkers.push_back(make_pair(make_pair(start,y),make_pair(x-1, y)));
                    // goodmarkers.push_back(make_pair(make_pair(x-5,y),make_pair(x-1, y)));
            list[5]+=count-5;
        }
        // else list[count]++;
    }
   
    for(int i=5;i>=0;i--){  
        int x = i;
        int y = 0;
        startx=i;
        starty=0;
        count=0;
        while(x<n&&y<n){
            if(board->b[x][y]==(m/2)){
                count++;
                list[min(5+count,10)]++;
            }
            else if(board->b[x][y]!=m){
                for(int i=1;i<=min(count,5);i++)
                    list[i]++;
                if(count>5){
                    // goodmarkers.push_back(make_pair(make_pair(startx,starty),make_pair(x-1, y-1)));
                    list[5]+=count-5;    
                }
                count=0;
                startx=x+1;
                starty=y+1;
            }
            else{
                count++;
            }
            x++;
            y++;
        }
        for(int i=1;i<=min(count,5);i++)
            list[i]++;
        if(count>5){
            list[5]+=count-5;
            // goodmarkers.push_back(make_pair(make_pair(startx,starty),make_pair(x-1, y-1)));
                    // goodmarkers.push_back(make_pair(make_pair(x-5,y-5),make_pair(x-1, y-1)));
        }
    }
    for(int j=1;j<=5;j++){
        int x = 0;
        int y = j;
        startx=0;
        starty=j;
        count=0;
        while(x<n&&y<n){
            if(board->b[x][y]==(m/2)){
                count++;
                list[min(5+count,10)]++;
            }
            else if(board->b[x][y]!=m){
                for(int i=1;i<=min(count,5);i++)
                    list[i]++;
                if(count>5){
                    // goodmarkers.push_back(make_pair(make_pair(startx,starty),make_pair(x-1, y-1)));
                    // goodmarkers.push_back(make_pair(make_pair(x-5,y-5),make_pair(x-1, y-1)));
                    list[5]+=count-5;
                }
                count=0;
                startx=x+1;
                starty=y+1;
            }
            else{
                count++;
            }
            x++;
            y++;
        }
        for(int i=1;i<=min(count,5);i++)
            list[i]++;
        if(count>5){
            // goodmarkers.push_back(make_pair(make_pair(startx,starty),make_pair(x-1, y-1)));
                    // goodmarkers.push_back(make_pair(make_pair(x-5,y-5),make_pair(x-1, y-1)));
            list[5]+=count-5;
        }
    }
    return list;
}
// int GamePlay::calcEval(Board* board)
// {

//     int m;
//     // m=2;
//     int count = 0;
//     int block=0;
//     int goodness = 0;
//     int n = 2*size+1;
//     int start =0;
//     bool vulner=false;
//     // cout<<"B ->"<<goodness<<endl;
//     // cerr<<"MY RING AND COUNTERSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<endl;
//     for(int x=0;x<n;x++){
//         int y=0;
//         start=0;
//         count=0;
//         block=0;
//         vulner=false;
//         // cerr<<"line eq: x="<<x<<endl;
//         while(y<n){
//             if(board->b[x][y]==2 || board->b[x][y]==1){
//                 // cerr<<board->b[x][y]<<" ";
//                 if(count==0 && y-1>=0)
//                 {
//                     if(board->b[x][y-1]!=0)
//                         block++;
//                     if(board->b[x][y-1]==-1)
//                         vulner=true;
//                 }
//                 else if(count==0 && y-1<0)
//                     block++;
                
//                 count++;
//                 if(board->b[x][y]==2)
//                 {
//                     if(count==1){
//                         goodness+=1;
//                     }
//                     else if(count==2){
//                         goodness+=5;
//                     }
//                     else if(count==3){
//                         goodness+=40;
//                     }                
//                     else if(count==4){
//                         goodness+=1000;
//                     }
//                     else if(count>=5){
//                         goodness+=25000;
//                     }
//                 }  
//                 if(board->b[x][y]==1)
//                 {
//                     if(count==1){
//                         goodness+=0;
//                     }
//                     else if(count==2){
//                         goodness+=2;
//                     }
//                     else if(count==3){
//                         goodness+=20;
//                     }                
//                     else if(count==4){
//                         goodness+=500;
//                     }
//                     else if(count>=5){
//                         goodness+=12500;
//                     }
//                 }
//             }
//             else{
//                 // if(board->b[x][y]!=0 && count>0)
//                 //     block++;
//                 // if(block==1)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness-=1;
//                 //     else if(count==3)
//                 //         goodness-=3;
//                 //     else if(count==4)
//                 //         goodness-=10;
//                 // }
//                 // else if(block==2)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness-=2;
//                 //     else if(count==3)
//                 //         goodness-=7;
//                 //     else if(count==4)
//                 //         goodness-=20;
//                 // }
//                 // if(board->b[x][y]==-1 && vulner==false)
//                 // {
//                 //     if(count==4)
//                 //         goodness=-50;
//                 //     else if(count==3)
//                 //         goodness=-20;
//                 // }
//                 // else if(vulner=true && board->b[x][y]!=-1)
//                 // {
//                 //     if(count==4)
//                 //         goodness=-50;
//                 //     else if(count==3)
//                 //         goodness=-20;
//                 // }
//                 // cerr<<endl;
//                 count=0;
//                 block=0;
//                 vulner=false;
//             }
//         y++;
//         }

//     }
//     // cout<<"X+"<<goodness<<endl;
//     for(int y=0;y<n;y++){
//         int x=0;
//         start=0;
//         count=0;
//         block=0;
//         vulner=false;
//         // cerr<<"line eq: y="<<y<<endl;
//         while(x<n){
//             if(board->b[x][y]==2 || board->b[x][y]==1){
//                 // cerr<<board->b[x][y]<<" ";
//                 if(count==0 && x-1>=0)
//                 {
//                     if(board->b[x-1][y]!=0)
//                         block++;
//                     if(board->b[x-1][y]==-1)
//                         vulner=true;
//                 }
//                 else if(count==0 && x-1<0)
//                     block++;
//                 count++;
//                 if(board->b[x][y]==2)
//                 {
//                     if(count==1){
//                         goodness+=1;
//                     }
//                     else if(count==2){
//                         goodness+=5;
//                     }
//                     else if(count==3){
//                         goodness+=40;
//                     }                
//                     else if(count==4){
//                         goodness+=1000;
//                     }
//                     else if(count>=5){
//                         goodness+=25000;
//                     }
//                 }  
//                 if(board->b[x][y]==1)
//                 {
//                     if(count==1){
//                         goodness+=0;
//                     }
//                     else if(count==2){
//                         goodness+=2;
//                     }
//                     else if(count==3){
//                         goodness+=20;
//                     }                
//                     else if(count==4){
//                         goodness+=500;
//                     }
//                     else if(count>=5){
//                         goodness+=12500;
//                     }
//                 }
//             }
//             else{
//                 // if(board->b[x][y]!=0 && count>0)
//                 //     block++;
//                 // if(block==1)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness-=1;
//                 //     else if(count==3)
//                 //         goodness-=3;
//                 //     else if(count==4)
//                 //         goodness-=10;
//                 // }
//                 // else if(block==2)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness-=2;
//                 //     else if(count==3)
//                 //         goodness-=7;
//                 //     else if(count==4)
//                 //         goodness-=20;
//                 // }
//                 // if(board->b[x][y]==-1 && vulner==false)
//                 // {
//                 //     if(count==4)
//                 //         goodness=-50;
//                 //     else if(count==3)
//                 //         goodness=-20;
//                 // }
//                 // else if(vulner=true && board->b[x][y]!=-1)
//                 // {
//                 //     if(count==4)
//                 //         goodness=-50;
//                 //     else if(count==3)
//                 //         goodness=-20;
//                 // }
//                 // cerr<<endl;
//                 count=0;
//                 block=0;
//                 vulner=false;
//             }
//         x++;
//         }
//         // if(count>0)
//         // {
//         //     block++;
//         //     if(block==1)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness-=1;
//         //         else if(count==3)
//         //             goodness-=3;
//         //         else if(count==4)
//         //             goodness-=10;
//         //     }
//         //     // else if(block==2)//blocking 
//         //     // {
//         //     //     if(count==2)
//         //     //         goodness-=2;
//         //     //     else if(count==3)
//         //     //         goodness-=7;
//         //     //     else if(count==4)
//         //     //         goodness-=20;
//         //     // }
//         // }

//     }
//     // cout<<"Y+ ->"<<goodness<<endl;
//     int startx = 1;
//     int starty = 0;
//     for(int i=5;i>=0;i--){  
//         int x = i;
//         int y = 0;
//         startx=i;
//         starty=0;
//         count=0;
//         block=0;
//         vulner=false;
//         // cerr<<"line eq: x-y="<<i<<endl;
//         while(x<n&&y<n){
//             if(board->b[x][y]==2 || board->b[x][y]==1){
//                 // cerr<<board->b[x][y]<<endl;
//                 if(count==0 && x-1>=0 && y-1>=0)
//                 {
//                     if(board->b[x-1][y-1]!=0)
//                         block++;
//                     if(board->b[x-1][y-1]==-1)
//                         vulner=true;
//                 }
//                 else if(count==0 && (x-1<0 || y-1<0))
//                     block++;
//                 count++;
//                 if(board->b[x][y]==2)
//                 {
//                     if(count==1){
//                         goodness+=1;
//                     }
//                     else if(count==2){
//                         goodness+=5;
//                     }
//                     else if(count==3){
//                         goodness+=40;
//                     }                
//                     else if(count==4){
//                         goodness+=1000;
//                     }
//                     else if(count>=5){
//                         goodness+=25000;
//                     }
//                 }  
//                 if(board->b[x][y]==1)
//                 {
//                     if(count==1){
//                         goodness+=0;
//                     }
//                     else if(count==2){
//                         goodness+=2;
//                     }
//                     else if(count==3){
//                         goodness+=20;
//                     }                
//                     else if(count==4){
//                         goodness+=500;
//                     }
//                     else if(count>=5){
//                         goodness+=12500;
//                     }
//                 }
//             }
//             else{
//                 // if(board->b[x][y]!=0 && count>0)
//                 //     block++;
//                 // if(block==1)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness-=1;
//                 //     else if(count==3)
//                 //         goodness-=3;
//                 //     else if(count==4)
//                 //         goodness-=10;
//                 // }
//                 // else if(block==2)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness-=2;
//                 //     else if(count==3)
//                 //         goodness-=7;
//                 //     else if(count==4)
//                 //         goodness-=20;
//                 // }
//                 // if(board->b[x][y]==-1 && vulner==false)
//                 // {
//                 //     if(count==4)
//                 //         goodness=-50;
//                 //     else if(count==3)
//                 //         goodness=-20;
//                 // }
//                 // else if(vulner=true && board->b[x][y]!=-1)
//                 // {
//                 //     if(count==4)
//                 //         goodness=-50;
//                 //     else if(count==3)
//                 //         goodness=-20;
//                 // }
//                 // cerr<<endl;
//                 count=0;
//                 block=0;
//                 vulner=false;
//             }
//         x++;
//         y++;
//         }
//         // if(count>0)
//         // {
//         //     block++;
//         //     if(block==1)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness-=1;
//         //         else if(count==3)
//         //             goodness-=3;
//         //         else if(count==4)
//         //             goodness-=10;
//         //     }
//         //     // else if(block==2)//blocking 
//         //     // {
//         //     //     if(count==2)
//         //     //         goodness-=2;
//         //     //     else if(count==3)
//         //     //         goodness-=7;
//         //     //     else if(count==4)
//         //     //         goodness-=20;
//         //     // }
//         // }
//     }
//     // cout<<"D+ ->"<<goodness<<endl;
//     for(int j=1;j<=5;j++){
//         int x = 0;
//         int y = j;
//         startx=0;
//         starty=j;
//         count=0;
//         block=0;
//         vulner=false;
//         // cerr<<"line eq: y-x="<<j<<endl;
//         while(x<n&&y<n){
//             if(board->b[x][y]==2 || board->b[x][y]==1){
//                 // cerr<<board->b[x][y]<<" ";
//                 if(count==0 && x-1>=0 && y-1>=0)
//                 {
//                     if(board->b[x-1][y-1]!=0)
//                         block++;
//                     if(board->b[x-1][y-1]==-1)
//                         vulner=true;
//                 }
//                 else if(count==0 && (x-1<0 || y-1<0))
//                     block++;
//                 count++;
//                 if(board->b[x][y]==2)
//                 {
//                     if(count==1){
//                         goodness+=1;
//                     }
//                     else if(count==2){
//                         goodness+=5;
//                     }
//                     else if(count==3){
//                         goodness+=40;
//                     }                
//                     else if(count==4){
//                         goodness+=1000;
//                     }
//                     else if(count>=5){
//                         goodness+=25000;
//                     }
//                 }  
//                 if(board->b[x][y]==1)
//                 {
//                     if(count==1){
//                         goodness+=0;
//                     }
//                     else if(count==2){
//                         goodness+=2;
//                     }
//                     else if(count==3){
//                         goodness+=10;
//                     }                
//                     else if(count==4){
//                         goodness+=500;
//                     }
//                     else if(count>=5){
//                         goodness+=12500;
//                     }
//                 }
//             }
//             else{
//                 // if(board->b[x][y]!=0 && count>0)
//                 //     block++;
//                 // if(block==1)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness-=1;
//                 //     else if(count==3)
//                 //         goodness-=3;
//                 //     else if(count==4)
//                 //         goodness-=10;
//                 // }
//                 // else if(block==2)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness-=2;
//                 //     else if(count==3)
//                 //         goodness-=7;
//                 //     else if(count==4)
//                 //         goodness-=20;
//                 // }
//                 // if(board->b[x][y]==-1 && vulner==false)
//                 // {
//                 //     if(count==4)
//                 //         goodness=-50;
//                 //     else if(count==3)
//                 //         goodness=-20;
//                 // }
//                 // else if(vulner=true && board->b[x][y]!=-1)
//                 // {
//                 //     if(count==4)
//                 //         goodness=-50;
//                 //     else if(count==3)
//                 //         goodness=-20;
//                 // }
//                 count=0;
//                 block=0;
//                 vulner=false;
//                 // cerr<<endl;
//             }
//         x++;
//         y++;
//         }
//         // if(count>0)
//         // {
//         //     block++;
//         //     if(block==1)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness-=1;
//         //         else if(count==3)
//         //             goodness-=3;
//         //         else if(count==4)
//         //             goodness-=10;
//         //     }
//         //     // else if(block==2)//blocking 
//         //     // {
//         //     //     if(count==2)
//         //     //         goodness-=2;
//         //     //     else if(count==3)
//         //     //         goodness-=7;
//         //     //     else if(count==4)
//         //     //         goodness-=20;
//         //     // }
//         // }
//     }
//     // cout<<"D++ ->"<<goodness<<endl;
    
//     //// calculate opponents continuity
//     // cerr<<"OPP RING AND COUNTERSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<endl;
//     m=-2;
//     count = 0;
//     n = 2*size+1;
//     start =0;
//     for(int x=0;x<n;x++){
//         int y=0;
//         start=0;
//         count=0;
//         block=0;
//         // cerr<<"line eq: x="<<x<<endl;
//         while(y<n){
//             if(board->b[x][y]==-2 || board->b[x][y]==-1){
//                 // if(count==0 && y-1>=0)
//                 // {
//                 //     if(board->b[x][y-1]!=0)
//                 //         block++;
//                 // }
//                 // else if(count==0 && y-1<0)
//                 //     block++;
//                 // cerr<<board->b[x][y]<<" ";
//                 count++;
//                 if(board->b[x][y]==-2)
//                 {
//                     if(count==1){
//                         goodness-=1;
//                     }
//                     else if(count==2){
//                         goodness-=5;
//                     }
//                     else if(count==3){
//                         goodness-=40;
//                     }                
//                     else if(count==4){
//                         goodness-=1000;
//                     }
//                     else if(count>=5){
//                         goodness-=25000;
//                     }
//                 }  
//                 if(board->b[x][y]==-1)
//                 {
//                     if(count==1){
//                         goodness-=0;
//                     }
//                     else if(count==2){
//                         goodness-=2;
//                     }
//                     else if(count==3){
//                         goodness-=20;
//                     }                
//                     else if(count==4){
//                         goodness-=500;
//                     }
//                     else if(count>=5){
//                         goodness-=-12500;
//                     }
//                 }
//             }
//             else{
//                 // if(board->b[x][y]!=0 && count>0)
//                 //     block++;
//                 // if(block==1)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness+=2;
//                 //     else if(count==3)
//                 //         goodness+=9;
//                 //     else if(count==4)
//                 //         goodness+=100;
//                 // }
//                 // else if(block==2)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness+=3;
//                 //     else if(count==3)
//                 //         goodness+=18;
//                 //     else if(count==4)
//                 //         goodness+=200;
//                 // }
//                 count=0;
//                 // cerr<<endl;
//                 block=0;
//             }
//         y++;
//         }
//         // if(count>0)
//         // {
//         //     block++;
//         //     if(block==1)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness+=2;
//         //         else if(count==3)
//         //             goodness+=9;
//         //         else if(count==4)
//         //             goodness+=100;
//         //     }
//         //     else if(block==2)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness+=3;
//         //         else if(count==3)
//         //             goodness+=18;
//         //         else if(count==4)
//         //             goodness+=200;
//         //     }
//         // }
//     }
//     // cout<<"X- ->"<<goodness<<endl;
//     for(int y=0;y<n;y++){
//         int x=0;
//         start=0;
//         count=0;
//         block=0;
//         // cerr<<"line eq: y="<<y<<endl;
//         while(x<n){
//             if(board->b[x][y]==-2 || board->b[x][y]==-1){
//                 // if(count==0 && x-1>=0)
//                 // {
//                 //     if(board->b[x-1][y]!=0)
//                 //         block++;
//                 // }
//                 // else if(count==0 && x-1<0)
//                 //     block++;
//                 // cerr<<board->b[x][y]<<" ";
//                 count++;
//                 if(board->b[x][y]==-2)
//                 {
//                     if(count==1){
//                         goodness-=1;
//                     }
//                     else if(count==2){
//                         goodness-=5;
//                     }
//                     else if(count==3){
//                         goodness-=40;
//                     }                
//                     else if(count==4){
//                         goodness-=1000;
//                     }
//                     else if(count>=5){
//                         goodness-=25000;
//                     }
//                 }  
//                 if(board->b[x][y]==-1)
//                 {
//                     if(count==1){
//                         goodness-=0;
//                     }
//                     else if(count==2){
//                         goodness-=2;
//                     }
//                     else if(count==3){
//                         goodness-=20;
//                     }                
//                     else if(count==4){
//                         goodness-=500;
//                     }
//                     else if(count>=5){
//                         goodness-=12500;
//                     }
//                 }
//             }
//             else{
//                 // if(board->b[x][y]!=0 && count>0)
//                 //     block++;
//                 // if(block==1)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness+=2;
//                 //     else if(count==3)
//                 //         goodness+=9;
//                 //     else if(count==4)
//                 //         goodness+=100;
//                 // }
//                 // else if(block==2)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness+=3;
//                 //     else if(count==3)
//                 //         goodness+=18;
//                 //     else if(count==4)
//                 //         goodness+=200;
//                 // }
//                 // cerr<<endl;
//                 count=0;
//                 block=0;
//             }
//         x++;
//         }
//         // if(count>0)
//         // {
//         //     block++;
//         //     if(block==1)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness+=2;
//         //         else if(count==3)
//         //             goodness+=9;
//         //         else if(count==4)
//         //             goodness+=100;
//         //     }
//         //     else if(block==2)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness+=3;
//         //         else if(count==3)
//         //             goodness+=18;
//         //         else if(count==4)
//         //             goodness+=200;
//         //     }
//         // }
//     }
//     // cout<<"Y- ->"<<goodness<<endl;
//     startx = 0;
//     starty = 0;
//     for(int i=5;i>=0;i--){  
//         int x = i;
//         int y = 0;
//         startx=i;
//         starty=0;
//         count=0;
//         block=0;
//         // cerr<<"line eq: x-y="<<i<<endl;
//         while(x<n&&y<n){
//             if(board->b[x][y]==-2 || board->b[x][y]==-1){
//                 // if(count==0 && x-1>=0 && y-1>=0)
//                 // {
//                 //     if(board->b[x-1][y]!=0)
//                 //         block++;
//                 // }
//                 // else if(count==0 && (x-1<0 || y-1<0))
//                 //     block++;
//                 // cerr<<board->b[x][y]<<" ";
//                 count++;
//                 if(board->b[x][y]==-2)
//                 {
//                     if(count==1){
//                         goodness-=1;
//                     }
//                     else if(count==2){
//                         goodness-=5;
//                     }
//                     else if(count==3){
//                         goodness-=40;
//                     }                
//                     else if(count==4){
//                         goodness-=1000;
//                     }
//                     else if(count>=5){
//                         goodness-=25000;
//                     }
//                 }  
//                 if(board->b[x][y]==-1)
//                 {
//                     if(count==1){
//                         goodness-=0;
//                     }
//                     else if(count==2){
//                         goodness-=2;
//                     }
//                     else if(count==3){
//                         goodness-=20;
//                     }                
//                     else if(count==4){
//                         goodness-=500;
//                     }
//                     else if(count>=5){
//                         goodness-=12500;
//                     }
//                 }
//             }
//             else{
//                 // if(board->b[x][y]!=0 && count>0)
//                 //     block++;
//                 // if(block==1)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness+=2;
//                 //     else if(count==3)
//                 //         goodness+=9;
//                 //     else if(count==4)
//                 //         goodness+=100;
//                 // }
//                 // else if(block==2)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness+=3;
//                 //     else if(count==3)
//                 //         goodness+=18;
//                 //     else if(count==4)
//                 //         goodness+=200;
//                 // }
//                 // cerr<<endl;
//                 count=0;
//                 block=0;
//             }
//         x++;
//         y++;
//         }
//         // if(count>0)
//         // {
//         //     block++;
//         //     if(block==1)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness+=2;
//         //         else if(count==3)
//         //             goodness+=9;
//         //         else if(count==4)
//         //             goodness+=100;
//         //     }
//         //     else if(block==2)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness+=3;
//         //         else if(count==3)
//         //             goodness+=18;
//         //         else if(count==4)
//         //             goodness+=200;
//         //     }
//         // }
//     }
//     // cout<<"D- ->"<<goodness<<endl;
//     for(int j=1;j<=5;j++){
//         int x = 0;
//         int y = j;
//         startx=0;
//         starty=j;
//         count=0;
//         block=0;
//         // cerr<<"line no. y-x="<<j<<endl;
//         while(x<n&&y<n){
//             if(board->b[x][y]==-2 || board->b[x][y]==-1){
//                 // if(count==0 && x-1>=0 && y-1>=0)
//                 // {
//                 //     if(board->b[x-1][y]!=0)
//                 //         block++;
//                 // }
//                 // else if(count==0 && (x-1<0 || y-1<0))
//                 //     block++;
//                 // cerr<<board->b[x][y]<<" ";
//                 count++;
//                 if(board->b[x][y]==-2)
//                 {
//                     if(count==1){
//                         goodness-=1;
//                     }
//                     else if(count==2){
//                         goodness-=5;
//                     }
//                     else if(count==3){
//                         goodness-=40;
//                     }                
//                     else if(count==4){
//                         goodness-=1000;
//                     }
//                     else if(count>=5){
//                         goodness-=25000;
//                     }
//                 }  
//                 if(board->b[x][y]==-1)
//                 {
//                     if(count==1){
//                         goodness-=0;
//                     }
//                     else if(count==2){
//                         goodness-=2;
//                     }
//                     else if(count==3){
//                         goodness-=20;
//                     }                
//                     else if(count==4){
//                         goodness-=500;
//                     }
//                     else if(count>=5){
//                         goodness-=12500;
//                     }
//                 }
//             }
//             else{
//                 // if(board->b[x][y]!=0 && count>0)
//                 //     block++;
//                 // if(block==1)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness+=2;
//                 //     else if(count==3)
//                 //         goodness+=9;
//                 //     else if(count==4)
//                 //         goodness+=100;
//                 // }
//                 // else if(block==2)//blocking 
//                 // {
//                 //     if(count==2)
//                 //         goodness+=3;
//                 //     else if(count==3)
//                 //         goodness+=18;
//                 //     else if(count==4)
//                 //         goodness+=200;
//                 // }
//                 // cerr<<endl;
//                 count=0;
//                 block=0;
//             }
//         x++;
//         y++;
//         }
//         // if(count>0)
//         // {
//         //     block++;
//         //     if(block==1)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness+=2;
//         //         else if(count==3)
//         //             goodness+=9;
//         //         else if(count==4)
//         //             goodness+=100;
//         //     }
//         //     else if(block==2)//blocking 
//         //     {
//         //         if(count==2)
//         //             goodness+=3;
//         //         else if(count==3)
//         //             goodness+=18;
//         //         else if(count==4)
//         //             goodness+=200;
//         //     }
//         // }
//     }
//     // cout<<"D-- ->"<<goodness<<endl;
//     // int mof=oppflipsum(board);
//     // if(mof==4 || mof==-4)
//     //     goodness-=10000;
//     // else if(mof==3 || mof==-3)
//     //     goodness-=500;
//     // else if(mof==2 || mof==-2)
//     //     goodness-=100;

//     // goodness-=50*oppflipsum(board);
//     //// consider for gaining a ring out
//     goodness+=board->myringout*200000;
//     // cout<<"Ring+ ->"<<goodness<<endl;
//     goodness-=board->oppringout*200000;
//     // cout<<"Ring- ->"<<goodness<<endl;
//     return goodness;
//     // return 1; 
// }

void GamePlay::printMarker(Board* board)
{

    int m;
    // m=2;
    int count = 0;
    int block=0;
    int goodness = 0;
    int n = 2*size+1;
    int start =0;
    bool vulner=false;
    // cout<<"B ->"<<goodness<<endl;
    cerr<<"MY RING AND COUNTERSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<endl;
    for(int x=0;x<n;x++){
        int y=0;
        start=0;
        count=0;
        block=0;
        vulner=false;
        cerr<<"line eq: x="<<x<<endl;
        while(y<n){
            if(board->b[x][y]==2 || board->b[x][y]==1){
                cerr<<board->b[x][y]<<" ";
                if(count==0 && y-1>=0)
                {
                    if(board->b[x][y-1]!=0)
                        block++;
                    if(board->b[x][y-1]==-1)
                        vulner=true;
                }
                else if(count==0 && y-1<0)
                    block++;
                
                count++;
                if(board->b[x][y]==2)
                {
                    if(count==1){
                        goodness+=1;
                    }
                    else if(count==2){
                        goodness+=4;
                    }
                    else if(count==3){
                        goodness+=10;
                    }                
                    else if(count==4){
                        goodness+=200;
                    }
                    else if(count>=5){
                        goodness+=5000;
                    }
                }  
                if(board->b[x][y]==1)
                {
                    if(count==1){
                        goodness+=0;
                    }
                    else if(count==2){
                        goodness+=2;
                    }
                    else if(count==3){
                        goodness+=5;
                    }                
                    else if(count==4){
                        goodness+=100;
                    }
                    else if(count>=5){
                        goodness+=2500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness-=1;
                //     else if(count==3)
                //         goodness-=3;
                //     else if(count==4)
                //         goodness-=10;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness-=2;
                //     else if(count==3)
                //         goodness-=7;
                //     else if(count==4)
                //         goodness-=20;
                // }
                // if(board->b[x][y]==-1 && vulner==false)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // else if(vulner=true && board->b[x][y]!=-1)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                cerr<<endl;
                count=0;
                block=0;
                vulner=false;
            }
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness-=1;
        //         else if(count==3)
        //             goodness-=3;
        //         else if(count==4)
        //             goodness-=10;
        //     }
        //     // else if(block==2)//blocking 
        //     // {
        //     //     if(count==2)
        //     //         goodness-=2;
        //     //     else if(count==3)
        //     //         goodness-=7;
        //     //     else if(count==4)
        //     //         goodness-=20;
        //     // }
        // }

    }
    // cout<<"X+"<<goodness<<endl;
    for(int y=0;y<n;y++){
        int x=0;
        start=0;
        count=0;
        block=0;
        vulner=false;
        cerr<<"line eq: y="<<y<<endl;
        while(x<n){
            if(board->b[x][y]==2 || board->b[x][y]==1){
                cerr<<board->b[x][y]<<" ";
                if(count==0 && x-1>=0)
                {
                    if(board->b[x-1][y]!=0)
                        block++;
                    if(board->b[x-1][y]==-1)
                        vulner=true;
                }
                else if(count==0 && x-1<0)
                    block++;
                count++;
                if(board->b[x][y]==2)
                {
                    if(count==1){
                        goodness+=1;
                    }
                    else if(count==2){
                        goodness+=4;
                    }
                    else if(count==3){
                        goodness+=10;
                    }                
                    else if(count==4){
                        goodness+=200;
                    }
                    else if(count>=5){
                        goodness+=5000;
                    }
                }  
                if(board->b[x][y]==1)
                {
                    if(count==1){
                        goodness+=0;
                    }
                    else if(count==2){
                        goodness+=2;
                    }
                    else if(count==3){
                        goodness+=5;
                    }                
                    else if(count==4){
                        goodness+=100;
                    }
                    else if(count>=5){
                        goodness+=2500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness-=1;
                //     else if(count==3)
                //         goodness-=3;
                //     else if(count==4)
                //         goodness-=10;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness-=2;
                //     else if(count==3)
                //         goodness-=7;
                //     else if(count==4)
                //         goodness-=20;
                // }
                // if(board->b[x][y]==-1 && vulner==false)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // else if(vulner=true && board->b[x][y]!=-1)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                cerr<<endl;
                count=0;
                block=0;
                vulner=false;
            }
        x++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness-=1;
        //         else if(count==3)
        //             goodness-=3;
        //         else if(count==4)
        //             goodness-=10;
        //     }
        //     // else if(block==2)//blocking 
        //     // {
        //     //     if(count==2)
        //     //         goodness-=2;
        //     //     else if(count==3)
        //     //         goodness-=7;
        //     //     else if(count==4)
        //     //         goodness-=20;
        //     // }
        // }

    }
    // cout<<"Y+ ->"<<goodness<<endl;
    int startx = 1;
    int starty = 0;
    for(int i=5;i>=0;i--){  
        int x = i;
        int y = 0;
        startx=i;
        starty=0;
        count=0;
        block=0;
        vulner=false;
        cerr<<"line eq: x-y="<<i<<endl;
        while(x<n&&y<n){
            if(board->b[x][y]==2 || board->b[x][y]==1){
                cerr<<board->b[x][y]<<" ";
                if(count==0 && x-1>=0 && y-1>=0)
                {
                    if(board->b[x-1][y-1]!=0)
                        block++;
                    if(board->b[x-1][y-1]==-1)
                        vulner=true;
                }
                else if(count==0 && (x-1<0 || y-1<0))
                    block++;
                count++;
                if(board->b[x][y]==2)
                {
                    if(count==1){
                        goodness+=1;
                    }
                    else if(count==2){
                        goodness+=4;
                    }
                    else if(count==3){
                        goodness+=10;
                    }                
                    else if(count==4){
                        goodness+=200;
                    }
                    else if(count>=5){
                        goodness+=5000;
                    }
                }  
                if(board->b[x][y]==1)
                {
                    if(count==1){
                        goodness+=0;
                    }
                    else if(count==2){
                        goodness+=2;
                    }
                    else if(count==3){
                        goodness+=5;
                    }                
                    else if(count==4){
                        goodness+=100;
                    }
                    else if(count>=5){
                        goodness+=2500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness-=1;
                //     else if(count==3)
                //         goodness-=3;
                //     else if(count==4)
                //         goodness-=10;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness-=2;
                //     else if(count==3)
                //         goodness-=7;
                //     else if(count==4)
                //         goodness-=20;
                // }
                // if(board->b[x][y]==-1 && vulner==false)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // else if(vulner=true && board->b[x][y]!=-1)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                cerr<<endl;
                count=0;
                block=0;
                vulner=false;
            }
        x++;
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness-=1;
        //         else if(count==3)
        //             goodness-=3;
        //         else if(count==4)
        //             goodness-=10;
        //     }
        //     // else if(block==2)//blocking 
        //     // {
        //     //     if(count==2)
        //     //         goodness-=2;
        //     //     else if(count==3)
        //     //         goodness-=7;
        //     //     else if(count==4)
        //     //         goodness-=20;
        //     // }
        // }
    }
    // cout<<"D+ ->"<<goodness<<endl;
    for(int j=1;j<=5;j++){
        int x = 0;
        int y = j;
        startx=0;
        starty=j;
        count=0;
        block=0;
        vulner=false;
        cerr<<"line eq: y-x="<<j<<endl;
        while(x<n&&y<n){
            if(board->b[x][y]==2 || board->b[x][y]==1){
                cerr<<board->b[x][y]<<" ";
                if(count==0 && x-1>=0 && y-1>=0)
                {
                    if(board->b[x-1][y-1]!=0)
                        block++;
                    if(board->b[x-1][y-1]==-1)
                        vulner=true;
                }
                else if(count==0 && (x-1<0 || y-1<0))
                    block++;
                count++;
                if(board->b[x][y]==2)
                {
                    if(count==1){
                        goodness+=1;
                    }
                    else if(count==2){
                        goodness+=4;
                    }
                    else if(count==3){
                        goodness+=10;
                    }                
                    else if(count==4){
                        goodness+=200;
                    }
                    else if(count>=5){
                        goodness+=5000;
                    }
                }  
                if(board->b[x][y]==1)
                {
                    if(count==1){
                        goodness+=0;
                    }
                    else if(count==2){
                        goodness+=2;
                    }
                    else if(count==3){
                        goodness+=5;
                    }                
                    else if(count==4){
                        goodness+=100;
                    }
                    else if(count>=5){
                        goodness+=2500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness-=1;
                //     else if(count==3)
                //         goodness-=3;
                //     else if(count==4)
                //         goodness-=10;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness-=2;
                //     else if(count==3)
                //         goodness-=7;
                //     else if(count==4)
                //         goodness-=20;
                // }
                // if(board->b[x][y]==-1 && vulner==false)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                // else if(vulner=true && board->b[x][y]!=-1)
                // {
                //     if(count==4)
                //         goodness=-50;
                //     else if(count==3)
                //         goodness=-20;
                // }
                count=0;
                block=0;
                vulner=false;
                cerr<<endl;
            }
        x++;
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness-=1;
        //         else if(count==3)
        //             goodness-=3;
        //         else if(count==4)
        //             goodness-=10;
        //     }
        //     // else if(block==2)//blocking 
        //     // {
        //     //     if(count==2)
        //     //         goodness-=2;
        //     //     else if(count==3)
        //     //         goodness-=7;
        //     //     else if(count==4)
        //     //         goodness-=20;
        //     // }
        // }
    }
    // cout<<"D++ ->"<<goodness<<endl;
    
    //// calculate opponents continuity
    cerr<<"OPP RING AND COUNTERSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<endl;
    m=-2;
    count = 0;
    n = 2*size+1;
    start =0;
    for(int x=0;x<n;x++){
        int y=0;
        start=0;
        count=0;
        block=0;
        cerr<<"line eq: x="<<x<<endl;
        while(y<n){
            if(board->b[x][y]==-2 || board->b[x][y]==-1){
                // if(count==0 && y-1>=0)
                // {
                //     if(board->b[x][y-1]!=0)
                //         block++;
                // }
                // else if(count==0 && y-1<0)
                //     block++;
                cerr<<board->b[x][y]<<" ";
                count++;
                if(board->b[x][y]==-2)
                {
                    if(count==1){
                        goodness-=1;
                    }
                    else if(count==2){
                        goodness-=5;
                    }
                    else if(count==3){
                        goodness-=40;
                    }                
                    else if(count==4){
                        goodness-=1000;
                    }
                    else if(count>=5){
                        goodness-=25000;
                    }
                }  
                if(board->b[x][y]==-1)
                {
                    if(count==1){
                        goodness-=0;
                    }
                    else if(count==2){
                        goodness-=2;
                    }
                    else if(count==3){
                        goodness-=20;
                    }                
                    else if(count==4){
                        goodness-=500;
                    }
                    else if(count>=5){
                        goodness-=-12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness+=2;
                //     else if(count==3)
                //         goodness+=9;
                //     else if(count==4)
                //         goodness+=100;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness+=3;
                //     else if(count==3)
                //         goodness+=18;
                //     else if(count==4)
                //         goodness+=200;
                // }
                count=0;
                cerr<<endl;
                block=0;
            }
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=2;
        //         else if(count==3)
        //             goodness+=9;
        //         else if(count==4)
        //             goodness+=100;
        //     }
        //     else if(block==2)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=3;
        //         else if(count==3)
        //             goodness+=18;
        //         else if(count==4)
        //             goodness+=200;
        //     }
        // }
    }
    // cout<<"X- ->"<<goodness<<endl;
    for(int y=0;y<n;y++){
        int x=0;
        start=0;
        count=0;
        block=0;
        cerr<<"line eq: y="<<y<<endl;
        while(x<n){
            if(board->b[x][y]==-2 || board->b[x][y]==-1){
                // if(count==0 && x-1>=0)
                // {
                //     if(board->b[x-1][y]!=0)
                //         block++;
                // }
                // else if(count==0 && x-1<0)
                //     block++;
                cerr<<board->b[x][y]<<" ";
                count++;
                if(board->b[x][y]==-2)
                {
                    if(count==1){
                        goodness-=1;
                    }
                    else if(count==2){
                        goodness-=5;
                    }
                    else if(count==3){
                        goodness-=40;
                    }                
                    else if(count==4){
                        goodness-=1000;
                    }
                    else if(count>=5){
                        goodness-=25000;
                    }
                }  
                if(board->b[x][y]==-1)
                {
                    if(count==1){
                        goodness-=0;
                    }
                    else if(count==2){
                        goodness-=2;
                    }
                    else if(count==3){
                        goodness-=20;
                    }                
                    else if(count==4){
                        goodness-=500;
                    }
                    else if(count>=5){
                        goodness-=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness+=2;
                //     else if(count==3)
                //         goodness+=9;
                //     else if(count==4)
                //         goodness+=100;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness+=3;
                //     else if(count==3)
                //         goodness+=18;
                //     else if(count==4)
                //         goodness+=200;
                // }
                cerr<<endl;
                count=0;
                block=0;
            }
        x++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=2;
        //         else if(count==3)
        //             goodness+=9;
        //         else if(count==4)
        //             goodness+=100;
        //     }
        //     else if(block==2)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=3;
        //         else if(count==3)
        //             goodness+=18;
        //         else if(count==4)
        //             goodness+=200;
        //     }
        // }
    }
    // cout<<"Y- ->"<<goodness<<endl;
    startx = 0;
    starty = 0;
    for(int i=5;i>=0;i--){  
        int x = i;
        int y = 0;
        startx=i;
        starty=0;
        count=0;
        block=0;
        cerr<<"line eq: x-y="<<i<<endl;
        while(x<n&&y<n){
            if(board->b[x][y]==-2 || board->b[x][y]==-1){
                // if(count==0 && x-1>=0 && y-1>=0)
                // {
                //     if(board->b[x-1][y]!=0)
                //         block++;
                // }
                // else if(count==0 && (x-1<0 || y-1<0))
                //     block++;
                cerr<<board->b[x][y]<<" ";
                count++;
                if(board->b[x][y]==-2)
                {
                    if(count==1){
                        goodness-=1;
                    }
                    else if(count==2){
                        goodness-=5;
                    }
                    else if(count==3){
                        goodness-=40;
                    }                
                    else if(count==4){
                        goodness-=1000;
                    }
                    else if(count>=5){
                        goodness-=25000;
                    }
                }  
                if(board->b[x][y]==-1)
                {
                    if(count==1){
                        goodness-=0;
                    }
                    else if(count==2){
                        goodness-=2;
                    }
                    else if(count==3){
                        goodness-=20;
                    }                
                    else if(count==4){
                        goodness-=500;
                    }
                    else if(count>=5){
                        goodness-=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness+=2;
                //     else if(count==3)
                //         goodness+=9;
                //     else if(count==4)
                //         goodness+=100;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness+=3;
                //     else if(count==3)
                //         goodness+=18;
                //     else if(count==4)
                //         goodness+=200;
                // }
                cerr<<endl;
                count=0;
                block=0;
            }
        x++;
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=2;
        //         else if(count==3)
        //             goodness+=9;
        //         else if(count==4)
        //             goodness+=100;
        //     }
        //     else if(block==2)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=3;
        //         else if(count==3)
        //             goodness+=18;
        //         else if(count==4)
        //             goodness+=200;
        //     }
        // }
    }
    // cout<<"D- ->"<<goodness<<endl;
    for(int j=1;j<=5;j++){
        int x = 0;
        int y = j;
        startx=0;
        starty=j;
        count=0;
        block=0;
        cerr<<"line no. y-x="<<j<<endl;
        while(x<n&&y<n){
            if(board->b[x][y]==-2 || board->b[x][y]==-1){
                // if(count==0 && x-1>=0 && y-1>=0)
                // {
                //     if(board->b[x-1][y]!=0)
                //         block++;
                // }
                // else if(count==0 && (x-1<0 || y-1<0))
                //     block++;
                cerr<<board->b[x][y]<<" ";
                count++;
                if(board->b[x][y]==-2)
                {
                    if(count==1){
                        goodness-=1;
                    }
                    else if(count==2){
                        goodness-=5;
                    }
                    else if(count==3){
                        goodness-=40;
                    }                
                    else if(count==4){
                        goodness-=1000;
                    }
                    else if(count>=5){
                        goodness-=25000;
                    }
                }  
                if(board->b[x][y]==-1)
                {
                    if(count==1){
                        goodness-=0;
                    }
                    else if(count==2){
                        goodness-=2;
                    }
                    else if(count==3){
                        goodness-=20;
                    }                
                    else if(count==4){
                        goodness-=500;
                    }
                    else if(count>=5){
                        goodness-=12500;
                    }
                }
            }
            else{
                // if(board->b[x][y]!=0 && count>0)
                //     block++;
                // if(block==1)//blocking 
                // {
                //     if(count==2)
                //         goodness+=2;
                //     else if(count==3)
                //         goodness+=9;
                //     else if(count==4)
                //         goodness+=100;
                // }
                // else if(block==2)//blocking 
                // {
                //     if(count==2)
                //         goodness+=3;
                //     else if(count==3)
                //         goodness+=18;
                //     else if(count==4)
                //         goodness+=200;
                // }
                cerr<<endl;
                count=0;
                block=0;
            }
        x++;
        y++;
        }
        // if(count>0)
        // {
        //     block++;
        //     if(block==1)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=2;
        //         else if(count==3)
        //             goodness+=9;
        //         else if(count==4)
        //             goodness+=100;
        //     }
        //     else if(block==2)//blocking 
        //     {
        //         if(count==2)
        //             goodness+=3;
        //         else if(count==3)
        //             goodness+=18;
        //         else if(count==4)
        //             goodness+=200;
        //     }
        // }
    }
    // cout<<"D-- ->"<<goodness<<endl;
    // int mof=oppflipsum(board);
    // if(mof==4 || mof==-4)
    //     goodness-=10000;
    // else if(mof==3 || mof==-3)
    //     goodness-=500;
    // else if(mof==2 || mof==-2)
    //     goodness-=100;

    // goodness-=50*oppflipsum(board);
    //// consider for gaining a ring out
    goodness+=board->myringout*200000;
    // cout<<"Ring+ ->"<<goodness<<endl;
    goodness-=board->oppringout*200000;
    // cout<<"Ring- ->"<<goodness<<endl;
    return;
    // return 1; 
}

