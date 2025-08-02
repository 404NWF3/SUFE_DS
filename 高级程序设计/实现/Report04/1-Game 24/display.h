#ifndef DISPLAY_H
#define DISPLAY_H

#include "gwindow.h"
#include "gcolor.h"
#include <string>
#include "console.h"
#include "set.h"
#include "map.h"
#include "tokenscanner.h"

Map<std::string, std::string> createCardMap();
Map<int, Vector<int>> createLOCATIONMAP();
void initGraphics(std::string title);
void closeGraphics();
void displayBackGround(int xStart, int yStart, int columnWidth);
void displaySolutions(const Set<std::string> & resultStrings, int num);
void displayHandCards(const std::string & handCardsString, int num);
void displayCards(const std::string & cardsString, int xStart,
                  int yStart, int columnWidth);

#endif // DISPLAY_H
