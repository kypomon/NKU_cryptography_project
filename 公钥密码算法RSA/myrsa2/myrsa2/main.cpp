#include<iostream>
#include<ctime>
#include"BigInt.h"
#include"rsa.h"
#include<windows.h>
using std::cout;
using std::endl;
using std::cin;

void menu()
{//�˵���ʾ����
	cout<<"==========��ӭ����rsa���ܽ���=========="<<endl;
	cout<<"               e.encrypt ����              "<<endl;
	cout<<"               d.decrypt ����              "<<endl;
	cout<<"               q.quit �˳�                 "<<endl;
	cout<<"input your choice:"<<endl;
}

bool islegal(const string& str)
{//�ж������Ƿ�Ϸ�
	for(string::const_iterator it=str.begin();it!=str.end();++it)
		if(!isalnum(*it))//������ĸ����
			return false;
	return true;
}

bool decode(Rsa& rsa)
{//����
	string str;
	do
	{
		cout<<">����16��������:";
		cin>>str;
	}while(cin && str.length()<1);
	if(!cin || islegal(str)==false)
		return false;
	BigInt c(str);
	
	long t1=clock();
	BigInt m=rsa.decodeByPr(c);
	long t2=clock();
	cout<<"��ʱ:"<<(t2-t1)<<"ms."<<endl;

	cout<<"����:"<<c<<endl
		<<"����:"<<m<<endl;
	return true;
}

bool encry(Rsa& rsa,BigInt& c)
{//����
	string str;
	do
	{
		cout<<">����16��������:";
		cin>>str;
	}while(cin && str.length()<1);
	if(!cin || islegal(str)==false)
		return false;
	BigInt m(str);

	c=rsa.encryptByPu(m);

	cout<<"����:"<<m<<endl
		<<"����:"<<c<<endl;
	return true;
}

void print(Rsa& rsa)
{//���
	cout<<rsa<<endl;
}

void init(Rsa& rsa,int n)
{//��ʼ��

	cout<<"��ʼ��...."<<endl;
	long t1=clock();
	rsa.init(n);
	long t2=clock();
	cout<<"��ʼ�����."<<endl;
	Sleep(5000);
	cout<<"��ʱ:"<<(t2-t1)/1000<<"s."<<endl;
}

int go()
{//���ƺ���
	char ch;
	string str;
	Rsa rsa;
	BigInt c,m;
	cout<<"����λ��:";
	int n;
	cin>>n;
	init(rsa,n/2);

	while(true)
	{
		menu();//�˵���ʾ
		cout<<">";
		cin>>str;
		if(!cin)
			return 0;
		
		if(str.length()<1)
			cout<<"��������"<<endl;
		else
		{
			ch=str.at(0);
			switch(ch)
			{
			case 'e':
			case 'E':
				encry(rsa,c);//����
				break;
			case 'd':
			case 'D':
				decode(rsa);//����
				break;
			case 's':
			case 'S':
				go();//���¿�ʼ��ʼ
				break;
			case 'p':
			case 'P':
				print(rsa);//�����˽Կ��Ϣ
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
	//����ת������
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
	cout << test << "��һ������";
	else
	cout << test << "��һ������";*/
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