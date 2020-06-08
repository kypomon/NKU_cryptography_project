#include<iostream>
#include<ctime>
#include"BigInt.h"
#include"rsa.h"
#include<windows.h>
using std::cout;
using std::endl;
using std::cin;

void menu()
{//菜单显示函数
	cout<<"==========欢迎进行rsa加密解密=========="<<endl;
	cout<<"               e.encrypt 加密              "<<endl;
	cout<<"               d.decrypt 解密              "<<endl;
	cout<<"               q.quit 退出                 "<<endl;
	cout<<"input your choice:"<<endl;
}

bool islegal(const string& str)
{//判断输入是否合法
	for(string::const_iterator it=str.begin();it!=str.end();++it)
		if(!isalnum(*it))//不是字母数字
			return false;
	return true;
}

bool decode(Rsa& rsa)
{//解密
	string str;
	do
	{
		cout<<">输入16进制数据:";
		cin>>str;
	}while(cin && str.length()<1);
	if(!cin || islegal(str)==false)
		return false;
	BigInt c(str);
	
	long t1=clock();
	BigInt m=rsa.decodeByPr(c);
	long t2=clock();
	cout<<"用时:"<<(t2-t1)<<"ms."<<endl;

	cout<<"密文:"<<c<<endl
		<<"明文:"<<m<<endl;
	return true;
}

bool encry(Rsa& rsa,BigInt& c)
{//加密
	string str;
	do
	{
		cout<<">输入16进制数据:";
		cin>>str;
	}while(cin && str.length()<1);
	if(!cin || islegal(str)==false)
		return false;
	BigInt m(str);

	c=rsa.encryptByPu(m);

	cout<<"明文:"<<m<<endl
		<<"密文:"<<c<<endl;
	return true;
}

void print(Rsa& rsa)
{//输出
	cout<<rsa<<endl;
}

void init(Rsa& rsa,int n)
{//初始化

	cout<<"初始化...."<<endl;
	long t1=clock();
	rsa.init(n);
	long t2=clock();
	cout<<"初始化完成."<<endl;
	Sleep(5000);
	cout<<"用时:"<<(t2-t1)/1000<<"s."<<endl;
}

int go()
{//控制函数
	char ch;
	string str;
	Rsa rsa;
	BigInt c,m;
	cout<<"输入位数:";
	int n;
	cin>>n;
	init(rsa,n/2);

	while(true)
	{
		menu();//菜单显示
		cout<<">";
		cin>>str;
		if(!cin)
			return 0;
		
		if(str.length()<1)
			cout<<"重新输入"<<endl;
		else
		{
			ch=str.at(0);
			switch(ch)
			{
			case 'e':
			case 'E':
				encry(rsa,c);//加密
				break;
			case 'd':
			case 'D':
				decode(rsa);//解密
				break;
			case 's':
			case 'S':
				go();//重新开始初始
				break;
			case 'p':
			case 'P':
				print(rsa);//输出公私钥信息
				break;
			case 'q':
			case 'Q':
				return 0;
			}
		}
	}
}


int main()
{
	//进制转换测试
	/*string hex = "FFFFF00FFFF";
	string bin = "01010111101000010010001";
	unsigned long int  dec = 111111111111;

	cout << trans_hexTobin(hex) << endl << trans_binTohex(bin) << endl<< trans_decTohex(dec)<<endl;
	cout << get_random(64,hextype) << endl;
	cout << get_random(64, bintype) << endl;
	cout << trans_binTodec("1000") << endl;

	cout << HugeInteger("28") % HugeInteger("5") << endl;
	cout << HugeInteger("5") % 28 << endl;
	//cout << get_random(64, inttype) << endl;

	if( HugeInteger("8") >= 9) cout<<"true";
	else cout << "false";

	//cout << HugeInteger("100") - HugeInteger("100");*/
	/*HugeInteger test = HugeInteger("101");
	if (Miller(test, 50))
	cout << test << "是一个素数";
	else
	cout << test << "是一个合数";*/
	//cout << trans_decTohex(get_prime(64));
	//cout << trans_hexTodec("92E8F766EA5365E5F4F04A12CD6CE9535E3E95F5ABEF3D46B615CB348C47FBB5");


	//cout<<LLL("22798217398966526980104000087614236407083901312080168003346598011105733635899")%163;

	//cout << get_reverse(LLL(3), LLL(8))<<endl;
	//cout << quick_power(LLL(3), LLL(2), LLL(8));

	/*LLL x, y;
	cout << exgcd(LLL(7), LLL(143), x, y) << endl;
	/*cout << x<<endl;
	cout << y<<endl;
	cout << LLL(7) % LLL(143)<<endl;
	cout << get_reverse(LLL(7), LLL(143));*/
	/*RSA rsa;
	string e;
	cout << "please put in e: " << endl;
	cin >> e;
	rsa.initial(LLL(e));
	cout << endl;
	cout << "please put in plain:" << endl;
	string plain;
	cin >> plain;
	cout << rsa.encrypt(LLL(plain)) << endl;

	cout << "please put in encryptxt:" << endl;
	string encryptxt;
	cin >> encryptxt;
	cout << rsa.encrypt(LLL(encryptxt)) << endl;

	//cout << LLL(get_random(64,inttype))<<endl;
	//cout << LLL(get_prime(64));



	system("pause");
	return 0;*/
	go();
}