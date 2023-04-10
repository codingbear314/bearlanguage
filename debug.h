#ifndef __debug_h_
#define __debug_h_
#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<map>
template<class t>
void print(std::deque<t> q,char btw=' ')
{
	for(auto i:q)
	std::cout<<i<<btw;
	std::cout<<std::endl;
}

template<class t>
void print(std::vector<t> q,char btw=' ')
{
	for(auto i:q)
	std::cout<<"\'"<<i<<"\'"<<btw;
	std::cout<<std::endl;
}

template<class a,class b>
void print(std::map<a,b> mp,char btw='\n')
{
	for(auto it=mp.begin();it!=mp.end();++it)
	{
        std::cout<<it->first<<" => "<<it->second<<btw;
    }
}
#endif
