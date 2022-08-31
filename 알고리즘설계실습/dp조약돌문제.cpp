#include<iostream>
#include<algorithm>
using namespace std;

int main() {

	int board[3][5] = { {1,2,3,4,5},
						{5,4,3,4,0},
						{2,2,6,4,0} };
	int dp[3][5];


	dp[0][0] = board[0][0];
	dp[1][0] = board[1][0];
	dp[2][0] = board[2][0];

	for (int j = 1; j < 5; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == 1) {
				dp[i][j] = max(dp[i - 1][j - 1], dp[i + 1][j - 1]) + board[i][j];
			}
			else if (i == 0) {
				dp[i][j] = dp[i + 1][j - 1] + board[i][j];
			}
			else if (i == 2) {
				dp[i][j] = dp[i -1][j - 1] + board[i][j];
			}
		}
		
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout<< dp[i][j]<<" ";
		}
		cout << endl;
	}
	return 0;
}