#include "rsa.h"
#include<iostream>
#include<sstream>
#include<ctime>
#include<cstdlib>

using std::cout;
using std::endl;
using std::ostringstream;
/*
#include "rsa.h"

string trans_hexTobin(string input)
{
map<char, string> dic;         //十六进制数到二进制数的转换表
dic['0'] = "0000"; dic['1'] = "0001"; dic['2'] = "0010"; dic['3'] = "0011"; dic['4'] = "0100"; dic['5'] = "0101"; dic['6'] = "0110"; dic['7'] = "0111"; dic['8'] = "1000"; dic['9'] = "1001"; dic['A'] = "1010"; dic['B'] = "1011"; dic['C'] = "1100"; dic['D'] = "1101"; dic['E'] = "1110"; dic['F'] = "1111"; dic['a'] = "1010"; dic['b'] = "1011"; dic['c'] = "1100"; dic['d'] = "1101"; dic['e'] = "1110"; dic['f'] = "1111";

string output;
for (int i = 0; i<input.size(); i++)
{
output += dic[input[i]];
}
return output;
}

string trans_binTohex(string input)
{
map<string, string> redic;         //二进制数到十六进制数的转换表
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

string trans_hexTodec(string input)
{
return trans_binTodec(trans_hexTobin(input));
}

string trans_decTohex(unsigned long int longint)
{
string temp;
unsigned long int res;
res = longint;
int result[16];
int i = 0;
while (res >= 16)
{
result[i++] = res % 16;
res = res / 16;
}
result[i] = res;


for (int j = 0; j <= i; j++)
{
temp += trans_intTohex(result[i - j]);
}

return temp;

}

string trans_decTohex(string input)
{
LLL res = LLL(input);
string output;

while (res >= 16)
{
output = output + trans_intTohex(res % 16);
res = res / 16;
}
output += trans_intTohex(res);

reverse(output.begin(), output.end());
return output;
}

string trans_binTodec(string input)
{
HugeInteger one =  HugeInteger("1");
HugeInteger output = HugeInteger("0");
int length = input.length();
for (int i = length - 1; i >= 0; i--)
{

int power = length - i - 1;
HugeInteger roundadder = one;

if (input[i] == '1')
{
while (power)
{
roundadder = roundadder * 2;
power--;
}

output = output + roundadder;

}
}

return output.getHugeInteger();
}

char trans_intTohex(int interger)
{
if (interger >= 0 && interger <= 9)
{
return ('0' + interger);
}
else
{
return ('A' + interger - 10);
}
}

string trans_intTohex(LLL interger)
{
if (interger >= 0 && interger <= 9)
{
return (interger.hugeInteger);
}
else
{
string temp;
char tool = 'A' + (interger - 10).hugeInteger[0] - '0';
temp = temp + tool;
return temp;
}
}

string get_random(int num,int type)
{
string temptr;
int currlen = 0;
string ptr;
mysrand(time(NULL));
myrand();

while (currlen < num)
{
ptr = trans_decTohex(myrand());//产生随机数，累计填满16位


if ((currlen + ptr.length()) <= num)
{
temptr += ptr;

currlen += ptr.length();
}
else
{
for (int i = currlen; i <= num - 1; i++)
{

temptr += ptr[i - currlen];
}

currlen = num;

}
}

if (type == 0)
return temptr;
else
if (type == 1)
return trans_hexTobin(temptr);
else
return trans_binTodec(trans_hexTobin(temptr));
}

string get_prime(int num)
{
while (1) {
bool flag = false;
string random = get_random(num, 2);
LLL output = LLL(random);
if (output % 2 == 0) output = output + 1;

for (int i=0; i <= 295; i++)
{
if (output % constprime[i] == 0)
{
flag = true;
break;
}

}
if (flag) continue;
if (Miller(output, 5))
{
return output.hugeInteger;
break;
}
}
}


void mysrand(unsigned long int seed)
{
rand_seed = seed;
}

int  myrand()
{
rand_seed = (rand_seed * 16807L) % ((1 << 31) - 1);
return rand_seed;
}

HugeInteger::HugeInteger() {
this->hugeInteger = "null";
}

HugeInteger::HugeInteger(string HugeInteger1) {
this->hugeInteger = HugeInteger1;
}
HugeInteger::HugeInteger(int HugeInteger1) {

char t[256];
sprintf(t, "%d", HugeInteger1);
this->hugeInteger = t;
}

string HugeInteger::getHugeInteger() {
return hugeInteger;
}

void HugeInteger::setHugeInteger(const string& hugeInteger) {
this->hugeInteger = hugeInteger;
}
bool HugeInteger::operator==(const HugeInteger & bHugeInteger)
{
HugeInteger temp = *this - bHugeInteger;
if (temp.hugeInteger[0] != '0')
return false;
else
return true;
}
bool HugeInteger::operator==(const int i)
{
HugeInteger temp = *this - i;
if (temp.hugeInteger[0] != '0')
return false;
else
return true;
}
bool HugeInteger::operator!=(const HugeInteger & bHugeInteger)
{
HugeInteger temp = *this - bHugeInteger;
if (temp.hugeInteger[0] != '0')
return true;
else
return false;

}
bool HugeInteger::operator!=(const int i)
{
HugeInteger temp = *this - i;
if (temp.hugeInteger[0] != '0')
return true;
else
return false;
}
bool HugeInteger::operator>(const HugeInteger & bHugeInteger)
{
HugeInteger temp = *this - bHugeInteger;


if ((temp.hugeInteger[0] != '-') && (temp != 0))
return true;
else
return false;
}
bool HugeInteger::operator>(const int i)
{
HugeInteger temp = *this - i;
if ((temp.hugeInteger[0] != '-') && (temp.hugeInteger[0] != '0'))
return true;
else
return false;
}
bool HugeInteger::operator>=(const HugeInteger & bHugeInteger)
{
if (*this > bHugeInteger || *this == bHugeInteger)
return true;
else
return false;
}
bool HugeInteger::operator>=(const int i)
{
if (*this > i || *this == i)
return true;
else
return false;
}
bool HugeInteger::operator<(const HugeInteger & bHugeInteger)
{
if (*this > bHugeInteger || *this == bHugeInteger) return false;
else return true;
}
bool HugeInteger::operator<(const int i)
{
if (*this > i || *this == i) return false;
else return true;
}
bool HugeInteger::operator<=(const HugeInteger & bHugeInteger)
{
if (*this < bHugeInteger || *this == bHugeInteger)
return true;
else
return false;
}
bool HugeInteger::operator<=(const int i)
{
if (*this < i || *this == i)
return true;
else
return false;
}
//加法运算
char* getAddNumber(char* HugeInteger1, char* HugeInteger2) {
int maxlen = max(strlen(HugeInteger1), strlen(HugeInteger2));
//多两个字符，一个是结束符'/0'，另一个保存当两个数最高位相加后有进位的情况
char* p = new char[maxlen + 2];
//结束符
*(p + maxlen + 1) = '\0';
//声明两个指针分别指向HugeInteger1和HugeInteger2的末尾，不含结束符
char* pHugeInteger1 = HugeInteger1 + strlen(HugeInteger1) - 1;
char* pHugeInteger2 = HugeInteger2 + strlen(HugeInteger2) - 1;
int m = 0;
int n = 0;
//进位
int c = 0;
for (int i = maxlen; i > 0; i--) {
m = n = 0;
//因为当pHugeInteger1到达第一个字符时，即pHugeInteger1=a时，也要进行计算，所以这里用(pHugeInteger1-1)来判断
//'0'的Asic是48，减去48转成数字
if ((pHugeInteger1 + 1) != HugeInteger1) {
m = *pHugeInteger1 - 48;
pHugeInteger1--;
}
if ((pHugeInteger2 + 1) != HugeInteger2) {
n = *pHugeInteger2 - 48;
pHugeInteger2--;
}
//为p指针的第i个字符赋值
*(p + i) = (m + n + c) % 10 + 48;
//取得进位
c = (m + n + c) / 10;
}
*p = 48 + c;

if (*p == '0') {                        //如果结果的第一位是‘0’，表示没有进位
return p + 1;                     //返回第二位的指针，以去除第一位多余的0
}
return p;
}

//减法运算
char* getSubNumber(char* HugeInteger1, char* HugeInteger2) {

int isNegative = 0;                   //定义结果是否为负数的标志，初始为0,不是负数

int lHugeInteger1 = strlen(HugeInteger1), lHugeInteger2 = strlen(
HugeInteger2);
if (lHugeInteger1 > lHugeInteger2) { //HugeInteger1的位数大于HugeInteger2，则HugeInteger1大
isNegative = 0;
}
else if (lHugeInteger1 < lHugeInteger2) { //HugeInteger1的位数小于HugeInteger2,则HugeInteger1小
char* temp = HugeInteger1;
HugeInteger1 = HugeInteger2;
HugeInteger2 = temp;

isNegative = 1;
}
else {                                                  //位数相等
char* pHugeInteger1 = HugeInteger1;
char* pHugeInteger2 = HugeInteger2;

for (int c = 0; c < lHugeInteger1; c++) {                  //依次比较每一位数的大小
if ((*(pHugeInteger1 + c)) >(*(pHugeInteger2 + c))) {         //不等，则比较大小
isNegative = 0;
break;
}
else if ((*(pHugeInteger1 + c)) <(*(pHugeInteger2 + c))) {
char* temp = HugeInteger1;
HugeInteger1 = HugeInteger2;
HugeInteger2 = temp;
isNegative = 1;
break;
}
else {                                          //相等继续
continue;
}
}
}

int maxlen = max(strlen(HugeInteger1), strlen(HugeInteger2));
//应为HugeInteger1始终大于HugeInteger2,不考虑被减数最高位不够减的情况
char* p = new char[maxlen + 1];
//最后一位是结束符
*(p + maxlen) = '\0';
//声明两个指针分别指向HugeInteger1和HugeInteger2的末尾，不包含结束符
char* pHugeInteger1 = HugeInteger1 + strlen(HugeInteger1) - 1;
char* pHugeInteger2 = HugeInteger2 + strlen(HugeInteger2) - 1;
int m = 0;
int n = 0;
//借位位
int c = 0;
for (int i = maxlen - 1; i >= 0; i--) {
m = n = 0;
//'0'的Asic是48，减去48转成数字
if ((pHugeInteger1 + 1) != HugeInteger1) {
m = *pHugeInteger1 - 48;
pHugeInteger1--;
}
if ((pHugeInteger2 + 1) != HugeInteger2) {
n = *pHugeInteger2 - 48;
pHugeInteger2--;
}
//不够减，要借位
if (m < n) {
//为p指针的第i个字符赋值
*(p + i) = 10 + m - n - c + 48;
c = 1;
}
else {
//虽然够减，但是如果再算是借走的一位，那么就小于0了
if (m - n - c < 0)
*(p + i) = 10 + m - n - c + 48;
else {
*(p + i) = m - n - c + 48;
c = 0;
}
}
}
if (isNegative == 1) {
if (*p == '0') {                        //如果结果的第一位是‘0’，表示没有进位
char* temp = new char[maxlen];
temp = p + 1;                            //返回第二位的指针，以去除第一位多余的0
char* newp = new char[maxlen + 1];
*newp = '-';                             //首地址带符号‘-’
for (int i = 0; i < maxlen; i++) {
*(newp + 1 + i) = *(temp + i);
}
return newp;                          //返回带符号的新字符串
}
else {
char* temp2 = new char[maxlen + 1];
temp2 = p;
char* newp2 = new char[maxlen + 2];
*newp2 = '-';                             //首地址带符号‘-’
for (int i = 0; i < maxlen + 1; i++) {
*(newp2 + 1 + i) = *(temp2 + i);
}
return newp2;                          //返回带符号的新字符串
}
}
else {
//这里存在首位为0的位移情况

while (*p == '0') {                        //如果结果的第一位是‘0’，表示没有进位
if (*(p + 1) == '\0') return p;
p = p + 1;							   //后移一位
}

return p;
}
}

//乘法运算
char* getMultNumber(char* a, char* b) {
int sizea = strlen(a);
int sizeb = strlen(b);
char* p = new char[sizea + sizeb + 1];
//两数相乘所得的积的位数最大为两个数位数只和，多申请一位放'\0'
char* pA = a + sizea - 1;
char* pB = b + sizeb - 1;
int m = 0;
int n = 0;
//进位
int c = 0;
//存放该位置原有的数
int s = 0;
//记数
int i = 0;
int j = 0;
//具体实现过程详见说明文件
for (i = 0; i < sizea; i++) {
m = *(pA - i) - 48;
c = 0;
for (j = 0; j < sizeb; j++) {
n = *(pB - j) - 48;
//判断该位置原来是否为0
if ((*(p + i + j) >= '0') && (*(p + i + j) <= '9'))
s = *(p + i + j) - 48;
else
s = 0;
*(p + i + j) = (m * n + c + s) % 10 + 48;
c = (m * n + c + s) / 10;
}
*(p + i + j) = 48 + c;
}
if (c > 0)
*(p + i + j) = '\0';
else
*(p + i + j - 1) = '\0';

int size1 = strlen(p) - 1;
int size2 = (size1 + 1) / 2;
char temp;
for (int i = 0; i < size2; i++) {
temp = p[i];
p[i] = p[size1 - i];
p[size1 - i] = temp;
}
return p;
}

//除法运算（保留个位）
string getDivNumber(const string &str1, const string &str2)  //  str1/str2
{
int i;
int length, len1, len2, len, index;
bool flag;

len1 = str1.length();
len2 = str2.length();
length = len1 - len2;
if (length<0) return "0";

int *num1 = new int[len1 + 1];
int *num2 = new int[len2 + 1];
int *quotient = new int[length + 2];

memset(num1, 0, sizeof(int)*(len1 + 1));
memset(num2, 0, sizeof(int)*(len2 + 1));
memset(quotient, 0, sizeof(int)*(length + 2));

for (i = len1 - 1, index = 0; i >= 0; i--)
{
num1[index++] = str1[i] - '0';
}
for (i = len2 - 1, index = 0; i >= 0; i--)
{
num2[index++] = str2[i] - '0';
}

while (true)
{
for (i = len1 - 1; i >= 0; i--)
{
if (num1[i])
{
len1 = i + 1;
break;
}
if (i == 0) len1 = 0;
}

len = len1 - len2;
if (len<0) break;

flag = false;
index = 0;

for (i = len1 - 1; i >= len; i--)
{
if (num1[i] == num2[i - len]) continue;
else if (num1[i]<num2[i - len])
{
flag = true;
break;
}
else
{
break;
}
}

if (flag) --len;
if (len<0) break;

while (++index)
{
flag = false;
for (i = len1 - 1; i >= len; i--)
{
if (num1[i] == num2[i - len]) continue;
else if (num1[i]<num2[i - len])
{
flag = true;
break;
}
else
{
break;
}
}
if (flag)
{
--index;
break;
}

for (i = len; i<len1; i++)
{
num1[i] -= num2[i - len];
if (num1[i]<0)
{
num1[i] += 10;
--num1[i + 1];
}
}
}
if (index == 0) break;
else quotient[len] = index;
}

string ans;
flag = false;
for (i = length; i >= 0; i--)
{
if (flag || quotient[i])
{
flag = true;
ans += '0' + quotient[i];
}
}
if (!flag) ans = "0";

delete[] num1;
delete[] num2;
delete[] quotient;

return ans;
}

//重载<<
ostream& operator<<(ostream& output, const HugeInteger& aHugeInter) {

output << aHugeInter.hugeInteger;
return output;
}

//重载+
HugeInteger operator +(const HugeInteger& aHugeInteger,
const HugeInteger& bHugeInteger) {

const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = bHugeInteger.hugeInteger.c_str();

return HugeInteger(getAddNumber((char*)a, (char*)b));

}
HugeInteger operator +(const HugeInteger& aHugeInteger, const string s) {
const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = s.c_str();

return HugeInteger(getAddNumber((char*)a, (char*)b));
}
HugeInteger operator +(const HugeInteger& aHugeInteger, const int i) {
char t[256];
sprintf(t, "%d", i);
string temp = t;
const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = temp.c_str();

return HugeInteger(getAddNumber((char*)a, (char*)b));
}

//重载-
HugeInteger operator -(const HugeInteger& aHugeInteger,
const HugeInteger& bHugeInteger) {

const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = bHugeInteger.hugeInteger.c_str();

return HugeInteger(getSubNumber((char*)a, (char*)b));

}
HugeInteger operator -(const HugeInteger& aHugeInteger, const string s) {
const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = s.c_str();

return HugeInteger(getSubNumber((char*)a, (char*)b));
}

HugeInteger operator -(const HugeInteger& aHugeInteger, const int i) {
char t[256];
sprintf(t, "%d", i);
string temp = t;
const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = temp.c_str();

return HugeInteger(getSubNumber((char*)a, (char*)b));
}
//重载*
HugeInteger operator *(const HugeInteger& aHugeInteger,
const HugeInteger& bHugeInteger) {

string stra = aHugeInteger.hugeInteger;
string strb = bHugeInteger.hugeInteger;
strb.substr(0, 1);
stra.substr(0, 1);

//考虑如何去除字符数组第一个
if (aHugeInteger.hugeInteger[0] != '-' && bHugeInteger.hugeInteger[0] != '-')
{
const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = bHugeInteger.hugeInteger.c_str();

return HugeInteger(getMultNumber((char*)a, (char*)b));
}
else
if(aHugeInteger.hugeInteger[0] != '-' && bHugeInteger.hugeInteger[0] == '-')
{
const char* a = aHugeInteger.hugeInteger.c_str();
const char* b = strb.c_str();
return HugeInteger(getMultNumber((char*)a, (char*)b));
}
else
if (aHugeInteger.hugeInteger[0] == '-' && bHugeInteger.hugeInteger[0] != '-')
{
const char* a = stra.c_str();
const char* b = bHugeInteger.hugeInteger.c_str();
return HugeInteger(getMultNumber((char*)a, (char*)b));

}
else
{
const char* a = stra.c_str();
const char* b = strb.c_str();
return HugeInteger(getMultNumber((char*)a, (char*)b));
}

}
HugeInteger operator *(const HugeInteger& aHugeInteger, const string s) {
const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = s.c_str();

return HugeInteger(getMultNumber((char*)a, (char*)b));
}

HugeInteger operator *(const HugeInteger& aHugeInteger, const int i) {

char t[256];
sprintf(t, "%d", i);
string temp = t;
const char* a = aHugeInteger.hugeInteger.c_str();    //sting转换成char*
const char* b = temp.c_str();

return HugeInteger(getMultNumber((char*)a, (char*)b));
}

//重载/
HugeInteger operator /(const HugeInteger& aHugeInteger,
const HugeInteger& bHugeInteger) {

return HugeInteger(getDivNumber(aHugeInteger.hugeInteger, bHugeInteger.hugeInteger));

}
HugeInteger operator /(const HugeInteger& aHugeInteger, const string s) {

return HugeInteger(getDivNumber(aHugeInteger.hugeInteger, s));
}

HugeInteger operator /(const HugeInteger& aHugeInteger, const int i) {

char t[256];
sprintf(t, "%d", i);
string temp = t;

return HugeInteger(getDivNumber(aHugeInteger.hugeInteger, temp));
}

HugeInteger operator%(const HugeInteger & aHugeInteger, const HugeInteger & bHugeInteger)
{
if ((aHugeInteger - bHugeInteger).hugeInteger[0] == '-') return aHugeInteger;
HugeInteger temp = aHugeInteger / bHugeInteger;
HugeInteger output = aHugeInteger - (bHugeInteger*temp);
return output;
}

HugeInteger operator%(const HugeInteger & aHugeInteger, const string s)
{
if ((aHugeInteger - s).hugeInteger[0] == '-') return aHugeInteger;

HugeInteger bHugeInteger = HugeInteger(s);
HugeInteger temp = aHugeInteger / bHugeInteger;
HugeInteger output = aHugeInteger - (bHugeInteger*temp);
return output;
}

HugeInteger operator%(const HugeInteger & aHugeInteger, const int i)
{
if ((aHugeInteger - i).hugeInteger[0] == '-') return aHugeInteger;
HugeInteger bHugeInteger = HugeInteger(i);
HugeInteger temp = aHugeInteger / bHugeInteger;
HugeInteger output = aHugeInteger - (bHugeInteger*temp);
return output;
}










LLL modulo(LLL base, LLL exponent, LLL mod)
{
LLL x = 1;
LLL y = base;
while (exponent > 0)
{

if (exponent % 2 == 1)
x = (x * y) % mod;
y = (y * y) % mod;
exponent = exponent / 2;
}
return x % mod;
}


bool Miller(LLL p, int iteration)
{
if (p < 2)
{
return false;
}
if (p != 2 && p % 2 == 0)
{
return false;
}

LLL s = p - 1;

while (s % 2 == 0)
{
s = s/ 2;
}

for (int i = 0; i < iteration; i++)
{
cout << "第"<<i<<"轮开始"<<endl;

LLL a = rand() % (p - 1) + 1, temp = s;
LLL mod = modulo(a, temp, p);


while (temp != p - 1 && mod != 1 && mod != p - 1)
{
mod = mulmod(mod, mod, p);
temp = temp* 2;
}
if (mod != p - 1 && temp % 2 == 0)
{

return false;
}
}
return true;
}

LLL mulmod(LLL a, LLL b, LLL mod)
{
LLL x = 0, y = a % mod;
while (b > 0)
{
if (b % 2 == 1)
{
x = (x + y) % mod;
}
y = (y * 2) % mod;
b = b/ 2;
}
return x % mod;
}

void RSA::initial(LLL input)
{
//选取512bit的素数
LLL p = LLL(get_prime(64));
LLL q = LLL(get_prime(64));

while ( p==q )
{
q = LLL(get_prime(64));
}

cout << "everything is ok" << endl;

this->n = p * q;
LLL f_n = (p - 1)*(q - 1);

//随机选取正整数e,使其与f_n互素
this->e = input;

this->d  = get_reverse(e, f_n);
}

string RSA::encrypt(LLL plain)
{
this->plain = plain;
this->encryptxt = quick_power(this->plain,this->e,this->n);
return this->encryptxt.hugeInteger;
}

string RSA::decrypt(LLL encryptxt)
{
this->encryptxt = encryptxt;
this->plain = quick_power(this->encryptxt, this->d, this->n);
return this->plain.hugeInteger;
}



//拓展欧几里得算法
LLL exgcd(LLL a, LLL b, LLL &x, LLL &y)
{
if (b == 0) {
x = 1;
y = 0;
cout << "最大公约数为：" << a << endl;
cout << "x:" << x<<" ";
cout << "y:" << y << endl;
return a;
}
LLL xx, yy;
LLL gcd = exgcd(b, a%b, xx, yy);
x = yy;
y = xx - a / b * yy;
cout << "最大公约数为：" << a << endl;
cout << "x:" << x << " ";
cout << "y:" << y << endl;
return gcd;
}

//获取a对于b的
LLL get_reverse(LLL a, LLL b)   //求a对b取模的逆元
{
LLL x, y;
exgcd(a, b, x, y);

return x;
}

//快速指数算法
// a^k=b(mod m)
LLL quick_power(LLL a, LLL k, LLL m) {
LLL b = 1;
while (k >= 1) {
if ((k % 2)!=0 ) b = (a*b) % m;
a = (a*a) % m;
k = k/ 2;
}
return b;
}
*/
Rsa::Rsa()
{
}

Rsa::~Rsa()
{
}

void Rsa::init(unsigned int n)
{
	srand(time(NULL));
	//产生大素数p、q
	_p=createPrime(n,10);
	_q=createPrime(n,10);
	//计算N
	N=_p*_q;
	//计算出欧拉数
	_ol=(_p-1)*(_q-1);
	//加密指数e
	createExp(_ol);
	//d
}

BigInt Rsa::createOddNum(unsigned int n)
{//生成长度为n的奇数
	n=n/4;
	static unsigned char hex_table[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	if(n)
	{
		ostringstream oss;
		for(std::size_t i=0;i<n-1;++i)
			oss<<hex_table[rand()%16];
		oss<<hex_table[1];
		string str(oss.str());
		return BigInt(str);
	}
	else
		return BigInt::Zero;
}

bool Rsa::isPrime(const BigInt& n,const unsigned int k)
{//判断素数
	assert(n!=BigInt::Zero);
	if(n==BigInt::Two)
		return true;

	BigInt n_1=n-1;
	BigInt::bit b(n_1);//二进制位
	if(b.at(0)==1)
		return false;

	for(std::size_t t=0;t<k;++t)
	{
		BigInt a=createRandomSmallThan(n_1);//随机数
		BigInt d(BigInt::One);
		for(int i=b.size()-1;i>=0;--i)
		{
			BigInt x=d;
			d=(d*d)%n;
			if(d==BigInt::One && x!=BigInt::One && x!=n_1)
				return false;

			if(b.at(i))
			{
				assert(d!=BigInt::Zero);
				d=(a*d)%n;
			}
		}
		if(d!=BigInt::One)
			return false;
	}
	return true;
}

BigInt Rsa::createRandomSmallThan(const BigInt& a)
{
	unsigned long t=0;
	do
	{
		t=rand();
	}while(t==0);

	BigInt mod(t);
	BigInt r=mod%a;
	if(r==BigInt::Zero)
		r=a-BigInt::One;	
	return r;
}

BigInt Rsa::createPrime(unsigned int n,int it_count)
{//生成长度为n的素数
	assert(it_count>0);
	BigInt res=createOddNum(n);
	while(!isPrime(res,it_count))
	{
		res.add(BigInt::Two);
	}
	return res;
}

void Rsa::createExp(const BigInt& ou)
{//从一个欧拉数中生成公钥、私钥指数
	//e=5;
	e=65537;
	_d=e.extendEuclid(ou);
}

BigInt Rsa::encryptByPu(const BigInt& m)
{//公钥加密
	return m.moden(e,N);
}

BigInt Rsa::decodeByPr(const BigInt& c)
{//私钥解密
	return c.moden(_d,N);
}

BigInt Rsa::encryptByPr(const BigInt& m)
{//私钥加密
	return decodeByPr(m);
}

BigInt Rsa::decodeByPu(const BigInt& c)
{//公钥解密
	return encryptByPu(c);
}