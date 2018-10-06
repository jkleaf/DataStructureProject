#include <iostream>
#include <list>
#include "SQLStat.h"
using namespace std;
struct goods{
	string goodsId;
	string goodsName;
	double goodsPrice;
	int goodsNum;
	int goodsSold;
};
list <goods> l;
int main()
{
	initHandle();
	mysql_init(&mysql);
	ConnectSQL();
	int n;
	string id,name;
	double price;
	int num,sold;
	cout<<"input n\n";
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>id>>name>>price>>num;
		goods g;
		g.goodsId=id;
		g.goodsName=name;
		g.goodsNum=num;
		g.goodsPrice=price;
		g.goodsSold=0;
		l.push_back(g);
		insertSQL("fuck_table",id,name,price,num,0);
	}
	cout<<"remove use id:\n";
	cin>>id;
	deleteSQLId("fuck_table",id);
	cout<<"update use id:\n";
	cin>>id>>sold;
	updateSQLId("fuck_table",sold,id);
	for(list<goods>::iterator iter = l.begin();iter!=l.end();++iter)
		cout<<(*iter).goodsId<<"\t"<<(*iter).goodsName<<
			"\t"<<(*iter).goodsNum<<(*iter).goodsPrice<<
			"\t"<<(*iter).goodsSold<<endl;
	return 0;
}
