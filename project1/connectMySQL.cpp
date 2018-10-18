#include <stdio.h>
#include <string>
#include <include/mysql.h>
#include <iostream>
using namespace std;
MYSQL mysql;
char query[100];
string dbname="odbcDemo";
bool createDB(string dbname)
{
	sprintf(query,"create database if not exists %s",dbname.c_str());
	if(mysql_real_query(&mysql,query,(unsigned)strlen(query))){
		printf("query error: %s\n",mysql_error(&mysql));
		return false;
	}else{ 
		printf("Success!\n");
		return true; 
	} 
}
int main()
{
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql,"localhost","root","195477","test",3306,NULL,0)){
			printf("Error connecting to database.%s\n",mysql_error(&mysql));
		}else 
			printf("Connected...\n");
	if(createDB(dbname)){ 
		sprintf(query,"use %s",dbname.c_str());	
		if(mysql_real_query(&mysql,query,(unsigned)strlen(query))){
			printf("query error: %s\n",mysql_error(&mysql));
		}else{ 
			string createTableInfo;
			createTableInfo="CREATE TABLE register (username varchar(255) DEFAULT NULL,password varchar(255) DEFAULT NULL) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
			if(mysql_real_query(&mysql,createTableInfo.c_str(),(unsigned)strlen(createTableInfo.c_str()))){
				printf("query error: %s\n",mysql_error(&mysql));
			}else{
				printf("success!\n");
			}
		} 
	} 
	return 0;
}

