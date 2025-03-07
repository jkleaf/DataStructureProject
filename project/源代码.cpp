/*商品管理系统*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cctype>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include<iomanip>
#include <fstream>
#include <windows.h>
#include "SQLStat.h"
#include "mainMenu.h"
using namespace std;
/*2018.1.2*/
struct  goods {//商品属性结构体 
	string id;//商品编号
	string name;//商品名称
	double price;//商品售价
	int  number;//商品数量
	int sold=0;//销售数据
	double cost;//进价 
	double profits=0;//利润 
	int sold_before=0;//前一次sold
	struct goods *next;
};
struct sort1 {//排序结构体 
	string id;
	string name;//商品名称
	double price;//商品售价
	int  number;//商品数量
	int sold;
};

bool Isrepeat(goods *head,string ID,string name) {//判断编码或名称是否重复 
	if(head==NULL) return true; 
	goods* p=head->next;
	while(p) {
		if(p->id==ID||p->name==name) {//比较商品ID或名称  
			return true;
		}
		p=p->next;
	}
	return false;
}
/*********************/
void repeatCheck(goods *head) {//查重函数 
	printf("您输入了重复的编码或名称，请重新输入\n");
	printf("是否需要进行编码与名称查重或是输出已使用编码和名称\n");
	printf("****1:编码查重***********2:名称查重****3：输出已使用的编码和名称（输入其他则继续输入商品信息）\n");
	/*********/
	string x;
	cin>>x;
	if(isInteger3(x,3)) {//三个选择菜单 
		switch(x[0]) {
			case '1': {
				cout<<"请输入需要查重的编码"<<endl;
				string ID;
				int flag=0;
				while(!flag) {
d:
					cin>>ID;
					if(checkNum(ID,0)) {

						if(Isrepeat(head,ID," ")) {
							cout<<"已存在该编码"<<endl;
						} else cout<<"该编码尚未被使用"<<endl;
					} else {
						cout<<"输入编码不符合系统要求，请重新输入"<<endl;
						goto d;
					}
					cout<<"是否继续查询？是请输入0，否则继续输入商品信息"<<endl;
					string flagString;
					cin>>flagString;
					flag=(flagString.length()==1&&flagString[0]=='0')?0:1;
				}
				break;
			}
			case '2':{	
				cout<<"请输入需要查重的名称"<<endl;
				string NAME;
				int flag=0;
				while(!flag) {
					cin>>NAME;
						if(Isrepeat(head,"-1",NAME)) {
							cout<<"已存在该名称"<<endl;
						} else cout<<"该名称尚未被使用"<<endl;
					cout<<"是否继续查询？是请输入0，否则继续输入商品信息"<<endl;
					string flagString;
					cin>>flagString;
					flag=(flagString.length()==1&&flagString[0]=='0')?0:1;
				}	
				break;
			} 
			case '3': {
				goods *temp=head->next;
				while(temp) {
					cout<<"编码："<<temp->id<<"    名称："<<temp->name<<endl;
					temp=temp->next;
				}
				break;
			}
		}
	}
}
bool selectToImport()//选择是否导入数据库 
{
	printf("输入Y或y执行导入数据库,输入其他则不执行导入.\n");
	string n;
	cin>>n;
	if(n[0]=='Y'||n[0]=='y') return true;
	else return false;	
} 
/**********************/
void menu(goods*head);
long zongshu;
bool flag_import;
bool repeat_first;
bool print_judge =true;
bool displaymainMenu;
goods *create() {//创建链表 
	goods *head,*p;
	head=p=new goods;
	/******************/
	string n,id,name,price,number,cost;
a:
	printf("请输入商品种类数量\n");
	cin>>n;
	if(!isInteger1(n)) {
		printf("输入错误,请输入正整数\n");
		goto a;
	} else {
		zongshu=(long)convertInteger(n);
		if(!flag_import&&selectToImport()){//登录默认同步数据库 
			printf("*****已选择将输入数据导入数据库*****\n"); 
			flag_import=true;
		}else{
			printf("*****后续操作将不会同步到数据库*****\n");
			flag_import=false;
		}
		printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
		long num=zongshu;
		while(num--) {
b:
			cin>>id>>name>>cost>>price>>number;
			if(!checkStrDigit(id)||!checkStrDigit(name)){//输儒ID，name长度检测 
				printf("输入编码或名称长度太长，请重新输入\n");
				goto b; 
			}
			else if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||(!isInteger1(cost)&&!isFraction(cost))||!isInteger1(number)) {
				//id,price,cost,number格式检查 
				printf("输入错误，请检查数据输入格式，请重新输入\n");
				goto b;
			} 
			else if((isInteger1(price)? (double)convertInteger(price):convertFraction(price))<(isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost))) {
				printf("输入商品售价低于进价，确定输入请输入yes,否则输入任意字符后重新输入\n");
				string pd;
				cin>>pd;
				if(pd!="yes"){
					printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
					goto b;
				}
			goto c; 
			
			}
			 if(repeat_first&&Isrepeat(head,id,name)) {
			 	//查重检测 
				repeatCheck(head);
				printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
				goto b;
			}
			else{
				c: 
				//插入链表末端 
				p->next=new goods;
				p=p->next;
				p->next=NULL;
				p->id=id;
				p->name=name;
				p->price=isInteger1(price)? (double)convertInteger(price):convertFraction(price); 
				p->cost=isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost);
				p->number=convertInteger(number);
				if(flag_import){
					insertSQL(getTablename(),p->id,p->name,p->price,p->number,0,0,p->cost,0);
				}
				repeat_first=true;
			}
		}
		p->next=NULL;
		return head;
	}
	/******************/
}
goods* assignCreate(string table_name)//数据库数据导出给链表赋值 
{
	if(querySQL(table_name)){
		res=mysql_store_result(&mysql);
	}else 
		return NULL;
	goods *head,*p;
	head=p=new goods;
	zongshu=(long)mysql_num_rows(res);
	while(row=mysql_fetch_row(res)){
		p->next=new goods;
		p=p->next;
		p->id=row[0];
		p->name=row[1];
		p->price=isInteger1(row[2])?(double)convertInteger(row[2]):convertFraction(row[2]);
		p->number=convertInteger(row[3]);
		p->sold=convertInteger(row[4]);
		p->sold_before=convertInteger(row[5]);
		p->cost=isInteger1(row[6])?(double)convertInteger(row[6]):convertFraction(row[6]);
		p->profits=isInteger1(row[7])?(double)convertInteger(row[7]):convertFraction(row[7]);
	}
	p->next=NULL;
	freeResult(res); 
	return head; 
}
void print( goods*head) {//打印(输出)系统数据表格 
    color(15); 
	goods*p=head->next;
	if(p==NULL) printf("                                                                   *********************************当前管理系统无数据****************************************\n");
	else{
	
	printf("                                    			*********************************************输入商品内容如下*******************************************\n");
	printf("                                    			    _________________________________________________________________________________________________\n"); 
	printf("                                    			   |      商品编码               商品名称                 商品售价               商品销售情况        |\n");
		printf("                                    			   +------------------+-------------------------+-----------------------+----------------------------+\n");
	
	while(p) {

		cout<<"                                    			   |"<<setw(12)<<p->id<<"      |  "<<setw(15)<<p->name<<"        |"<<setw(15)<<p->price<<"        |   "<<setw(12)<<p->sold<<"             |"<<endl;
		
		p=p->next;
		if(p)
				printf("                                    			   +------------------+-------------------------+-----------------------+----------------------------+\n");
	}
		printf("                                    			    ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n"); }
	if(!print_judge){
		print_judge =true;
		return;
	}else
		menu(head);
}
void output()
{
	fstream fin("welcome.txt");
	string line;
	while(getline(fin,line)){
		cout<<line<<endl;
	}		
} 
void welcome(){//欢迎栏 
    color(13);
    output();
	color(15);
	system("PAUSE");
	system("cls");
}
void Revise_price(goods *head){//修改售价函数
	
	goods* p=head->next;
	color(15);
	printf("                                    			                                *******************商品编码名称表*******************(输出提供参考)\n");
	printf("                                     			                         ___________________________________________________________________________\n"); 
	printf("                                    			                        |     商品编码    |      商品名称      |      商品进价    |     商品售价   |\n");
	printf("                                    			                        +-----------------+--------------------+------------------+----------------+\n");
	while(p) {
//			printf("编号：%d    名称：%s     售价：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"                                                		        	|"<<setw(10)<<p->id<<"       |    "<<setw(10)<<p->name<<"      |"<<setw(10)<<p->cost<<"        |"<<setw(10)<<p->price<<"      |"<<endl;
//
		printf("                                                		        	+-----------------+--------------------+------------------+----------------+\n");
			
			p=p->next;
			color(15);
		}
	p=head->next;
	printf("请输入要修改商品售价的商品编码+修改后的商品售价\n");
	string n1,n2,j;
	double k; 
	a:   p=head->next;
		cin>>n1>>n2;
		if(!checkNum(n1,0)||(!isInteger1(n2)&&!isFraction(n2))) {
			printf("输入错误，请检查输入格式重新输入\n");
			goto a;
		}
		j=n1;
		k=isInteger1(n2)?(double)convertInteger(n2):convertFraction(n2);
		//遍历查找对比 
	while(p!=NULL){
		if(p->id==j){
			if(k<p->cost){
				printf("修改售价低于进价是否确认修改，确认请输入yes，否则输入任意字符后重新输入\n");
				string jd;
				cin>>jd;
				if(jd!="yes"){
					printf("请输入要修改商品售价的商品编码+修改后的商品售价\n");
					goto a;
				}
			} 
			p->profits+=(p->sold-p->sold_before)*p->price;
			p->sold_before=p->sold;
			p->price=k;
			long sum=zongshu; 
			if(flag_import)
				updateSQLSales(getTablename(),p->price,p->sold_before,p->profits,p->id);
			zongshu=sum;
			printf("修改成功\n");
			displaymainMenu=true;
			menu(head); 
		}
		p=p->next; 
	}
	printf("输入的编码不存在\n");
	printf("请重新输入商品编码+修改后的商品售价\n");
	goto a;	 
}
void change1(goods*head) {//通过编码输入销售数据 
	goods*p=head->next;
	string j,n,n1,n2;
	int k;
	color(15);
	printf("                                    			                                *******************商品编码名称表*******************(输出提供参考)\n");
	printf("                                     			                         ___________________________________________________________________________\n"); 
	printf("                                    			                        |     商品编码    |      商品名称      |      商品进价    |     商品售价   |\n");
	printf("                                    			                        +-----------------+--------------------+------------------+----------------+\n");
	while(p) {
//			printf("编号：%d    名称：%s     售价：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"                                                		        	|"<<setw(10)<<p->id<<"       |    "<<setw(10)<<p->name<<"      |"<<setw(10)<<p->cost<<"        |"<<setw(10)<<p->price<<"      |"<<endl;
//
		printf("                                                		        	+-----------------+--------------------+------------------+----------------+\n");
			
			p=p->next;
			color(15);
		}
	p=head->next;
	printf("请输入要修改商品销售数据的商品个数||此时系统内有%ld种商品（如果需要返回菜单请输入menu)\n",zongshu);
	/*******************/
a:	
	cin>>n;
	if(n=="menu")  menu(head);
	if(!isInteger1(n)) {
		printf("输入错误，请输入正整数\n");
//		menu(head);
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("输入种数大于商品管理系统中商品种数，请重新输入\n");
//		menu(head);
		goto a;
	}
	printf("                                     			***********************************输出商品列表信息作为参考*************************\n");
	print_judge=false;
	print(head);
	/*******************/
	printf("修改格式为商品编码+销售额（输入负数即代表进货)\n");
	if(flag_import)
		setColor(YELLOW);printf("**************修改将同步到数据库**************\n");setColor(WHITE);
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!checkNum(n1,0)||!isInteger2(n2)) {
			printf("输入错误，请检查输入格式重新输入\n");
			goto b;
		}
		j=n1;//convertInteger(n1);
		k=convertInteger(n2);
		/*******************/
		
		while(p) {
			if(p->id==j) {
				if(k<0)  p->number=p->number-k;
				else {
					if(k<=p->number) {
						p->sold+=k;
						p->number=p->number-k;
					} else {
						printf("销售数量大于库存，输入有误,请重新输入编码+销售额\n");
						goto b;
					}
				}
				if(flag_import)
					updateSQLId(getTablename(),p->number,p->sold,p->id);
				break;
			}
			p=p->next;
		}
		if(p==NULL) {
			printf("未找到该商品,请重新输入编码+销售额\n");
			p=head->next;
			goto b;
		}
		p=head->next;
	}
	printf("输入销售数据成功\n");
	menu(head);
}
void change2(goods*head) {//通过名称输入销售数据 
	goods*p=head->next;
	int k;
	string n,n1,n2;
	color(15);
	printf("                                    			                                *******************商品编码名称表*******************(输出提供参考)\n");
	printf("                                     			                         ___________________________________________________________________________\n"); 
	printf("                                    			                        |     商品编码    |      商品名称      |      商品进价    |     商品售价   |\n");
	printf("                                    			                        +-----------------+--------------------+------------------+----------------+\n");
	while(p) {
//			printf("编号：%d    名称：%s     售价：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"                                                		        	|"<<setw(10)<<p->id<<"       |    "<<setw(10)<<p->name<<"      |"<<setw(10)<<p->cost<<"        |"<<setw(10)<<p->price<<"      |"<<endl;
//
		printf("                                                		        	+-----------------+--------------------+------------------+----------------+\n");
			
			p=p->next;
			color(15);
		}
	p=head->next;
	printf("请输入要修改商品销售数据的商品个数||此时系统内有%ld种商品（如果需要返回菜单请输入menu)\n",zongshu);
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!isInteger1(n)) {
		printf("输入错误，请输入正整数\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("输入种数大于商品管理系统中商品种数，请重新输入\n");
		goto a;
	}
	printf("修改格式为商品名称+销售额（输入负数即代表进货)\n");
	if(flag_import)
		setColor(YELLOW);printf("**************修改将同步到数据库**************\n");setColor(WHITE);
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!isInteger2(n2)) {
			printf("输入错误，请输入正整数\n");
			goto b;
		}
		k=convertInteger(n2);
		while(p) {
			if(n1==p->name) {
				if(k<0) p->number=p->number-k;
				else {
					if(k<=p->number) {
						p->sold+=k;
						p->number=p->number-k;
					} else {
						printf("销售数量大于库存，输入有误,请重新输入编码+销售额\n");
						goto b;
					}
				}
				if(flag_import)	
					updateSQLName(getTablename(),p->number,p->sold,p->name);
				break;
			}
			p=p->next;
		}
		if(p==NULL) {
			printf("未找到该商品,请重新输入编码+销售额\n");
			p=head->next;
			goto b;
		}
		p=head->next;
	}
	printf("输入销售数据成功\n");
	menu(head);
}
void add(goods*head);
goods*seek(goods*head,int i) {//查找链表 
	goods*p=head;
	int j=0;
	while(j<i&&p) {
		p=p->next;
		j++;
	}
	return p;
}
void add(goods*head) {//在中间或尾端添加一条记录 
	string id,name,price,cost,number;
	goods*p,*q;
	printf("请输入插入位置，输入0默认插入末端||此时系统内有%ld种商品（如果需要返回菜单请输入menu)\n",zongshu);
	string n;
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!checkNum(n,0)) { //包含0
		printf("输入错误，请输入正确格式数据\n");
		goto a; 
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("插入位置有误，请重新输入\n");
		goto a;
	}
	if(num) {
		p=seek(head,num-1);
		q=new goods;
		printf("请输入要插入的新商品信息（格式为商品编号+商品名称+商品进价+商品售价+商品数量）\n");
b:
		cin>>id>>name>>cost>>price>>number;
		if(!checkStrDigit(id)||!checkStrDigit(name)){
			printf("输入编码或名称长度太长(字符不多于10位,中文不多于5位)，请重新输入\n");
			goto b; 
		}
		if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||(!isInteger1(cost)&&!isFraction(cost))||!isInteger1(number)) {
			printf("输入错误，请检查格式重新输入\n");
			goto b;
		} else if(zongshu>0&&Isrepeat(head,id,name)) {
			repeatCheck(head);
			/*******/
			printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
			goto b;
		} 
		  else if((isInteger1(price)? (double)convertInteger(price):convertFraction(price))<(isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost))) {
				printf("输入商品售价低于进价，确定输入请输入yes,否则输入任意字符后重新输入\n");
				string pd;
				cin>>pd;
				if(pd!="yes"){
					printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
					goto b;
				}
			goto f; } 
		else {
			f:
			q->id=id;
			q->name=name;
			q->price=isInteger1(price)? (double)convertInteger(price):convertFraction(price);
			q->cost=isInteger1(cost)? (double)convertInteger(cost):convertFraction(cost);
			q->number=convertInteger(number);
			q->next=p->next;
			p->next=q;
			printf("插入已成功\n");
			zongshu++;
			if(flag_import)	
				insertSQL(getTablename(),q->id,q->name,q->price,q->number,0,0,q->cost,0);
		}
	}

	else {
		bool a=true;
		if(head->next==NULL){	
			q=new goods;
			head->next=q;
			a=false;
		} 
		else{	
			goods*temp;
			p=head->next;
			while(p) {
				temp=p;
				p=p->next;
			}
			q=new goods;
			p=temp;
		}
		printf("请输入要插入的新商品信息（格式为商品编号+商品名称+商品进价+商品售价+商品数量）\n");
c:
		cin>>id>>name>>cost>>price>>number;
		if(!checkStrDigit(id)||!checkStrDigit(name)){
			printf("输入编码或名称长度太长(字符不多于10位,中文不多于5位)，请重新输入\n");
			goto b; 
		}
			if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||(!isInteger1(cost)&&!isFraction(cost))||!isInteger1(number)){
			printf("输入错误，请检查格式重新输入\n");
			goto c;
		} else if(zongshu>0&&Isrepeat(head,id,name)) {
			repeatCheck(head);
			/*******/
			printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
			goto c;
			
		}	
		else if((isInteger1(price)? (double)convertInteger(price):convertFraction(price))<(isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost))) {
				printf("输入商品售价低于进价，确定输入请输入yes,否则输入任意字符后重新输入\n");
				string pd;
				cin>>pd;
				if(pd!="yes"){
					printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
					goto c;
				}
			goto g; } 
		else {
			g: 
			q->id=id;//convertInteger(id);
			q->name=name;
			q->cost=isInteger1(cost)? (double)convertInteger(cost):convertFraction(cost); 
			q->price=isInteger1(price)? (double)convertInteger(price):convertFraction(price);
			q->number=convertInteger(number);
			if(a){
			q->next=p->next;
			p->next=q;
			}else{
				q->next=NULL;
			}
			printf("插入已成功\n");
			zongshu++;
			if(flag_import)
				insertSQL(getTablename(),q->id,q->name,q->price,q->number,0,0,q->cost,0);
		}		
	}
	menu(head);
}
void Batch_add(goods *head){//批量插入记录 
	printf("********请输入要插入商品的个数********\n");
		string n;
	a:	cin>>n;
		if(!isInteger1(n)) {
		printf("输入错误,请输入正整数\n");
		goto a;}
		int num=convertInteger(n);
		zongshu+=num;
		goods *p,*q;
		p=head->next;
		if(p==NULL)
		   p=head;
		else{
			while(p->next!=NULL){
				p=p->next;
		}}
		string id,name,cost,price,number;
		printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
	while(num--) {
b:		cin>>id>>name>>cost>>price>>number;
		if(!checkStrDigit(id)||!checkStrDigit(name)){
			printf("输入编码或名称长度太长(字符不多于10位,中文不多于5位)，请重新输入\n");
			goto b; 
		}
				if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||(!isInteger1(cost)&&!isFraction(cost))||!isInteger1(number)) {
				printf("输入错误，请检查格式重新输入\n");
				goto b;
			} 
			else if(zongshu>0&&Isrepeat(head,id,name)) {
				repeatCheck(head);
				printf("请输入商品编号 商品名称 商品售价 商品数量\n");
				goto b;
			}
			else	 if((isInteger1(price)? (double)convertInteger(price):convertFraction(price))<(isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost))) {
				printf("输入商品售价低于进价，确定输入请输入yes,否则输入任意字符后重新输入\n");
				string pd;
				cin>>pd;
				if(pd!="yes"){
					printf("请输入商品编号 商品名称 商品进价 商品售价 商品数量\n");
					goto b;
				}
			goto d; } 
			else{
				d:
				p->next=new goods;
				p=p->next;
				p->next=NULL;
				p->id=id;
				p->name=name;
				p->price=isInteger1(price)? (double)convertInteger(price):convertFraction(price);
				p->cost=isInteger1(cost)? (double)convertInteger(cost):convertFraction(cost); 
				p->number=convertInteger(number);
				long a=zongshu;
				if(flag_import){
					insertSQL(getTablename(),p->id,p->name,p->price,p->number,0,0,p->cost,0);
				}
				zongshu=a;
			}
		}
		p->next=NULL;		
		printf("插入已成功\n"); 
	menu(head);
}
void delet(goods*head) {//删除一条记录 
	goods*q,*p=head->next;
	color(15);
	printf("                                     			  			*******************商品编码名称表*******************(输出提供参考)\n");
	printf("                                     			  					_______________________________________\n"); 
	printf("                                     			  					|     商品编码    |      商品名称     |\n");
	printf("                                     			  					+----------------+--------------------+\n");
	while(p) {
			//printf("编号：%d    名称：%s     售价：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"                                     			  					|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |"<<endl;

		printf("                                     			  					+----------------+--------------------+\n");
			
			p=p->next;
		}
	p=head->next;
	int i=0;
	string j,s;
	printf("请输入要删除商品的编码或名称\n");
	cin>>s;
	goods*temp;
	if(checkNum(s,0)) {
		j=s;
		temp=head;
		while(p) {
			if(p->id==j) {
				if(flag_import)
					deleteSQLId(getTablename(),p->id);
				q=temp->next;
				temp->next=q->next;
				delete q;
				printf("删除商品信息成功\n");
				zongshu--;
				break;
			}
			temp=p;
			p=p->next;
		}
		if(p==NULL) {
			printf("不存在该商品\n");
			delet(head);
		}
	} else {
		temp=head;
		while(p) {
			if(s==p->name) {
				if(flag_import)
					deleteSQLName(getTablename(),p->name);
				q=temp->next;
				temp->next=q->next;
				delete q;
				printf("删除商品信息成功\n");
				zongshu--;
				break;
			}
			temp=p;
			p=p->next;
		}
		if(p==NULL) {
			printf("不存在该商品\n");
			delet(head);
		}
	}
	menu(head);
}
void addor(goods*head) {//选择添加或删除记录操作 
	string n;
	printf("*******请输入选择*******\n");
	printf("#####1：添加单个商品信息#####2：删除单个商品信息#####3：批量添加商品信息#####(输入menu返回菜单)\n");
	if(flag_import){ 
		setColor(YELLOW);printf("*****修改将同步到数据库*****\n");setColor(WHITE);
	}
	/*****************/
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!isInteger3(n,3)) {
		printf("输入错误，请输入正确格式\n");
		goto a;
	}
	/*****************/
	switch(n[0]-48) {
		case 1:
			add(head);
			break;
		case 2:
			{
			if(zongshu<=0 ){
				cout<<"目前商品管理系统内无商品数据，无法修改"<<endl; 
				menu(head);}
			delet(head);
			break;}
		case 3:
			Batch_add(head);
			break; 	
	}
}
void workout(goods*head) {//计算销售情况 
	string n;
	goods*p=head->next;
	color(15);
	printf("                                     			  			*******************商品编码名称表*******************(输出提供参考)\n");
	printf("                                     			  					_______________________________________\n"); 
	printf("                                     			  					|     商品编码    |      商品名称     |\n");
	printf("                                     			  					+----------------+--------------------+\n");
	while(p) {
			//printf("编号：%d    名称：%s     售价：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"                                     			  					|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |"<<endl;

		printf("                                     			  					+----------------+--------------------+\n");
			
			p=p->next;
		}
	p=head->next;
	printf("请输入要查询的商品编码（若输入-1则输出所有商品的销售总额及库存）///输入menu即可返回主菜单\n");
a:
	cin>>n;
	if(!isInteger2(n)&&n!="menu") {
		printf("输入错误，请重新输入\n");
		goto a;
	}
	if(n=="menu") menu(head); 
	if(n.length()==2&&n[0]=='-'&&n[1]=='1') {
		
		printf("                                     			_________________________________________________________________________________________________________________________\n"); 
		printf("                                     			|     商品编码           商品名称             商品售价             商品库存             商品销售量          商品利润     |\n");
		printf("                                     			+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
		while(p) {
			//printf("编号：%d    名称：%s     售价：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"                                     			|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |   "<<setw(10)<<p->price<<"       | "<<setw(13)<<p->number<<"        |  "<<setw(10)<<p->sold<<"       |";
		printf(" %8.2lf         |\n",p->profits+1.0*(p->sold-p->sold_before)*(p->price-p->cost));
		printf("                                     			+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
			
			p=p->next;
		}
	} else if(n[0]!='-') {
		string num=n;//convertInteger(n)
		while(p) {
			if(p->id==num) {
				
		printf("                                     			_________________________________________________________________________________________________________________________\n"); 
		printf("                                     			|     商品编码           商品名称             商品售价             商品库存             商品销售量         商品销售额    |\n");
		printf("                                     			+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
		cout<<"                                     			|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |   "<<setw(10)<<p->price<<"       | "<<setw(13)<<p->number<<"        |  "<<setw(10)<<p->sold<<"       |";
		printf(" %8.2lf         |\n",p->profits+1.0*(p->sold)*(p->price-p->cost));
		printf("                                     			+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
	
				break;
			}
			p=p->next;
		}
		if(p==NULL) {
			cout<<"输入有误，未找到编码为"<<num<<"的商品"<<endl; 
			workout(head);
		}
	}
	menu(head);
}
/*****************/
bool compare(sort1 a,sort1 b) {//定义排序比较方式 
	return a.sold>b.sold;
}
void top(goods*head) {//输出销售情况好的商品 
	goods *p=head->next;
	printf("请输入要输出的商品个数||||此时系统内有%ld种商品（如果需要返回菜单请输入menu)\n",zongshu);
	string n;
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!isInteger1(n)) {
		printf("输入错误,请输入正确格式\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("输入错误，此时商品管理系统商品种类小于输入数，请重新输入\n");
		goto a;
	}
	sort1 *flag=new sort1[zongshu];
	for(int i=0; i<zongshu; i++) {
		flag[i].id=p->id;
		flag[i].name=p->name;
		flag[i].number=p->number;
		flag[i].price=p->price;
		flag[i].sold=p->sold;
		p=p->next;
	}
	sort(flag,flag+zongshu,compare);
	printf("                                     			    **************************************销售情况好的商品**************************************\n") ;
	printf("                                     			_______________________________________________________________________________________________________\n"); 
	printf("                                     			|     商品编码           商品名称             商品售价             商品库存             商品销售量    |\n");
	printf("                                     			+----------------+--------------------+--------------------+----------------------+-------------------+\n");
	bool f=true;
	for(int i=0; i<num&&i<zongshu; i++) {
		cout<<"                                     			|"<<setw(10)<<flag[i].id<<"      |    "<<setw(10)<<flag[i].name<<"      |   "<<setw(10)<<flag[i].price<<"       | "<<setw(13)<<flag[i].number<<"        |  "<<setw(10)<<flag[i].sold<<"       |"<<endl;
		printf("                                     			+----------------+--------------------+--------------------+----------------------+-------------------+\n");
		if((i+1)<=zongshu&&flag[i].sold==flag[i+1].sold) {
			if(num+1<=zongshu)
				num++;
			f=false;
		}  
	
	}
	if(!f)cout<<"备注：多输出的商品是由于商品销售情况相同"<<endl; 
	delete[] flag;
	menu(head);
}
void low(goods*head) {//输出销售情况差的商品 
	goods *p=head->next;
	printf("请输入要输出的商品个数||||此时系统内有%ld种商品（如果需要返回菜单请输入menu)\n",zongshu);
	string n;
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!isInteger1(n)) {
		printf("输入错误,请输入正确格式\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("输入错误，此时商品管理系统商品种类小于输入数，请重新输入\n");
		goto a;
	}
	sort1 *flag=new sort1[zongshu];
	for(int i=0; i<zongshu; i++) {
		flag[i].id=p->id;
		flag[i].name=p->name;
		flag[i].number=p->number;
		flag[i].price=p->price;
		flag[i].sold=p->sold;
		p=p->next;
	}
	sort(flag,flag+zongshu,compare);
	printf("                                     			    ****************************************销售情况差的商品***************************************\n") ;
	printf("                                     			_______________________________________________________________________________________________________\n"); 
	printf("                                     			|     商品编码           商品名称             商品            商品销售情况          商品销售额    |\n");
	printf("                                     			+----------------+--------------------+--------------------+----------------------+-------------------+\n");
	bool f=true;
	for(int i=zongshu-1; i>zongshu-num-1&&i>=0; i--) {
			cout<<"                                     			|"<<setw(10)<<flag[i].id<<"      |    "<<setw(10)<<flag[i].name<<"      |   "<<setw(10)<<flag[i].price<<"       | "<<setw(13)<<flag[i].number<<"        |  "<<setw(10)<<flag[i].sold<<"       |"<<endl;
		printf("                                     			+----------------+--------------------+--------------------+----------------------+-------------------+\n");
		if((i-1)>=0&&flag[i-1].sold==flag[i].sold) {
			if(num+1<=zongshu)
				num++;
			f=false;
		}  
	
	}
	if(!f)cout<<"备注：多输出的商品是由于商品销售情况相同"<<endl; 
	delete[] flag;
	menu(head);
}
void search(goods* head) {//选择输出销售好或差的商品 
	printf("请输入操作码（1：查询销售火爆的商品，2：查询销售较差的商品）\n");
	string n;
d:
	cin>>n;
	if(!isInteger3(n,2)) {
	    printf("输入序号不存在，请重新输入\n");
		goto d;
	}
	switch(n[0]-48) {
		case 1:
			top(head);
			break;
		case 2:
			low(head);
			break;
	}
}
/*****************/
void deleteall(goods *head) {//删除用户所有数据 
	printf("*****此操作将删除所有该用户数据库数据******\n");
	int ret;
	if(flag_import)
		ret=MessageBox(NULL,TEXT("注意:此操作将删除所有该用户数据库数据\n是否继续？"),TEXT("清除数据"),
			MB_YESNO|MB_ICONWARNING);//MB_ICONQUESTION
	else
		ret=MessageBox(NULL,TEXT("注意:此操作将删除所有该用户当前链表数据\n是否继续？"),TEXT("清除数据"),
			MB_YESNO|MB_ICONWARNING);
	if(ret==IDYES){ 
		goods *pnext;
		pnext=head->next;
		while (pnext!=NULL) {
			goods *temp;
			temp=pnext;
			pnext=pnext->next; 
			delete temp;
		}
		head->next=NULL;
		zongshu=0;
		if(flag_import)
			truncateSQL(getTablename());
		printf("商品信息已清空\n");
	}
	menu(head);
}

void tuichu() {//退出程序 
	printf("#########欢迎下次使用########\n");
	getch();
	exit(0);
}
void qingpin(goods*head) {//清屏函数 
	system("cls");
	menu(head);
}
void menu(goods*head) {//菜单
	if(!displaymainMenu){
		drawMenu1();
		displaymainMenu=true; 
	}else{ 
		drawMenu2();
	} 
	/********************/
	string n;
a:
	cin>>n;
	if(!isInteger3(n,9)) {
		printf("输入序号不存在，请重新输入\n");
		goto a;
	}
	/********************/
	switch(n[0]-48) {
		case 0:{
			if(zongshu<=0){
				cout<<"                                     ******************目前商品管理系统内无商品数据，无法修改商品售价*****************"<<endl;
				menu(head); 
			}
			Revise_price(head);
			break;
		} 
		case 1:{
			if(zongshu<=0 ){
				cout<<"                                           *******************目前商品管理系统内无商品数据，无法修改******************"<<endl; 
				menu(head);
			} 
			change1(head);
			break;}
		case 2:{
				if(zongshu<=0 ){
				cout<<"                                           ******************目前商品管理系统内无商品数据，无法修改*******************"<<endl; 
				menu(head);
			} 
			change2(head);
			break;}
		case 3:
			addor(head);
			break;
		case 4:{
			if(zongshu<=0 ){
				cout<<"                                           ***************目前商品管理系统内无商品数据，无法计算*********************"<<endl; 
				menu(head);
			} 
			workout(head);
			break;} 
		case 5:
			print(head);
			break;
		case 6:{ 
			if(zongshu<=0){ 
				cout<<"                                       ***************目前商品管理系统内无商品数据，无法查看销售情况*************"<<endl;
				menu(head);
			}
			search(head);
			break;} 
		case 7:
			qingpin(head);
			break;
		case 8:
			tuichu();
			break;
		case 9:
			deleteall(head);
			break;
	}
}
bool select(string *username)//用户选择注册或登录数据库 
{
a:	setColor(WHITE);	
    cout<<"                                                                                                      *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl; 
	cout<<"                                                                                                     |+++++1.注册#####2.登录#####3.退出+++++|\n";
	cout<<"                                                                                                      *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl; 
	setColor(WHITE);
	string input;
	cin>>input;
	if(!isInteger3(input,3)){
		printf("输入序号不存在，请重新输入\n");
		goto a;
	}
	switch(input[0]){
		case '1': {
			cout<<"                                                                                                           ***********注册**********\n";		
			(*username)=signUp();
			return false;
		}
		case '2': {
			cout<<"                                                                                                            ***********登录***********\n";
			(*username)=signIn();
			if((*username).empty()) goto a;
//			signIn();
			return true;
		}
		case '3' : {
			tuichu(); 
		}
	}
}
bool loginMySQL()//连接并初始化数据库 
{
	string username;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	ConnectSQL();
	return select(&username);
}
void checkLoginMySQL()//判断登录数据库是否为空 
{
	goods *head;
	if(!loginMySQL()){//
		head=create();
	}else{
		head=assignCreate(getTablename());
		if(!head||!head->next){ 
			printf("                                                                                 该用户数据库为空,正在进入初始化...\n");
			printf("                                                                                      *****1.创建数据***2.退出*****\n");
			string n;
		a:	cin>>n;
			if(!isInteger3(n,2)){
				printf("输入序号不存在，请重新输入\n");
				goto a;
			}
			switch(n[0]){
				case '1':{
					head=create();		
					break;
				}
				case '2':{
					tuichu();
					break;
				}
			}
		}else
			flag_import=true;
	}
	menu(head);
}
int main() {//主函数 
	HWND consle = GetForegroundWindow();
	ShowWindow(consle, SW_MAXIMIZE);
	welcome();
	checkLoginMySQL();	
	return 0;
}

