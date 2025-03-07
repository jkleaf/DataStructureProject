#include <iostream>
#include <include/mysql.h>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#define RED FOREGROUND_RED | FOREGROUND_INTENSITY
#define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define BLUE FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define YELLOW FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define PURPLE FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define LIGHT_BLUE FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
using namespace std;
string username,password,database_name;
char str[100];
char pwd_database[100];
char pwd_user[100];	
MYSQL mysql;
HANDLE hOut;     
void inputPwd(char *pwd){
	memset(pwd_user,'\0',sizeof(pwd_user));
	int i=0;
	while((pwd[i++]=getch())!='\r') 
		cout<<"*";
	pwd[i-1]='\0';
	cout<<endl;		
}
void setColor(WORD wAttributes){
	SetConsoleTextAttribute(hOut,wAttributes);   	
}
bool createDataBase(string dbname){
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string query="create database if not exists ";
	query+=dbname;
	if(!mysql_query(&mysql,query.c_str())){
		query="use ";
		query+=dbname;
		if(!mysql_query(&mysql,query.c_str()))
			return true; 
	}	
	return false;		
}
int main() {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	MYSQL_RES *res; 
    MYSQL_ROW row;
	char query[100];
	string dbname;
	mysql_init(&mysql);
	setColor(PURPLE);
	cout<<"*****sign in MySQL*****"<<endl;
	setColor(WHITE);
	cout<<"user:";
	cin>>username;
	cout<<"password:";
	inputPwd(pwd_database);
	password=pwd_database;
	cout<<"database_name:";
	cin>>dbname;
//	if(createDataBase(dbname)){
		if(!mysql_real_connect(&mysql,"localhost",username.c_str(),password.c_str(),
			dbname.c_str(),3306,NULL,0)){
			setColor(RED);printf("Error connecting to database.%s\n",mysql_error(&mysql));
			setColor(WHITE);
			cout<<"exit...";
			Sleep(1000);
			exit(0);
		}else{setColor(BLUE);
			printf("Connected...\n");
			Sleep(1000);
		}
//	}else
//		cout<<"Wrong!";
	setColor(PURPLE);	
	cout<<"1.sign up########2.sign in\n";
	setColor(WHITE);
	int input;
	cin>>input;
	switch(input){
		case 1: {
			cout<<"*********register*********\n";
	a1:		cout<<"user:";
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
				}	
				else cout<<"insert error!"<<endl;		
			}else{
				setColor(RED);
				cout<<"user already exits! please input again.\n";
				setColor(WHITE);
				goto a1;
			}
			break;
		}
		case 2: {
			cout<<"***********login***********\n"; 
	a2:		cout<<"user:";
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
//						string queryStr="select COLUMN_NAME from information_schema.COLUMNS where ";
//						string str="table_name = "+username+"_table";
//						queryStr+=str;
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
			break;
		}
	}
	return 0;		
}
