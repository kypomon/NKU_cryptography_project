#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <exception>

using namespace std;






//ͷ�ļ�ģ��
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
class DES
{
public:
	DES();                                                            //DES: Ĭ�Ϲ��캯��
	void key(string key, string mode);                                //key: �趨��Կ
	string encrypt(string input, string inmode, string outmode);      //encrypt: DES����
	string decrypt(string input, string inmode, string outmode);      //decrypt: DES����
	string getkey(string mode);                                       //getkey:��ȡ��ǰ��Կ
public:

	int __plain[64], __enpt[64], __key[64];           //plain, enpt, key: ��������ĺ����ģ���Կ
	bool __flag;

	string hexToBinary(string input);                              //hexToBinary: ʮ����������ת��Ϊ������
	string binToHexto(string input);                               //binToHexto: ����������ת��Ϊʮ������
	void ipSub(const int input[64], int output[64]);               //ipSub: IP�û�
	void eSub(const int input[32], int output[48]);                //eSub: E��չ�û�
	void shiftBinary(int lis[56], int num);                        //shiftBinary: ѭ������
	void keySub(int roll_no, const int input[64], int output[48]);  //keySub: ��Կ�û�
	void sSub(const int input[48], int output[32]);                //sSub: S�д���
	void pSub(const int input[32], int output[32]);                //pSub: P�д���
	void ipReSub(const int input[64], int output[64]);             //ipReSub: IP���û�
	void roleDES(const int leftinput[32], const int rightinput[32], int leftoutput[32], int rightoutput[32], int rolekey[48]);    //roleDES:����DES����
	void _DES(int input[64], int output[64], int key[64]);           //_DES: �ײ�DES����ʵ��
	void _deDES(int input[64], int output[64], int key[64]);         //_deDES: �ײ�DES����ʵ�� 
};

/********************* public functions *************************/

/*0.
*DES: ��Ĭ�ϳ�ʼ������
*/
DES::DES()
{
	__flag = false;
}

/*1.
*key: �÷����趨DES������Կ
*Param: input--��ǰ׺ʮ�����ƻ��߶��������룬 mode--'0b'ָʾ���������룬'0x'ָʾʮ����������
*/
void DES::key(string key, string mode)
{
	__flag = true;
	if (mode == "0x")
		key = hexToBinary(key);
	for (int i = 0; i<key.size(); i++)
	{
		__key[i] = key[i] - '0';
	}
	return;
}

/*2.
*encrypt: �÷�������DES���ܣ����ؼ��ܺ������
*Param: input--��ǰ׺ʮ�����ƻ��߶������������룬 inmode--'0b'ָʾ�Զ�������ʽ���룬'0x'ָʾ��ʮ��������ʽ���룬outmode--'0b'ָʾ�Զ�������ʽ�����'0x'ָʾ��ʮ��������ʽ���
*Return: ��ǰ׺ʮ�����ƻ��߶������������
*/
string DES::encrypt(string input, string inmode, string outmode)
{
	if (!__flag)
		throw "Having not set key for encrypt or decrypt";

	input = (inmode == "0x") ? hexToBinary(input) : input;
	for (int i = 0; i<input.size(); i++)
	{
		__plain[i] = input[i] - '0';
	}

	_DES(__plain, __enpt, __key);

	string output;
	for (int i = 0; i<64; i++)
	{
		output.push_back(__enpt[i] + '0');

	}
	output = (outmode == "0x") ? binToHexto(output) : output;
	return output;
}

/*3.
*decrypt: �÷�������DES���ܣ����ؽ��ܺ������
*Param: input--��ǰ׺ʮ�����ƻ��߶������������룬 inmode--'0b'ָʾ�Զ�������ʽ���룬'0x'ָʾ��ʮ��������ʽ���룬outmode--'0b'ָʾ�Զ�������ʽ�����'0x'ָʾ��ʮ��������ʽ���
*Return: ��ǰ׺ʮ�����ƻ��߶������������
*/
string DES::decrypt(string input, string inmode, string outmode)
{
	if (!__flag)
		throw "Having not set key for encrypt or decrypt";

	input = (inmode == "0x") ? hexToBinary(input) : input;
	for (int i = 0; i<input.size(); i++)
	{
		__enpt[i] = input[i] - '0';
	}

	_deDES(__enpt, __plain, __key);

	string output;
	for (int i = 0; i<64; i++)
	{
		output.push_back(__plain[i] + '0');

	}
	output = (outmode == "0x") ? binToHexto(output) : output;
	return output;
}

/*4.
*hexToBinary: �÷�����ʮ�������ַ���ת��Ϊ�������ַ�����������ǰ׺��
*Param: input--��ǰ׺ʮ����������
*Return��output--��ǰ׺���������
*/
string DES::getkey(string mode)
{
	string key;
	for (int i = 0; i<key.size(); i++)
	{
		key.push_back(__key[i] + '0');
	}
	return key;
}


/********************* private functions ************************/

/*1.
*hexToBinary: �÷�����ʮ�������ַ���ת��Ϊ�������ַ�����������ǰ׺��
*Param: input--��ǰ׺ʮ����������
*Return��output--��ǰ׺���������
*/
string DES::hexToBinary(string input)
{
	map<char, string> dic;         //ʮ��������������������ת����
	dic['0'] = "0000"; dic['1'] = "0001"; dic['2'] = "0010"; dic['3'] = "0011"; dic['4'] = "0100"; dic['5'] = "0101"; dic['6'] = "0110"; dic['7'] = "0111"; dic['8'] = "1000"; dic['9'] = "1001"; dic['A'] = "1010"; dic['B'] = "1011"; dic['C'] = "1100"; dic['D'] = "1101"; dic['E'] = "1110"; dic['F'] = "1111"; dic['a'] = "1010"; dic['b'] = "1011"; dic['c'] = "1100"; dic['d'] = "1101"; dic['e'] = "1110"; dic['f'] = "1111";

	string output;
	for (int i = 0; i<input.size(); i++)
	{
		output += dic[input[i]];
	}
	return output;
}

/*2.
*binToHexto: �÷�����ʮ�������ַ���ת��Ϊ�������ַ�����������ǰ׺��
*Param: input--��ǰ׺����������
*Return: output--��ǰ׺ʮ���������
*/
string DES::binToHexto(string input)
{
	map<string, string> redic;         //����������ʮ����������ת����
	redic["0000"] = "0"; redic["0001"] = "1"; redic["0010"] = "2"; redic["0011"] = "3"; redic["0100"] = "4"; redic["0101"] = "5"; redic["0110"] = "6"; redic["0111"] = "7"; redic["1000"] = "8"; redic["1001"] = "9"; redic["1010"] = "a"; redic["1011"] = "b"; redic["1100"] = "c"; redic["1101"] = "d"; redic["1110"] = "e"; redic["1111"] = "f";

	string output;
	for (int i = 0; i<input.size() / 4; i++)
	{
		string temp;
		for (int k = i * 4; k<(i + 1) * 4; k++)
		{
			temp.push_back(input[k]);
		}
		output += redic[temp];
	}
	return output;
}

/*3.
*ipSub: �÷�������IP�û�
*Param: input--64λ�������룬output--64λ����IP�û�������
*/
void DES::ipSub(const int input[64], int output[64])
{
	//���ȣ�����IP�û���
	int IP_lis[64] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };    //IP�û���
																																																					//Ȼ�󣬽����û�������IP�û����
	for (int i = 0; i<64; i++)
	{
		output[i] = input[IP_lis[i] - 1];
	}
	return;
}

/*4.
*eSub:�÷�������E��չ�û�
*Param: input--32λ�������룬output--48λ����E��չ�û����
*/
void DES::eSub(const int input[32], int output[48])
{
	//���ȣ�����E��չ�û���
	int E_lis[48] = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1 };
	//Ȼ�󣬽����û�������E��չ�û����
	for (int i = 0; i<48; i++)
	{
		output[i] = input[E_lis[i] - 1];
	}
	return;
}

/*5.
*shiftBinary:�÷���������Ķ������������ǰ���εķֱ����ѭ�����Ʋ���
*�����б�:lis--56λ���������飬num--ѭ������λ��
*/
void DES::shiftBinary(int lis[56], int num)
{
	int temp2[56];
	for (int i = 0; i<28; i++)
	{
		temp2[i] = lis[(i + num) % 28];
	}
	for (int i = 28; i<56; i++)
	{
		temp2[i] = lis[(i - 28 + num) % 28 + 28];
	}
	for (int i = 0; i<56; i++)
	{
		lis[i] = temp2[i];
	}
	return;
}

/*6.
*keySub: �÷���������Կ�û�
*Param: roll_no--��ǰ��������(0-15)��input--64λԭʼ��Կ���룬output--48λ��ǰ�ּ�����Կ���
*/
void DES::keySub(int roll_no, const int input[64], int output[48])
{
	//���ȣ�������64λ��56λ����Կ�û���56λ��48λ�������Կ�û����͸���������������λ��
	int roll_lis[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };    //������������λλ����
	int lis_64_56[56] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };    //64λ��56λ���û���
	int lis_56_48[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 };    //56λ��48λ������û���
																																										//Ȼ���ȶ�ԭʼ������Կinput���д�64λ��56λ���û�(PC-1�û�)
	int temp[56];
	for (int i = 0; i<56; i++)
	{
		temp[i] = input[lis_64_56[i] - 1];
	}
	//Ȼ��Ը�PC-1�û���56λ�������ǰ���εķֱ���λ��ע�⵱ǰ�Ƕ����־���Ҫ������λ���ٴ�
	for (int i = 0; i<roll_no; i++)
	{
		shiftBinary(temp, roll_lis[i]);
	}
	//Ȼ���������λ�������56λ��48λ��PC-2�û������ɵõ����յ�48λ��ǰ����Կ
	for (int i = 0; i<48; i++)
	{
		output[i] = temp[lis_56_48[i] - 1];
	}
	return;
}

/*7.
*sSub: �÷�������S�д���
*Param: input--48λE��չ�û�����͵�ǰ��48λ��Կ��48λ�������output--32λS�д�����
*/
void DES::sSub(const int input[48], int output[32])
{
	//��������8��DES���ܱ�׼S��
	int S_Box[8][4][16] = {                     //8��S����ά����
												// S1
		14, 4,  13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
		15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
		// S2
		15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
		3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
		0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
		13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
		// S3
		10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
		13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
		13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
		1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
		// S4
		7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
		13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
		10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
		3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
		// S5
		2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
		14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
		4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
		11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
		// S6
		12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
		10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
		9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
		4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
		// S7
		4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
		13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
		1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
		6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
		// S8
		13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
		1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
		7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
		2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
	};
	//Ȼ������ʹ��S�ж�48λ�������ݽ��д��洦��
	for (int i = 0; i<8; i++)    //ÿһ��S�д���6���������ݵ�λ
	{
		//��ǰS�д����6λ�����У����λ�����λ����������м���λ��Ϊ����
		//���λΪi*6+5�����λΪi*6���м���λ�ֱ�Ϊi*6+1,i*6+2,i*6+3,i*6+4
		int row = input[i * 6] * 2 + input[i * 6 + 5] * 1;     //����S�����ֵ��������
		int col = input[i * 6 + 1] * 8 + input[i * 6 + 2] * 4 + input[i * 6 + 3] * 2 + input[i * 6 + 4] * 1;   //����S�����ֵ��������
		int res = S_Box[i][row][col];     //���ֵ��ʮ���ƣ�     
										  //���ʮ����ת��Ϊ�����Ʋ�д�����output�Ķ�Ӧλ��
		for (int k = 3; k >= 0; k--)
		{
			output[i * 4 + k] = res % 2;
			res /= 2;
		}
	}
	return;
}

/*8.
*pSub: �÷�������P���û�
*Param: input--32λS�д����Ľ�����룬output--32λP���û�������
*/
void DES::pSub(const int input[32], int output[32])
{
	//��������P��
	int P_box[32] = { 16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25 };
	//Ȼ��ʹ��P�ж�32λ�������P���û����õ�32λ���
	for (int i = 0; i<32; i++)
	{
		output[i] = input[P_box[i] - 1];
	}
	return;
}

/*9.
*ipReSub: �÷�������IP���û�
*Param: input--32λ���룬output--32λIP���û�������
*/
void DES::ipReSub(const int input[64], int output[64])
{
	//��������IP�û���
	int REIP_lis[64] = { 40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25 };
	//Ȼ�����IP���û������IP���û�
	for (int i = 0; i<64; i++)
	{
		output[i] = input[REIP_lis[i] - 1];
	}
	return;
}

/*10.
*roleDES: �÷������е���DES����
*Param: leftinput--32λ��벿��ԭ�����룬rightinput--32λ�Ұ벿��ԭ�����룬leftoutput--32λ��벿��ԭ�������rightoutput--32λ�Ұ벿��ԭ�������key--��ǰ�ֵ�48λ��Կ
*/
void DES::roleDES(const int leftinput[32], const int rightinput[32], int leftoutput[32], int rightoutput[32], int rolekey[48])
{
	//���ȼ�����벿���������벿����������Ұ벿������
	for (int i = 0; i<32; i++)
	{
		leftoutput[i] = rightinput[i];
	}
	//Ȼ������Ұ벿��������ⲿ�ְ������¼����������
	//1.��ԭʼ��32λ�Ұ벿��������E��չ�û�����չΪ48λ
	int rightinput_2[48];
	eSub(rightinput, rightinput_2);
	//2.��48λ��E��չ�û����rightinput_2�뵱ǰ�ֵ���Կ����������
	int rightinput_3[48];
	for (int i = 0; i<48; i++)
	{
		rightinput_3[i] = rightinput_2[i] ^ rolekey[i];
	}
	//3.����������ν���S�д����Լ�P���û�
	int rightinput_4[32];
	sSub(rightinput_3, rightinput_4);     //�����ڴ� 
	int rightinput_5[32];
	pSub(rightinput_4, rightinput_5);
	//4.�����ִ����Լ��û���Ľ���ٺ���벿������leftinput����������
	int rightinput_6[32];
	for (int i = 0; i<32; i++)
	{
		rightinput_6[i] = rightinput_5[i] ^ leftinput[i];
	}
	//5.rightinput_6�������յ��Ұ벿��������
	for (int i = 0; i<32; i++)
	{
		rightoutput[i] = rightinput_6[i];
	}
}

/*11.
*DES:�÷�������DES����
*Param:input--64λ�������룬output--64λ���������key--64λDES����ԭʼ��Կ������56λ��Ч������λ����Ϊ��żУ��λ��
*/
void DES::_DES(int input[64], int output[64], int key[64])
{
	//1.��ԭʼ���Ľ���IP�û�
	int input_2[64];
	ipSub(input, input_2);
	//2.��ԭʼ���ķֲ�Ϊ���������֣�����16�ֵ�DES���ּ��ܣ�����ٽ��õ������������ֺϲ�
	int leftinput[32], rightinput[32], leftoutput[32], rightoutput[32], rolekey[48];
	for (int i = 0; i<64; i++)
	{
		if (i >= 0 && i<32)
			leftinput[i] = input_2[i];
		else
			rightinput[i - 32] = input_2[i];
	}
	for (int i = 1; i <= 16; i++)
	{
		//�������ɵ�ǰ�ֵ���Կ
		keySub(i, key, rolekey);
		//���õ�ǰ����Կ���м���
		roleDES(leftinput, rightinput, leftoutput, rightoutput, rolekey);
		//Ȼ����leftinput=leftoutput,rightinput=rightoutput��׼��������һ�ֵ���
		for (int i = 0; i<32; i++)
		{
			leftinput[i] = leftoutput[i];
			rightinput[i] = rightoutput[i];
		}
	}
	//���һ�ֵõ���leftoutput��rightoutput��Ϊ�õ�������
	//3.�Եõ�������32λ���Ļ���λ�ú�ϲ���Ȼ�����IP���û������õ����ռ��ܵ����Ľ��output
	int tempres[64];
	for (int i = 0; i<64; i++)
	{
		if (i >= 0 && i<32)
			tempres[i] = rightoutput[i];
		else
			tempres[i] = leftoutput[i - 32];
	}
	ipReSub(tempres, output);
	return;
}

/*12.
*deDES: �÷�������DES����
*Param: input--64λ�������룬output--64λ���������key--64λDES����ԭʼ��Կ
*/
void DES::_deDES(int input[64], int output[64], int key[64])
{
	//1.��ԭʼ���Ľ���IP�û�
	int input_2[64];
	ipSub(input, input_2);
	//2.��ԭʼ���ķֲ�Ϊ���������֣�����16�ֵ�DES���ּ��ܣ�����ٽ��õ������������ֺϲ�
	int leftinput[32], rightinput[32], leftoutput[32], rightoutput[32], rolekey[48];
	for (int i = 0; i<64; i++)
	{
		if (i >= 0 && i<32)
			leftinput[i] = input_2[i];
		else
			rightinput[i - 32] = input_2[i];
	}
	for (int i = 16; i >= 1; i--)
	{
		//�������ɵ�ǰ�ֵ���Կ
		keySub(i, key, rolekey);    //DES����ʱ��Ҫ����ʹ����Կ
									//���õ�ǰ����Կ���м���
		roleDES(leftinput, rightinput, leftoutput, rightoutput, rolekey);
		//Ȼ����leftinput=leftoutput,rightinput=rightoutput��׼��������һ�ֵ���
		for (int i = 0; i<32; i++)
		{
			leftinput[i] = leftoutput[i];
			rightinput[i] = rightoutput[i];
		}
	}
	//���һ�ֵõ���leftoutput��rightoutput��Ϊ�õ�������
	//3.�Եõ�������32λ���Ļ���λ�ú�ϲ���Ȼ�����IP���û������õ����ռ��ܵ����Ľ��output
	int tempres[64];
	for (int i = 0; i<64; i++)
	{
		if (i >= 0 && i<32)
			tempres[i] = rightoutput[i];
		else
			tempres[i] = leftoutput[i - 32];
	}
	ipReSub(tempres, output);
	return;
}
