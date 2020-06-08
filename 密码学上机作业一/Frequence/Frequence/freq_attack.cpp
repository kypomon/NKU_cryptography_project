#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//aim1:获取所有频率相等的字母集合并输出，在vector里面的索引定位
//依据这些索引进行全排序，输出所有可能的情况


struct symbol
{
	char character;
	int freq;
	char changeto;
};

struct segment
{
	int startnum;
	int endnum;
};
int length;
void init_vector();
void cout_vector(string txtstr);
bool GreaterSort(symbol a, symbol b);
vector<char> accord_list;
vector<symbol> result_list;
vector<vector<symbol>> all_list;
vector<segment> same_seq;
void trans_list(string &txtstr);
void getsame_group();
void output_table();
void perm(int low, int high);


int main()
{
	init_vector();
	string txtstr;
	string temp;
	getline(cin,txtstr);
	temp = txtstr;
	cout_vector(txtstr);	
	trans_list(txtstr);
	txtstr = temp;
	getsame_group();
	length = 0;
	system("pause");
	return 0;
}

void init_vector()
{
	accord_list.push_back('e');
	accord_list.push_back('t');
	accord_list.push_back('o');
	accord_list.push_back('i');
	accord_list.push_back('a');
	accord_list.push_back('n');
	accord_list.push_back('s');
	accord_list.push_back('r');
	accord_list.push_back('h');
	accord_list.push_back('l');
	accord_list.push_back('d');
	accord_list.push_back('u');
	accord_list.push_back('c');
	accord_list.push_back('m');
	accord_list.push_back('p');
	accord_list.push_back('y');
	accord_list.push_back('f');
	accord_list.push_back('g');
	accord_list.push_back('w');
	accord_list.push_back('b');
	accord_list.push_back('v');
	accord_list.push_back('k');
	accord_list.push_back('x');
	accord_list.push_back('j');
	accord_list.push_back('q');
	accord_list.push_back('z');
}

void cout_vector(string txtstr)
{
	for (int i = 0; i<=25; i ++)
	{
		char sym = 'a' + i;
		int num = count(txtstr.begin(), txtstr.end(), sym) + count(txtstr.begin(), txtstr.end(), 'A'+i);
		symbol temp;
		temp.character = sym;
		temp.freq = num;
		result_list.push_back(temp);
	}
	sort(result_list.begin(),result_list.end(),GreaterSort);
}

bool GreaterSort(symbol a, symbol b)
{
	     return (a.freq > b.freq);
 }

void trans_list(string &txtstr)
{
	cout << "ciphertext\t" << "plaintext\t" << endl;
	for (int i = 0; i <= 25; i++)
	{
		cout << result_list[i].character << "\t\t" << accord_list[i] << "\t\t" << result_list[i].freq << endl;
		result_list[i].changeto = accord_list[i];
	}
	for (int i = 0; i < txtstr.length(); i++)
	{
		char t1 = txtstr[i];
		char t2 = txtstr[i] + 32;
		char t3 = txtstr[i] - 32;

		for (std::vector<symbol>::iterator it = result_list.begin(); it != result_list.end(); ++it)
		{
			if (t1 == it->character || t2 == it->character || t3 == it->character)
			{
				txtstr[i] = it->changeto;
			}
		}
	}
	cout << endl << endl;
	cout << txtstr;
}


void getsame_group()
{
	int i = 0;

	for (std::vector<symbol>::iterator it = result_list.begin(); it != result_list.end(); ++it)
	{
		i = it - result_list.begin();
		segment temp;

		if (it <= result_list.end() - 2)
		{
			if (it->freq == (it + 1)->freq)
			{
				temp.startnum = i;
				for (std::vector<symbol>::iterator now = it + 1; now != result_list.end(); ++now)
				{
					if (it->freq == now->freq)
					{
						temp.endnum = now - result_list.begin();
					}
				}

				same_seq.push_back(temp);
				it = temp.endnum + result_list.begin();
			}

		}
	}
}

void output_table()
{
	cout << endl;
	cout << "ciphertext\t" << "plaintext\t" << endl;
	for (int i = 0; i <= 25; i++)
	{
		cout << result_list[i].character << "\t\t" << accord_list[i] << "\t\t" << result_list[i].freq << endl;
		result_list[i].changeto = accord_list[i];
	}
	cout << endl;
}

void perm(int low, int high) {
	if (low == high) {   //当low==high时,此时list就是其中一个排列,输出list
		
		all_list.push_back(result_list);
	}
	else {
		for (int i = low; i <= high; i++) {//每个元素与第一个元素交换
			swap(result_list[i], result_list[low]);
			perm(low + 1, high); //交换后,得到子序列,用函数perm得到子序列的全排列
			swap(result_list[i], result_list[low]);//最后,将元素交换回来,复原,然后交换另一个元素
		}
	}
}