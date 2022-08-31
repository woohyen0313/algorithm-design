#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;
struct node
{


	string symbol;
	int frequency;
	node* left=NULL;
	node* right=NULL;

	s(string a, int b) : symbol(a), frequency(b) {}
};
int main(){
priority_queue<node> pq;
pq.push(node("r",10));

}