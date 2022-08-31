#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <sstream>
#include<queue>
#pragma once
using namespace std;
int skip[10000] = {0,};



int findindex(string s, char s1) { 
	int i = 0;
	for (i = 0; i <s.length()-1; i++) { 
		if (s[i] == s1) break;
	}
	return i;
}

void InitSkip(string t) {
	int m = t.length();
	for (int i = 0; i <m+1;  i++)
	{
		skip[i] = m;
	}
	for (int i = 0; i < m; i++)
	{
		skip[findindex(t, t[i])] = m - i - 1;
	}
}

void MisChar(string s, string t) {
	
	 int n = s.length();
     int m = t.length();
	int count = 0;
	int i, j,k;
	cout << t << "에 대한 검색결과"<<endl;
	for (i = m-1, j = m-1; j>=0 && i<=n-1; i-- , j--){
		if (i == -1 || j == -1) { break; }
		while (s[i] != t[j]) {
			k = skip[findindex(t, s[i])];
			if ((m - j) > k) i = i + m - j;
			else i += k;
			if (i >= n) break;
			j = m - 1;
		}
		if (j == 0) { 
			count++;
			cout << "패턴이 발견된 갯수: " << count<< "  패턴이 탐색된 위치: " << i << "번째" << endl;
			j = m;
			i = i + m +1;
		}
	}


}

void main() {
	string s;
	string t;
	cout << "찾고싶은 문자열을 입력하시오: ";
	getline(cin, t);

	
	ifstream file("test.txt");
	if (file.is_open()) {

		file.seekg(0, ios::end);
		int size = file.tellg();
		s.resize(size);
		file.seekg(0, ios::beg);
		file.read(&s[0], size);
	}

	InitSkip(t);
	MisChar(s, t);


	
		file.close();
	
	
}