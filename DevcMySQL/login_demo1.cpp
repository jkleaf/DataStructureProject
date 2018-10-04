#include <iostream>
#include <include/mysql.h>
#include <cstdio>
using namespace std;
string username,password,database_name;
char str[100];
int main() {
	MYSQL mysql;
	MYSQL_RES *res; 
    MYSQL_ROW row;
//	string query;
	char query[100];
	mysql_init(&mysql);
b:	cout<<"*****sign in MySQL*****"<<endl;
	cout<<"user:";
	cin>>username;
	cout<<"password:";
	cin>>password;
	cout<<"database_name:";//logindemo1
	cin>>database_name; 
	if(!mysql_real_connect(&mysql,"localhost", username.c_str(), password.c_str(),
			 database_name.c_str(),3306,NULL,0)){
		printf("Error connecting to database%s\n",mysql_error(&mysql));
		cout<<"please input again.\n";
		goto b;
	}else
		printf("Connected...\n");
	cout<<"1.sign up########2.sign in\n";
	int input;
	cin>>input;
	switch(input){
		case 1: {
			cout<<"*********register*********\n";
			cout<<"user:";
			cin>>username;
			cout<<"password:";
			cin>>password;
			string insert_info="'"+username+"','"+password+"'";
			sprintf(str,"values(%s)",insert_info.c_str());
		//	query="insert into register(username,password) "+str;
			strcpy(query,"insert into register(username,password) "); 
			strcat(query,str);
			if(!mysql_query(&mysql,query)) 
				cout<<"successfully register!"<<endl;
			else cout<<"insert error!"<<endl;
			break;
		}
		case 2: {
			cout<<"***********login***********\n"; 
	a:		cout<<"user:";
			cin>>username;
			cout<<"password:";
			cin>>password;
			strcpy(query,"select *from register");
			int t=mysql_real_query(&mysql,query,(unsigned int)strlen(query)); 
      		if(t){ 
          		printf("query error: %s",mysql_error(&mysql)); 
 			}else{ 
				res=mysql_store_result(&mysql);
				row=mysql_fetch_row(res);
				if(strcmp(username.c_str(),row[0])||strcmp(password.c_str(),row[1])){ 
					cout<<"username or password wrong! please input again.\n";
					goto a; 
				}else
					cout<<"successfully login!";	 
			} 
			break;
		}
	}
}
