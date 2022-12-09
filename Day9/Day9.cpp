
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

const int NUM_TAILS = 9;
using namespace std;

struct pos {
	int x, y;
};

pos knots[NUM_TAILS] = {};
vector<pos> visited;
int uniqueLocations = 0;



void checkIfNew(int tail) {
	for (int i = 0; i < visited.size(); i++) {
		pos p = visited.at(i);
		if (knots[tail].x == p.x && knots[tail].y == p.y) return;
	}
	visited.push_back(knots[tail]);
	uniqueLocations++;
}

void moveTail(pos* head, int curKnot) {
	int xDis = head->x - knots[curKnot].x;
	int yDis = head->y - knots[curKnot].y;
	if ((abs(xDis) + abs(yDis) > 2)) {
		knots[curKnot].x += (xDis > 0 ? 1 : -1);
		knots[curKnot].y += (yDis > 0 ? 1 : -1);
	}
	else if (abs(xDis) > 1) knots[curKnot].x += (xDis > 0 ? 1 : -1);
	else if (abs(yDis) > 1) knots[curKnot].y += (yDis > 0 ? 1 : -1);
	else return;
	if (curKnot == NUM_TAILS - 1) checkIfNew(NUM_TAILS - 1);
	if(curKnot + 1 < NUM_TAILS) moveTail(&knots[curKnot], curKnot + 1);
}

int main()
{
	fstream input("input.txt");
	if (!input.is_open()) return -23;
	string line;
	pos head = {0, 0};
	visited.push_back(head);
	uniqueLocations++;
	while (getline(input, line)) {
		char dir = line.at(0);
		int dis = stoi(line.substr(2, line.length() - 2));
		switch (dir) {
			case 'U': 
				for (int i = 0; i < dis; i++) {
					head.y--;
					moveTail(&head, 0);
				}
				break;
			case 'D': 
				for (int i = 0; i < dis; i++) {
					head.y++;
					moveTail(&head, 0);
				}
				break;
			case 'L': 
				for (int i = 0; i < dis; i++) {
					head.x--;
					moveTail(&head, 0);
				}
				break;
			case 'R': 
				for (int i = 0; i < dis; i++) {
					head.x++;
					moveTail(&head, 0);
				}
				break;
		}
	}
	cout << "Unique spots: " << uniqueLocations;
}

