#include <iostream>
#include <include/mysql.h>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <list>
#include "SetColor.h"
#include "checkInput.h"
#include "checkConfigFile.h"
using namespace std;
char str[100];
string username,password;
string dbname="odbcDemo";
MYSQL mysql;
MYSQL_RES *res; 
MYSQL_ROW row;
char pwd_user[100];
char query[100];
void inputPwd(char *pwd){//模拟密码输入用'*'代替 
	memset(pwd_user,'\0',sizeof(pwd_user));
	int i=0;
	while((pwd[i++]=getch())!='\r'){ 
		if(pwd[i-1]==8){ 
			printf("\b \b");
			i-=2; 
		} 
		else 
			printf("*");
	} 
	pwd[i-1]='\0';
	cout<<endl;		
}
bool createDB(string dbname)//创建数据库 
{
	sprintf(query,"create database if not exists %s",dbname.c_str());
	if(mysql_real_query(&mysql,query,(unsigned)strlen(query))){
		printf("query error: %s\n",mysql_error(&mysql));
		return false;
	}else{ 
//		printf("Success!\n");
		return true; 
	} 
}
void ConnectSQL()//连接数据库 
{
	initHandle();
	if(!checkFileExists()){ 
		setColor(PURPLE);
		cout<<"\t                                                                                  *************************sign in MySQL*******************"<<endl;
		setColor(WHITE);
		cout<<"\t                                                                                                           用户名:";
		cin>>username;                 
		cout<<"\t                                                                                                           密  码:";
		inputPwd(pwd_user);
		password=pwd_user;
	}else{
		configFileRead(&username,&password);
	}
	if(!mysql_real_connect(&mysql,"localhost",username.c_str(),password.c_str(),
			"mysql",3306,NULL,0)){setColor(RED);
//			printf("Error connecting to database.%s\n",mysql_error(&mysql));setColor(WHITE);
			printf("\t\t\t\t\t\t\t\t\t\t\t\t数据库连接失败！请检查密码是否输入正确\n");setColor(WHITE); 
			printf("exit...");
			Sleep(1000);
			getch();
			exit(0);
	}else{
		configFileWrite(username,password);
		setColor(GREEN);
		printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tConnecting MySQL...\n");
		setColor(WHITE);
		Sleep(1000);
		if(createDB(dbname)){ 
		sprintf(query,"use %s",dbname.c_str());	
		if(mysql_real_query(&mysql,query,(unsigned)strlen(query))){
			printf("query error: %s\n",mysql_error(&mysql));
		}else{ 
			string createTableInfo;
			createTableInfo="CREATE TABLE if not exists register (username varchar(255) DEFAULT NULL,password varchar(255) DEFAULT NULL) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
			if(mysql_real_query(&mysql,createTableInfo.c_str(),(unsigned)strlen(createTableInfo.c_str()))){
				printf("query error: %s\n",mysql_error(&mysql));
			}else{
//				printf("success!\n");
			}
		} 
	}
	}
}
bool queryError(char *query,string handle)//判断数据库查询失败 
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
void freeResult(MYSQL_RES *res)//释放数据库资源 
{
	mysql_free_result(res);  
}
void loading()//加载数据库效果 
{
	setColor(BLUE);
	printf("                                                                                                      "); 
	for(int i=1;i<=20;i++){ 
		Sleep(50); 
		
		printf("▉");
	}setColor(WHITE);
	printf("\n");	
}
string signUp()//注册用户 
{
a1:	cout<<"                                                                                                             用户名:";
	cin>>username;
	cout<<"                                                                                                             密  码:";
	inputPwd(pwd_user);
	password=pwd_user;
	if(invalidStr(username)||invalidStr(password)){
		setColor(RED);printf("                                                                                             用户名或密码非法！(只能包括数字、字母或下划线)请重新输入\n");setColor(WHITE);
		goto a1;
	}
	if(!checkStrDigit(username)||!checkStrDigit(password)){
		setColor(RED);printf("\t\t\t\t\t\t\t\t\t\t\t\t\t用户名或密码长度太长(不超过10位),请重新输入\n");setColor(WHITE);
		goto a1;
	}
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
	cout<<"                                                                                                                   注册成功..."<<endl;
				Sleep(1000);setColor(YELLOW);
				cout<<"                                                                                                                     欢迎! "<<endl;
				setColor(WHITE);
		setColor(WHITE);cout<<"                                                                                                               用户："<<username;setColor(WHITE);cout<<endl;
		string queryStr;
		queryStr="create table "+username+"_table"
			+"(goodsId varchar(100) DEFAULT NULL,"
			+ "goodsName varchar(100) DEFAULT NULL,"
			+ "goodsPrice double DEFAULT NULL,"
			+ "goodsNum int(11) DEFAULT NULL,"
			+ "goodsSold int(11) DEFAULT NULL,"
			+ "goodsBeforeSold int(11) DEFAULT NULL,"
			+ "goodsCost double(11,2) DEFAULT NULL,"
			+ "goodsProfits double(11,2) DEFAULT NULL"
			+ ") ENGINE=InnoDB DEFAULT CHARSET=utf8";
		Sleep(1000);
		if(mysql_real_query(&mysql,queryStr.c_str(),
			(unsigned int)strlen(queryStr.c_str()))){
			setColor(RED);printf("query error: %s",mysql_error(&mysql)); 
			setColor(WHITE); 
		}else
			setColor(WHITE); 
			printf("                                                                                                      正在初始化数据库...\n");
			loading();
			return username;
		}	
		else cout<<"insert error!"<<endl;		
	}else{
		setColor(RED);
		cout<<"                                                                                                            用户名已存在! 请再次输入.\n";
		setColor(WHITE);
		goto a1;
	}
	return NULL;
}
string signIn()//用户登录 
{
	printf("                                                                                                    ************登录失败5次默认返回************\n\n");
	int times=0;
a2:	cout<<"                                                                                                              用户名:";
	cin>>username;
	cout<<"                                                                                                              密  码:";
	inputPwd(pwd_user);
	password=pwd_user;
	strcpy(query,"select *from register");
	int t=mysql_real_query(&mysql,query,(unsigned int)strlen(query)); 
	if(t){ 
		setColor(RED);printf("query error: %s",mysql_error(&mysql)); 
		setColor(WHITE);	
	}
	else{
	 	bool flag=false; 
		res=mysql_store_result(&mysql);
		/***********/
//		string selectQuery="select count(1) from "+username+"_table"
//			+"where username=";
//		sprintf(query,"select count(1) from %s_table where username='%s' and password='%s'",username.c_str(),username.c_str(),password.c_str());
//		if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){
//			setColor(RED);printf("query error: %s",mysql_error(&mysql));setColor(WHITE);
//		}else
//			printf("YES");
		/***********/ 
		while(row=mysql_fetch_row(res)){ 
			if(!strcmp(username.c_str(),row[0])&&!strcmp(password.c_str(),row[1])){
				flag=true;					
				cout<<"                                                                                                                   登录成功..."<<endl;
				Sleep(1000);setColor(YELLOW);
				cout<<"                                                                                                                     欢迎! "<<endl;
				setColor(WHITE);cout<<"                                                                                                             用户："<<row[0]<<endl;setColor(WHITE);
				cout<<"                                                                                                      正在加载数据库...\n";
				loading();
				printf("                                                                                                      数据库加载完成.\n");
				return username; 
//				string selectQuery="select *from "+username+"_table";	
//				strcpy(query,selectQuery.c_str());
//				if(mysql_real_query(&mysql,query,(unsigned int)strlen(query))){
//					setColor(RED);printf("query error: %s",mysql_error(&mysql)); 
//					setColor(WHITE);
//				}else{	
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
//					freeResult(res);
//					return username;
//				}
			}
		}	
		if(!flag){ 
			setColor(RED);
			cout<<"                                                                                                           用户名或密码错误! 请再次输入.\n"; 
			setColor(WHITE);
			times++;
			if(times==5){
				setColor(RED);cout<<"\n                                                                                                              登录失败5次!重新进行选择\n";setColor(WHITE);
				return "";
			} 
			goto a2; 
		} 
	}
	return NULL;	
}
bool insertSQL(string table_name,string goodsId,string goodsName,//SQL插入语句 
		double goodsPrice,int goodsNum,int goodsSold,int goodsBeforeSold,double goodsCost,double goodsProfits)
{
	sprintf(query,"insert into %s values('%s','%s','%lf','%d','%d','%d','%lf','%lf')",table_name.c_str(),
			goodsId.c_str(),goodsName.c_str(),goodsPrice,goodsNum,goodsSold,goodsBeforeSold,goodsCost,goodsProfits);		
	return queryError(query,"插入");	
}
bool deleteSQLId(string table_name,string goodsId)//SQL根据编码删除语句 
{
	sprintf(query,"delete from %s where goodsId='%s'",table_name.c_str(),goodsId.c_str());
	return queryError(query,"删除");
}
bool deleteSQLName(string table_name,string goodsName)//SQL根据用户名删除语句 
{
	sprintf(query,"delete from %s where goodsName='%s'",table_name.c_str(),goodsName.c_str());
	return queryError(query,"删除");
}
bool updateSQLId(string table_name,int goodsNum,int goodsSold,string goodsId)//SQL根据编码更新语句 
{
	sprintf(query,"update %s set goodsNum = %d , goodsSold = %d where goodsId ='%s'",
			table_name.c_str(),goodsNum,goodsSold,goodsId.c_str());			
	return queryError(query,"更新");	
}
bool updateSQLName(string table_name,int goodsNum,int goodsSold,string goodsName)//SQL根据名称更新语句 
{
	sprintf(query,"update %s set goodsNum = %d , goodsSold = %d where goodsName ='%s'",
		table_name.c_str(),goodsNum,goodsSold,goodsName.c_str());			
	return queryError(query,"更新");	
}
bool updateSQLSales(string table_name,double goodsPrice,int goodsBeforeSold,double goodsProfits,string goodsId)
{																			//SQL更新销售情况 
	sprintf(query,"update %s set goodsPrice = %lf , goodsBeforeSold = %d , goodsProfits = %lf where goodsId ='%s'",
		table_name.c_str(),goodsPrice,goodsBeforeSold,goodsProfits,goodsId.c_str());			
	return queryError(query,"更新");
}
bool truncateSQL(string table_name)//SQL清空表语句 
{
	sprintf(query,"truncate table %s",table_name.c_str());
	return queryError(query,"清空");
}
bool querySQL(string table_name)//SQL查询语句 
{
	sprintf(query,"select *from %s",table_name.c_str());
	return queryError(query,"查询");			
}
string getUsername()//返回用户名 
{
	return username;
}
string getTablename()//返回用户表名 
{
	return getUsername()+"_table";
}
void closeMySQL()//关闭数据库 
{
	mysql_close(&mysql);	 
}
