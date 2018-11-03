/* 
 * File:   Conference.h
 * Author: Kapil Thakkar
 *
 * Created on 9 August, 2015, 10:07 AM
 */

// #ifndef CONFERENCE_H
// #define	CONFERENCE_H

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

// #include "Track.h"

class Board {
private:
    // The size of Board
    

    // The 2D array representing points on yinsh board.

    // The number of rings taken out by player1 and player2
    
    
    //evaluation value of the board
    double eval;
    
public:
    int size;
    int myringout, oppringout;
    int **b;
    
    vector<pair<int,int> > myringpos;
    vector<pair<int,int> > oppringpos;

    Board();
    
    /**
     * Constructor for Board.
     * initialize the board to empty(0 everywhere)
     * @param size is the size of board.
     */
    Board(int size);
    
    
    
    void initialize(int size);
    Board* copyBoard();
    /**
     * @param x is the x coordinate.
     * @param y is the y coordinate.
     */
    void setMyRing(int x, int y);
    
    void setMyMarker(int x, int y);

    void setOppRing(int x, int y);
    
    void setOppMarker(int x, int y);

    void printBoard();
    int remove(int x, int y);;
    /**
     * Gets the value at point (x,y).
     * @return the number of parallel tracks.
     */
    int getValue(int x, int y);
    
    
    /**
     * returns the value after applying evaluation function.
     */
    // double evaluate();
    
    
    /**
     * Gets the number of papers in a session.
     * @return the number of papers in a session.
     */
    // int getPapersInSession();
    
    
    double getEval ( );
    Board* flipBoard();
    void setEval(double eval);
    /**
     * Gets the track at the specified index.
     * @param index is the index of the specified track.
     * @return the track
     */
    // Track getTrack(int index);
    
    // bool isSameConference(Conference *);
    // // bool isSameConferenceByScore(Conference *);
    // Conference * copyConf();
    // /**
    //  * Sets the paper in the specified slot to the given paper id.
    //  * @param trackIndex is the track index.
    //  * @param sessionIndex is the session index.
    //  * @param paperIndex is the paper index.
    //  * @param paperId is the id of the paper.
    //  */
    // void setPaper(int trackIndex, int sessionIndex, int paperIndex, int paperId);
    
    // int  getNumPapers();
    // void printConference(char *);
    // void printConferenceConsole();
};
	/* CONFERENCE_H */

