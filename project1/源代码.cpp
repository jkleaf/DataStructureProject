/*��Ʒ����ϵͳ*/
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
	string id;//��Ʒ���
	string name;//��Ʒ����
	double price;//��Ʒ�ۼ�
	int  number;//��Ʒ����
	int sold=0;//��������
	double cost;
	double Sales=0; 
	int before=0;
	struct goods *next;
};
struct sort1 {
	string id;
	string name;//��Ʒ����
	double price;//��Ʒ�ۼ�
	int  number;//��Ʒ����
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
void repeatCheck(goods *head) {
	printf("���������ظ��ı�������ƣ�����������\n");
	printf("�Ƿ���Ҫ���б��������Ʋ��ػ��������ʹ�ñ��������\n");
	printf("****1:�������***********2:���Ʋ���****3�������ʹ�õı�������ƣ��������������������Ʒ��Ϣ��\n");
	/*********/
	string x;
	cin>>x;
	if(isInteger3(x,3)) {
		switch(x[0]) {
			case '1': {
				cout<<"��������Ҫ���صı���"<<endl;
				string ID;
				int flag=0;
				while(!flag) {
d:
					cin>>ID;
					if(checkNum(ID,0)) {

						if(Isrepeat(head,ID," ")) {
							cout<<"�Ѵ��ڸñ���"<<endl;
						} else cout<<"�ñ�����δ��ʹ��"<<endl;
					} else {
						cout<<"������벻����ϵͳҪ������������"<<endl;
						goto d;
					}
					cout<<"�Ƿ������ѯ����������0���������������Ʒ��Ϣ"<<endl;
					string flagString;
					cin>>flagString;
					flag=(flagString.length()==1&&flagString[0]=='0')?0:1;
				}
				break;
			}
			case '2':{	
				cout<<"��������Ҫ���ص�����"<<endl;
				string NAME;
				int flag=0;
				while(!flag) {
					cin>>NAME;
						if(Isrepeat(head,"-1",NAME)) {
							cout<<"�Ѵ��ڸ�����"<<endl;
						} else cout<<"��������δ��ʹ��"<<endl;
					cout<<"�Ƿ������ѯ����������0���������������Ʒ��Ϣ"<<endl;
					string flagString;
					cin>>flagString;
					flag=(flagString.length()==1&&flagString[0]=='0')?0:1;
				}	
				break;
			} 
			case '3': {
				goods *temp=head->next;
				while(temp) {
					cout<<"���룺"<<temp->id<<"    ���ƣ�"<<temp->name<<endl;
					temp=temp->next;
				}
				break;
			}
		}
	}
}
bool selectToImport()
{
	printf("����Y��yִ�е������ݿ�,����������ִ�е���.\n");
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
goods *create() {
	goods *head,*p;
	head=p=new goods;
	/******************/
	string n,id,name,price,number,cost;
a:
	printf("��������Ʒ��������\n");
	cin>>n;
	if(!isInteger1(n)) {
		printf("�������,������������\n");
		goto a;
	} else {
		zongshu=convertInteger(n);
		if(!flag_import&&selectToImport()){//��¼Ĭ��ͬ�����ݿ� 
			printf("*****��ѡ���������ݵ������ݿ�*****\n"); 
			flag_import=true;
		}else{
			printf("*****��������������ͬ�������ݿ�*****\n");
			flag_import=false;
		}
		printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
		int num=zongshu;
		while(num--) {
b:
			cin>>id>>name>>cost>>price>>number;
			if(!checkStrDigit(id)||!checkStrDigit(name)){
				printf("�����������Ƴ���̫��������������\n");
				goto b; 
			}
			else if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||(!isInteger1(cost)&&!isFraction(cost))||!isInteger1(number)) {
				printf("��������������������ʽ������������\n");
				goto b;
			} 
			else if((isInteger1(price)? (double)convertInteger(price):convertFraction(price))<(isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost))) {
				printf("������Ʒ�ۼ۵��ڽ��ۣ�ȷ������������yes,�������������ַ�����������\n");
				string pd;
				cin>>pd;
				if(pd!="yes"){
					printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
					goto b;
				}
			goto c; 
			
			}
			 if(repeat_first&&Isrepeat(head,id,name)) {
				repeatCheck(head);
				printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
				goto b;
			}
			else{
				c: 
				p->next=new goods;
				p=p->next;
				p->next=NULL;
				p->id=id;
				p->name=name;
				p->price=isInteger1(price)? (double)convertInteger(price):convertFraction(price); 
				p->cost=isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost);
				p->number=convertInteger(number);
				if(flag_import){
					insertSQL(getTablename(),p->id,p->name,p->price,p->number,0);
				}
				repeat_first=true;
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
	if(p==NULL) printf("*********************************��ǰ����ϵͳ������****************************************\n");
	else{
	
	printf("*********************************************������Ʒ��������*******************************************\n");
	printf("    _________________________________________________________________________________________________\n"); 
	printf("   |      ��Ʒ����               ��Ʒ����                 ��Ʒ�ۼ�               ��Ʒ�������        |\n");
		printf("   +------------------+-------------------------+-----------------------+----------------------------+\n");
	
	while(p) {

		cout<<"   |"<<setw(12)<<p->id<<"      |  "<<setw(15)<<p->name<<"        |"<<setw(15)<<p->price<<"        |   "<<setw(12)<<p->sold<<"             |"<<endl;
		
		p=p->next;
		if(p)
				printf("   +------------------+-------------------------+-----------------------+----------------------------+\n");
	}
		printf("    ��������������������������������������������������������������������������������������������������\n"); }
	if(!print_judge){
		print_judge =true;
		return;
	}else
		menu(head);
}
void welcome() {
	printf("****************************************\n");
	printf("**********��ӭʹ�ñ���Ʒ����ϵͳ********\n");
	printf("****************************************\n");
}
void Revise_price(goods *head){
	goods* p=head->next;
	printf("*******************��Ʒ�������Ʊ�*******************(����ṩ�ο�)\n");
	printf(" __________________________________________________________________________\n"); 
	printf("|     ��Ʒ����    |      ��Ʒ����     |      ��Ʒ����    |     ��Ʒ�ۼ�   |\n");
	printf("+----------------+--------------------+------------------+----------------+\n");
	while(p) {
			//printf("��ţ�%d    ���ƣ�%s     �ۼۣ�%.2lf     ������%d   ���������%d     ���۽�%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |"<<setw(10)<<p->cost<<"      |"<<setw(10)<<p->price<<"      |"<<endl;

		printf("+----------------+--------------------+------------------+------------------+\n");
			
			p=p->next;
		}
	p=head->next;
	printf("������Ҫ�޸���Ʒ�ۼ۵���Ʒ����+�޸ĺ����Ʒ�ۼ�\n");
	string n1,n2,j;
	double k; 
	a:
		cin>>n1>>n2;
		if(!checkNum(n1,0)||(!isInteger1(n2)&&!isFraction(n2))) {
			printf("����������������ʽ��������\n");
			goto a;
		}
		j=n1;//convertInteger(n1);
		k=convertInteger(n2);
	while(p!=NULL){
		if(p->id==j){
			if(k<p->cost){
				printf("�޸��ۼ۵��ڽ����Ƿ�ȷ���޸ģ�ȷ��������yes���������������ַ�����������\n");
				string jd;
				cin>>jd;
				if(jd!="yes"){
					printf("������Ҫ�޸���Ʒ�ۼ۵���Ʒ����+�޸ĺ����Ʒ�ۼ�\n");
					goto a;
				}
			} 
			p->Sales+=(p->sold-p->before)*p->price;
			p->before=p->sold;
			p->price=k; 
			printf("�޸ĳɹ�\n"); 
			menu(head); 
		}
		else {
			printf("����ı��벻����\n");
			printf("������������Ʒ����+�޸ĺ����Ʒ�ۼ�\n");
			goto a; 
			 
		}
	}
}
void change1(goods*head) {
	goods*p=head->next;
	string j,n,n1,n2;
	int k;
	printf("������Ҫ�޸���Ʒ�������ݵ���Ʒ����||��ʱϵͳ����%ld����Ʒ�������Ҫ���ز˵�������menu)\n",zongshu);
	/*******************/
a:	
	cin>>n;
	if(n=="menu")  menu(head);
	if(!isInteger1(n)) {
		printf("�������������������\n");
//		menu(head);
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("��������������Ʒ����ϵͳ����Ʒ����������������\n");
//		menu(head);
		goto a;
	}
	printf("***********************************�����Ʒ�б���Ϣ��Ϊ�ο�*************************\n");
	print_judge=false;
	print(head);
	/*******************/
	printf("�޸ĸ�ʽΪ��Ʒ����+���۶���븺�����������)\n");
	if(flag_import)
		setColor(YELLOW);printf("**************�޸Ľ�ͬ�������ݿ�**************\n");setColor(WHITE);
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!checkNum(n1,0)||!isInteger2(n2)) {
			printf("����������������ʽ��������\n");
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
						printf("�����������ڿ�棬��������,�������������+���۶�\n");
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
			printf("δ�ҵ�����Ʒ,�������������+���۶�\n");
			p=head->next;
			goto b;
		}
		p=head->next;
	}
	printf("�����������ݳɹ�\n");
	menu(head);
}
void change2(goods*head) {
	goods*p=head->next;
	int k;
	string n,n1,n2;
	printf("������Ҫ�޸���Ʒ�������ݵ���Ʒ����||��ʱϵͳ����%ld����Ʒ�������Ҫ���ز˵�������menu)\n",zongshu);
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!isInteger1(n)) {
		printf("�������������������\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("��������������Ʒ����ϵͳ����Ʒ����������������\n");
		goto a;
	}
	printf("�޸ĸ�ʽΪ��Ʒ����+���۶���븺�����������)\n");
	if(flag_import)
		setColor(YELLOW);printf("**************�޸Ľ�ͬ�������ݿ�**************\n");setColor(WHITE);
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!isInteger2(n2)) {
			printf("�������������������\n");
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
						printf("�����������ڿ�棬��������,�������������+���۶�\n");
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
			printf("δ�ҵ�����Ʒ,�������������+���۶�\n");
			p=head->next;
			goto b;
		}
		p=head->next;
	}
	printf("�����������ݳɹ�\n");
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
	string id,name,price,cost,number;
	goods*p,*q;
	printf("���������λ�ã�����0Ĭ�ϲ���ĩ��||��ʱϵͳ����%ld����Ʒ�������Ҫ���ز˵�������menu)\n",zongshu);
	string n;
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!checkNum(n,0)) { //����0
		printf("���������������ȷ��ʽ����\n");
		goto a; 
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("����λ����������������\n");
		goto a;
	}
	if(num) {
		p=seek(head,num-1);
		q=new goods;
		printf("������Ҫ���������Ʒ��Ϣ����ʽΪ��Ʒ���+��Ʒ����+��Ʒ����+��Ʒ�ۼ�+��Ʒ������\n");
b:
		cin>>id>>name>>cost>>price>>number;
		if(!checkStrDigit(id)||!checkStrDigit(name)){
			printf("�����������Ƴ���̫��(�ַ�������10λ,���Ĳ�����5λ)������������\n");
			goto b; 
		}
		if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||(!isInteger1(cost)&&!isFraction(cost))||!isInteger1(number)) {
			printf("������������ʽ��������\n");
			goto b;
		} else if(zongshu>0&&Isrepeat(head,id,name)) {
			repeatCheck(head);
			/*******/
			printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
			goto b;
		} 
		  else if((isInteger1(price)? (double)convertInteger(price):convertFraction(price))<(isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost))) {
				printf("������Ʒ�ۼ۵��ڽ��ۣ�ȷ������������yes,�������������ַ�����������\n");
				string pd;
				cin>>pd;
				if(pd!="yes"){
					printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
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
			printf("�����ѳɹ�\n");
			zongshu++;
			if(flag_import)	
				insertSQL(getTablename(),q->id,q->name,q->price,q->number,0);
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
		printf("������Ҫ���������Ʒ��Ϣ����ʽΪ��Ʒ���+��Ʒ����+��Ʒ����+��Ʒ�ۼ�+��Ʒ������\n");
c:
		cin>>id>>name>>cost>>price>>number;
		if(!checkStrDigit(id)||!checkStrDigit(name)){
			printf("�����������Ƴ���̫��(�ַ�������10λ,���Ĳ�����5λ)������������\n");
			goto b; 
		}
			if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||(!isInteger1(cost)&&!isFraction(cost))||!isInteger1(number)){
			printf("������������ʽ��������\n");
			goto c;
		} else if(zongshu>0&&Isrepeat(head,id,name)) {
			repeatCheck(head);
			/*******/
			printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
			goto c;
			
		}	
		else if((isInteger1(price)? (double)convertInteger(price):convertFraction(price))<(isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost))) {
				printf("������Ʒ�ۼ۵��ڽ��ۣ�ȷ������������yes,�������������ַ�����������\n");
				string pd;
				cin>>pd;
				if(pd!="yes"){
					printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
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
			printf("�����ѳɹ�\n");
			zongshu++;
			if(flag_import)
				insertSQL(getTablename(),q->id,q->name,q->price,q->number,0);
		}		
	}
	menu(head);
}
void Batch_add(goods *head){
	printf("********������Ҫ������Ʒ�ĸ���********\n");
		string n;
	a:	cin>>n;
		if(!isInteger1(n)) {
		printf("�������,������������\n");
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
		printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
	while(num--) {
b:		cin>>id>>name>>cost>>price>>number;
		if(!checkStrDigit(id)||!checkStrDigit(name)){
			printf("�����������Ƴ���̫��(�ַ�������10λ,���Ĳ�����5λ)������������\n");
			goto b; 
		}
				if(!checkNum(id,0)||(!isInteger1(price)&&!isFraction(price))||(!isInteger1(cost)&&!isFraction(cost))||!isInteger1(number)) {
				printf("������������ʽ��������\n");
				goto b;
			} 
			else if(zongshu>0&&Isrepeat(head,id,name)) {
				repeatCheck(head);
				printf("��������Ʒ��� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
				goto b;
			}
			else	 if((isInteger1(price)? (double)convertInteger(price):convertFraction(price))<(isInteger1(cost)?(double)convertInteger(cost):convertFraction(cost))) {
				printf("������Ʒ�ۼ۵��ڽ��ۣ�ȷ������������yes,�������������ַ�����������\n");
				string pd;
				cin>>pd;
				if(pd!="yes"){
					printf("��������Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ�ۼ� ��Ʒ����\n");
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
				if(flag_import){
					insertSQL(getTablename(),p->id,p->name,p->price,p->number,0);
				}
			}
		}
		p->next=NULL;		
	menu(head);
}
void delet(goods*head) {
	goods*q,*p=head->next;
	int i=0;
	string j,s;
	printf("������Ҫɾ����Ʒ�ı��������\n");
	cin>>s;
	goods*temp;
	if(checkNum(s,0)) {
		j=s;
		temp=head;
		while(p) {
			if(p->id==j) {
				q=temp->next;
				temp->next=q->next;
				delete q;
				printf("ɾ����Ʒ��Ϣ�ɹ�\n");
				zongshu--;
				if(flag_import)
					deleteSQLId(getTablename(),p->id);
				break;
			}
			temp=p;
			p=p->next;
		}
		if(p==NULL) {
			printf("�����ڸ���Ʒ\n");
			delet(head);
		}
	} else {
		temp=head;
		while(p) {
			if(s==p->name) {
				q=temp->next;
				temp->next=q->next;
				delete q;
				printf("ɾ����Ʒ��Ϣ�ɹ�\n");
				zongshu--;
				if(flag_import)
					deleteSQLName(getTablename(),p->name);
				break;
			}
			temp=p;
			p=p->next;
		}
		if(p==NULL) {
			printf("�����ڸ���Ʒ\n");
			delet(head);
		}
	}
	menu(head);
}
void addor(goods*head) {
	string n;
	printf("*******������ѡ��*******\n");
	printf("#####1����ӵ�����Ʒ��Ϣ#####2��ɾ��������Ʒ��Ϣ#####3�����������Ʒ��Ϣ#####(����menu���ز˵�)\n");
	if(flag_import){ 
		setColor(YELLOW);printf("*****�޸Ľ�ͬ�������ݿ�*****\n");setColor(WHITE);
	}
	/*****************/
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!isInteger3(n,3)) {
		printf("���������������ȷ��ʽ\n");
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
				cout<<"Ŀǰ��Ʒ����ϵͳ������Ʒ���ݣ��޷��޸�"<<endl; 
				menu(head);}
			delet(head);
			break;}
		case 3:
			Batch_add(head);
			break; 	
	}
}
void workout(goods*head) {
	string n;
	goods*p=head->next;
	
	printf("*******************��Ʒ�������Ʊ�*******************(����ṩ�ο�)\n");
	printf("_______________________________________\n"); 
	printf("|     ��Ʒ����    |      ��Ʒ����     |\n");
	printf("+----------------+--------------------+\n");
	while(p) {
			//printf("��ţ�%d    ���ƣ�%s     �ۼۣ�%.2lf     ������%d   ���������%d     ���۽�%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |"<<endl;

		printf("+----------------+--------------------+\n");
			
			p=p->next;
		}
	p=head->next;
	printf("������Ҫ��ѯ����Ʒ���루������-1�����������Ʒ�������ܶ��棩///����menu���ɷ������˵�\n");
a:
	cin>>n;
	if(!isInteger2(n)&&n!="menu") {
		printf("�����������������\n");
		goto a;
	}
	if(n=="menu") menu(head); 
	if(n.length()==2&&n[0]=='-'&&n[1]=='1') {
		
		printf("_________________________________________________________________________________________________________________________\n"); 
		printf("|     ��Ʒ����           ��Ʒ����             ��Ʒ�ۼ�             ��Ʒ���             ��Ʒ������          ��Ʒ����     |\n");
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
		while(p) {
			//printf("��ţ�%d    ���ƣ�%s     �ۼۣ�%.2lf     ������%d   ���������%d     ���۽�%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
		cout<<"|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |   "<<setw(10)<<p->price<<"       | "<<setw(13)<<p->number<<"        |  "<<setw(10)<<p->sold<<"       |";
		printf(" %8.2lf         |\n",p->Sales+1.0*(p->sold-p->before)*(p->price-p->cost));
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
			
			p=p->next;
		}
	} else if(n[0]!='-') {
		string num=n;//convertInteger(n)
		while(p) {
			if(p->id==num) {
				
		printf("_________________________________________________________________________________________________________________________\n"); 
		printf("|     ��Ʒ����           ��Ʒ����             ��Ʒ�ۼ�             ��Ʒ���             ��Ʒ������         ��Ʒ���۶�    |\n");
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
		cout<<"|"<<setw(10)<<p->id<<"      |    "<<setw(10)<<p->name<<"      |   "<<setw(10)<<p->price<<"       | "<<setw(13)<<p->number<<"        |  "<<setw(10)<<p->sold<<"       |";
		printf(" %8.2lf         |\n",p->Sales+1.0*(p->sold)*(p->price-p->cost));
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+------------------+\n");
	
				break;
			}
			p=p->next;
		}
		if(p==NULL) {
			cout<<"��������δ�ҵ�����Ϊ"<<num<<"����Ʒ"<<endl; 
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
	printf("������Ҫ�������Ʒ����||||��ʱϵͳ����%ld����Ʒ�������Ҫ���ز˵�������menu)\n",zongshu);
	string n;
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!isInteger1(n)) {
		printf("�������,��������ȷ��ʽ\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("������󣬴�ʱ��Ʒ����ϵͳ��Ʒ����С��������������������\n");
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
	printf("**************************************��������õ���Ʒ**************************************\n") ;
	printf("_______________________________________________________________________________________________________\n"); 
	printf("|     ��Ʒ����           ��Ʒ����             ��Ʒ�ۼ�             ��Ʒ���             ��Ʒ������    |\n");
	printf("+----------------+--------------------+--------------------+----------------------+-------------------+\n");
	bool f=true;
	for(int i=0; i<num&&i<zongshu; i++) {
		cout<<"|"<<setw(10)<<flag[i].id<<"      |    "<<setw(10)<<flag[i].name<<"      |   "<<setw(10)<<flag[i].price<<"       | "<<setw(13)<<flag[i].number<<"        |  "<<setw(10)<<flag[i].sold<<"       |"<<endl;
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+\n");
		if((i+1)<=zongshu&&flag[i].sold==flag[i+1].sold) {
			if(num+1<=zongshu)
				num++;
			f=false;
		}  
	
	}
	if(!f)cout<<"��ע�����������Ʒ��������Ʒ���������ͬ"<<endl; 
	delete[] flag;
	menu(head);
}
void low(goods*head) {
	goods *p=head->next;
	printf("������Ҫ�������Ʒ����||||��ʱϵͳ����%ld����Ʒ�������Ҫ���ز˵�������menu)\n",zongshu);
	string n;
a:
	cin>>n;
	if(n=="menu") menu(head);
	if(!isInteger1(n)) {
		printf("�������,��������ȷ��ʽ\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("������󣬴�ʱ��Ʒ����ϵͳ��Ʒ����С��������������������\n");
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
	printf("****************************************������������Ʒ***************************************\n") ;
	printf("_______________________________________________________________________________________________________\n"); 
	printf("|     ��Ʒ����           ��Ʒ����             ��Ʒ            ��Ʒ�������          ��Ʒ���۶�    |\n");
	printf("+----------------+--------------------+--------------------+----------------------+-------------------+\n");
	bool f=true;
	for(int i=zongshu-1; i>zongshu-num-1&&i>=0; i--) {
			cout<<"|"<<setw(10)<<flag[i].id<<"      |    "<<setw(10)<<flag[i].name<<"      |   "<<setw(10)<<flag[i].price<<"       | "<<setw(13)<<flag[i].number<<"        |  "<<setw(10)<<flag[i].sold<<"       |"<<endl;
		printf("+----------------+--------------------+--------------------+----------------------+-------------------+\n");
		if((i-1)>=0&&flag[i-1].sold==flag[i].sold) {
			if(num+1<=zongshu)
				num++;
			f=false;
		}  
	
	}
	if(!f)cout<<"��ע�����������Ʒ��������Ʒ���������ͬ"<<endl; 
	delete[] flag;
	menu(head);
}
void search(goods* head) {
	printf("����������루1����ѯ���ۻ𱬵���Ʒ��2����ѯ���۽ϲ����Ʒ��\n");
	string n;
d:
	cin>>n;
	if(!isInteger3(n,2)) {
	    printf("������Ų����ڣ�����������\n");
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
	printf("*****�˲�����ɾ�����и��û����ݿ�����******\n");
	int ret;
	if(flag_import)
		ret=MessageBox(NULL,TEXT("ע��:�˲�����ɾ�����и��û����ݿ�����\n�Ƿ������"),TEXT("�������"),
			MB_YESNO|MB_ICONWARNING);//MB_ICONQUESTION
	else
		ret=MessageBox(NULL,TEXT("ע��:�˲�����ɾ�����и��û���ǰ��������\n�Ƿ������"),TEXT("�������"),
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
	}
	printf("��Ʒ��Ϣ�����\n");
	menu(head);
}

void tuichu() {
	printf("#########��ӭ�´�ʹ��########\n");
	exit(0);
}
void qingpin(goods*head) {
	system("cls");
	menu(head);
}
void menu(goods*head) {
	printf("**************************************\n");
	printf("**********���ѽ���ѡ��˵�************\n");
	printf("**************************************\n");
	printf("****************0���޸���Ʒ�ۼ�**************\n");
	printf("***1:������Ʒ�������ݣ�������Ʒ�������ѡ��***\n");
	printf("***2:������Ʒ�������ݣ�������Ʒ���ƽ���ѡ��***\n");
	printf("***3:�����ɾ����Ʒ��Ϣ***\n");
	printf("***4:���������ܶ���***\n");
	printf("***5:�����Ʒ�б���Ϣ***\n");
	printf("***6:����������Ʒ�������***\n");
	printf("***7:����***\n");
	printf("***8:�˳�����***\n");
	printf("***9:����ڲ�����***\n");
	/********************/
	string n;
a:
	cin>>n;
	if(!isInteger3(n,9)) {
		printf("������Ų����ڣ�����������\n");
		goto a;
	}
	/********************/
	switch(n[0]-48) {
		case 0:{
			if(zongshu<=0){
				cout<<"Ŀǰ��Ʒ����ϵͳ������Ʒ���ݣ��޷��޸���Ʒ�ۼ�"<<endl;
				menu(head); 
			}
			Revise_price(head);
			break;
		} 
		case 1:{
			if(zongshu<=0 ){
				cout<<"Ŀǰ��Ʒ����ϵͳ������Ʒ���ݣ��޷��޸�"<<endl; 
				menu(head);
			} 
			change1(head);
			break;}
		case 2:{
				if(zongshu<=0 ){
				cout<<"Ŀǰ��Ʒ����ϵͳ������Ʒ���ݣ��޷��޸�"<<endl; 
				menu(head);
			} 
			change2(head);
			break;}
		case 3:
			addor(head);
			break;
		case 4:{
			if(zongshu<=0 ){
				cout<<"Ŀǰ��Ʒ����ϵͳ������Ʒ���ݣ��޷�����"<<endl; 
				menu(head);
			} 
			workout(head);
			break;} 
		case 5:
			print(head);
			break;
		case 6:{ 
			if(zongshu<=0){ 
				cout<<"Ŀǰ��Ʒ����ϵͳ������Ʒ���ݣ��޷��鿴�������"<<endl;
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
bool select(string *username)
{
a:	setColor(PURPLE);	
	cout<<"1.ע��#####2.��¼#####3.�˳�\n";
	setColor(WHITE);
	string input;
	cin>>input;
	if(!isInteger3(input,3)){
		printf("������Ų����ڣ�����������\n");
		goto a;
	}
	switch(input[0]){
		case '1': {
			cout<<"***********ע��**********\n";		
			(*username)=signUp();
			return false;
		}
		case '2': {
			cout<<"***********��¼***********\n";
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
bool loginMySQL()
{
	string username;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	ConnectSQL();
	return select(&username);
}
void checkLoginMySQL()
{
	goods *head;
	if(!loginMySQL()){//
		head=create();
		menu(head);
	}else{
		head=assignCreate(getTablename());
		if(!head||!head->next){ 
			printf("���û����ݿ�Ϊ��,���ڽ����ʼ��...\n");
			printf("*****1.��������***2.�˳�*****\n");
			string n;
		a:	cin>>n;
			if(!isInteger3(n,2)){
				printf("������Ų����ڣ�����������\n");
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
		menu(head);
	}
}
int main() {
	HWND my_consle = GetForegroundWindow();
	ShowWindow(my_consle, SW_MAXIMIZE);
	welcome();
	checkLoginMySQL();
	goods *head;
	head=create();
	menu(head);		
	return 0;
}

