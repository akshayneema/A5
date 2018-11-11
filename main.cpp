/* 
 * File:   GamePlay.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "GamePlay.h"

/*
int main(){
    Board *b = new Board(5);
    GamePlay *g = new GamePlay(5);
    //b->printBoard();

    // g->ChangeBoard(true, g->curboard, "P 1 3");
    // g->ChangeBoard(true, g->curboard, "S 1 3 M 1 2");
    // //  g->ChangeBoard(true, g->curboard, "S 1 2 M 2 3 RS 1 3 RE 1 2 X 2 3");
    //  g->ChangeBoard(true, g->curboard, "S 1 2 M 2 3");
    //  g->ChangeBoard(false,g->curboard,"P 4 10");
    //  g->ChangeBoard(false,g->curboard,"S 4 10 M 2 7");
    //  g->ChangeBoard(false,g->curboard,"S 2 7 M 3 11");
    //  g->ChangeBoard(true, g->curboard,"P 2 11");

    // g->ChangeBoard(g->curboard, "S 2 3 M 2 7");
    // auto haven = g->neighbourPosition(g->curboard, 6, 7);
    // for(auto x: haven){
    //     cerr<<x.first<<" "<<x.second<<"\n";
    // }
    // g->curboard->printBoard();
    return 0;
}
*/

#include <iostream>

using namespace std;

// Sample C++ Code 
int main(int argc, char** argv) {
    

    
    int player_id, board_size, time_limit;
    string move;
    int s;
    cin >> player_id >> board_size >> time_limit >> s;
    cin.ignore();
    GamePlay *g = new GamePlay(board_size, s);
    // cout<<"chalu"<<endl;
    // test function for checking conversion
    
    // for(int i=0;i<5;i++){
    //     for(int j=0;j<i*6;j++){
    //         auto c = g->coordinateConversion(i, j);
    //         cout<<"h,p = ("<<i<<", "<<j<<")->("<<c.first<<", "<<c.second<<")"<<"\n";
    //     }
    // }
    
    // test function for checking neighbours

    // int h=0;
    // while(h<5){
    //         string mymove = g->nextMove();
    //         g->ChangeBoard(true, g->curboard, mymove);
    //         h++;
    // }
    // g->ChangeBoard(true, g->curboard,"P 2 11");
    // g->ChangeBoard(true, g->curboard, "P 1 3");
    // g->ChangeBoard(true, g->curboard, "S 1 3 M 0 0");
    // //  g->ChangeBoard(true, g->curboard, "S 1 2 M 2 3 RS 1 3 RE 1 2 X 2 3");
    //  g->ChangeBoard(true, g->curboard, "S 0 0 M 1 0");
    //  g->ChangeBoard(true, g->curboard, "S 1 0 M 2 0");
    //  g->ChangeBoard(true, g->curboard, "S 2 0 M 3 0");
    //  g->ChangeBoard(true, g->curboard, "S 3 0 M 4 0");
    

    //  g->curboard->printBoard();
     
    //  g->ChangeBoard(false,g->curboard,"P 4 10");
    //  g->ChangeBoard(false,g->curboard,"S 4 10 M 2 7");
    //  g->ChangeBoard(false,g->curboard,"S 2 7 M 3 11");
    
    // // g->ChangeBoard(g->curboard, "S 2 3 M 2 7");
    // g->curboard->printBoard();
    // vector<pair<int, int> > list = g->neighbourPosition(g->curboard, g->curboard->myringpos[0].first, g->curboard->myringpos[0].second);
    // cout<<list[0].first<<list[0].second;
    // for(auto x: g->curboard->myringpos){
    //     cout<<x.first<<" "<<x.second<<"\n";
    // }
    /********checking copyboard function
    Board* faltuboard;
    faltuboard = g->curboard->copyBoard();
    faltuboard->printBoard();
    ***/
   /*** checking cont marker function
    auto list = g->CheckContMarker(true,g->curboard);
    cout<<list.size()<<"\n";
    for(auto x:list){
        cout<<x.first.first<<x.first.second<<"\n";
                cout<<x.second.first<<x.second.second<<"\n";
    }
    ***/
    // auto list = g->neighbours(g->curboard,true);
    // cout<<list.size()<<"\n";
    // for(auto x:list){
    //     cout<<x<<"\n";
    // }
    // string s;
    // s=g->nextMove();
    // g->ChangeBoard(true, g->curboard, s);
    // cout<<"-----------"<<s<<"\n";
    // s=g->nextMove();
    // g->ChangeBoard(true, g->curboard, s);
    // cout<<"-----------"<<s<<"\n";
    // s=g->nextMove();
    // g->ChangeBoard(true, g->curboard, s);
    // cout<<"-----------"<<s<<"\n";
    // s=g->nextMove();
    // g->ChangeBoard(true, g->curboard, s);
    // cout<<"-----------"<<s<<"\n";

/////// rockboy /////////

// g->ChangeBoard(true, g->curboard, "P 1 4");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "P 0 0");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard, "P 1 5");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "P 1 3");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard, "P 2 6");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "P 2 8");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard, "P 2 7");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "P 6 21");g->curboard->printBoard();
// string yoda = g->nextMove();
// cerr<<yoda;


//////////////dieeeeeee////////////////////
// cerr<<"bwahaha";
// g->ChangeBoard(false, g->curboard, "P 1 2");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"P 5 9");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "P 2 8");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"P 4 21");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "P 4 13");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"P 4 18");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "P 3 10");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"P 3 2");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "P 4 11");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"P 2 10");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 3 10 M 2 5");g->curboard->printBoard();
// string mymove = g->nextMove();
// g->ChangeBoard(true, g->curboard,"S 5 9 M 5 8");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 1 2 M 1 3");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 4 21 M 5 27");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 1 3 M 1 0");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 4 18 M 4 19");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 1 0 M 3 16");g->curboard->printBoard();
// mymove = g->nextMove();
// g->ChangeBoard(true, g->curboard,"S 3 2 M 4 2");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 2 5 M 3 5");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 2 10 M 2 9");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 3 5 M 2 6");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 5 8 M 5 7");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 2 8 M 2 2");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 5 27 M 3 15");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 2 2 M 0 0");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 4 19 M 4 20");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 0 0 M 1 1");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 4 2 M 5 2");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 2 6 M 3 13");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 2 9 M 3 11");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 3 13 M 5 21");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 5 7 M 5 6");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 3 16 M 2 11");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 3 15 M 3 14");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 4 11 M 3 9");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 4 20 M 5 26");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 1 1 M 1 4");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 5 2 M 2 3");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 1 4 M 1 5");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 3 11 M 4 22");g->curboard->printBoard();
// g->ChangeBoard(false, g->curboard, "S 3 9 M 5 13");g->curboard->printBoard();
// g->ChangeBoard(true, g->curboard,"S 3 14 M 3 7 RS 4 19 RE 1 3 X 5 6");
// g->curboard->printBoard();
// vector<string> list=g->neighbours(g->curboard,true);
// for(auto l:list)
// {
//     cerr<<l<<endl;
// }

//////////////dieeeeeee////////////////////
// g->ChangeBoard(false,g->curboard, "P 2 4");
// g->ChangeBoard(true, g->curboard, "P 5 9");
// g->ChangeBoard(false,g->curboard, "P 1 4");
// g->ChangeBoard(true, g->curboard, "P 4 21");
// g->ChangeBoard(false,g->curboard, "P 5 29");
// g->ChangeBoard(true, g->curboard, "P 4 13");
// g->ChangeBoard(false,g->curboard, "P 1 0");
// g->ChangeBoard(true, g->curboard, "P 4 18");
// g->ChangeBoard(false,g->curboard, "P 4 10");
// g->ChangeBoard(true, g->curboard, "P 3 2");
// g->ChangeBoard(false,g->curboard, "S 1 0 M 0 0");
// g->ChangeBoard(true, g->curboard, "S 5 9 M 5 8");
// g->ChangeBoard(false,g->curboard, "S 1 4 M 1 5");
// g->ChangeBoard(true, g->curboard, "S 5 8 M 5 7");
// g->ChangeBoard(false,g->curboard, "S 5 29 M 2 11");
// g->ChangeBoard(true, g->curboard, "S 5 7 M 5 6");
// g->ChangeBoard(false,g->curboard, "S 4 10 M 2 8");
// g->ChangeBoard(true, g->curboard, "S 5 6 M 4 4");
// g->ChangeBoard(false,g->curboard, "S 2 4 M 2 5");
// g->ChangeBoard(true, g->curboard, "S 4 4 M 5 4");
// g->ChangeBoard(false,g->curboard, "S 2 5 M 4 1");
// g->ChangeBoard(true, g->curboard, "S 5 4 M 4 5");
// g->ChangeBoard(false,g->curboard, "S 1 5 M 3 13");
// g->ChangeBoard(true, g->curboard, "S 4 5 M 4 6");
// g->ChangeBoard(false,g->curboard, "S 2 8 M 2 7");
// g->ChangeBoard(true, g->curboard, "S 4 6 M 4 7");
// g->ChangeBoard(false,g->curboard, "S 2 7 M 3 4");
// g->ChangeBoard(true, g->curboard, "S 4 7 M 4 8");
// g->ChangeBoard(false,g->curboard, "S 3 4 M 3 3");
// g->ChangeBoard(true, g->curboard, "S 4 8 M 5 11");
// g->ChangeBoard(false,g->curboard, "S 4 1 M 1 1");
// g->ChangeBoard(true, g->curboard, "S 5 11 M 4 9 RS 5 11 RE 4 5 X 4 21");
// g->ChangeBoard(false,g->curboard, "S 1 1 M 2 1");
// g->ChangeBoard(true, g->curboard, "S 4 13 M 3 10");
// g->ChangeBoard(false,g->curboard, "S 0 0 M 2 0");
// g->ChangeBoard(true, g->curboard, "S 3 10 M 5 16");
// g->ChangeBoard(false,g->curboard, "S 2 0 M 3 1");
// g->ChangeBoard(true, g->curboard, "S 4 18 M 4 19");
// g->ChangeBoard(false,g->curboard, "S 3 13 M 3 14");
// g->ChangeBoard(true, g->curboard, "S 4 19 M 4 17");
// g->ChangeBoard(false,g->curboard, "S 2 11 M 2 10");
// g->ChangeBoard(true, g->curboard, "S 4 17 M 3 9");
// g->ChangeBoard(false,g->curboard, "RS 1 5 RE 4 13 X 3 3 S 2 1 M 1 5");
// g->ChangeBoard(true, g->curboard, "S 3 9 M 5 22");
// g->ChangeBoard(false,g->curboard, "S 1 5 M 2 9");
// g->ChangeBoard(true, g->curboard, "S 3 2 M 4 2");
// g->ChangeBoard(false,g->curboard, "S 3 1 M 1 2");
// g->ChangeBoard(true, g->curboard, "S 4 2 M 2 2");
// g->ChangeBoard(false,g->curboard, "S 2 10 M 5 28");
// g->ChangeBoard(true, g->curboard, "S 2 2 M 5 2");
// g->ChangeBoard(false,g->curboard, "RS 4 2 RE 2 10 X 2 9 S 5 28 M 2 9");
// g->ChangeBoard(true, g->curboard, "S 5 2 M 2 3");
// g->ChangeBoard(false,g->curboard, "S 3 14 M 3 1");
// g->ChangeBoard(true, g->curboard, "S 2 3 M 3 5");
// g->ChangeBoard(false,g->curboard, "S 3 1 M 2 0");
// g->ChangeBoard(true, g->curboard, "S 3 5 M 2 11");
// g->ChangeBoard(false,g->curboard, "S 2 0 M 3 17");
// g->ChangeBoard(true, g->curboard, "S 2 11 M 4 7");
// g->ChangeBoard(false,g->curboard, "S 3 17 M 1 4");
// g->curboard->printBoard();
// vector<string> list=g->neighbours(g->curboard,true);
// for(auto l:list)
// {
//     cout<<l<<endl;
// }
    ///give me some space
    // cerr<<"hi"<<endl;
// g->ChangeBoard(false,g->curboard,"P 0 0");
// g->ChangeBoard(true,g->curboard,"P 5 11");
// g->ChangeBoard(false,g->curboard,"P 4 22");
// g->ChangeBoard(true,g->curboard,"P 5 12");
// g->ChangeBoard(false,g->curboard,"P 4 9");
// g->ChangeBoard(true,g->curboard,"P 5 13");
// g->ChangeBoard(false,g->curboard,"P 4 1");
// g->ChangeBoard(true,g->curboard,"P 5 14");
// g->ChangeBoard(false,g->curboard,"P 2 11");
// g->ChangeBoard(true,g->curboard,"P 1 5");
// g->ChangeBoard(false,g->curboard,"S 0 0 M 1 0");
// g->ChangeBoard(true,g->curboard,"S 5 11 M 4 7");
// g->ChangeBoard(false,g->curboard,"S 4 9 M 1 3");
// g->ChangeBoard(true,g->curboard,"S 5 12 M 3 6");
// g->ChangeBoard(false,g->curboard,"S 1 0 M 2 0");
// g->ChangeBoard(true,g->curboard,"S 3 6 M 3 4");
// g->ChangeBoard(false,g->curboard,"S 2 0 M 3 0");
// g->ChangeBoard(true,g->curboard,"S 3 4 M 3 5");
// g->ChangeBoard(false,g->curboard,"S 1 3 M 4 5");
// g->ChangeBoard(true,g->curboard,"S 1 5 M 1 2");
// g->ChangeBoard(false,g->curboard,"S 4 1 M 1 1");
// g->ChangeBoard(true,g->curboard,"S 3 5 M 3 3 RS 5 12 RE 3 4 X 4 7");
// g->ChangeBoard(false,g->curboard,"S 1 1 M 1 4");
// g->ChangeBoard(true,g->curboard,"S 1 2 M 2 10");
// g->ChangeBoard(false,g->curboard,"S 1 4 M 2 7");
// g->ChangeBoard(true,g->curboard,"S 5 13 M 3 2");
// g->ChangeBoard(false,g->curboard,"S 4 22 M 2 1");
// g->ChangeBoard(true,g->curboard,"S 3 3 M 2 8");
// g->ChangeBoard(false,g->curboard,"S 2 11 M 3 1");
// g->ChangeBoard(true,g->curboard,"S 2 10 M 2 4");
// g->ChangeBoard(false,g->curboard,"S 3 0 M 3 16");
// g->ChangeBoard(true,g->curboard,"S 2 4 M 2 3");
// g->ChangeBoard(false,g->curboard,"S 4 5 M 4 8");
// g->ChangeBoard(true,g->curboard,"S 2 3 M 3 7");
// g->ChangeBoard(false,g->curboard,"S 4 8 M 3 15 RS 3 0 RE 1 3 X 3 15");
// g->ChangeBoard(true,g->curboard,"S 3 7 M 4 10");
// g->ChangeBoard(false,g->curboard,"S 2 1 M 2 5");
// g->ChangeBoard(true,g->curboard,"S 3 2 M 1 0");
// g->ChangeBoard(false,g->curboard,"S 2 5 M 4 9");
// g->ChangeBoard(true,g->curboard,"S 4 10 M 2 2");
// g->ChangeBoard(false,g->curboard,"S 2 7 M 1 3");
// g->ChangeBoard(true,g->curboard,"S 1 0 M 2 9");
// g->ChangeBoard(false,g->curboard,"S 3 1 M 5 7");
// g->ChangeBoard(true,g->curboard,"S 2 2 M 0 0");
// g->ChangeBoard(false,g->curboard,"S 5 7 M 5 6");
// g->ChangeBoard(true,g->curboard,"S 2 8 M 3 13");
// g->ChangeBoard(false,g->curboard,"S 5 6 M 3 4 RS 3 1 RE 5 7 X 4 9");
// g->ChangeBoard(true,g->curboard,"S 0 0 M 3 6 RS 2 8 RE 2 2 X 3 13");
// g->ChangeBoard(false,g->curboard,"S 1 3 M 1 4");
// g->ChangeBoard(true,g->curboard,"S 3 6 M 4 7");
// g->ChangeBoard(false,g->curboard,"S 1 4 M 1 1");
// g->ChangeBoard(true,g->curboard,"S 5 14 M 3 8");
// g->ChangeBoard(false,g->curboard,"S 3 4 M 4 9");
// g->ChangeBoard(true,g->curboard,"S 2 9 M 2 8");
// g->ChangeBoard(false,g->curboard,"S 1 1 M 3 1");
// g->ChangeBoard(true,g->curboard,"S 2 8 M 2 6"); 
// g->ChangeBoard(false,g->curboard,"S 3 1 M 4 5");
// g->ChangeBoard(true,g->curboard,"S 3 8 M 5 1");
// g->ChangeBoard(false,g->curboard,"S 4 5 M 3 11");
// g->curboard->printBoard();
// vector<string> str=g->neighbours(g->curboard,true);
// for(auto a: str)
//     cerr<<a<<endl;
// string stri=g->nextMove();
// cerr<<stri<<endl;
    if(player_id == 2) {
        // Get other player's move
        getline(cin, move); 
        g->ChangeBoard(false, g->curboard, move);

        while(true) {
            // g->curboard->printBoard();
            
            string mymove = g->nextMove();
             cout<<mymove<<"\n";
             
             cerr<<"-----------------------------My Move "<<mymove<<endl;
           g->ChangeBoard(true, g->curboard, mymove);
           
            // cerr<<"Player me"<<"\n";
            // cerr<<"int max---------------- "<<INT_MAX<<endl;
            g->curboard->printBoard();
            // g->printMarker(g->curboard);
            getline(cin, move); 
           
           cerr<<"-----------------------------Opp Move "<<move<<endl;
            g->ChangeBoard(false, g->curboard, move); 


            vector<int> list = g->calcContinuous(g->curboard, true);
            int hiii=0;
            for(auto x:list){
                cerr<<hiii<<":"<<x<<" ";
                hiii++;
            }
            vector<int> list2 = g->calcContinuous(g->curboard, false);
            hiii=0;
            for(auto x:list2){
                cerr<<hiii<<":"<<x<<" ";
                hiii++;
            }
           g->curboard->printBoard();
            // cerr<<"Player opp"<<"\n";
            // g->curboard->printBoard();

        }
    }   
    else if(player_id == 1) {
        while(true) {
            string mymove = g->nextMove();
            cout<<mymove<<"\n";
            // g->curboard->printBoard();
           
            cerr<<"-----------------------------My Move "<<mymove<<endl;
             g->ChangeBoard(true, g->curboard, mymove); 
            // cerr<<"Player me"<<"\n";
            // cerr<<"int max---------------- "<<INT_MAX<<endl;
            g->curboard->printBoard();
            // g->printMarker(g->curboard);
            getline(cin, move); 
           
           cerr<<"-----------------------------Opp Move "<<move<<endl;
            g->ChangeBoard(false, g->curboard, move);
            // cerr<<"Player opp"<<"\n";
            vector<int> list = g->calcContinuous(g->curboard, true);
            int hiii=0;
            for(auto x:list){
                cerr<<hiii<<":"<<x<<" ";
                hiii++;
            }
            vector<int> list2 = g->calcContinuous(g->curboard, false);
            hiii=0;
            for(auto x:list2){
                cerr<<hiii<<":"<<x<<" ";
                hiii++;
            }
            g->curboard->printBoard();
        }
    }
    return 0;
}
