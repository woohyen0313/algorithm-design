#include<iostream>
#include<algorithm>
using namespace std;

int main() {

	int board[9][9]= {
{-1, -1, 1, -1, -1, -1, -1, -1, -1},
{-1, -1, -1, -1, -1, 1, -1, 2, -1},
{1, -1, 2, -1, -1, -1, -1, 1, -1},
{-1, -1, -1, -1, 1, 2, -1, -1, -1},
{-1, 1, -1, 1, -1, -1, -1, -1, -1},
{-1, -1, -1, -1, -1, 2, 1, 2, -1},
{-1, 1, -1, -1, 1, -1, -1, -1, -1},
{-1, -1, -1, -1, -1, 1, -1, -1, -1},
{-1, -1, -1, -1, -1, -1, -1, -1, -1}
    };
	int dp[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 2) {
                dp[i][j] = -10;
            }
            else if(board[i][j]==-1){
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = board[i][j];
            }
        }
    }

    for (int i = 8; i >= 0; i--)
    {
        for (int j = 0; j <=8; j++)
        {
            if (board[i][j] != 2) {
                if (i + 1 > 8)dp[i][j] = dp[i][j] + dp[i][j - 1];
                else if (j - 1 < 0) dp[i][j] = dp[i][j] + dp[i + 1][j];
                else if (j - 1 < 0 && i + 1 > 8)dp[i][j] = 0;

                else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]) + dp[i][j];
            }
         }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << dp[i][j]<<" ";
        }
        cout << endl;
    }
	return 0;

}