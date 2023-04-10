//#define debugmode
#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <stdexcept>
#include <functional>
#include<Windows.h>
#include<time.h>
#include<conio.h>
using namespace std;

#include "codertree.h"
#include "CEval.h"
#include "router.h"

int main()
{
	//freopen("output.txt","w",stdout);
	
	clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();
    
	//std::ios_base::sync_with_stdio(false); 
	FILE* std=stdout;
	FILE* fp=fopen("inputtoc.txt","r");
	sassert(fp!=NULL,"file not opened");
	//freopen("outputtopy.txt","w",stdout);
	treenode code=compiletotree(fp);
	vector<treenode*> dfs;
	dfs.push_back(&code);
	sassert(code.choice==ROOT,"error making to tree");
	vector<DATA> dt;
	map<string,DATA> variables;
	code.resetrun();
	//code.print();
	while(!dfs.empty())
	{
		if(fopen("end.now","rb")!=NULL)
		{
			break;
		}
		treenode* now=dfs.back();
		now->added=true;
		if(now->remain())

		{
			for(int i=now->child.size()-1;i>=0;i--)
			{
				if(!now->child[i].added)
				{
					dfs.push_back(&now->child[i]);
				}
			}
		}
		else
		{
			treenode k=*dfs.back();
			treenode* pt=dfs.back();
			
			switch(k.choice)
			{

				case ROOT:
					dfs.pop_back();
					break;
				case END:
					dt.push_back(makedata(k.name));
					dfs.pop_back();
					break;
				case builtin_function:
					if(k.name=="make")
					{
						DATA dat=dt.back();
						dt.pop_back();
						DATA name=dt.back();
						dt.pop_back();
						variables.insert({name.datas,dat});
						variables[name.datas]=dat;
					}
					else if(k.name=="set")
					{
						DATA dat=dt.back();
						dt.pop_back();
						DATA name=dt.back();
						dt.pop_back();
						sassert(variables.find(name.datas)!=variables.end());
						variables[name.datas]=dat;
					}
					else if(k.name=="change")
					{
						DATA dat=dt.back();
						dt.pop_back();
						DATA name=dt.back();
						dt.pop_back();
						sassert(variables.find(name.datas)!=variables.end());
						variables[name.datas]=dat+variables[name.datas];
					}
					else if(k.name=="print")
					{
						#ifdef debugmode
						printf("print\n");
						#endif
						DATA dat=dt.back();
						dt.pop_back();
						cprintDATA(dat);
					}
					else if(k.name=="println")
					{
						#ifdef debugmode
						printf("println\n");
						#endif
						DATA dat=dt.back();
						dt.pop_back();
						cprintDATAl(dat);
					}
					else if(k.name=="eval")
					{
						DATA dat=dt.back();
						dt.pop_back();
						dt.push_back(eval(dat.datas,variables));
					}
					dfs.pop_back();
					break;
				case builtin_expression:
					if(k.name=="forever")
					{
						pt->resetrun();
					//	printf("reseted run\n");
					}
					if(k.name=="for")
					{
						pt->number++;
						if(!((double)(pt->number)>=to_double(eval(pt->iter,variables))))
						pt->resetrunex();
						else
						dfs.pop_back();
					//	printf("reseted run\n");
					}
					break;
			}
			now->runned=true;
		}
		
//		code.print();
//		printf("\n\n");
	}
	end_time = clock();
    
    // Calculate the elapsed time
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    // Print the elapsed time
    cout<<"\n\n\n"<<"--------------------\n"<<"Elapsed time: "<<elapsed_time<<"seconds\n";
	cout<<"press any key to continue";
	getch();
	return 0;
}
