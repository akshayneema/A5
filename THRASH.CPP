vector<string> GamePlay::neighbours(Board* board, bool ismyturn){
    // cerr<<"outloop";
    vector<string> moves(0);
    Board *tempboard;
    // Board *preloopboard;
    string hey;
    auto precontlist = CheckContMarker(ismyturn, board);
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
                for (auto r: tempringsabell){
                    // cerr<<"b";
                    vector<pair<int, int> > list = neighbourPosition(tempboard, r.first, r.second);
                    for(auto mymove : list){
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
                
                for (auto r: tempringsabell){
                    // cerr<<"b";
                    vector<pair<int, int> > list = neighbourPosition(tempboard, r.first, r.second);
                    for(auto mymove : list){
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
