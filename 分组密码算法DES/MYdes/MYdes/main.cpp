#include "mydes.h"
#include <iostream>
#include <string>
/**********�������ݳ�ʼ�û����̵�����****************/

//���ݳ�ʼ�û���
static const int data_Initial[64] =
{
	58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
};
//�������ʼ�û���
const static int data_reInitial[64] = {
	40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
};

//E��չ�����
static const int data_Expansion[48] =
{
	32,1,2,3,4,5,
	4,5,6,7,8,9,
	8,9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32,1
};

//S�д�����
static const int data_Sbox[8][4][16] =
{
	{
		{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 },
	},
	{
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 },
	},
	{
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 },
	},
	{
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 },
	},
	{
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 },
	},
	{
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 },
	},
	{
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 },
	},
	{
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 },
	}
};

//P�д�����
static const int data_Pbox[32] =
{
	16,7,20,21,
	29,12,28,17,
	1,15,23,26,
	5,18,31,10,
	2,8,24,14,
	32,27,3,9,
	19,13,30,6,
	22,11,4,25
};
using namespace std;

int main(void)
{

	/*int result_key[16][48];//ʮ���ֵ�����Կ�洢�������ά������
	int initial_key[64]={0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	};

	get_key(initial_key,result_key);//�����ȡ��16������Կ

	//���16������Կ
	for (int i = 0; i <= 15; i++)
	{
	cout << "��" << i + 1 << "�ֵ�����Կ���Ϊ:    ";
	for (int j = 0; j <= 47; j++)
	{
	cout << result_key[i][j];
	}
	cout << endl;
	}

	int data[64] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	};
	initial_trans(data);
	int R_data[32];
	int L_data[32];
	data_separate(data,  R_data,  L_data);

	for (int i = 0; i <= 15; i++) turn_function(R_data,  L_data, i,   result_key);

	for (int i = 0; i <= 31; i++)
	{
	data[i] = L_data[i];
	data[i + 32] = R_data[i];
	}
	reinitial_trans(data);
	for (int i = 0; i < 63; i++)
	cout << data[i];*/
	while (1) {
		
		cout << "select menu:" << endl;
		cout << "1.encrpty:" << endl;
		cout << "2.decrpty:" << endl;
		cout << "3:Avalanche effect" << endl;
		cout << "4:quit" << endl;
		int choose;
		cin >> choose;
		if (choose == 1)
		{
			string plain;
			cout << "plain:";
			cin >> plain;
			string key;
			cout << "��Կ:";
			cin >> key;
			string enpt;

			DES des = DES();
			des.key(key, "0x");

			enpt = des.encrypt(plain, "0x", "0x");
			cout << "encrypt result: " << enpt << endl;

		}
		else if (choose == 2)
		{
			string enpt;
			cout << " enpt:";
			cin >> enpt;
			string key;

			cout << "��Կ:";
			cin >> key;
			

			DES des = DES();	
			string plain;
			plain = des.decrypt(enpt, "0x", "0x");
			cout << "decrypt result: " << plain << endl;
			

		}
		else if (choose == 3)
		{

			int total=0;
			int average=0;
			string plain;
			cout << "plain:";
			cin >> plain;
			
			string key;
			cout << "��Կ:";
			cin >> key;
			string enpt;

			DES des = DES();
			des.key(key, "0x");

			enpt = des.encrypt(plain, "0x", "0x");
			cout << "encrypt result: " << enpt << endl;



			string binplain = des.hexToBinary(plain);
			string binkey = des.hexToBinary(key);

			for (int i = 0; i <= 7; i++)
			{
				
				
					if (binplain[i] == '0') binplain[i] = '1';
					else binplain[i] = '0';
					
					DES des1 = DES();
					des1.key(key, "0x");
					
					string plain1 = des1.binToHexto(binplain);
					string enpt1;
					enpt1 = des1.encrypt(plain1, "0x", "0x");
					string binenpt1 = des1.hexToBinary(enpt1);
					string binenpt = des1.hexToBinary(enpt);
					int change = 0;
					
					for (int j = 0; j <= binenpt.length(); j++)
					{
						
						if (binenpt1[j] != binenpt[j]) change++;
					}


					cout << "���ĸı�" << i + 1 << "λ" << ",���ĸı���"<<change<<"λ"<<endl;;
					total += change;
			}

			cout << endl << endl;
			for (int i = 0; i <= 7; i++)
			{


				if (binkey[i] == '0') binkey[i] = '1';
				else binkey[i] = '0';

				DES des1 = DES();
				string key1 = des1.binToHexto(binkey);
				des1.key(key1, "0x");

				
				string enpt1;
				enpt1 = des1.encrypt(plain, "0x", "0x");
				string binenpt1 = des1.hexToBinary(enpt1);
				string binenpt = des1.hexToBinary(enpt);
				int change = 0;
				for (int j = 0; j <= 63; j++)
				{
					if (binenpt1[j] != binenpt[j]) change++;
				}


				cout << "��Կ�ı�" << i + 1 << "λ" << ",���ĸı���" << change<<"λ" << endl;;
				total += change;
			}
			cout << endl << "��ֵ��" << float(total) / 16.00;
		}
		else if (choose == 4)
		{
			break;
		}
		
		cout << "another turn" << endl;
		system("pause");
		system("cls");
		
	}
	system("pause");
	return 0;

}