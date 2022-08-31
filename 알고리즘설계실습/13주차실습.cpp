#include<iostream>
#include<utility>
#include<algorithm>
using namespace std;

int main() {
	pair<int, int> input[7] = { {0,0} ,{ 5,5 }, { 10, 7 }, { 7, 10 }, { 3, 6 }, { 4, 8 },{ 11,20 } };

	int p[7][16] = {0,};
	p[0][0] = 0;

	for (int i = 1; i <= 6; i++)
	{
		for (int w = 1; w <= 15; w++)
		{
			if (input[i].first > i) p[i][w] = p[i - 1][w];
			else p[i][w] = max(p[i - 1][w], (input[i].second + p[i - 1][w - input[i].first]));
		}
	}
	cout << "입력1:" << p[6][15] << endl;


	pair<int, int> input1[9] = { {0,0} ,{ 3,5 }, { 7, 7 }, { 8, 10 }, { 5, 6 }, { 6, 8 },{ 13,20 },{11,18},{2,5} };

	int p1[9][31] = { 0, };


	for (int i = 1; i <= 8; i++)
	{
		for (int w = 1; w <= 30; w++)
		{
			if (input1[i].first > w) 	p1[i][w] = p1[i - 1][w];

			else 	p1[i][w] = max(p1[i - 1][w], (input1[i].second + p1[i - 1][w - input1[i].first]));

		}
	}
	cout << "입력2:" << p1[8][30];

	return 0;
}
