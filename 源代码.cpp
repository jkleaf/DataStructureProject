/*商品管理系统*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cctype>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include<set> 
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
bool Isrepeat(goods *head,string ID,string name){
	goods* p=head->next;
	while(p){
		if(p->id==ID||p->name==name){
		   return 0;
		}
		p=p->next;
	}
	return true;
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
/**********************/
void menu(goods*head);
int zongshu;
goods *creat() {
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
		printf("请输入商品编号 商品名称 商品价格 商品数量\n");
		int num=zongshu;
		while(num--) {
			p->next=new goods;
			p=p->next;
b:
			cin>>id>>name>>price>>number;
			//scanf("%d%s%lf%d",&p->id,p->name,&p->price,&p->number);
			if(!isInteger1(id)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
				printf("输入错误，请重新输入\n");
				goto b;
			}
			else if(!Isrepeat(head,id,name)){
				printf("您输入了重复的编码或名称，请重新输入\n");
				printf("是否需要进行编码与名称查重或是输出已使用编码和名称\n");
				printf("****1:编码名称查重***********2:输出已使用编码和名称****（输入其他则继续输入商品信息）\n");
				/*********/ 
				int x;
				cin>>x;
				switch(x){
					case 1:{
						cout<<"请输入需要查重的编码"<<endl; 
						string ID;
						int flag=0;
						while(!flag){
						d:cin>>ID;
						if(isInteger1(ID)){
						 
							if(!Isrepeat(head,ID," ")){
								cout<<"已存在该编码"<<endl;}
							else cout<<"该编码尚未被使用"<<endl; 
								}
						else {
							cout<<"输入编码不符合系统要求，请重新输入"<<endl;
							goto d;
						}
						cout<<"是否继续查询？是请输入0，否则继续输入商品信息"<<endl;
						 cin>>flag;
						}
						break;
					}
					case 2:{
						goods *temp=head->next;
						while(temp->next){
							cout<<"编码："<<temp->id<<"    名称："<<temp->name<<endl; 
							temp=temp->next;
						}
						break;
					} 
					
				}
				
			/*******/ 
			printf("请输入商品编号 商品名称 商品价格 商品数量\n");
				goto b; 
			}
			else{
			
			p->id=id;//convertInteger(id);
			p->name=name;
			p->price=isInteger1(price)? convertInteger(price):convertFraction(price);
			p->number=convertInteger(number);}
		}
		p->next=NULL;
		return head;
	}
	/******************/
}
void print( goods*head) {
	goods*p=head->next;
	if(p==NULL) printf("当前管理系统无数据\n");
	printf("输入商品内容如下\n");
	while(p) {
		//printf("编号：%d    名称：%s     价格：%.2lf     数量：%d   销售情况：%d\n",p->id,p->name,p->price,p->number,p->sold);
		cout<<"编号："<<p->id<<"    名称："<<p->name<<"     价格："<<p->price<<"     数量："<<p->sold<<endl;
		p=p->next;
	}
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
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!isInteger1(n1)||!isInteger2(n2)) {
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
a:	cin>>n;
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
		if(!isInteger1(id)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
			printf("输入错误，请重新输入\n");
			goto b;
		}
		else if(!Isrepeat(head,id,name)){
				printf("您输入了重复的编码或名称，请重新输入\n");
				printf("是否需要进行编码与名称查重或是输出已使用编码和名称\n");
				printf("****1:编码名称查重***********2:输出已使用编码和名称****（输入其他则继续输入商品信息）\n");
				/*********/ 
				int x;
				cin>>x;
				switch(x){
					case 1:{
						cout<<"请输入需要查重的编码"<<endl; 
						string ID;
						int flag=0;
						while(!flag){
						e:cin>>ID;
						if(isInteger1(ID)){
						 
							if(!Isrepeat(head,ID," ")){
								cout<<"已存在该编码"<<endl;}
							else cout<<"该编码尚未被使用"<<endl; 
								}
						else {
							cout<<"输入编码不符合系统要求，请重新输入"<<endl;
							goto e;
						}
						cout<<"是否继续查询？是请输入0，否则继续输入商品信息"<<endl;
						 cin>>flag;
						}
						break;
					}
					case 2:{
						goods *temp=head->next;
						while(temp->next){
							cout<<"编码："<<temp->id<<"    名称："<<temp->name<<endl; 
							temp=temp->next;
						}
						break;
					} 
					
				}
				
			/*******/ 
			printf("请输入商品编号 商品名称 商品价格 商品数量\n");
				goto b; }
			else{
		
		q->id=id;//convertInteger(id);
		q->name=name;
		q->price=isInteger1(price)? convertInteger(price):convertFraction(price);
		q->number=convertInteger(number);
		q->next=p->next;
		p->next=q;
		printf("插入已成功\n");
		zongshu++;}} 
	
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
		if(!isInteger1(id)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
			printf("输入错误，请重新输入\n");
			goto c;
		}
	else if(!Isrepeat(head,id,name)){
				printf("您输入了重复的编码或名称，请重新输入\n");
				printf("是否需要进行编码与名称查重或是输出已使用编码和名称\n");
				printf("****1:编码名称查重***********2:输出已使用编码和名称****（输入其他则继续输入商品信息）\n");
				/*********/ 
				int x;
				cin>>x;
				switch(x){
					case 1:{
						cout<<"请输入需要查重的编码"<<endl; 
						string ID;
						int flag=0;
						while(!flag){
						f:cin>>ID;
						if(isInteger1(ID)){
						 
							if(!Isrepeat(head,ID," ")){
								cout<<"已存在该编码"<<endl;}
							else cout<<"该编码尚未被使用"<<endl; 
								}
						else {
							cout<<"输入编码不符合系统要求，请重新输入"<<endl;
							goto f;
						}
						cout<<"是否继续查询？是请输入0，否则继续输入商品信息"<<endl;
						 cin>>flag;
						}
						break;
					}
					case 2:{
						goods *temp=head->next;
						while(temp->next){
							cout<<"编码："<<temp->id<<"    名称："<<temp->name<<endl; 
							temp=temp->next;
						}
						break;
					} 
					
				}
				
			/*******/ 
			printf("请输入商品编号 商品名称 商品价格 商品数量\n");
				goto c; }
		else{
		
		q->id=id;//convertInteger(id);
		q->name=name;
		q->price=isInteger1(price)? convertInteger(price):convertFraction(price);
		q->number=convertInteger(number);
		q->next=p->next;
		p->next=q;
		printf("插入已成功\n");
		zongshu++;}
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
	if(isInteger1(s)) {
		j=s;//convertInteger(s);
		temp=head;
		while(p) {
			if(p->id==j) {
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
void addor(goods*head) {
	string n;
	printf("*******请输入选择*******\n");
	printf("#####1：添加商品信息#####2：删除商品信息#####\n");
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
			delet(head);
			break;
	}
}
void workout(goods*head) {
	string n;
	goods*p=head->next;
	printf("请输入要查询的商品编码（若输入-1则输出所有商品的销售总额及库存）\n");
a:
	cin>>n;
	if(!isInteger2(n)) {
		printf("输入错误，请重新输入\n");
		goto a;
	}
	if(n.length()==2&&n[0]=='-'&&n[1]=='1') {
		while(p) {
			//printf("编号：%d    名称：%s     价格：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
			cout<<"编号："<<p->id<<"    名称："<<p->name<<"     价格："<<p->price<<"     数量："<<
				p->number<<"   销售情况："<<p->sold;
			printf("     销售金额：%.2lf\n",1.0*(p->sold)*(p->price));
			p=p->next;
		}
	} else if(n[0]!='-') {
		string num=n;//convertInteger(n);
		while(p) {
			if(p->id==num) {
				//printf("编号：%d    名称：%s     价格：%.2lf     数量：%d   销售情况：%d     销售金额：%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
			cout<<"编号："<<p->id<<"    名称："<<p->name<<"     价格："<<p->price<<"     数量："<<
				p->number<<"   销售情况："<<p->sold;
			printf("     销售金额：%.2lf\n",1.0*(p->sold)*(p->price));
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
	printf("**********************销售最多的商品！！！！！********************\n") ;
	printf("商品编号    商品名称     商品价格       商品数量       商品销售额 \n");
	for(int i=0; i<num; i++) {
//	printf("%d    %s   %.2f    %d      %d   ",flag[i].id,flag[i].name,flag[i].price,flag[i].number,flag[i].sold);
		cout<<flag[i].id<<"    "<<flag[i].name<<"   "<<flag[i].price<<"    "<<flag[i].number<<"      "<<flag[i].sold<<endl;
	}
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
	printf("**********************销售最差的商品！！！！！********************\n") ;
	printf("商品编号    商品名称     商品价格       商品数量       商品销售额 \n");
	for(int i=zongshu-1; i>zongshu-num-1; i--) {
//		printf("%d    %s   %.2f    %d      %d   \n",flag[i].id,flag[i].name,flag[i].price,flag[i].number,flag[i].sold);
		cout<<flag[i].id<<"    "<<flag[i].name<<"   "<<flag[i].price<<"    "<<flag[i].number<<"      "<<flag[i].sold<<endl;
	}
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
	goods *pnext;
	while (head->next!=NULL) {
		pnext=head->next;
		delete head;
		head=pnext;
	}
	zongshu=0;
	menu(head);
}

void tuichu() {
	printf("#########欢迎下次使用########\n");
	exit(1);
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
		case 1:
			change1(head);
			break;
		case 2:
			change2(head);
			break;
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
int main() {
	welcome();
	goods *head;
	head=creat();
	menu(head);
	return 0;
}

