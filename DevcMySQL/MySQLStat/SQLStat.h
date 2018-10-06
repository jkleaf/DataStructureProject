#include <include/mysql.h>
#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include "SetColor.h"
using namespace std; 
MYSQL mysql;
MYSQL_ROW row;
char query[100],pwd_user[100],pwd_database[100];
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
bool insertSQL(string table_name,string goodsId,string goodsName,
		double goodsPrice,int goodsNum,int goodsSold)
{
	sprintf(query,"insert into %s values('%s','%s','%lf','%d','%d')",table_name.c_str(),
			goodsId.c_str(),goodsName.c_str(),goodsPrice,goodsNum,goodsSold);		
	if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){setColor(RED);
		printf("query error: %s",mysql_error(&mysql));setColor(WHITE);
		return false;
	}
	else{
		printf("sucessfully insert!\n");
		return true;
	}	
}
bool deleteSQLId(string table_name,string goodsId)
{
	sprintf(query,"delete from %s where goodsId=%s",table_name.c_str(),goodsId.c_str());
	if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){setColor(RED);
		printf("query error: %s",mysql_error(&mysql));setColor(WHITE);
		return false;
	}
	else{
		printf("sucessfully delete!\n");
		return true;
	}
}
bool deleteSQLName(string table_name,string goodsName)
{
	sprintf(query,"delete from %s where goodsName=%s",table_name.c_str(),goodsName.c_str());
	if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){setColor(RED);
		printf("query error: %s",mysql_error(&mysql));setColor(WHITE);
		return false;
	}
	else{
		printf("sucessfully delete!\n");
		return true;
	}
}
bool updateSQLId(string table_name,int goodsSold,string goodsId)
{
	sprintf(query,"update %s set goodsSold = %d where goodsId =%s",
			table_name.c_str(),goodsSold,goodsId.c_str());			
	if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){setColor(RED);
		printf("query error: %s",mysql_error(&mysql));setColor(WHITE);
		return false;
	}
	else{
		printf("sucessfully update!\n");
		return true;
	}	
}
bool updateSQLName(string table_name,int goodsSold,string goodsName)
{
	sprintf(query,"update %s set goodsSold =%d where goodsName =%s",
		table_name.c_str(),goodsSold,goodsName.c_str());			
	if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){setColor(RED);
		printf("query error: %s",mysql_error(&mysql));setColor(WHITE);
		return false;
	}
	else{
		printf("sucessfully update!\n");
		return true;
	}	
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

