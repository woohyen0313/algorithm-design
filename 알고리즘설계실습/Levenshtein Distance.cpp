#define _CRT_SECURE_NO_WARINGS
#include<iostream>
#include<string>
#include<algorithm>
#include<stack>
#include<wchar.h>
#include<iomanip>
#include<cmath>
#define zzzz 0.001
using namespace std;

double dp[100][100];//다이나믹 프로그래밍중 이전값을 담는 배열

void EditDistance(char s[],char t[]) {//가중치가 없을 때의 함수

	int sl = sizeof(s)-1;
	int tl = sizeof(t)-1;
	for (int i = 1; i <= sl; i++)
	{
		dp[0][i] = i * 1;
	}
	for (int i = 1; i <= tl; i++)
	{
		dp[i][0] = i * 1;
	}

	for (int i = 1; i <= tl; i++)
	{
		for (int j = 1; j <= sl; j++)
		{
			double cost;
			if (s[j - 1] == t[i - 1]) cost = 0;
			else  cost = 1;

			dp[i][j] = min(dp[i][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i - 1][j - 1] + cost));
		}
	}

}
void EditDistance1(char  s[], char t[]) {//가중치가 다른 경우 최소비용을 구하는 함수이다.

	int sl = strlen(s);
	int tl = strlen(t);
	for (int i = 0; i <= sl; i++)//삭제에 관한 가중치를 배열에 채우는 반복문
	{
		dp[0][i] = i * 0.5;
	}
	for (int i = 0; i <= tl; i++)//삽입에 관한 가중치를 배열에 채우는 반복문
	{
		dp[i][0] = i * 0.7;
	}

	for (int i = 1; i <= tl; i++)
	{
		for (int j = 1; j <= sl; j++)
		{
			double cost;
			if (s[j - 1] == t[i - 1]) cost = 0; // 문자가 같을 때 가중치를 0으로 해주는 부분이다

			else cost = 0.3;//문자가 다를 때 가중치를 0.3으로 바꾸어 준다.

			dp[i][j] = min(dp[i][j - 1] + 0.5, min(dp[i - 1][j] + 0.7, dp[i - 1][j - 1] + cost)); //levenshtien알고리즘의 핵심적인 점화식을 코드로 작성한 부분이다.
		}
	}
}

void EditDistance2(wchar_t s[], wchar_t t[]) {//한글을 처리하기 위해 만든 함수로 위의 editdistance1함수와 로직은 동일하다.

	int sl = wcslen(s);
	int tl = wcslen(t);
	for (int i = 0; i <= sl; i++)
	{
		dp[0][i] = i * 0.5;
	}
	for (int i = 0; i <= tl; i++)
	{
		dp[i][0] = i * 0.7;
	}

	for (int i = 1; i <= tl; i++)
	{
		for (int j = 1; j <= sl; j++)
		{
			double cost;
			if (s[j - 1] == t[i - 1]) cost = 0;

			else cost = 0.3;
			dp[i][j] = min(dp[i][j - 1] + 0.5, min(dp[i - 1][j] + 0.7, dp[i - 1][j - 1] + cost));
		}
	}
}

void path1(char s[], char t[]) {//최단거리를 구했을때 어떤 편집이 발생하는지 확인하는 함수이다.

	stack<int> sta;
	int sl = strlen(s);
	int tl = strlen(t);

	while (sl > 0 && tl > 0) {
		int a;
		if ( abs(dp[tl][sl]- dp[tl - 1][sl - 1])<zzzz) {//대각선 방향과 현재위치를 비교한다.(zzzz를 사용한 이유는 부동소수점을 해결하기 위해서이다.)
			a = 0;
		}
		if (abs(dp[tl][sl] - 0.3-dp[tl - 1][sl - 1])<zzzz ) {//대각선 방향과 현재위치를 비교한다.
			a = 1;
		}
		if (abs(dp[tl][sl] - 0.5 - dp[tl][sl - 1])<zzzz ) {//왼쪽 방향과 현재위치를 비교한다. 
			a = 2;
		}
		if (abs(dp[tl][sl] - 0.7 - dp[tl - 1][sl])<zzzz ) {//위쪽 방향과 현재위치를 비교한다.
			a = 3;
		}

		if (dp[tl][sl - 1] < dp[tl - 1][sl - 1]) {// 위에서 정한 4가지 경우로만 할 경우 가중치가 같은경우가 생긴다 이를 방지하기위해 가중치를 더하지 않은 초기값이 더작은것을 우선으로 넣어주었다.
			if (abs(dp[tl][sl] - 0.5 - dp[tl][sl - 1]) < zzzz) {
				a = 2;
			}
		}
		if (dp[tl-1][sl] < dp[tl - 1][sl - 1]) {// 위에서 정한 4가지 경우로만 할 경우 가중치가 같은경우가 생긴다 이를 방지하기위해 가중치를 더하지 않은 초기값이 더작은것을 우선으로 넣어주었다.
			if (abs(dp[tl][sl] - 0.7 - dp[tl-1][sl]) < zzzz) {
				a = 3;
			}
		}
		if (a == 0) {//이후 각각 a에 맞게 sta에 넣어주었다. 이후 tl과 sl값을 최신화해주었다(이동한 위치로 초기화 해주었다.)
			sta.push(0);
			tl--;
			sl--;
		}
		else if (a == 1) {
			sta.push(1);
			tl--;
			sl--;
		}
		else if (a == 2) {
			sta.push(2);
			sl--;
		}	
		else if (a == 3) {
			sta.push(3);
			tl--;
		}
	}
		if (sl > 0) {
			for (int k = sl; k > 0; k--) {
				sta.push(2);
			}
		}
	
		else if (tl > 0) {
			for (int k = tl; k > 0; k--) {
				sta.push(3);
			}
		}
	
	while (!sta.empty()) {//stack에 넣은 값을 빼면서 편집한 순서대로 출력하였다.

		int a1 = sta.top();
		sta.pop();
		if (a1 == 1) cout << "변경: 0.3" <<endl;
		else if (a1 == 2) cout << "삭제: 0.5" << endl;
		else if (a1 == 3) cout << "삽입: 0.7" << endl;
	}

	cout << "최소편집거리" << dp[strlen(t)][strlen(s)]<<endl;
}

void path2(wchar_t s[], wchar_t t[]) {//한글을 처리하기 위해 만든 함수로 위의 path1함수와 로직은 동일하다.

	stack<int> sta;
	int sl = wcslen(s);
	int tl = wcslen(t);

	while (sl > 0 && tl > 0) {
		int a;
		if (abs(dp[tl][sl] - dp[tl - 1][sl - 1]) < zzzz) {
			a = 0;

		}
		if (abs(dp[tl][sl] - 0.3 - dp[tl - 1][sl - 1]) < zzzz) {

			a = 1;
		}
		if (abs(dp[tl][sl] - 0.5 - dp[tl][sl - 1]) < zzzz) {
			a = 2;
		}
		if (abs(dp[tl][sl] - 0.7 - dp[tl - 1][sl]) < zzzz) {
			a = 3;
		}

		if (dp[tl][sl - 1] < dp[tl - 1][sl - 1]) {
			if (abs(dp[tl][sl] - 0.5 - dp[tl][sl - 1]) < zzzz) {
				a = 2;
			}
		}
		if (dp[tl - 1][sl] < dp[tl - 1][sl - 1]) {
			if (abs(dp[tl][sl] - 0.7 - dp[tl - 1][sl]) < zzzz) {
				a = 3;
			}
		}
		if (a == 0) {
			sta.push(0);
			tl--;
			sl--;
		}
		else if (a == 1) {
			sta.push(1);
			tl--;
			sl--;
		}
		else if (a == 2) {
			sta.push(2);
			sl--;
		}
		else if (a == 3) {
			sta.push(3);
			tl--;
		}
	}
	if (sl > 0) {
		for (int k = sl; k > 0; k--) {
			sta.push(2);
		}
	}

	else if (tl > 0) {
		for (int k = tl; k > 0; k--) {
			sta.push(3);
		}
	}

	while (!sta.empty()) {

		int a1 = sta.top();
		sta.pop();
		if (a1 == 1) cout << "변경: 0.3" << endl;
		else if (a1 == 2) cout << "삭제: 0.5" << endl;
		else if (a1 == 3) cout << "삽입: 0.7" << endl;
	}
	cout <<"최소편집거리"<< dp[wcslen(t)][wcslen(s)] << endl;
}

int main() {
	dp[0][0] = 0.0;

	char s1[20] = "Levenshtein";
	char t1[20] = "Meilenstein";
	EditDistance1(s1, t1);
	cout << "예제1" << endl;
	path1(s1, t1);

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout<<setw(5)<<dp[i][j];
		}
		cout << endl;
	}



	return 0;
}