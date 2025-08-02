#include <iostream>
#include <vector>
using namespace std;

struct location {
    int row, col;
};

int main() {
    int a[3][4] = {{27, 12, 23, 56}, {37, 2, 56, 46}, {-12, -34, 56, 8}};
    // int a[3][4] = {{30, 25, 23, 56}, {12, 2, 6, 46}, {-12, -34, 16, 28}};
    int max = 0;
    vector<location> locations;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (a[i][j] == max) locations.push_back({i, j});
            if (a[i][j] > max) {
                max = a[i][j];
                locations.clear();
                //location l = { i, j };
                locations.push_back({i, j});
            }
        }
    }

    for (location l: locations) {
        cout << "max = " << max << ", row = " << l.row << ", column = " << l.col << endl;
    }

    return 0;
}
