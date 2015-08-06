#include<iostream>
#include<string.h>
#include<fstream>
#include<time.h>
#include<random>
using namespace std;
void main()
{
	srand(time(0));
	for (int i=0; i < 20; i++)
		cout << rand() % 10;
	getchar();
	/*char message[20] = { 'A', 'B', 'C', 'D' };
	char *m ;
	int mess[4] = {1,2,3,4};
	m = message;
//	cin >> message;
	*(message + 0) = 77+1;
	*(message + 1) = 78+2;
	*(message + 2) = 80+3;
	*(message + 3) = 79+4;
	cout << message<<endl;
	cout << m;
	ofstream out;
	out.open("history.txt");
	out << "helloworld " << message << endl;
	out << mess[0]+'0'+17 << endl;
	cin >> message;*/
	
}