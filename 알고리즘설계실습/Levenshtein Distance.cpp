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

double dp[100][100];//���̳��� ���α׷����� �������� ��� �迭

void EditDistance(char s[],char t[]) {//����ġ�� ���� ���� �Լ�

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
void EditDistance1(char  s[], char t[]) {//����ġ�� �ٸ� ��� �ּҺ���� ���ϴ� �Լ��̴�.

	int sl = strlen(s);
	int tl = strlen(t);
	for (int i = 0; i <= sl; i++)//������ ���� ����ġ�� �迭�� ä��� �ݺ���
	{
		dp[0][i] = i * 0.5;
	}
	for (int i = 0; i <= tl; i++)//���Կ� ���� ����ġ�� �迭�� ä��� �ݺ���
	{
		dp[i][0] = i * 0.7;
	}

	for (int i = 1; i <= tl; i++)
	{
		for (int j = 1; j <= sl; j++)
		{
			double cost;
			if (s[j - 1] == t[i - 1]) cost = 0; // ���ڰ� ���� �� ����ġ�� 0���� ���ִ� �κ��̴�

			else cost = 0.3;//���ڰ� �ٸ� �� ����ġ�� 0.3���� �ٲپ� �ش�.

			dp[i][j] = min(dp[i][j - 1] + 0.5, min(dp[i - 1][j] + 0.7, dp[i - 1][j - 1] + cost)); //levenshtien�˰����� �ٽ����� ��ȭ���� �ڵ�� �ۼ��� �κ��̴�.
		}
	}
}

void EditDistance2(wchar_t s[], wchar_t t[]) {//�ѱ��� ó���ϱ� ���� ���� �Լ��� ���� editdistance1�Լ��� ������ �����ϴ�.

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

void path1(char s[], char t[]) {//�ִܰŸ��� �������� � ������ �߻��ϴ��� Ȯ���ϴ� �Լ��̴�.

	stack<int> sta;
	int sl = strlen(s);
	int tl = strlen(t);

	while (sl > 0 && tl > 0) {
		int a;
		if ( abs(dp[tl][sl]- dp[tl - 1][sl - 1])<zzzz) {//�밢�� ����� ������ġ�� ���Ѵ�.(zzzz�� ����� ������ �ε��Ҽ����� �ذ��ϱ� ���ؼ��̴�.)
			a = 0;
		}
		if (abs(dp[tl][sl] - 0.3-dp[tl - 1][sl - 1])<zzzz ) {//�밢�� ����� ������ġ�� ���Ѵ�.
			a = 1;
		}
		if (abs(dp[tl][sl] - 0.5 - dp[tl][sl - 1])<zzzz ) {//���� ����� ������ġ�� ���Ѵ�. 
			a = 2;
		}
		if (abs(dp[tl][sl] - 0.7 - dp[tl - 1][sl])<zzzz ) {//���� ����� ������ġ�� ���Ѵ�.
			a = 3;
		}

		if (dp[tl][sl - 1] < dp[tl - 1][sl - 1]) {// ������ ���� 4���� ���θ� �� ��� ����ġ�� ������찡 ����� �̸� �����ϱ����� ����ġ�� ������ ���� �ʱⰪ�� ���������� �켱���� �־��־���.
			if (abs(dp[tl][sl] - 0.5 - dp[tl][sl - 1]) < zzzz) {
				a = 2;
			}
		}
		if (dp[tl-1][sl] < dp[tl - 1][sl - 1]) {// ������ ���� 4���� ���θ� �� ��� ����ġ�� ������찡 ����� �̸� �����ϱ����� ����ġ�� ������ ���� �ʱⰪ�� ���������� �켱���� �־��־���.
			if (abs(dp[tl][sl] - 0.7 - dp[tl-1][sl]) < zzzz) {
				a = 3;
			}
		}
		if (a == 0) {//���� ���� a�� �°� sta�� �־��־���. ���� tl�� sl���� �ֽ�ȭ���־���(�̵��� ��ġ�� �ʱ�ȭ ���־���.)
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
	
	while (!sta.empty()) {//stack�� ���� ���� ���鼭 ������ ������� ����Ͽ���.

		int a1 = sta.top();
		sta.pop();
		if (a1 == 1) cout << "����: 0.3" <<endl;
		else if (a1 == 2) cout << "����: 0.5" << endl;
		else if (a1 == 3) cout << "����: 0.7" << endl;
	}

	cout << "�ּ������Ÿ�" << dp[strlen(t)][strlen(s)]<<endl;
}

void path2(wchar_t s[], wchar_t t[]) {//�ѱ��� ó���ϱ� ���� ���� �Լ��� ���� path1�Լ��� ������ �����ϴ�.

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
		if (a1 == 1) cout << "����: 0.3" << endl;
		else if (a1 == 2) cout << "����: 0.5" << endl;
		else if (a1 == 3) cout << "����: 0.7" << endl;
	}
	cout <<"�ּ������Ÿ�"<< dp[wcslen(t)][wcslen(s)] << endl;
}

int main() {
	dp[0][0] = 0.0;

	char s1[20] = "Levenshtein";
	char t1[20] = "Meilenstein";
	EditDistance1(s1, t1);
	cout << "����1" << endl;
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