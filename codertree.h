#ifndef codertree__v0316
#define codertree__v0316
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

inline constexpr auto DEFAULT=0;
inline constexpr auto ROOT=1;
inline constexpr auto builtin_function=2;
inline constexpr auto builtin_expression=3;
inline constexpr auto END=4;

class treenode
{
public:
	__int8 choice;
	string name;
	string iter;
	int number;
	vector<treenode> child;
	
	treenode* root;
	bool added;
	bool runned;
	void operator=(const treenode& other)
	{
		this->choice=other.choice;
		std::vector<treenode> v(other.child);
		this->child=v;
		this->name=other.name;
		this->root=other.root;
		this->added=other.added;
		return;
	}
	treenode(void)
	{
		this->choice=DEFAULT;
		this->name="";
		this->iter="";
		this->added=false;
		this->runned=false;
		root=NULL;
	}
	treenode(__int8 choice,string name,treenode* root=NULL)
	{
		this->name=name;
		this->choice=choice;
		this->root=root;
		this->added=false;
		this->runned=false;
		return;
	}
	treenode* addchild(__int8 type,string name)
	{
		treenode temp(type,name,this);
		child.push_back(temp);
		return &child.back();
	}
	void setiter(string name)
	{
		iter=name;
		return;
	}
	treenode* addchild(treenode rf)
	{
		child.push_back(rf);
		return &child.back();
	}
	void print(int co=0) const
	{
		std::cout<<"data:"<<name<<"\trunned:"<<(this->runned?"true":"false")<<"\titer: "<<iter<<std::endl;
		for(int i=0;i<child.size();i++)
		{
			for(int j=0;j<co;j++)std::cout<<"     ";
			std::cout<<i<<"-----";
			child[i].print(co+1);
			std::cout<<std::endl;
		}
	}
	void resetrun(void)
	{
		this->added=false;
		this->number=0;
		for(int i=0;i<child.size();i++)
			child[i].resetrun();
	}
	void resetrunex(void)
	{
		for(int i=0;i<child.size();i++)
			child[i].resetrun();
	}
	bool remain(void)
	{
		for(int i=0;i<child.size();i++)
		if(child[i].added==false)
		return true;
		return false;
	}
};
#endif 
