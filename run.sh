#!/bin/bash

g++ -std=c++11 main.cpp


./a.out b_should_be_easy.in b &
BACK_PID1=$!


./a.out c_no_hurry.in c  &
BACK_PID2=$!


./a.out e_high_bonus.in e &
BACK_PID4=$!


./a.out d_metropolis.in d  &
BACK_PID3=$!


wait $BACK_PID1
wait $BACK_PID2
wait $BACK_PID3
wait $BACK_PID4
