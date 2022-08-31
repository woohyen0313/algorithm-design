#include <iostream>
#include <stdlib.h>
#include <ctime>
#include<string>
using namespace std;

int *initNext(char p[], int m) { 
    int i, j;
    int* next = new int[m]; 
  
    for (i = 0, j = -1; i < m; i++, j++) {
        if (p[i] == p[j]) next[i] = next[j];
        else next[i] = j;
       while ((j >= 0) && (p[i] != p[j])) {
            j = next[j];
        }
    }
    return next;
}
void kmp(char* p, string t,int m) {
     

    int n = t.length();
    int i = 0;
    int j = 0;
    int* next = initNext(p, m);

    for (i = 0, j = 0; j < m && i < n; j++, i++)
    {
        while (j >= 0 && t[i] != p[j]) {
            j = next[j];
        }
        if (j == m - 2) {
            cout <<"pattern start location:" << i - m + 2 << endl;
        }

    }

}

   

int main() {

    string text1= "ababababcababababcaabbabababcaab";
    char a1[9] = "abababca";
    kmp(a1, text1, 9);
    cout << endl;

    string text2 = "This class is an algorithm design class. Therefore, students will have time to learn about algorithms and implement each algorithm themselves";
   char a2[10] = "algorithm";
 
  
    kmp(a2, text2, 10);
    cout << endl;

   
    cout << endl;
    return 0;
}