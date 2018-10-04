#include <iostream>
#include <include/mysql.h>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <set>
using namespace std;
string username,password,database_name;
char str[100];
char pwd_database[100];
char pwd_user[100];
set <string> s; 
void inputPwd(char *pwd){
	memset(pwd_user,'\0',sizeof(pwd_user));
	int i=0;
	while((pwd[i++]=getch())!='\r') 
		cout<<"*";
	pwd[i-1]='\0';//length
	cout<<endl;		
} 
void insertSet(MYSQL_RES *res_set){
	MYSQL_ROW row;
	while(row=mysql_fetch_row(res_set)){
		s.insert(row[0]);
	}
}
int main() {
	MYSQL mysql;
	MYSQL_RES *res; 
    MYSQL_ROW row;
//	string query;
	char query[100];
	mysql_init(&mysql);
//b:	cout<<"*****sign in MySQL*****"<<endl;
//	cout<<"user:";
//	cin>>username;
//	cout<<"password:";
//	inputPwd(pwd_database);
//	password=pwd_database;
////	cin>>password;
//	cout<<"database_name:";//logindemo1
//	cin>>database_name; 
	if(!mysql_real_connect(&mysql,"localhost",username.c_str(),password.c_str(),
			database_name.c_str(),3306,NULL,0)){
//	if(!mysql_real_connect(&mysql,"localhost","root","195477",
//		"logindemo1",3306,NULL,0)){
		printf("Error connecting to database.%s\n",mysql_error(&mysql));
//		cout<<"please input again.\n";
//		goto b;
	}else
		printf("Connected...\n");	
//	insertSet(mysql_store_result(&mysql));
//	row=mysql_fetch_row(mysql_store_result(&mysql));
	cout<<"1.sign up########2.sign in\n";
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
//			cin>>password;
			bool flag_repeat=false;
//			if(s.count(username))
//				flag_repeat=true;
			if(!flag_repeat){ 
				string insert_info="'"+username+"','"+password+"'";
				sprintf(str,"values(%s)",insert_info.c_str());
			//	query="insert into register(username,password) "+str;
				strcpy(query,"insert into register(username,password) "); 
				strcat(query,str);
				if(!mysql_query(&mysql,query)){ 
					cout<<"successfully register..."<<endl;
					Sleep(1000);
					cout<<"welcome! "<<username; 
				}	
				else cout<<"insert error!"<<endl;
			}
//			else{
//				cout<<"user already exits! please input again.\n";
//				goto a1;
//			} 
			break;
		}
		case 2: {
			cout<<"***********login***********\n"; 
	a2:		cout<<"user:";
			cin>>username;
			cout<<"password:";
			inputPwd(pwd_user);
			password=pwd_user;
//			cin>>password;
			strcpy(query,"select *from register");
			int t=mysql_real_query(&mysql,query,(unsigned int)strlen(query)); 
      		if(t){ 
          		printf("query error: %s",mysql_error(&mysql)); 
 			}else{
			 	bool flag=false; 
				res=mysql_store_result(&mysql);
				while(row=mysql_fetch_row(res)){ 
//					for(t=0;t<mysql_num_fields(res);t++){ 
					if(!strcmp(username.c_str(),row[0])&&!strcmp(password.c_str(),row[1])){
						flag=true;					
						cout<<"successfully login..."<<endl;
						Sleep(1000);
						cout<<"welcome! "<<row[0];						 
						break;
					}
//					} 
				}	
				if(!flag){ 
					cout<<"username or password wrong! please input again.\n"; 
					goto a2; 
				} 
			} 
			break;
		}
	}
}
