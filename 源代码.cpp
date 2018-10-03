/*��Ʒ����ϵͳ*/
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
	string id;//��Ʒ���
	string name;//��Ʒ����
	double price;//��Ʒ�۸�
	int  number;//��Ʒ����
	int sold=0;//��������
	struct goods *next;
};
struct sort1 {
	string id;
	string name;//��Ʒ����
	double price;//��Ʒ�۸�
	int  number;//��Ʒ����
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
bool isInteger1(string s) {//������0
	if(s[0]=='0') return false;
	return checkNum(s,0);
}
bool isInteger2(string s) { //����
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

int convertInteger(string s) {//ת������
	int i=0;
	if(s[0]=='-') i++;
	int n=0;
	for(; i<s.length(); i++)
		n=n*10+s[i]-48;
	return s[0]=='-'? -n:n;
}
double convertFraction(string s) { //ת��С��(�۸�)
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
	printf("��������Ʒ��������\n");
	cin>>n;
	if(!isInteger1(n)) {
		printf("�������,����������\n");
		goto a;
	} else {
		zongshu=convertInteger(n);
		printf("��������Ʒ��� ��Ʒ���� ��Ʒ�۸� ��Ʒ����\n");
		int num=zongshu;
		while(num--) {
			p->next=new goods;
			p=p->next;
b:
			cin>>id>>name>>price>>number;
			//scanf("%d%s%lf%d",&p->id,p->name,&p->price,&p->number);
			if(!isInteger1(id)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
				printf("�����������������\n");
				goto b;
			}
			else if(!Isrepeat(head,id,name)){
				printf("���������ظ��ı�������ƣ�����������\n");
				printf("�Ƿ���Ҫ���б��������Ʋ��ػ��������ʹ�ñ��������\n");
				printf("****1:�������Ʋ���***********2:�����ʹ�ñ��������****���������������������Ʒ��Ϣ��\n");
				/*********/ 
				int x;
				cin>>x;
				switch(x){
					case 1:{
						cout<<"��������Ҫ���صı���"<<endl; 
						string ID;
						int flag=0;
						while(!flag){
						d:cin>>ID;
						if(isInteger1(ID)){
						 
							if(!Isrepeat(head,ID," ")){
								cout<<"�Ѵ��ڸñ���"<<endl;}
							else cout<<"�ñ�����δ��ʹ��"<<endl; 
								}
						else {
							cout<<"������벻����ϵͳҪ������������"<<endl;
							goto d;
						}
						cout<<"�Ƿ������ѯ����������0���������������Ʒ��Ϣ"<<endl;
						 cin>>flag;
						}
						break;
					}
					case 2:{
						goods *temp=head->next;
						while(temp->next){
							cout<<"���룺"<<temp->id<<"    ���ƣ�"<<temp->name<<endl; 
							temp=temp->next;
						}
						break;
					} 
					
				}
				
			/*******/ 
			printf("��������Ʒ��� ��Ʒ���� ��Ʒ�۸� ��Ʒ����\n");
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
	if(p==NULL) printf("��ǰ����ϵͳ������\n");
	printf("������Ʒ��������\n");
	while(p) {
		//printf("��ţ�%d    ���ƣ�%s     �۸�%.2lf     ������%d   ���������%d\n",p->id,p->name,p->price,p->number,p->sold);
		cout<<"��ţ�"<<p->id<<"    ���ƣ�"<<p->name<<"     �۸�"<<p->price<<"     ������"<<p->sold<<endl;
		p=p->next;
	}
	menu(head);
}
void welcome() {
	printf("****************************************\n");
	printf("**********��ӭʹ�ñ���Ʒ����ϵͳ********\n");
	printf("****************************************\n");
}

void change1(goods*head) {
	goods*p=head->next;
	string j,n,n1,n2;
	int k;
a:
	printf("������Ҫ�޸���Ʒ���ݵ���Ʒ����\n");
	/*******************/
	cin>>n;
	if(!isInteger1(n)) {
		printf("�����������������\n");
//		menu(head);
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("�����������������\n");
//		menu(head);
		goto a;
	}
	/*******************/
	printf("�޸ĸ�ʽΪ��Ʒ����+���۶���븺�����������)\n");
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!isInteger1(n1)||!isInteger2(n2)) {
			printf("�����������������\n");
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
						printf("���۶���ڿ�棬��������,�������������+���۶�\n");
						goto b;
					}
				}
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
	printf("������Ҫ�޸���Ʒ���ݵ���Ʒ����\n");
a:
	cin>>n;
	if(!isInteger1(n)) {
		printf("�����������������\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("�����������������\n");
		goto a;
	}
	printf("�޸ĸ�ʽΪ��Ʒ����+���۶���븺�����������)\n");
	for(int i=1; i<=num; i++) {
b:
		cin>>n1>>n2;
		if(!isInteger2(n2)) {
			printf("�����������������\n");
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
						printf("���۶���ڿ�棬��������,�������������+���۶�\n");
						goto b;
					}
				}
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
	string id,name,price,number;
	goods*p,*q;
	printf("���������λ�ã�����0Ĭ�ϲ���ĩ��\n");
	string n;
a:	cin>>n;
	if(!checkNum(n,0)) { //����0
		printf("�����������������\n");
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
		printf("������Ҫ���������Ʒ��Ϣ����ʽΪ��Ʒ���+��Ʒ����+��Ʒ�۸�+��Ʒ������\n");
b:
		cin>>id>>name>>price>>number;
		if(!isInteger1(id)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
			printf("�����������������\n");
			goto b;
		}
		else if(!Isrepeat(head,id,name)){
				printf("���������ظ��ı�������ƣ�����������\n");
				printf("�Ƿ���Ҫ���б��������Ʋ��ػ��������ʹ�ñ��������\n");
				printf("****1:�������Ʋ���***********2:�����ʹ�ñ��������****���������������������Ʒ��Ϣ��\n");
				/*********/ 
				int x;
				cin>>x;
				switch(x){
					case 1:{
						cout<<"��������Ҫ���صı���"<<endl; 
						string ID;
						int flag=0;
						while(!flag){
						e:cin>>ID;
						if(isInteger1(ID)){
						 
							if(!Isrepeat(head,ID," ")){
								cout<<"�Ѵ��ڸñ���"<<endl;}
							else cout<<"�ñ�����δ��ʹ��"<<endl; 
								}
						else {
							cout<<"������벻����ϵͳҪ������������"<<endl;
							goto e;
						}
						cout<<"�Ƿ������ѯ����������0���������������Ʒ��Ϣ"<<endl;
						 cin>>flag;
						}
						break;
					}
					case 2:{
						goods *temp=head->next;
						while(temp->next){
							cout<<"���룺"<<temp->id<<"    ���ƣ�"<<temp->name<<endl; 
							temp=temp->next;
						}
						break;
					} 
					
				}
				
			/*******/ 
			printf("��������Ʒ��� ��Ʒ���� ��Ʒ�۸� ��Ʒ����\n");
				goto b; }
			else{
		
		q->id=id;//convertInteger(id);
		q->name=name;
		q->price=isInteger1(price)? convertInteger(price):convertFraction(price);
		q->number=convertInteger(number);
		q->next=p->next;
		p->next=q;
		printf("�����ѳɹ�\n");
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
		printf("������Ҫ���������Ʒ��Ϣ����ʽΪ��Ʒ���+��Ʒ����+��Ʒ�۸�+��Ʒ������\n");
c:
		cin>>id>>name>>price>>number;
		if(!isInteger1(id)||(!isInteger1(price)&&!isFraction(price))||!isInteger1(number)) {
			printf("�����������������\n");
			goto c;
		}
	else if(!Isrepeat(head,id,name)){
				printf("���������ظ��ı�������ƣ�����������\n");
				printf("�Ƿ���Ҫ���б��������Ʋ��ػ��������ʹ�ñ��������\n");
				printf("****1:�������Ʋ���***********2:�����ʹ�ñ��������****���������������������Ʒ��Ϣ��\n");
				/*********/ 
				int x;
				cin>>x;
				switch(x){
					case 1:{
						cout<<"��������Ҫ���صı���"<<endl; 
						string ID;
						int flag=0;
						while(!flag){
						f:cin>>ID;
						if(isInteger1(ID)){
						 
							if(!Isrepeat(head,ID," ")){
								cout<<"�Ѵ��ڸñ���"<<endl;}
							else cout<<"�ñ�����δ��ʹ��"<<endl; 
								}
						else {
							cout<<"������벻����ϵͳҪ������������"<<endl;
							goto f;
						}
						cout<<"�Ƿ������ѯ����������0���������������Ʒ��Ϣ"<<endl;
						 cin>>flag;
						}
						break;
					}
					case 2:{
						goods *temp=head->next;
						while(temp->next){
							cout<<"���룺"<<temp->id<<"    ���ƣ�"<<temp->name<<endl; 
							temp=temp->next;
						}
						break;
					} 
					
				}
				
			/*******/ 
			printf("��������Ʒ��� ��Ʒ���� ��Ʒ�۸� ��Ʒ����\n");
				goto c; }
		else{
		
		q->id=id;//convertInteger(id);
		q->name=name;
		q->price=isInteger1(price)? convertInteger(price):convertFraction(price);
		q->number=convertInteger(number);
		q->next=p->next;
		p->next=q;
		printf("�����ѳɹ�\n");
		zongshu++;}
	}
	menu(head);
}
void delet(goods*head) {
	goods*q,*p=head->next;
	int i=0;
	string j,s;
	printf("������Ҫɾ����Ʒ�ı��������\n");
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
				printf("ɾ����Ʒ��Ϣ�ɹ�\n");
				zongshu--;
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
	printf("#####1�������Ʒ��Ϣ#####2��ɾ����Ʒ��Ϣ#####\n");
	/*****************/
a:
	cin>>n;
	if(!isInteger3(n,2)) {
		printf("�����������������\n");
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
	printf("������Ҫ��ѯ����Ʒ���루������-1�����������Ʒ�������ܶ��棩\n");
a:
	cin>>n;
	if(!isInteger2(n)) {
		printf("�����������������\n");
		goto a;
	}
	if(n.length()==2&&n[0]=='-'&&n[1]=='1') {
		while(p) {
			//printf("��ţ�%d    ���ƣ�%s     �۸�%.2lf     ������%d   ���������%d     ���۽�%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
			cout<<"��ţ�"<<p->id<<"    ���ƣ�"<<p->name<<"     �۸�"<<p->price<<"     ������"<<
				p->number<<"   ���������"<<p->sold;
			printf("     ���۽�%.2lf\n",1.0*(p->sold)*(p->price));
			p=p->next;
		}
	} else if(n[0]!='-') {
		string num=n;//convertInteger(n);
		while(p) {
			if(p->id==num) {
				//printf("��ţ�%d    ���ƣ�%s     �۸�%.2lf     ������%d   ���������%d     ���۽�%lf\n",p->id,p->name,p->price,p->number,p->sold,1.0*(p->sold)*(p->price));
			cout<<"��ţ�"<<p->id<<"    ���ƣ�"<<p->name<<"     �۸�"<<p->price<<"     ������"<<
				p->number<<"   ���������"<<p->sold;
			printf("     ���۽�%.2lf\n",1.0*(p->sold)*(p->price));
				break;
			}
			p=p->next;
		}
		if(p==NULL) {
			printf("��������\n");
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
	printf("������Ҫ�������Ʒ����");
	string n;
a:
	cin>>n;
	if(!isInteger1(n)) {
		printf("�������,����������\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("�������,����������\n");
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
	printf("**********************����������Ʒ����������********************\n") ;
	printf("��Ʒ���    ��Ʒ����     ��Ʒ�۸�       ��Ʒ����       ��Ʒ���۶� \n");
	for(int i=0; i<num; i++) {
//	printf("%d    %s   %.2f    %d      %d   ",flag[i].id,flag[i].name,flag[i].price,flag[i].number,flag[i].sold);
		cout<<flag[i].id<<"    "<<flag[i].name<<"   "<<flag[i].price<<"    "<<flag[i].number<<"      "<<flag[i].sold<<endl;
	}
	delete[] flag;
	menu(head);
}
void low(goods*head) {
	goods *p=head->next;
	printf("������Ҫ�������Ʒ����");
	string n;
a:
	cin>>n;
	if(!isInteger1(n)) {
		printf("�������,����������\n");
		goto a;
	}
	int num=convertInteger(n);
	if(num>zongshu) {
		printf("�������,����������\n");
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
	printf("**********************����������Ʒ����������********************\n") ;
	printf("��Ʒ���    ��Ʒ����     ��Ʒ�۸�       ��Ʒ����       ��Ʒ���۶� \n");
	for(int i=zongshu-1; i>zongshu-num-1; i--) {
//		printf("%d    %s   %.2f    %d      %d   \n",flag[i].id,flag[i].name,flag[i].price,flag[i].number,flag[i].sold);
		cout<<flag[i].id<<"    "<<flag[i].name<<"   "<<flag[i].price<<"    "<<flag[i].number<<"      "<<flag[i].sold<<endl;
	}
	delete[] flag;
	menu(head);
}
void search(goods* head) {
	printf("����������루1����ѯ���ۻ𱬵���Ʒ��2����ѯ���۽ϲ����Ʒ\n");
	string n;
d:
	cin>>n;
	if(!isInteger3(n,2)) {
		printf("�����������������\n");
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
	printf("#########��ӭ�´�ʹ��########\n");
	exit(1);
}
void qingpin(goods*head) {
	system("cls");
	menu(head);
}
void menu(goods*head) {
	printf("**************************************\n");
	printf("**********���ѽ���ѡ��˵�************\n");
	printf("**************************************\n");
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
		printf("�����������������\n");
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

