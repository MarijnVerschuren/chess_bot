cd lib
cmake --build build --clean-first --target chess_py
cd ..
cp lib/bin/chess_py.* console/chess/chess.so
