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
	cout << t << "�� ���� �˻����"<<endl;
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
			cout << "������ �߰ߵ� ����: " << count<< "  ������ Ž���� ��ġ: " << i << "��°" << endl;
			j = m;
			i = i + m +1;
		}
	}


}

void main() {
	string s;
	string t;
	cout << "ã����� ���ڿ��� �Է��Ͻÿ�: ";
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