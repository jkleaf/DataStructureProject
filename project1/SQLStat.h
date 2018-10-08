#include <iostream>
#include <include/mysql.h>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <list>
#include "SetColor.h"
using namespace std;
char str[100];
string username,password;
MYSQL mysql;
MYSQL_RES *res; 
MYSQL_ROW row;
char pwd_user[100];
char query[100];
void inputPwd(char *pwd){
	memset(pwd_user,'\0',sizeof(pwd_user));
	int i=0;
	while((pwd[i++]=getch())!='\r') 
		cout<<"*";
	pwd[i-1]='\0';
	cout<<endl;		
}
void ConnectSQL()
{
	initHandle();
	if(!mysql_real_connect(&mysql,"localhost","root","195477",
			"odbc_demo1",3306,NULL,0)){setColor(RED);
			printf("Error connecting to database.%s\n",mysql_error(&mysql));setColor(WHITE);
			printf("exit...");
			Sleep(1000);
			exit(0);
	}else{
		setColor(GREEN);
		printf("Connecting MySQL...\n");
		setColor(WHITE);
		Sleep(1000);	
	}
}
bool queryError(char *query,string handle)
{
	if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){setColor(RED);
		printf("query error: %s",mysql_error(&mysql));setColor(WHITE);
		return false;
	}
	else{
//		printf("%s成功!\n",handle.c_str());
		return true;
	}
} 
void loading()
{
	setColor(BLUE);
	for(int i=1;i<=20;i++){ 
		Sleep(50); 
		printf("▉");
	}setColor(WHITE);
	printf("\n");	
}
string signUp()
{
a1:	cout<<"用户名:";
	cin>>username;
	cout<<"密码:";
	inputPwd(pwd_user);
	password=pwd_user;
	bool flag_repeat=false;
	strcpy(query,"select *from register");
	if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){
		setColor(RED);printf("query error: %s",mysql_error(&mysql)); 
		setColor(WHITE);
	}else{
		res=mysql_store_result(&mysql);
		while(row=mysql_fetch_row(res)){
			if(!strcmp(row[0],username.c_str())){
				flag_repeat=true; break;
			}
		}
	}
	if(!flag_repeat){	
	string insert_info="'"+username+"','"+password+"'";
	sprintf(str,"values(%s)",insert_info.c_str());
	strcpy(query,"insert into register(username,password) "); 
	strcat(query,str);
	if(!mysql_query(&mysql,query)){ 
		cout<<"注册成功..."<<endl;
		Sleep(1000);setColor(LIGHT_BLUE);
		cout<<"欢迎! ";
		setColor(GREEN);cout<<username;setColor(WHITE);cout<<endl;
		string queryStr;
		queryStr="create table "+username+"_table"
			+"(goodsId varchar(100) DEFAULT NULL,"
			+ "goodsName varchar(100) DEFAULT NULL,"
			+ "goodsPrice double DEFAULT NULL,"
			+ "goodsNum int(11) DEFAULT NULL,"
			+ "goodsSold int(11) DEFAULT NULL"
			+ ") ENGINE=InnoDB DEFAULT CHARSET=utf8";
		Sleep(1000);
		if(mysql_real_query(&mysql,queryStr.c_str(),
			(unsigned int)strlen(queryStr.c_str()))){
			setColor(RED);printf("query error: %s",mysql_error(&mysql)); 
			setColor(WHITE); 
		}else
			setColor(YELLOW); 
			printf("正在初始化数据库...\n");
			loading();
			return username;
		}	
		else cout<<"insert error!"<<endl;		
	}else{
		setColor(RED);
		cout<<"用户名已存在! 请再次输入.\n";
		setColor(WHITE);
		goto a1;
	}
	return NULL;
}
string signIn()
{
a2:	cout<<"用户名:";
	cin>>username;
	cout<<"密码:";
	inputPwd(pwd_user);
	password=pwd_user;
	strcpy(query,"select *from register");
	int t=mysql_real_query(&mysql,query,(unsigned int)strlen(query)); 
	if(t){ 
		setColor(RED);printf("query error: %s",mysql_error(&mysql)); 
		setColor(WHITE);	
	}else{
	 	bool flag=false; 
		res=mysql_store_result(&mysql);
		while(row=mysql_fetch_row(res)){ 
			if(!strcmp(username.c_str(),row[0])&&!strcmp(password.c_str(),row[1])){
				flag=true;					
				cout<<"登录成功..."<<endl;
				Sleep(1000);setColor(LIGHT_BLUE);
				cout<<"欢迎! ";
				setColor(GREEN);cout<<row[0]<<endl;setColor(WHITE);
				cout<<"正在加载数据库...\n";
				loading();
				string selectQuery="select *from "+username+"_table";	
				strcpy(query,selectQuery.c_str());
				if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){
					setColor(RED);printf("query error: %s",mysql_error(&mysql)); 
					setColor(WHITE);
				}else{	
//					res=mysql_store_result(&mysql);
//					char *str_fields[100];
//					for(int i=0;i<5;i++)
//						str_fields[i]=mysql_fetch_field(res)->name;
//					Sleep(1000);
//					cout<<"\t\t\t  fields of "<<username+"_table as follows\n";
//					setColor(YELLOW);cout<<"\t";
//					for(int i=0;i<5;i++)
//						printf("%-10s\t",str_fields[i]);
//					cout<<endl;
//					setColor(WHITE);
					return username;
				}
				break;
			}
		}	
		if(!flag){ 
			setColor(RED);
			cout<<"username or password wrong! please input again.\n"; 
			setColor(WHITE);
			goto a2; 
		} 
	}
	return NULL;
}
bool select(string *username)
{
	setColor(PURPLE);	
	cout<<"1.注册##########2.登录\n";
	setColor(WHITE);
	int input;
	cin>>input;
	switch(input){
		case 1: {
			cout<<"***********注册**********\n";		
			(*username)=signUp();
			return false;
		}
		case 2: {
			cout<<"***********登录***********\n";
			(*username)=signIn();
			return true;
		}
	}
}
bool insertSQL(string table_name,string goodsId,string goodsName,
		double goodsPrice,int goodsNum,int goodsSold)
{
	sprintf(query,"insert into %s values('%s','%s','%lf','%d','%d')",table_name.c_str(),
			goodsId.c_str(),goodsName.c_str(),goodsPrice,goodsNum,goodsSold);		
	return queryError(query,"插入");	
}
bool deleteSQLId(string table_name,string goodsId)
{
	sprintf(query,"delete from %s where goodsId=%s",table_name.c_str(),goodsId.c_str());
	return queryError(query,"删除");
}
bool deleteSQLName(string table_name,string goodsName)
{
	sprintf(query,"delete from %s where goodsName=%s",table_name.c_str(),goodsName.c_str());
	return queryError(query,"删除");
}
bool updateSQLId(string table_name,int goodsSold,string goodsId)
{
	sprintf(query,"update %s set goodsSold = %d where goodsId =%s",
			table_name.c_str(),goodsSold,goodsId.c_str());			
	return queryError(query,"更新");	
}
bool updateSQLName(string table_name,int goodsSold,string goodsName)
{
	sprintf(query,"update %s set goodsSold =%d where goodsName =%s",
		table_name.c_str(),goodsSold,goodsName.c_str());			
	return queryError(query,"更新");	
}
bool querySQL(string table_name)
{
	sprintf(query,"select *from %s",table_name.c_str());
	return queryError(query,"查询");			
}
string getUsername()
{
	return username;
}
string getTablename()
{
	return getUsername()+"_table";
}
void FreeResult(MYSQL_RES *res)
{
	mysql_free_result(res);  
}
void closeMySQL()
{
	mysql_close(&mysql);	 
}

