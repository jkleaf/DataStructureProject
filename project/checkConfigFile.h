#include <iostream>
#include <fstream>
using namespace std;
string filePath="config.ini";
void configFileRead(string *username,string *password)
{
	ifstream configFile;
	string line;
	configFile.open(filePath.c_str());
	if(configFile.is_open()){
		while(!configFile.eof()){
			getline(configFile,line);
			size_t pos=line.find("=");
			string key=line.substr(0,pos);
			if(key=="username")
				(*username)=line.substr(pos+1);
			if(key=="password")
				(*password)=line.substr(pos+1);
		}
	}
}
bool checkFileExists()
{
	fstream configFile;
	configFile.open(filePath.c_str());
	return configFile;
}
void configFileWrite(string username,string password)
{
	ofstream fout(filePath.c_str());
	if(fout){ 
		fout<<"username="<<username<<endl;
		fout<<"password="<<password; 
	}
	fout.close();		
}
