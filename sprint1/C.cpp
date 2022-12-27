#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Dir {
	int x;
	int y;

	Dir(int a, int b) : x(a), y(b) {}; 
};

vector <int> GetNeighbours(const vector <vector <int> > &matrix, int row, int col) {

	vector<int> out = {};
	vector<Dir> directions = {Dir(0,+1), Dir(-1, 0), Dir(0,-1), Dir(+1,0)};

	for (auto dir : directions) {
		try{	int neighbour = matrix.at(row + dir.x).at(col + dir.y);
				out.push_back(neighbour); 								} catch(out_of_range const& exc) {}
	}

	sort(out.begin(), out.end());
	return out;
}

void print(const vector <int> &result) {
	for (int x : result)
		cout << x << " ";
	cout << endl;
}

int main() {
	int n, m;
	cin >> n >> m;
	vector <vector <int> > matrix(n, vector <int> (m));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> matrix[i][j];
	int row, col;
	cin >> row >> col;
	print(GetNeighbours(matrix, row, col));
}