#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

int dfa = 0; 


void start(char c){ 
	
if (c == 'i') { 
		
dfa = 7;	
}
else if (c == 'f' | 'e' | 'l'| 's'){	
dfa = 8; 
	
}
// -1 is used to check for any invalid symbol 
	
else{ 
		
dfa = -1; 
	
} 

} 


void state1(char c) 

{ 
	
if (c == 'i' | 'f' | 'e' | 'l'| 's') {

 
		dfa = 8;
 
	}
 
	else {
 
		dfa = -1;
 
	} 

} 
void state2(char c) 

{ 
	
if (c == 'e') {

 
		dfa = 1;
 
	}
 
	else if (c == 'i' | 'f' | 'e' | 'l'| 's') {
 
		dfa = 8;
 
	}
 
	else {
 
		dfa = -1;
 
	} 

} 
void state3(char c) 

{ 
	
if (c == 's') {

 
		dfa = 2;
 
	}
 
	else if (c == 'i' | 'f' | 'e' | 'l') {
 
		dfa = 8;
 
	}
 
	else {
 
		dfa = -1;
 
	} 

} 
void state4(char c) 

{ 
	
if (c == 'l') {

 
		dfa = 3;
 
	}
 
	else if (c == 'i' | 'f' | 'e' |'s') {
 
		dfa = 8;
 
	}
 
	else {
 
		dfa = -1;
 
	} 

} 
void state5(char c) 

{ 
	
if (c == 'e') {

 
		dfa = 4;
 
	}
 
	else if (c == 'i' | 'f' | 'e' | 's') {
 
		dfa = 8;
 
	}
 
	else {
 
		dfa = -1;
 
	} 

} 

void state6(char c) 

{ 
	
if (c == ' ') {

 
		dfa = 5;
 
	}
 
	else if (c == 'i' | 'f' | 'e' | 'l'| 's') {
 
		dfa = 8;
 
	}
 
	else {
 
		dfa = -1;
 
	} 

} 

void state7(char c) 

{ 
	
if (c == 'f') {

 
		dfa = 6;
 
	}
 
	else if (c == 'i' | 'e' | 'l'| 's') {
 
		dfa = 8;
 
	}
 
	else {
 
		dfa = -1;
 
	} 

} 






//GLobal Declaration of all methods 
bool isKeyword(char mybuffer[]);	
bool isIdentifier(std::string str);
bool isBinaryOperators(char str);
bool isRelationalOperators(std::string str);
bool isDigit(char str);
bool isQuotation(char str);
bool isAssignmentOperators(char str);
bool isParanthesis(char str);
bool isTerminator(char s);
bool isPartOfRelationOperator(char c);


//Main function

int main()

{
	cout<<"Token file created in existing folder"<<endl;
	
	std::ofstream ofs;
	ofs.open("Token.txt");
	
	
	
	ofs<<endl<<"Lexemes \t Tokens "<<endl<<endl;
	ofs<<"______________________________________________________"<<endl<<endl;
	
	int count;
	char c;
	char mybuffer[16];
	
	ifstream filein("input.zen");
	int i,j=0;
	
	if(!filein.is_open()){
		ofs<<"Some error in opening File"<<endl;
		exit(0);
	}
	while(!filein.eof())
	{
   		c = filein.get();
   		
   		if(isDigit(c)){
   			ofs<<c<< "  \t\t\t\tNUM_CONST"<<endl;
   			count++;
		}
		else if(isalnum(c))
		{
   			mybuffer[j++] = c;
   		}
		else if((c == ' ' || c == '\n') && (j != 0))
		{
	   		mybuffer[j] = '\0';
	   		j = 0;
	   				   				
	   		if(isKeyword(mybuffer) == true)
	   		{
	   			ofs<<mybuffer<<"  \t\t\t\tKEYWORDS"<<endl;
	   			count++;
			}
	   			
	   		else if(isIdentifier(mybuffer)==true)
			{
				ofs<<mybuffer<<"  \t\t\t\tIDENTIFIER"<<endl;
			   	count++;
			}
	   	}
		else if(isParanthesis(c)){
			ofs<<c<<"   \t\t\t\tBRACES"<<endl;
			count++;
		}
		else if (isTerminator(c)){
			ofs<<c<<"  \t\t\t\tBREAK"<<endl;
			count++;
		}
		else if(isPartOfRelationOperator(c)){
			bool flag = false;
			j=0;
			mybuffer[j] = c;
			c = filein.get();
			if(isPartOfRelationOperator(c)){
				mybuffer[j+1] = c;
				mybuffer[j+2]='\0';
				if(isRelationalOperators(mybuffer)){
					flag = true;
					ofs<<mybuffer<< "  \t\t\t\tCOMPARISON_OP"<<endl;
					count++;
				}	
			}
			j=0;
			if(!flag){
				mybuffer[1]='\0';
				if(isRelationalOperators(mybuffer)){
					flag=true;
					ofs<<mybuffer[0]<<" \t\t\t\t Operator"<<endl;
					count++;			
				}
				else if(isAssignmentOperators(mybuffer[0])){
					ofs<<mybuffer[0]<<"  \t\t\t\t ASSIGNMENT_OP"<<endl;
					count++;
				}
			}
		}
		else if(isQuotation(c))
		{
			ofs<<c<< "  \t\t\t\tQUOTATION"<<endl;
			count++;
		}		
	}
	
	
	filein.close();
	
	ofs<<endl<<"______________________________________________________"<<endl;
	ofs<<endl<<"\tCOUNT:  "<<count<<endl<<endl;
	
	return 0;
}

bool isKeyword(char mybuffer[])
{
	char keywords[40][40]={                         "int","Yes","No",
							"read","write","stop",
							
							};
	bool flag=false;
	for(int i=0;i<40;i++){
		if(strcmp(keywords[i],mybuffer)==0){
			flag=true;
			break;
		}
	}
	return flag;						
}
bool isIdentifier(std::string str)
{
	bool choice = false;
	int i;
	for(i =0; i < str.length(); i++)
	{
		if((str[i]>= 'a' || str[i]<= 'z') || (str[i]>= 'A' || str[i]<= 'Z'))
		{
			choice = true;
		}
		else
		{
			choice = false;
		}
		return choice;
	}
}
bool isBinaryOperators(char str){
		return str=='/' || str=='-' || str=='+' || str=='%' || str=='*';
}
bool isAssignmentOperators(char str){
	return str=='=';
}

bool isRelationalOperators(std::string str){
	return str=="==" || str=="<=" || str==">="  || str==">" || str=="<" || str=="!=";	
}
bool isQuotation(char str){
	return str=='"';
}
bool isDigit(char str)
{
	return str>='0' && str<='9';
}
bool isPartOfRelationOperator(char c){
	return c=='!' || c=='>' || c=='<' || c=='=';
}
bool isParanthesis(char str)
{
		return str=='(' || str==')' || str=='[' || str==']' || str=='{' || str=='}';
}
bool isTerminator(char s)
{
	return s==';';
}


