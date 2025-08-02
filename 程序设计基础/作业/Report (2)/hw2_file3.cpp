#include <iostream>
using namespace std;

int leap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int non_leap[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int days[7] = { 0 };

bool isLeap(int n) {
	return n % 4 == 0 && n % 100 != 0 || n % 400 == 0;
}

int main() {
	int n;
	cin >> n;

	//1900??1??13?????????
	int start = 6;
	for (int i = 1900; i < 1900 + n; i++) {
		if (isLeap(i)) {
			for (int j = 0; j < 12; j++) {
				days[start]++;
				start = start + leap[j];
				start %= 7;
			}
		}
		else {
			for (int j = 0; j < 12; j++) {
				days[start]++;
				start = start + non_leap[j];
				start %= 7;
			}
		}
	}

	// cout << days[6] << " ";
	for (int i = 1; i < 7; i++) {
		cout << days[i] << " ";
	}
	cout << days[0] << endl;

	return 0;
}