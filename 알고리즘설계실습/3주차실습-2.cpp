#include<iostream>
#include<ctime>

using namespace std;
double fibo(int n) {//����Լ��� �Ǻ���ġ ������ �����ߴ�
	if (n == 1)return 1;
	else if (n == 0) return 0;
	else
		return (fibo(n - 1) + fibo(n - 2));
}
int main() {
	clock_t start, end, take;

	int a;
	double b;
	cin >> a;
	start = clock();//���� �ð�

	b = fibo(a);//�Ǻ���ġ ���� ����

	end = clock();//���� �ð�

	take = end - start;//�ɸ� �ð�


	cout << "2^n(Exponential complexity) �ҿ�ð� = " << double(take) / 1000 << "s" << endl; // �ɸ��ð� ���


	return 0;

}
