#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int main() {
	int m, n;
	cin >> m >> n;
	int arr1[50][50];
	int dp[50][50];
	int check[50][50] = { 0, };
	vector<int>finder;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr1[i][j];
		}
	}
	cout << endl;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			dp[i][j] = arr1[i][j];
		}
	}


	for (int i = 1; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a, b, c;
			if (j - 1 < 0) {
				b = dp[i - 1][j];
				c = dp[i - 1][j + 1];
				dp[i][j] = arr1[i][j] + max(b, c);
				check[i][j] = max(arr1[i - 1][j], arr1[i - 1][j+1]);
			}
			else if (j >= n) {
				a = dp[i - 1][j - 1];
				b = dp[i - 1][j];
				dp[i][j] = arr1[i][j] + max( a, b);
				check[i][j] = max(arr1[i-1][j-1],arr1[i-1][j]);
			}
			else {
			a = dp[i - 1][j - 1];
			b = dp[i - 1][j];
			c = dp[i - 1][j + 1];

			dp[i][j] = arr1[i][j] + max({ a, b, c });
			check[i][j] = max({ arr1[i - 1][j - 1],arr1[i - 1][j],arr1[i-1][j+1] });
		}
		}
	}
	cout << "선택한 값들" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{


			cout << check[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl<<endl;
	cout << "최댓값을 저장하고 있는 dp테이블" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{

			if (i == m - 1) {
				finder.push_back(dp[i][j]);
			}
			cout << dp[i][j] << "  ";
		}
		cout << endl;
	}
	int findmax = *max_element(finder.begin(), finder.end());
	cout << endl << endl;
	cout << "최댓값: " << findmax << endl;

	return 0;

}