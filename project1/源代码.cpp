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
#include <windows.h>
#include "SQLStat.h" 
using namespace std;
/*2018.1.2*/
struct  goods {
	string id;//商品编号
	string name;//商品名称
	double price;//商品价格
	int  number;//商品数量
	int sold=0;//销售数据
	struct goods *next;
};
struct sort1 {
	string id;
	string name;//商品名称
	double price;//商品价格
	int  number;//商品数量
	int sold;
};
bool Isrepeat(goods *head,string ID,string name) {
	if(head==NULL) return true; 
	goods* p=head->next;
	while(p) {
		if(p->id==ID||p->name==name) {
			return true;
		}
		p=p->next;
	}
	return false;
}
/*********************/
bool checkNum(string s,int i) {
	while(s[i]) {
		if(isdigit(s[i])) i++;
		else return false;
	}
	if(i==s.length())
		return true;
	return false;
}
bool isInteger1(string s) {//不包含0
	if(s[0]=='0') return false;
	return checkNum(s,0);
}
bool isInteger2(string s) { //负数
	int i=0;
	if(s[0]=='-') {
		i++;
		if(s[i]=='0') return false;
	}
	return checkNum(s,i);
}
bool isInteger3(string s,int n) {
	if(s.length()!=1) return false;
	for(int i=1; i<=n; i++)
		if(s[0]-48==i) return true;
	return false;
}
bool isFraction(string s) {
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
void repeatCheck(goods *head) {
	printf("您输入了重复的编码或名称，请重新输入\n");
	printf("是否需要进行编码与名称查重或是输出已使用编码和名称\n");
	printf("****1:编码查重***********2:名称查重****3：输出已使用的编码和名称（输入其他则继续输入商品信息）\n");
	/*********/
	string x;
	cin>>x;
	if(isInteger3(x,3)) {
		switch(x[0]) {
			case '1': {
				cout<<"请输入需要查重的编码"<<endl;
				string ID;
				int flag=0;
				while(!flag) {
d:
					cin>>ID;
					if(isInteger1(ID)) {

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
bool selectToImport()
{
	printf("输入Y或y执行导入数据库,输入其他则不执行导入.\n");
	string n;
	cin>>n;
	if(n[0]=='Y'||n[0]=='y') return true;
	else return false;	
} 
/**********************/
void menu(goods*head);
int zongshu;
bool flag_import;
goods *create() {
	goods *head,*p;
	head=p=new goods;
	/******************/
	string n,id,name,price,number;
a:
	printf("请输入商品种类数量\n");
	cin>>n;
	if(!isInteger1(n)) {
		printf("输入错误,请重新输入\n");
		goto a;
	} else {
		zongshu=convertInteger(n);
		if(selectToImport()){
			printf("*****已选择将输入数据导入数据库*****\n"); 
			flag_import=true;
		}else{
			printf("*****后续操作将不会同步到数据库*****\n");
			flag_import=false;
		}
		printf("请输入商品编号 商品名称 商品价格 商品数量\n");
		int num=zongshu;
		while(num--) {
b:
			cin>>id>>name>>price>>number;
			if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
				printf("输入错误，请重新输入\n");
				goto b;
			} 
			else if(Isrepeat(head,id,name)) {
				repeatCheck(head);
				printf("请输入商品编号 商品名称 商品价格 商品数量\n");
				goto b;
			}
			else{
				p->next=new goods;
				p=p->next;
				p->next=NULL;
				p->id=id;
				p->name=name;
				p->price=isInteger1(price)? (double)convertInteger(price):convertFraction(price);
				p->number=convertInteger(number);
				if(flag_import){
					insertSQL(getTablename(),p->id,p->name,p->price,p->number,0);
				}
			}
		}
		p->next=NULL;
		return head;
	}
	/******************/
}
goods* assignCreate(string table_name)
{
	if(querySQL(table_name)){
		res=mysql_store_result(&mysql);
	}else 
		return NULL;
//	sprintf(query,"select *from %s",table_name.c_str());
//	if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){setColor(RED);
//		printf("query error: %s",mysql_error(&mysql));setColor(WHITE);
//		return NULL;
//	}
//	res=mysql_store_result(&mysql);
	goods *head,*p;
	head=p=new goods;
	zongshu=mysql_num_rows(res);
	while(row=mysql_fetch_row(res)){
		p->next=new goods;
		p=p->next;
		p->id=row[0];
		p->name=row[1];
		p->price=isInteger1(row[2])?(double)convertInteger(row[2]):convertFraction(row[2]);
		p->number=convertInteger(row[3]);
		p->sold=convertInteger(row[4]);
	}
	p->next=NULL;
	freeResult(res); 
	return head; 
}
void print( goods*head) {
	goods*p=head->next;
	if(p==NULL) printf("*********************************当前管理系统无数据****************************************\n");
	else{
	
	printf("*********************************************输入商品内容如下*******************************************\n");
	printf("    _________________________________________________________________________________________________\n"); 
	printf("   |      商品编码               商品名称                 商品价格               商品销售情况        |\n");
		printf("   +------------------+-------------------------+-----------------------+----------------------------+\n");
	
	while(p) {
		//printf("编号：%d    名称：%s     价格：%.2lf     数量：%d   销售情况：%d\n",p->id,p->name,p->price,p->number,p->sold);

		cout<<"   |"<<setw(12)<<p->id<<"      |  "<<setw(15)<<p->name<<"        |"<<setw(15)<<p->price<<"        |   "<<setw(12)<<p->sold<<"             |"<<endl;
		
		p=p->next;
		if(p)
				printf("   +------------------+-------------------------+-----------------------+----------------------------+\n");
	}
		printf("    ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n"); }
	menu(head);
}
void welcome() {
	printf("****************************************\n");
	printf("**********欢迎使用本商品管理系统********\n");
	printf("****************************************\n");
}

void change1(goods*head) {
	goods*p=head->next;
	string j,n,n1,n2;
	int k;
a:
	printf("请输入要修改商品数据的商品个数\n");
	/*******************/
	cin>>n;
	if(!isInteger1(n)) {
		printf("输入错误，请重新输入\n");
//		menu(head);
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("输入错误，请重新输入\n");
//		menu(head);
		goto a;
	}
	/*******************/
	printf("修改格式为商品编码+销售额（输入负数即代表进货)\n");
	if(flag_import)
		setColor(YELLOW);printf("**************修改将同步到数据库**************\n");setColor(WHITE);
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!checkNum(n1,0)||!isInteger2(n2)) {
			printf("输入错误，请重新输入\n");
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
						printf("销售额大于库存，输入有误,请重新输入编码+销售额\n");
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
void change2(goods*head) {
	goods*p=head->next;
	int k;
	string n,n1,n2;
	printf("请输入要修改商品数据的商品个数\n");
a:
	cin>>n;
	if(!isInteger1(n)) {
		printf("输入错误，请重新输入\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("输入错误，请重新输入\n");
		goto a;
	}
	printf("修改格式为商品名称+销售额（输入负数即代表进货)\n");
	if(flag_import)
		setColor(YELLOW);printf("**************修改将同步到数据库**************\n");setColor(WHITE);
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!isInteger2(n2)) {
			printf("输入错误，请重新输入\n");
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
						printf("销售额大于库存，输入有误,请重新输入编码+销售额\n");
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
goods*seek(goods*head,int i) {
	goods*p=head;
	int j=0;
	while(j<i&&p) {
		p=p->next;
		j++;
	}
	return p;
}
void add(goods*head) {
	string id,name,price,number;
	goods*p,*q;
	printf("请输入插入位置，输入0默认插入末端\n");
	string n;
a:
	cin>>n;
	if(!checkNum(n,0)) { //包含0
		printf("输入错误，请重新输入\n");
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
		printf("请输入要插入的新商品信息（格式为商品编号+商品名称+商品价格+商品数量）\n");
b:
		cin>>id>>name>>price>>number;
		if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
			printf("输入错误，请重新输入\n");
			goto b;
		} else if(Isrepeat(head,id,name)) {
			repeatCheck(head);
			/*******/
			printf("请输入商品编号 商品名称 商品价格 商品数量\n");
			goto b;
		} else {
			q->id=id;//convertInteger(id);
			q->name=name;
			q->price=isInteger1(price)? (double)convertInteger(price):convertFraction(price);
			q->number=convertInteger(number);
			q->next=p->next;
			p->next=q;
			printf("插入已成功\n");
			zongshu++;
			if(flag_import)	
				insertSQL(getTablename(),q->id,q->name,q->price,q->number,0);
		}
	}

	else {
		goods*temp;
		p=head->next;
		while(p) {
			temp=p;
			p=p->next;
		}
		q=new goods;
		p=temp;
		printf("请输入要插入的新商品信息（格式为商品编号+商品名称+商品价格+商品数量）\n");
c:
		cin>>id>>name>>price>>number;
		if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
			printf("输入错误，请重新输入\n");
			goto c;
		} else if(Isrepeat(head,id,name)) {
			repeatCheck(head);
			/*******/
			printf("请输入商品编号 商品名称 商品价格 商品数量\n");
			goto c;
		} else {

			q->id=id;//convertInteger(id);
			q->name=name;
			q->price=isInteger1(price)? (double)convertInteger(price):convertFraction(price);
			q->number=convertInteger(number);
			q->next=p->next;
			p->next=q;
			printf("插入已成功\n");
			zongshu++;
			if(flag_import)
				insertSQL(getTablename(),q->id,q->name,q->price,q->number,0);
		}		
	}
	menu(head);
}
void delet(goods*head) {
	goods*q,*p=head->next;
	int i=0;
	string j,s;
	printf("请输入要删除商品的编码或名称\n");
	cin>>s;
	goods*temp;
	if(checkNum(s,0)) {
		j=s;//convertInteger(s);
		temp=head;
		while(p) {
			if(p->id==j) {
				q=temp->next;
				temp->next=q->next;
				delete q;
				printf("删除商品信息成功\n");
				zongshu--;
				if(flag_import)
					deleteSQLId(getTablename(),p->id);
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
				q=temp->next;
				temp->next=q->next;
				delete q;
				printf("删除商品信息成功\n");
				zongshu--;
				if(flag_import)
					deleteSQLName(getTablename(),p->name);
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
void addor(goods*head) {
	string n;
	printf("*******请输入选择*******\n");
	printf("#####1：添加商品信息#####2：删除商品信息#####\n");
	if(flag_import){ 
		setColor(YELLOW);printf("*****修改将同步到数据库*****\n");setColor(WHITE);
	}
	/*****************/
a:
	cin>>n;
	if(!isInteger3(n,2)) {
		printf("输入错误，请重新输入\n");
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
	}
}
void workout(goods*head) {
	string n;
	goods*p=head->next;
	printf("请输入要查询的商品编码（若输入-1则输出所有商品的销售总额及库存）///输入menu即可返回主菜单\n");
a:
	cin>>n;
	if(!isInteger2(n)&&n!="menu") {
		printf("输入错误，请重新输入\n");
		goto a;
	}
	if(n=="menu") menu(head); 
	if(n.length()==2&&n[0]=='-'&&n[1]=='1') {
		
		printf("_________________________________________________________________________________________________________________________\n"); 
		printf("|     商品编码           商品名称             商品价格             商品库存             商品销售量         商品销售额    |\n");
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
		while(p) {
			//printf("编号：%d    名称：%s     价格：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |   "<<setw(10)<<p->price<<"       | "<<setw(13)<<p->number<<"        |  "<<setw(10)<<p->sold<<"       |";
		printf(" %8.2lf         |\n",1.0*(p->sold)*(p->price));
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
			
			p=p->next;
		}
	} else if(n[0]!='-') {
		string num=n;//convertInteger(n)
		while(p) {
			if(p->id==num) {
				
		printf("_________________________________________________________________________________________________________________________\n"); 
		printf("|     商品编码           商品名称             商品价格             商品库存             商品销售量         商品销售额    |\n");
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
		cout<<"|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |   "<<setw(10)<<p->price<<"       | "<<setw(13)<<p->number<<"        |  "<<setw(10)<<p->sold<<"       |";
		printf(" %8.2lf         |\n",1.0*(p->sold)*(p->price));
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
	
				break;
			}
			p=p->next;
		}
		if(p==NULL) {
			printf("输入有误\n");
			workout(head);
		}
	}
	menu(head);
}
/*****************/
bool compare(sort1 a,sort1 b) {
	return a.sold>b.sold;
}
void top(goods*head) {
	goods *p=head->next;
	printf("请输入要输出的商品个数");
	string n;
a:
	cin>>n;
	if(!isInteger1(n)) {
		printf("输入错误,请重新输入\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("输入错误,请重新输入\n");
		goto a;
	}
	sort1 *flag=new sort1[zongshu];
	for(int i=0; i<zongshu; i++) {
		flag[i].id=p->id;
//	strcpy(flag[i].name,p->name);
		flag[i].name=p->name;
		flag[i].number=p->number;
		flag[i].price=p->price;
		flag[i].sold=p->sold;
		p=p->next;
	}
	sort(flag,flag+zongshu,compare);
	printf("**************************************销售情况好的商品**************************************\n") ;
	printf("_______________________________________________________________________________________________________\n"); 
	printf("|     商品编码           商品名称             商品价格             商品库存             商品销售量    |\n");
	printf("+----------------+--------------------+--------------------+----------------------+-------------------+\n");
	bool f=true;
	for(int i=0; i<num; i++) {
//	printf("%d    %s   %.2f    %d      %d   ",flag[i].id,flag[i].name,flag[i].price,flag[i].number,flag[i].sold);
		cout<<"|"<<setw(10)<<flag[i].id<<"      |    "<<setw(10)<<flag[i].name<<"      |   "<<setw(10)<<flag[i].price<<"       | "<<setw(13)<<flag[i].number<<"        |  "<<setw(10)<<flag[i].sold<<"       |"<<endl;
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+\n");
		if((i+1)<zongshu&&flag[i].sold==flag[i+1].sold) {
			num++;
			f=false;
		}  
	
	}
	if(!f)cout<<"备注：多输出的商品是由于商品销售情况相同"<<endl; 
	delete[] flag;
	menu(head);
}
void low(goods*head) {
	goods *p=head->next;
	printf("请输入要输出的商品个数");
	string n;
a:
	cin>>n;
	if(!isInteger1(n)) {
		printf("输入错误,请重新输入\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("输入错误,请重新输入\n");
		goto a;
	}
	sort1 *flag=new sort1[zongshu];
	for(int i=0; i<zongshu; i++) {
		flag[i].id=p->id;
		//strcpy(flag[i].name,p->name);
		flag[i].name=p->name;
		flag[i].number=p->number;
		flag[i].price=p->price;
		flag[i].sold=p->sold;
		p=p->next;
	}
	sort(flag,flag+zongshu,compare);
	printf("****************************************销售情况差的商品***************************************\n") ;
	printf("_______________________________________________________________________________________________________\n"); 
	printf("|     商品编码           商品名称             商品价格            商品销售情况          商品销售额    |\n");
	printf("+----------------+--------------------+--------------------+----------------------+-------------------+\n");
	bool f=true;
	for(int i=zongshu-1; i>zongshu-num-1; i--) {
//		printf("%d    %s   %.2f    %d      %d   \n",flag[i].id,flag[i].name,flag[i].price,flag[i].number,flag[i].sold);

			cout<<"|"<<setw(10)<<flag[i].id<<"      |    "<<setw(10)<<flag[i].name<<"      |   "<<setw(10)<<flag[i].price<<"       | "<<setw(13)<<flag[i].number<<"        |  "<<setw(10)<<flag[i].sold<<"       |"<<endl;
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+\n");
		if((i-1)>=0&&flag[i-1].sold==flag[i].sold) {
			num++;
			f=false;
		}  
	
	}
	if(!f)cout<<"备注：多输出的商品是由于商品销售情况相同"<<endl; 
	delete[] flag;
	menu(head);
}
void search(goods* head) {
	printf("请输入操作码（1：查询销售火爆的商品，2：查询销售较差的商品\n");
	string n;
d:
	cin>>n;
	if(!isInteger3(n,2)) {
		printf("输入错误，请重新输入\n");
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
void deleteall(goods *head) {
	//printf("*****此操作将删除所有该用户数据库数据******\n");
	int ret;
	if(flag_import)
		ret=MessageBox(NULL,TEXT("注意:此操作将删除所有该用户数据库数据\n是否继续？"),TEXT("清除数据"),
			MB_YESNO|MB_ICONWARNING);//MB_ICONQUESTION
	else
		ret=MessageBox(NULL,TEXT("注意:此操作将删除所有该用户当前链表数据\n是否继续？"),TEXT("清除数据"),
			MB_YESNO|MB_ICONWARNING);
	if(ret==IDYES){ 
		goods *pnext;
		while (head->next!=NULL) {
			pnext=head->next;
			delete head;
			head=pnext;
		}
		zongshu=0;
		if(flag_import)
			truncateSQL(getTablename());
	} 
	menu(head);
}

void tuichu() {
	printf("#########欢迎下次使用########\n");
	exit(0);
}
void qingpin(goods*head) {
	system("cls");
	menu(head);
}
void menu(goods*head) {
	printf("**************************************\n");
	printf("**********您已进入选择菜单************\n");
	printf("**************************************\n");
	printf("***1:输入商品销售数据（利用商品编码进行选择）***\n");
	printf("***2:输入商品销售数据（利用商品名称进行选择）***\n");
	printf("***3:增添或删除商品信息***\n");
	printf("***4:计算销售总额及库存***\n");
	printf("***5:输出商品列表信息***\n");
	printf("***6:查找销售商品销售情况***\n");
	printf("***7:清屏***\n");
	printf("***8:退出程序***\n");
	printf("***9:清除内部数据***\n");
	/********************/
	string n;
a:
	cin>>n;
	if(!isInteger3(n,9)) {
		printf("输入错误，请重新输入\n");
		goto a;
	}
	/********************/
	switch(n[0]-48) {
		case 1:{
			if(zongshu<=0 ){
				cout<<"目前商品管理系统内无商品数据，无法修改"<<endl; 
				menu(head);
			} 
			change1(head);
			break;}
		case 2:{
				if(zongshu<=0 ){
				cout<<"目前商品管理系统内无商品数据，无法修改"<<endl; 
				menu(head);
			} 
			change2(head);
			break;}
		case 3:
			addor(head);
			break;
		case 4:
			workout(head);
			break;
		case 5:
			print(head);
			break;
		case 6:
			search(head);
			break;
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
bool select(string *username)
{
	setColor(PURPLE);	
a:	cout<<"1.注册##########2.登录\n";
	setColor(WHITE);
	string input;
	cin>>input;
	if(!isInteger3(input,2)){
		printf("输入错误，请重新输入\n");
		goto a;
	}
	switch(input[0]){
		case '1': {
			cout<<"***********注册**********\n";		
			(*username)=signUp();
			return false;
		}
		case '2': {
			cout<<"***********登录***********\n";
			(*username)=signIn();
//			signIn();
			return true;
		}
	}
}
bool loginMySQL()
{
	string username;
	mysql_init(&mysql);
	ConnectSQL();
	return select(&username);
}
int main() {
	HWND my_consle = GetForegroundWindow();
	ShowWindow(my_consle, SW_MAXIMIZE);
	welcome();
	goods *head;
	if(!loginMySQL()){
		head=create();
		menu(head);
	}else{
		head=assignCreate(getTablename());
		if(!head) head=create();
		flag_import=true;
		menu(head);
	}	
	return 0;
}

