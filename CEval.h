#ifndef stringeval
#define stringeval

#include<string>
#include<map>
#include<cstdio>
#include<deque>
#include<cassert>
#include<stdexcept>
#include<iostream>
#include "supported.h"

inline bool isnum(char n)
{
	return (n>='0')&&(n<='9');
}

inline bool issmallletter(char n)
{
	return (n>='a')&&(n<='z');
}

inline bool iscapitalletter(char n)
{
	return (n>='A')&&(n<='Z');
}

inline bool isoperator(char n)
{
	return (n=='+')||(n=='-')||(n=='*')||(n=='/');
}

inline bool isalnum(char n)
{
	return isnum(n)||issmallletter(n)||iscapitalletter(n);
}

inline bool isal(char n)
{
	return iscapitalletter(n)||issmallletter(n);
}

inline constexpr auto DATATYPE_double=1;
inline constexpr auto DATATYPE_string=2;
inline constexpr auto DATATYPE_default=0;
inline constexpr auto DATATYPE_variablename=3;

//#define debugmode
#define cleanprint

using namespace std;

string tostringd(double dt)
{
	string sr=to_string(dt);
	sr.erase(sr.find_last_not_of('0') + 1, std::string::npos);
	if (sr.back() == '.')
	    sr.pop_back();
	return sr;
}

class DATA
{
public:
	__int8 type;
	__int8 typenow;
	double datad;
	string datas;
	string tmp;
	bool returned;
	void reset()
	{
		type=DATATYPE_default;
		typenow=DATATYPE_default;
		datad=0;
		datas="";
		tmp="";
		returned=false;
	}
	DATA()
	{
		this->reset();
	}
	DATA(const DATA& dt)
	{
		this->type=dt.type;
		this->typenow=dt.typenow;
		this->datad=dt.datad;
		this->datas=dt.datas;
		this->tmp=dt.tmp;
		this->returned=dt.returned;
	}
	DATA operator+(const DATA& d)
	{
		if(this->type==DATATYPE_double&&d.type==DATATYPE_double)
		{
			DATA returner;
			returner.datad=this->datad+d.datad;
			returner.type=returner.typenow=DATATYPE_double;
			return returner;
		}
		else if(this->type==DATATYPE_string&&d.type==DATATYPE_string)
		{
			DATA returner;
			returner.datas=this->datas+d.datas;
			returner.type=returner.typenow=DATATYPE_string;
			return returner;
		}
		else if(this->type==DATATYPE_string&&d.type==DATATYPE_double)
		{
			DATA returner;
			returner.datas=this->datas+tostringd(d.datad);
			returner.type=returner.typenow=DATATYPE_string;
			return returner;
		}
		else if(d.type==DATATYPE_string&&this->type==DATATYPE_double)
		{
			DATA returner;
			returner.datas=tostringd(this->datad)+d.datas;
			returner.type=returner.typenow=DATATYPE_string;
			return returner;
		}
		DATA returnervoid;
		return returnervoid;
	}
	DATA operator-(DATA d)
	{
		assert(this->type==d.type);
		if(this->type==DATATYPE_double)
		{
			DATA returner;
			returner.datad=this->datad-d.datad;
			returner.type=returner.typenow=DATATYPE_double;
			return returner;
		}
		else if(this->type==DATATYPE_string)
		{
			throw runtime_error("- in string is not supported.");
		}
		DATA returnervoid;
		return returnervoid;
	}
	string repeatstring(string a,int times)
	{
		string returner="";
		for(int i=0;i<times;i++)
		returner+=a;
		return returner;
	}
	DATA operator*(const DATA& d)
	{
	
		if(this->type==DATATYPE_double&&d.type==DATATYPE_double)
		{
			DATA returner;
			returner.datad=this->datad*d.datad;
			returner.type=returner.typenow=DATATYPE_double;
			return returner;
		}
		else if(this->type==DATATYPE_string&&d.type==DATATYPE_double)
		{
			DATA returner;
			returner.datas=repeatstring(this->datas,d.datad);
			returner.type=returner.typenow=DATATYPE_string;
			return returner;
		}
		else if(this->type==DATATYPE_string)
		{
			throw runtime_error("* in string is not supported.");
		}
		DATA returnervoid;
		return returnervoid;
	}
	DATA operator/(const DATA& d)
	{
		assert(this->type==d.type);
		if(this->type==DATATYPE_double)
		{
			DATA returner;
			returner.datad=this->datad/d.datad;
			returner.type=returner.typenow=DATATYPE_double;
			return returner;
		}
		else if(this->type==DATATYPE_string)
		{
			throw runtime_error("/ in string is not supported.");
		}
		DATA returnervoid;
		return returnervoid;
	}
};
DATA makedata(double d)
{
	DATA rtr;
	rtr.reset();
	rtr.datad=d;
	rtr.type=rtr.typenow=DATATYPE_double;
	return rtr;
}
DATA makedata(string d)
{
	DATA rtr;
	rtr.reset();
	rtr.datas=d;
	rtr.type=rtr.typenow=DATATYPE_string;
	return rtr;
}
double to_double(DATA dat)
{
	sassert(dat.type==DATATYPE_double);
	return dat.datad;
}
void printDATA(DATA dat)
{	
#ifndef cleanprint
	cout<<"datad:"<<dat.datad<<"\tdatas:"<<dat.datas<<"\ttype:"<<(int)dat.type<<"\ttypenow:"<<(int)dat.typenow<<"\treturned:"<<(dat.returned?"true":"false")<<endl;
#else	
	switch(dat.type)
	{
		case DATATYPE_double:
			cout<<dat.datad<<" ";
			break;
		case DATATYPE_string:
			cout<<dat.datas<<" ";
			break;
	}
#endif
}
void cprintDATA(DATA dat)
{
	if(dat.type==DATATYPE_double)
	{	
		string sr=to_string(dat.datad);
		sr.erase(sr.find_last_not_of('0') + 1, std::string::npos);
	    if (sr.back() == '.') {
	        sr.pop_back();
	    }
	    cout<<sr;
	}
	else if(dat.type==DATATYPE_string)
	cout<<dat.datas;
}


void cprintDATAl(DATA dat)
{
	if(dat.type==DATATYPE_double)
	{	
		string sr=to_string(dat.datad);
		sr.erase(sr.find_last_not_of('0') + 1, std::string::npos);
	    if (sr.back() == '.') {
	        sr.pop_back();
	    }
	    cout<<sr;
	}
	else if(dat.type==DATATYPE_string)
	cout<<dat.datas;
	cout<<"\n";
}
void clear(DATA& dat)
{
	switch(dat.type)
	{
		case DATATYPE_double:
			dat.datas="";
			break;
		case DATATYPE_string:
			dat.datad=0;
			break;
	}
}
void print(std::deque<DATA> q,char btw=' ')
{
	for(auto i:q)
	printDATA(i);
	std::cout<<std::endl;
}
void castintoneededDATA(DATA& data,map<string,DATA> variables)
{
	//if(data.type==data.typenow)
	//return;
	if(data.returned)
	return;
	if(data.type==DATATYPE_default)
	throw runtime_error("datatype not even sure. evalerror");
	if(data.type==DATATYPE_double)
	{
		data.datad=stod(data.tmp);
		data.tmp="";
		data.typenow=DATATYPE_double;
	}
	if(data.type==DATATYPE_string)
	{
		#ifdef debugmode
		cout<<"data.tmp:"<<data.tmp<<endl;
		#endif
		assert(data.tmp.length()!=0);
		assert(data.tmp[0]=='\"');
		assert(data.tmp[data.tmp.length()-1]=='\"');
		data.datas="";
		for(int i=1;i<data.tmp.length()-1;i++)
		data.datas.push_back(data.tmp[i]);
		data.tmp="";
		data.typenow=DATATYPE_string;
	}
	if(data.type==DATATYPE_variablename)
	{
		if(data.tmp=="scanfloat")
		{
			data.typenow=data.type=DATATYPE_double;
			double im;
			scanf("%lf",&im);
			data.datad=im;
		}
		else if(data.tmp=="scanstring")
		{
			data.typenow=data.type=DATATYPE_string;
			cin>>data.datas;
		}
		else if(variables.find(data.tmp)==variables.end())
		throw runtime_error("error! variable "+data.tmp+" does not exist!\n\a");
		else
		{
			DATA vari=variables[data.tmp];
			if(vari.type==DATATYPE_string)
			{
				data.typenow=data.type=DATATYPE_string;
				data.datas=vari.datas;
			}
			else if(vari.type==DATATYPE_double)
			{
				data.typenow=data.type=DATATYPE_double;
				data.datad=vari.datad;
			}
		}
	}
}

DATA eval(string expression,map<string,DATA> variables)
{
	#ifdef debugmode
	cout<<"eval called with\t"<<expression<<endl;
	#endif
	deque<DATA> operands;
	deque<char> operators;
	DATA now;
	now.reset();
	bool inside;
	bool lookinginsidestring=false;
	for(int iter=0;iter<expression.length();iter++)
	{
		char t=expression[iter];
		inside=false;
		if(t=='\"')
		lookinginsidestring=!lookinginsidestring;
		if(t=='(')
		{
			int guarho=1;
			string expressioninside;
			iter++;
			while(guarho!=0)
			{
				if(iter>=expression.length())
				throw runtime_error("not closed!");
				expressioninside.push_back(expression[iter]);
				if(expression[iter]==')')
				{
					guarho--;
				}
				else if(expression[iter]=='(')
				{	
					guarho++;
				}
				iter++;
			}
			expressioninside.pop_back();
			now=eval(expressioninside,variables);
			#ifdef debugmode
			cout<<"inside ��ȣ\t";
			printDATA(now);
			cout<<endl;
			#endif
			char t=expression[iter];
			inside=true;
		}
		if(!isoperator(t)||lookinginsidestring)
		{
//			assert(now.typenow==DATATYPE_default);
			#ifdef debugmode
			cout<<"pushing "<<t;
			cout<<"isoperator:"<< (int)isoperator(t) <<endl;
			#endif
			now.tmp.push_back(t);
			
			if((t=='\"')/*&&now.type==DATATYPE_default*/)
			now.type=DATATYPE_string;
			else if(t=='\"')
			throw runtime_error("string blended in with double.");
			
			if(now.type==DATATYPE_default&&now.typenow==DATATYPE_default&&!isnum(t)&&!isoperator(t))
			now.type=now.typenow=DATATYPE_variablename;
			
			if(isnum(t))
			now.typenow=DATATYPE_double;
		}
		if((isoperator(t)&&!lookinginsidestring)||iter>=expression.length()-1)
		{
			if(now.type==DATATYPE_default)
			now.type=DATATYPE_double;
			if(!inside)
			castintoneededDATA(now,variables); 
			if(!operators.empty()&&!operands.empty())
			{
				char lastoperator=operators.back();
				if(lastoperator=='*')
				{
					DATA last=operands.back();
					operands.pop_back();
					operators.pop_back();
					operands.push_back(last*now);
				}
				else if(lastoperator=='/')
				{
					DATA last=operands.back();
					operands.pop_back();
					operators.pop_back();
					operands.push_back(last/now);
				}
				else
					operands.push_back(now);
			}
			else
			operands.push_back(now);
			if(!(iter==expression.length()-1&&now.tmp!="")&&t!='\0'&&isoperator(t))
			operators.push_back(t);
			now.reset();
		}
	}
	#ifdef debugmode
	print(operands);
	#endif
	while(operands.size()>1)//���������� +,- ó��
	{
		if(operators.empty())
		throw std::runtime_error("error! your expression is weird\n\a");
		
		
		DATA a=operands.front();
		operands.pop_front();
		DATA b=operands.front();
		operands.pop_front();
		char c=operators.front();
		operators.pop_front();
		switch(c)
		{
			case '+':
				operands.push_front(a+b);
				break;
			case '-':
				operands.push_front(a-b);
				break;
			default:
				throw std::runtime_error("error! I don\'t know why this happend.\n\a");
		}
	}
	#ifdef debugmode
	printf("returning data:");
	printDATA(operands.back());
	cout<<endl;
	#endif
	DATA rtr=operands.back();
	rtr.returned=true;
	clear(rtr);
	return rtr;
}

#endif
