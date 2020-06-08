#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


const char c[27] = { 'd','j','k','z','u',
'x','c','m','l','i','w','b','v','n','o','p',
'q','a','r','s','g','h',
'f','t','y','e',' ' };

void encryption(ifstream& fin, ofstream& fout)//加密过程
{
	char next;
	char ch;
	int i;
	while (fin.get(next))
	{
		if (next >= 'a'&&next <= 'z')
		{
			i = next - 'a';
			ch = c[i];
			fout << ch;
		}
		else
		{
			fout << ' ';
		}
	}
}
void decryption(ifstream& fin, ofstream& fout)//解密过程
{
	char ch;
	char chout;
	while (fin.get(ch))
	{
		for (int i = 0; i <= 26; i++)
		{
			if (ch == c[i])
			{
				if (i == 26)
				{
					fout << ' ';
				}
				else
				{
					chout = char('a' + i);
					fout << chout;
				}
			}
		}
	}
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	if (fin.fail())
	{
		cout << "File open error!(Input)" << endl;
		system("pause");
	}
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "File open error!(Output)" << endl;
	}
	cout << "请选择要进行的操作：" << endl << "1:加密" << endl << "2:解密" << endl;
	int key;
	cin >> key;
	if(key==1) encryption(fin, fout);
	else if(key==2)
	decryption(fin, fout);
	fin.close();
	fout.close();
	system("pause");
	return 0;
}
