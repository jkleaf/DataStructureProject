#include <iostream>
#include <include/mysql.h>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include "SetColor.h"
using namespace std;
string username,password,database_name;
char str[100];	
MYSQL mysql;
MYSQL_RES *res; 
MYSQL_ROW row;
char pwd_user[100],pwd_database[100];
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
	initHandle();//
	string username,password,dbname;
	setColor(PURPLE);
	printf("*****sign in MySQL*****\n");
	setColor(WHITE);
	printf("user:");
	cin>>username;
	printf("passwrod:");
	inputPwd(pwd_database);
	password=pwd_database;
	printf("database_name:");
	cin>>dbname;
	if(!mysql_real_connect(&mysql,"localhost",username.c_str(),password.c_str(),
			dbname.c_str(),3306,NULL,0)){setColor(RED);
			printf("Error connecting to database.%s\n",mysql_error(&mysql));setColor(WHITE);
			printf("exit...");
			Sleep(1000);
			exit(0);
	}else{
		setColor(GREEN);
		printf("Connected...\n");
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
		printf("sucessfully %s!\n",handle.c_str());
		return true;
	}
} 
string signUp()
{
a1:	cout<<"user:";
	cin>>username;
	cout<<"password:";
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
		cout<<"successfully register..."<<endl;
		Sleep(1000);setColor(LIGHT_BLUE);
		cout<<"welcome! ";
		setColor(GREEN);cout<<username;setColor(WHITE);cout<<endl;
		cout<<"creating a table...\n";
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
			cout<<"successfully created!\n";
			return username;
		}	
		else cout<<"insert error!"<<endl;		
	}else{
		setColor(RED);
		cout<<"user already exits! please input again.\n";
		setColor(WHITE);
		goto a1;
	}
	return NULL;
}
string signIn()
{
a2:	cout<<"user:";
	cin>>username;
	cout<<"password:";
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
				cout<<"successfully login..."<<endl;
				Sleep(1000);setColor(LIGHT_BLUE);
				cout<<"welcome! ";
				setColor(GREEN);cout<<row[0]<<endl;setColor(WHITE);
				cout<<"loading your table...\n";
				string selectQuery="select *from "+username+"_table";	
				strcpy(query,selectQuery.c_str());
				if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){
					setColor(RED);printf("query error: %s",mysql_error(&mysql)); 
					setColor(WHITE);
				}else{	
					res=mysql_store_result(&mysql);
					char *str_fields[100];
					for(int i=0;i<5;i++)
						str_fields[i]=mysql_fetch_field(res)->name;
					Sleep(1000);
					cout<<"\t\t\t  fields of "<<username+"_table as follows\n";
					setColor(YELLOW);cout<<"\t";
					for(int i=0;i<5;i++)
						printf("%-10s\t",str_fields[i]);
					cout<<endl;
					setColor(WHITE);
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
void select(string *username)
{
	setColor(PURPLE);	
	cout<<"1.sign up########2.sign in\n";
	setColor(WHITE);
	int input;
	cin>>input;
	switch(input){
		case 1: {
			cout<<"*********register*********\n";		
			(*username)=signUp();
			break;
		}
		case 2: {
			cout<<"***********login***********\n";
			(*username)=signIn();
			break;
		}
	}
}
bool insertSQL(string table_name,string goodsId,string goodsName,
		double goodsPrice,int goodsNum,int goodsSold)
{
	sprintf(query,"insert into %s values('%s','%s','%lf','%d','%d')",table_name.c_str(),
			goodsId.c_str(),goodsName.c_str(),goodsPrice,goodsNum,goodsSold);		
	return queryError(query,"insert");	
}
bool deleteSQLId(string table_name,string goodsId)
{
	sprintf(query,"delete from %s where goodsId=%s",table_name.c_str(),goodsId.c_str());
	return queryError(query,"delete");
}
bool deleteSQLName(string table_name,string goodsName)
{
	sprintf(query,"delete from %s where goodsName=%s",table_name.c_str(),goodsName.c_str());
	return queryError(query,"delete");
}
bool updateSQLId(string table_name,int goodsSold,string goodsId)
{
	sprintf(query,"update %s set goodsSold = %d where goodsId =%s",
			table_name.c_str(),goodsSold,goodsId.c_str());			
	return queryError(query,"update");	
}
bool updateSQLName(string table_name,int goodsSold,string goodsName)
{
	sprintf(query,"update %s set goodsSold =%d where goodsName =%s",
		table_name.c_str(),goodsSold,goodsName.c_str());			
	return queryError(query,"update");	
}
void querySQL()
{
			
}
void FreeResult(MYSQL_RES *res)
{
	mysql_free_result(res);  
}
void closeMySQL()
{
	mysql_close(&mysql);	 
}

