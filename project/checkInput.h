#include <string>
#include <cmath>
using namespace std;
int convertInteger(string s) {//转换整数
	int i=0;
	if(s[0]=='-') i++;
	int n=0;
	for(; i<s.length(); i++)
		n=n*10+s[i]-48;
	return s[0]=='-'? -n:n;
}
double convertFraction(string s) { //转换小数(价格)
	int i,j;
	double n=0.0;
	for(i=0; s[i]!='.'; i++) {
		n=n*10+s[i]-48;
	}
	double t=n;
	n=0.0;
	for(j=1; j<=3; j++) {
		if(s[i+j]=='\0') return t+n;
		n+=(s[i+j]-48)/pow(10,j);
	}
	return t+(int)(n*100+0.5)/100.0;
}
bool checkNum(string s,int i) {
	while(s[i]) {
		if(isdigit(s[i])) i++;
		else return false;
	}
	if(i==s.length())
		return true;
	return false;
}
bool isInteger1(string s) {//判断整数(不包含0) 
	if(s[0]=='0') return false;
	return checkNum(s,0);
}
bool isInteger2(string s) { //判断整数(包含负数)
	int i=0;
	if(s[0]=='-') {
		i++;
		if(s[i]=='0') return false;
	}
	return checkNum(s,i);
}
bool isInteger3(string s,int n) { //判断个位序号(包含0) 
	if(s.length()!=1) return false;
	 for(int i=0; i<=n; i++)
		if(s[0]-48==i) return true;
	return false;
}
bool isFraction(string s) {//判断小数 
	if(s[0]=='0'&&s[1]!='.') return false;
	int i=0,flag=0;
	while(s[i]) {
		if(flag&&s[i]=='.') return false;
		if(isdigit(s[i])) i++;
		else if(s[i]=='.'&&!flag) {
			flag=1;
			i++;
		} else return false;
	}
	if(i==s.length()&&flag)
		return true;
	return false;
}
bool checkStrDigit(string s)//判断字符串位数，进行限制 
{
	return s.length()<=10;
}
bool invalidStr(string str)//判断非法输入 
{
	int i=0;
	while(str[i]){
		if(isalpha(str[i])||isdigit(str[i])||str[i]=='_') i++;
		else return true;
	}
	return !(i==str.length());
}
