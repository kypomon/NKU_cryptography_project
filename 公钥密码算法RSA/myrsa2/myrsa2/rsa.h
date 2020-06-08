#pragma once
#include"BigInt.h"
class Rsa
{
public:
	Rsa();
	~Rsa();
	void init(unsigned int n);//��ʼ����������˽Կ��

	friend void test();
public:
	BigInt encryptByPu(const BigInt& m);//˽Կ����
	BigInt decodeByPr(const BigInt& c);//��Կ����

	BigInt encryptByPr(const BigInt& m);//��Կ����
	BigInt decodeByPu(const BigInt& m);//˽Կ����
private:
	BigInt createOddNum(unsigned int n);//���ɳ���Ϊn������
	bool isPrime(const BigInt& a,const unsigned int k);//�ж�����
	BigInt createPrime(unsigned int n,int it_cout);//���ɳ���Ϊn������
	void createExp(const BigInt& ou);//��һ��ŷ���������ɹ�Կ��˽Կָ��
	BigInt createRandomSmallThan(const BigInt& a);//����С��
	friend ostream& operator <<(ostream& out,const Rsa& rsa)//���
	{
		out<<"N:"<<rsa.N<<"\n";
		out<<"p:"<<rsa._p<<"\n";
		out<<"q:"<<rsa._q<<"\n";
		out<<"e:"<<rsa.e<<"\n";
		out<<"d:"<<rsa._d;
		return out;
	}
public:
	BigInt e,N;//��Կ
private:
	BigInt _d;//˽Կ
	BigInt _p,_q;//
	BigInt _ol;//ŷ����
};
/*

*/