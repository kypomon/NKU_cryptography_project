#include <iostream>
#include <string>
using namespace std;

unsigned char w[11][4][4];

string trans_unschar2binstr(unsigned char* unschar);
unsigned char* trans_binstr2unschar(string binstr);

//part1:字节替换，独立对状态的每个字节进行
//代换表：S盒
//ByteSub置换表
//ByteSub
unsigned char ByteSub(unsigned char input_byte);
unsigned char inverse_ByteSub(unsigned char input_byte);
//group操作
void group_SubBytes(unsigned char state[][4]);
//group操作
void InvSubBytes(unsigned char state[][4]);
unsigned char sBox[] =
{   
	0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76, /*0*/
	0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0, /*1*/
	0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15, /*2*/
	0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75, /*3*/
	0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84, /*4*/
	0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf, /*5*/
	0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8, /*6*/
	0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2, /*7*/
	0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73, /*8*/
	0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb, /*9*/
	0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79, /*a*/
	0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08, /*b*/
	0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a, /*c*/
	0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e, /*d*/
	0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf, /*e*/
	0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16  /*f*/
};
//与S盒对应的逆置换表
unsigned char invsBox[256] =
{ 
	0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb, /*0*/
	0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb, /*1*/
	0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e, /*2*/
	0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25, /*3*/
	0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92, /*4*/
	0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84, /*5*/
	0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06, /*6*/
	0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b, /*7*/
	0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73, /*8*/
	0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e, /*9*/
	0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b, /*a*/
	0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4, /*b*/
	0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f, /*c*/
	0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef, /*d*/
	0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61, /*e*/
	0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d  /*f*/
};


//part2:行移位：ShiftRow
//第一行保持不变，第二、三、四行依次循环左移1，2，3个字节
//循环左移位
void LeftReverse(unsigned char *a, int begin, int end);
//将长为n的数组循环左移K个位置
void Converse(unsigned char *a, int n, int k);
void ShiftRow(unsigned char [][4] );
void inverse_ShiftRow(unsigned char [][4]);


//part3:列混合MixCol
void MixColumns(unsigned char state[][4]);
void InvMixColumns(unsigned char state[][4]);
unsigned char FFmul(unsigned char a, unsigned char b);

//part4:密钥加AddRoundKey
void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);
void myKeyExpansion(unsigned char* key, unsigned char w[][4][4]);

//part5:密钥编排
//keyexpansion
//将输入的种子密钥拓展为11组128位密码组
//计算方法与nk的不同取值有关
//第0组为输入密钥本身
void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);

//part6:加密
unsigned char* Cipher(unsigned char* input);
//part7:解密
unsigned char* InvCipher(unsigned char* input);

int main()
{
	//字节代换测试
	/*unsigned char test = 0x00;
	cout<<hex<<int(ByteSub(test));
	cout << hex << int(inverse_ByteSub(ByteSub(test)));*/
	//字节代换部分没有问题
	
	unsigned char key[] = {
		0x2b,0x7e, 0x15,0x16, 0x28,0xae, 0xd2,0xa6, 0xab,0xf7, 0x15,0x88, 0x09,0xcf, 0x4f,0x3c

	};
	cout << trans_unschar2binstr(key) << endl;

	unsigned char * p = trans_binstr2unschar(trans_unschar2binstr(key));

	for (int i = 0; i <= 15; i++)
		cout << hex << int(p[i]) << endl;



	myKeyExpansion(key,w);

	cout << endl<< "轮密钥的结果：" << endl;
	for (int u = 0; u<= 10; u++)
	{
		cout << "第"<<u<<"轮密钥的结果：" << endl;
		for (int i = 0; i <= 3; i++)
			for (int j = 0; j <= 3; j++)
				cout << hex << int(w[u][j][i]) << " ";
		cout << endl;
	}





	unsigned char input[] = {
	
		0x32,0x43, 0xf6,0xa8, 0x88,0x5a, 0x30,0x8d, 0x31,0x31, 0x98,0xa2, 0xe0,0x37, 0x07,0x34
	};
	Cipher(input);
	string cipher = trans_unschar2binstr(input);
	cout << endl;
	cout << "最终加密结果为：" << endl;
	for (int i = 0; i <= 15; i++)
		cout << hex << int(input[i]) << " ";

	cout << endl << endl << "解密结果为：" << endl;
	InvCipher(input);
	for (int i = 0; i <= 15; i++)
		cout << hex << int(input[i]) << " ";



	//雪崩效应检测
	//以现有的明文，密钥为基础，进行雪崩效应检测

	cout << endl << endl << endl;
	//cout << "对明文进行改变：" << endl;
	int adder1 = 0;
	
	

	cout << "对密钥进行改变,显示结果为16进制：" << endl;
	int adder = 0;
	string keystr = trans_unschar2binstr(key);

	for (int i = 0; i <= 7; i++)
	{
		cout << "密钥改变" << i << "位时: ";
		if (keystr[i] == '0')keystr[i] = '1';
		else keystr[i] = '0';

		unsigned char* tempkey = trans_binstr2unschar(keystr);
		myKeyExpansion(tempkey, w);

		unsigned char tempinput[] = {

			0x32,0x43, 0xf6,0xa8, 0x88,0x5a, 0x30,0x8d, 0x31,0x31, 0x98,0xa2, 0xe0,0x37, 0x07,0x34
		};

		Cipher(tempinput);

		string result = trans_unschar2binstr(tempinput);

		int count = 0;

		for (int m = 0; m <= 127; m++)
		{
			if (result[m] != cipher[m]) count++;
		}

		cout << "密文改变了" << int(count) << "位" << endl;
		adder += count;

	}
	cout << "最终均值为64" << endl;


	system("pause");
	return 0;
}

string trans_unschar2binstr(unsigned char * unschar)
{
	string output;
	for (int i = 0; i <= 15; i++)
	{
		int temp = unschar[i];
		string str = "00000000";
		
		for (int j = 7; j >= 0; j--)
		{
			str[j] = '0' + temp % 2;
			temp = temp / 2;
		}
		
		output += str;
	}
	return output;
}

unsigned char * trans_binstr2unschar(string binstr)
{
	unsigned char* output = new unsigned char[16];

	for (int i = 0; i <= 15; i++)
	{
		int start = i * 8;
		int temp=0;

		for (int j = start; j <= start + 7; j++)
		{
			int each = 1;
			for (int s = 1; s <= 7 - (j - start); s++)
			{
				each = each * 2;
			}

			if (binstr[j] == '1')
			{
				temp += each;
			}
			
		}

		output[i] = temp;
	}
	return output;
}

//基本操作
unsigned char ByteSub(unsigned char input_byte)
{
	unsigned char temp = sBox[int(input_byte)];
	return temp;
}

//基本操作
unsigned char inverse_ByteSub(unsigned char input_byte)
{
	unsigned char temp = invsBox[int(input_byte)];
	return temp;
}

//group操作
void group_SubBytes(unsigned char state[][4])
{
	int r, c;
	for (r = 0; r<4; r++)
	{
		for (c = 0; c<4; c++)
		{
			state[r][c] = sBox[state[r][c]];
		}
	}
}

//group操作
void InvSubBytes(unsigned char state[][4])
{
	int r, c;
	for (r = 0; r<4; r++)
	{
		for (c = 0; c<4; c++)
		{
			state[r][c] = invsBox[state[r][c]];
		}
	}
}


void ShiftRow(unsigned char  inputarr[][4])
{
	//AES默认有4行，4列
	for (int i = 1; i <= 3; i++)
	{
		Converse(inputarr[i], 4, i);
	}
	
}

void inverse_ShiftRow(unsigned char inputarr[][4])
{
	//AES默认有4行，4列
	for (int i = 1; i <= 3; i++)
	{
		Converse(inputarr[i], 4, 4-i);
	}
}

void MixColumns(unsigned char state[][4])
{
	unsigned char t[4];
	int r, c;
	for (c = 0; c< 4; c++)
	{
		for (r = 0; r<4; r++)
		{
			t[r] = state[r][c];
		}
		for (r = 0; r<4; r++)
		{
			state[r][c] = FFmul(0x02, t[r])
				^ FFmul(0x03, t[(r + 1) % 4])
				^ FFmul(0x01, t[(r + 2) % 4])
				^ FFmul(0x01, t[(r + 3) % 4]);
		}
	}
}

unsigned char FFmul(unsigned char a, unsigned char b)
{
	unsigned char bw[4];
	unsigned char res = 0;
	int i;
	bw[0] = b;
	for (i = 1; i<4; i++)
	{
		bw[i] = bw[i - 1] << 1;
		if (bw[i - 1] & 0x80)
		{
			bw[i] ^= 0x1b;
		}
	}
	for (i = 0; i<4; i++)
	{
		if ((a >> i) & 0x01)
		{
			res ^= bw[i];
		}
	}
	return res;
}

void AddRoundKey(unsigned char state[][4], unsigned char k[][4])
{
	int r, c;
	for (c = 0; c<4; c++)
	{
		for (r = 0; r<4; r++)
		{
			state[r][c] ^= k[r][c];
		}
	}
}

//循环左移位
void LeftReverse(unsigned char *a, int begin, int end)
{
	for (int i = 0; i<(end - begin + 1) / 2; i++)// 交换移动
	{
		int temp = a[begin + i];
		a[begin + i] = a[end - i];
		a[end - i] = temp;
	}
}

//将长为n的数组循环左移K个位置
void Converse(unsigned char *a, int n, int k)
{
	LeftReverse(a, 0, k - 1);
	LeftReverse(a, k, n - 1);
	LeftReverse(a, 0, n - 1);
}


void KeyExpansion(unsigned char* key, unsigned char w[][4][4])
{
	int i, j, row, col;
	
	//进行拼接 row+col*4是输入的16个字节的密钥的角标
	for (row = 0; row<4; row++)
	{
		for (col = 0; col<4; col++)
		{
			w[0][row][col] = key[row + col * 4];
		}
	}



	unsigned char rc[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
	
	for (i = 1; i <= 10; i++)
	{
		for (j = 0; j<4; j++)
		{
			unsigned char t[4];
			for (row = 0; row<4; row++)
			{
				t[row] = j ? w[i][row][j - 1] : w[i - 1][row][3];
			}
			if (j == 0)
			{
				unsigned char temp = t[0];
				for (row = 0; row<3; row++)
				{
					t[row] = sBox[t[(row + 1) % 4]];
				}
				t[3] = sBox[temp];
				t[0] ^= rc[i - 1];
			}
			for (row = 0; row<4; row++)
			{
				w[i][row][j] = w[i - 1][row][j] ^ t[row];
			}
		}
	}
}

void myKeyExpansion(unsigned char* key, unsigned char w[][4][4])
{
	unsigned char storecol[44][4];

	//将key拆分成4行，存进storecol的前4个
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			storecol[i][j]=key[j+i*4];
		}
	}

	//求解store下标为4到43的值
	unsigned char rc[] = { 0x00,0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
	for (int j = 4; j <= 43; j++)
	{	
		//储存w[j-1]
		if (j % 4 == 0)
		{
			unsigned char temp[4];
			for (int mm = 0; mm <= 3; mm++)
			{
				temp[mm] = storecol[j - 1][mm];
			}
			//w[j] = w[j - 4]⊕g(w[j - 1])
			//对storecol[j-1]进行循环左移位
			Converse(temp, 4, 1);
			//对每个字节做S盒置换
			for (int mm = 0; mm <= 3; mm++)
			{
				temp[mm] = sBox[int(temp[mm])];
			}
			//与32比特的常量（RC[j/4],0,0,0）进行异或
			temp[0] ^= rc[j / 4];
			temp[1] ^= rc[0];
			temp[2] ^= rc[0];
			temp[3] ^= rc[0];
			//⊕
			for (int mm = 0; mm <= 3; mm++)
			{
				storecol[j][mm] = storecol[j - 4][mm] ^ temp[mm];
			}

		}
		else
		{
			//w[j]=w[j-4]⊕w[j-1]
			for (int mm = 0; mm <= 3; mm++)
			{
				storecol[j][mm] = storecol[j-4][mm] ^ storecol[j-1][mm];
			}
		}
	}

	//将全部的44个列存储成11个拓展密钥
	for (int i = 0; i <= 10; i++)
	{
		int colbegin = i * 4;
		int colend = i * 4 + 3;

		for (int j = colbegin; j <= colend; j++)
		{
			for (int row = 0; row <= 3; row++)
			{
				w[i][row][j % 4] = storecol[j][row];
			}
		}

	}

}


unsigned char* Cipher(unsigned char* input)
{
	unsigned char state[4][4];
	int i, r, c;

	for (r = 0; r<4; r++)
	{
		for (c = 0; c<4; c++)
		{
			state[r][c] = input[c * 4 + r];
		}
	}

	AddRoundKey(state, w[0]);

	/*cout << "第0轮处理成功：" << endl;
	for (int i = 0; i <= 3; i++)
		for(int j=0; j<=3;j++)
		cout << hex << int(state[i][j]) << " ";
	cout << endl;*/

	for (i = 1; i <= 10; i++)
	{
		//cout << "第" << i << "轮处理成功：" << endl;
		group_SubBytes(state);
		//cout << "subBytes results: " << endl;
		for (int i = 0; i <= 3; i++)
			for (int j = 0; j <= 3; j++)
				//cout << hex << int(state[i][j]) << " ";
		
		//cout << endl;
		ShiftRow(state);
		//cout << "ShiftRow results: " << endl;
		//for (int i = 0; i <= 3; i++)
			//for (int j = 0; j <= 3; j++)
				//cout << hex << int(state[i][j]) << " ";

		//cout << endl;
		if (i != 10)
		{
			MixColumns(state);
			//cout << "MixColumn results: " << endl;
			//for (int i = 0; i <= 3; i++)
				//for (int j = 0; j <= 3; j++)
					//cout << hex << int(state[i][j]) << " ";

			//cout << endl;
		}
		//else
			//cout << "最后一轮没有列混淆" << endl;

		AddRoundKey(state, w[i]);
		
		/*for (int i = 0; i <= 3; i++)
			for (int j = 0; j <= 3; j++)
				cout << hex << int(state[i][j]) << " ";
		cout << endl;*/
	}

	for (r = 0; r<4; r++)
	{
		for (c = 0; c<4; c++)
		{
			input[c * 4 + r] = state[r][c];
		}
	}

	return input;
}


unsigned char* InvCipher(unsigned char* input)
{
	unsigned char state[4][4];
	int i, r, c;

	for (r = 0; r<4; r++)
	{
		for (c = 0; c<4; c++)
		{
			state[r][c] = input[c * 4 + r];
		}
	}
	cout << "第0轮" << endl;
	AddRoundKey(state, w[10]);
	for (int t = 0; t < 4; t++) {
		for (int j = 0; j < 4; j++) {
			cout<<hex << int(state[t][j]) << " ";
		}
	}
	cout << endl;
	for (i = 9; i >= 0; i--)
	{

		cout << "第" << 10 - i << "轮 "<< endl;
		inverse_ShiftRow(state);
		cout << "逆行移位结果：" << endl;
		for (int t = 0; t < 4; t++) {
			for (int j = 0; j < 4; j++) {
				cout << hex << int(state[t][j]) << " ";
			}
		}
		cout << endl;
		cout << "逆字节替换结果结果：" << endl;
		InvSubBytes(state);
		for (int t = 0; t < 4; t++) {
			for (int j = 0; j < 4; j++) {
				cout << hex << int(state[t][j]) << " ";
			}
		}
		cout << endl;
		cout << "密钥加结果：" << endl;
		AddRoundKey(state, w[i]);
		for (int t = 0; t < 4; t++) {
			for (int j = 0; j < 4; j++) {
				cout << hex << int(state[t][j]) << " ";
			}
		}
		cout << endl;
		cout << "列混淆结果：" << endl;
		if (i)InvMixColumns(state);
		for (int t = 0; t < 4; t++) {
			for (int j = 0; j < 4; j++) {
				cout << hex << int(state[t][j]) << " ";
			}
		}
		cout << endl<<endl<<endl<<endl;
	}

	for (r = 0; r<4; r++)
	{
		for (c = 0; c<4; c++)
		{
			input[c * 4 + r] = state[r][c];
		}
	}

	return input;
}



void InvShiftRows(unsigned char state[][4])
{
	unsigned char t[4];
	int r, c;
	for (r = 1; r<4; r++)
	{
		for (c = 0; c<4; c++)
		{
			t[c] = state[r][(c - r + 4) % 4];
		}
		for (c = 0; c<4; c++)
		{
			state[r][c] = t[c];
		}
	}
}

void InvMixColumns(unsigned char state[][4])
{
	unsigned char t[4];
	int r, c;
	for (c = 0; c< 4; c++)
	{
		for (r = 0; r<4; r++)
		{
			t[r] = state[r][c];
		}
		for (r = 0; r<4; r++)
		{
			state[r][c] = FFmul(0x0e, t[r])
				^ FFmul(0x0b, t[(r + 1) % 4])
				^ FFmul(0x0d, t[(r + 2) % 4])
				^ FFmul(0x09, t[(r + 3) % 4]);
		}
	}
}

