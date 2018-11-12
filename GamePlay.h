/* 
 * File:   SessionOrganizer.h
 * Author: Kapil Thakkar
 *
 */

// #ifndef SESSIONORGANIZER_H
// #define	SESSIONORGANIZER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <ctime>
#include "Board.h"

// #include "Track.h"
// #include "Session.h"

using namespace std;


/**
 * SessionOrganizer reads in a similarity matrix of papers, and organizes them
 * into sessions and tracks.
 * 
 * @author Kapil Thakkar
 *
 */
class GamePlay {
private:
    // double ** distanceMatrix;

    int size;
    int contmarker;
    int startring;
    int MAX_DEPTH;
    int wall;

    double processingTimeInMinutes ;
    // double tradeoffCoefficient ; // the tradeoff coefficient


public:
    GamePlay();
    GamePlay(int size, int contmarker);
    Board *curboard;
    
    
    /**
     * Read in the number of parallel tracks, papers in session, sessions
     * in a track, and the similarity matrix from the specified filename.
     * @param filename is the name of the file containing the matrix.
     * @return the similarity matrix.
     */
    //changes board configuration according to the opponent's move

    pair<int,int> coordinateConversion(int h, int p);
    pair<int, int> coordinatebackConversion(int x, int y);
    vector<string> moveVector(string move);
    void oppMove (Board* board, vector<string> v);
    void myMove (Board* board, vector<string> v);
    void ChangeBoard(bool ismyturn, Board* board, string move);
    vector<string> neighbours(Board* board, bool me);
    int maxoppflip(Board* board,int x,int y);

    int oppflipsum(Board* board);
    vector<pair<int,int> > neighbourPosition(Board* board, int x, int y);
    string nextMove();
    // vector<pair<int,int> > CheckContMarker(Board* board);
    // string miniMax(Board* curboard, int depth);
    vector<pair<pair<int, int>,pair<int, int> > > CheckContMarker( bool ismyturn, Board* board);
    
    vector<pair<pair<int, int>,pair<int, int> > > CheckContMarkerX( bool ismyturn, Board* board);
    vector<pair<pair<int, int>,pair<int, int> > > CheckContMarkerY( bool ismyturn, Board* board);
    vector<pair<pair<int, int>,pair<int, int> > > CheckContMarkerXY( bool ismyturn, Board* board);
    int calcEval(Board* curBoard);
        vector<int> calcContinuous(Board* curBoard, bool player);

    int calcpuranaEval(Board* board);
    int calcnayaEval(Board* board);


    //implements minimax to determine the next move
    string miniMaxAlt();
    pair<int, string> maxValue(Board* curboard, int alpha, int beta, int depth);
    pair<int, string> minValue(Board* curboard, int alpha, int beta, int depth);
    string miniMax(Board* curboard, int depth);
    void printMarker(Board* board);
    vector<int> myRingClash(Board* board,int x,int y);
    vector<int> totalMyRingClash(Board* board);
    vector<int> totalOppRingClash(Board* board);
    vector<int> ringClash(Board* board,int x,int y);
    vector<int > markerSpaceRing(Board* board, int x, int y);
    vector<int> totalMarkerSpaceRing(Board* board);
    vector<int> oppMyOpp(Board* board, int x, int y);
    vector<int> totalOppMyOpp(Board* board);
};


