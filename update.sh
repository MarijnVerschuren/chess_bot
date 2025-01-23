#!/bin/bash

cd lib
cmake --build build --clean-first --target chess_py -j 10
cd ..
cp lib/bin/chess_py.* console/chess/chess.so
