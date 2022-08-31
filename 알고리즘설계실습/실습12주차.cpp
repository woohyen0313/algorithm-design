#include<iostream>
using namespace std;

void floyd2(int n, int W[6][6], int D[6][6], int P[6][6]) {
	int i, j, k;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			P[i][j] = 0;

	for (i = 0; i <= n; i++)
		for (j = 0; j <= n; j++)
			D[i][j] = W[i][j];

	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}

}
void path(int P[6][6], int q, int r) {

	if (P[q][r] != 0) {
		path(P, q, P[q][r]);
		cout << " v" << P[q][r] << " ->";
		path(P, P[q][r], r);
	}

}
int main() {

	int P[6][6];

	int w[6][6] = {

		1000,1000,1000,1000,1000,1000,
		1000,0,1,1000,1,5,
		1000,9,0,3,2,1000,
		1000,1000,1000,0,4,1000,
		1000,1000,1000,2,0,3,
		1000,3,1000,1000,1000,0
	};
	int d[6][6] = {0};

	floyd2(5, w, d, P);

	cout << "D[i][j] is" << endl;
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 5; j++) {
			cout << d[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "P[i][j] is" << endl;
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 5; j++) {
			cout << P[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "path: ";
	cout << " v" << 2 << " ->";
	path(P, 2, 5);
	cout << " v" << 5 ;
	return 0;
}