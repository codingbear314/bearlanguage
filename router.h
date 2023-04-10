#ifndef maketree_h
#define maketree_h

#include<string>
using namespace std;

#include "codertree.h"
#include "CEval.h"
#include "supported.h"
#include "debug.h"

vector<string> divide(string str,char k)
{
	string a;
	bool cdivide=true;
	vector<string> result;
	for(int i=0;i<=str.size();i++)
	{
		if(str[i]=='\"')
		cdivide=!cdivide;
		if((str[i]==k||i==str.size())&&cdivide)
		{
			if(a!="")
			{
				result.push_back(a);
				a="";
			}
			continue;
		}
		a.push_back(str[i]);
	}
	return result;
}

treenode processbuiltinfunction(string code)
{
	#ifdef debugmode
	cout<<"processing ("<<code<<")"<<"\n\n";
	#endif
	treenode result;
	vector<string> divided=divide(code,' ');
	string command=divided[0];
	#ifdef debugmode
	print(divided);
	cout<<endl;
	#endif
	if(command=="make")
	{
		result.name="make";
		result.choice=builtin_function;
		sassert(divided[1]=="variable","makeing anything other then variable is not supported in 3.16 version");
		result.addchild(END,divided[2]);
		sassert(divided[3]=="as","reseting needed in a new variable!");
		result.addchild(builtin_function,"eval")->addchild(END,divided[4]);
	}
	else if(divided[0]=="set")
	{
		result.name="set";
		result.choice=builtin_function;
		sassert(divided[2]=="as");
		result.addchild(END,divided[1]);
		result.addchild(builtin_function,"eval")->addchild(END,divided[3]);
	}
	else if(command=="change")
	{
		sassert(divided[2]=="by");
		result.name="change";
		result.choice=builtin_function;
		result.addchild(END,divided[1]);
		result.addchild(builtin_function,"eval")->addchild(END,divided[3]);
	}
	else if(command=="print")
	{
		result.name="print";
		result.choice=builtin_function;
		result.addchild(builtin_function,"eval")->addchild(END,divided[1]);
	}
	else if(command=="println")
	{
		result.name="println";
		result.choice=builtin_function;
		result.addchild(builtin_function,"eval")->addchild(END,divided[1]);
	}
	else if(command=="for")
	{
		result.name="for";
		result.choice=builtin_expression;
		result./*addchild(builtin_function,"eval")->*/setiter(divided[1]);
	}
	else if(command=="while")
	{
		result.name="while";
		result.choice=builtin_expression;
		result.setiter(divided[1]);
	}
	else if(command=="forever")
	{
		result.name="forever";
		result.choice=builtin_expression;
	}
	else if(command=="if")
	{
		result.name="if";
		result.choice=builtin_expression;
		result.setiter(divided[1]);
	}
	#ifdef debugmode
	result.print();
	#endif
	return result;
}

treenode compiletotree(FILE* fp)
{
	treenode result(ROOT,"ROOT");
	treenode* rt=&result;
	treenode* last=&result;
	string now;
	int c;
	bool continuewithoutendl=false;
	while(true)
	{
		c=fgetc(fp);
		if(c=='\t')
		continue;
		if(continuewithoutendl&&c=='\n')
		{
			continue;
			now="";
		}
		if(c=='{')
		{
			rt=last;
			#ifdef debugmode
			cout<<"redirecting to "<<rt->name<<endl;
			#endif
			continuewithoutendl=true;
			continue;
		}
		else if(c=='}')
		{
			rt=rt->root;
			#ifdef debugmode
			cout<<"redirecting to "<<rt->name<<endl;
			#endif
			now="";
			continuewithoutendl=true;
			continue;
		}
		else
		continuewithoutendl=false;
		if(c==';'||c=='\n'||c==EOF)
		{
			if((c==EOF)&&(now==""))
			break;
			treenode im=processbuiltinfunction(now);
			im.root=rt;
			rt->addchild(im);
			last=&(rt->child.back());
			#ifdef debugmode
			cout<<"router:set rt to"<<last->name<<endl;
			#endif
			now="";
			if(c==EOF)
			break;
			continue;
		}
		now.push_back(c);
		#ifdef debugmode
		printf("router::%d\n",c);
		#endif
	}
	#ifdef debugmode
	printf("router printing routed tree:\n");
	result.print();
	#endif
	return result;
}

#endif
