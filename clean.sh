find . -name "*.o" | xargs rm
find . -name "moc_*" | xargs rm
rm Makefile
rm qrc_resources.cpp
rm TicTacToe