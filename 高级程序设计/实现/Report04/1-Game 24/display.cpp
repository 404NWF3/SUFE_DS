
#include "display.h"

using namespace std;

/* Constants */

static const int WindowWidth = 970;
static const int WindowHeight = 768;
static const int STARTX = 50;
static const int STARTY = 80;
static const int OFFSETY = 110;
static const int COLUMNWIDTH = 80;
static const int CARDINTEVAL = 100;
static const int ROWINTEVAL = 500;
static const Map<string, string> CARDMAP = createCardMap();
static const Map<int, Vector<int>> LOCATIONMAP = createLOCATIONMAP();
static GWindow *gw;

#ifdef Q_OS_WIN
   static const string DIRECTORY = "res\\";
#else
   static const string DIRECTORY = "res//";
#endif

/* Implementation of the display functions */

Map<string, string> createCardMap(){
    Map<string, string> cardMap;
    cardMap.put("(", "openparenthesis");
    cardMap.put(")", "closeparenthesis");
    cardMap.put("+", "addition");
    cardMap.put("-", "subtraction");
    cardMap.put("*", "multiplication");
    cardMap.put("/", "division");
    return cardMap;
}

Map<int, Vector<int>> createLOCATIONMAP(){
    Map<int, Vector<int>> locationMap;
    locationMap.put(2,{3, 5, 330, 60, 140});
    locationMap.put(3,{7, 28, 650, 150, 140});
    locationMap.put(4,{11, 51, 970, 150, 200});
    locationMap.put(5,{15, 74, 1290, 150, 230});
    locationMap.put(6,{19, 97, 1610, 150, 247});
    return locationMap;
}

void initGraphics(string title){
    setConsoleWindowTitle(title);
    setConsoleLocation(getScreenWidth() / 2 + 100, getScreenHeight() / 3);
    gw = new GWindow(WindowWidth, WindowHeight);
    gw->setLocation(STARTX, STARTX);
    gw->setBackground(GColor::convertRGBToRGB(18,92,39));
    gw->clear();
    gw->setTitle(title);
    gw->setVisible(true);
    gw->setExitOnClose(true);
    gw->requestFocus();
}

void closeGraphics(){
    gw->close();
    delete gw;
}

void displaySolutions(const Set<string> & solutionsStrings, int num){
    gw->setColor("yellow");
    gw->setFont(QFont("Microsoft YaHei", 10, 75));
    int positionY = STARTY;
    string str;
    str.resize(static_cast<unsigned int>(LOCATIONMAP[num][1]), '-');
    if (!solutionsStrings.isEmpty()){
        gw->drawString(str + "        Solutions       " + str, 51, 165);
        for(string solutionString : solutionsStrings){
            solutionString = solutionString.substr(2, solutionString.size() - 4);
            cout << "  " << solutionString << endl;
            if (positionY > WindowHeight - 2 * OFFSETY){
                positionY = STARTY;
            }
            displayCards(solutionString, 50, positionY += OFFSETY, COLUMNWIDTH);
        }
    }
    else{
        cout << "No Solution!" << endl << endl;
        gw->drawString(str + "       No Solution!     " + str, 51, 180);
    }
}

void displayBackGround(int xStart, int yStart, int columnWidth){
    while(xStart < gw->getWidth() - columnWidth){
        gw->drawImage(DIRECTORY + "Background.jpg", xStart, yStart);
        xStart += columnWidth;
    }
}

void displayHandCards(const string & handCardsString, int num){
    gw->setSize(LOCATIONMAP[num][2], WindowHeight);
    gw->repaint();
    gw->clear();
    displayCards(handCardsString, LOCATIONMAP[num][3], 30, LOCATIONMAP[num][4]);
}

void displayCards(const string & cardsString, int xStart,
                  int yStart, int columnWidth){
    if (cardsString == "") return;
    displayBackGround(xStart, yStart, columnWidth);
    TokenScanner scanner(cardsString);
    scanner.ignoreWhitespace();
    Vector<string> fileNamePrefixs;
    while (scanner.hasMoreTokens()) {
        string displayToken = scanner.nextToken();
        fileNamePrefixs.add(CARDMAP.containsKey(displayToken) ?
                            CARDMAP[displayToken] : displayToken);
    }
    for(string prefix : fileNamePrefixs) {
        gw->drawImage(DIRECTORY + prefix + ".gif", xStart, yStart);
        xStart += columnWidth ;
        pause(CARDINTEVAL);
    }
    pause(ROWINTEVAL);
}


