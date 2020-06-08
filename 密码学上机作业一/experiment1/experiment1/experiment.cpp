//移位密码加密和解密实现
#include <iostream>
#include <map>
using namespace std;
map<char, int> ini_map;
map<int, char> sft_map;

void init_table()
{
	for(int i=0; i<=25; i++)
	{
		ini_map['a' + i] = i;
	}
}

void shift_table(int n)
{
	for (int i = 0; i <= 25; i++)
	{
		sft_map[(i + n) % 26] = 'a' + i;
	}
}

void encode(char* M,int n,int length)
{
	init_table();
	shift_table(n);
	for (int i = 0; i < length; i++)
	{
		M[i] = sft_map[ ini_map[ M[i] ] ];
	}
}

void decode(char* M,int n,int length)
{
	n = 26 - n;
	init_table();
	shift_table(n);
	for (int i = 0; i < length; i++)
	{
		M[i] = sft_map[ini_map[M[i]]];
	}
}

int main()
{
	int n;
	cout << "shift n = ";
	cin >> n;
	char M[256];
	cout << "please type in your message :" << endl;
	cin >> M;
	cout << "please choose your mode:" << endl << "1:加密" << endl << "2:解密" << endl;
	int choose;
	cin >> choose;
	if (choose == 1)
	{
		encode(M, n, strlen(M));
		cout << endl << "encode result:" << M << endl;
	}
	else
		if (choose == 2)
		{
			decode(M, n, strlen(M));
			cout << endl << "decode result:" << M << endl;
		}
		else
			cout << "invalid! error!" << endl;
	system("pause");
	return 0;
}
