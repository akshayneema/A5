#!/bin/bash

## This is to run the first program main.cpp
rm gamer
g++ -o gamer main.cpp Board.cpp GamePlay.cpp -std=c++14
cp gamer ../Yinsh-AI/
