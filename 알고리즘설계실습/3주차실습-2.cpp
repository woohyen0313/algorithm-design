#include<iostream>
#include<ctime>

using namespace std;
double fibo(int n) {//재귀함수로 피보나치 수열을 구현했다
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
	start = clock();//시작 시간

	b = fibo(a);//피보나치 수열 진행

	end = clock();//종료 시간

	take = end - start;//걸린 시간


	cout << "2^n(Exponential complexity) 소요시간 = " << double(take) / 1000 << "s" << endl; // 걸린시간 출력


	return 0;

}
