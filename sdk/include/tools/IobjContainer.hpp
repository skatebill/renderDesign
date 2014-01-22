/************************************************************************/
/*    容器模板类
	  自由存储指定类型的内容
	  默认使用list来存储									
	author by 肖驰 @ 2013年11月3日2:37:42								*/
/************************************************************************/
#pragma once
#include<list>
#include<algorithm>
#include<functional>
namespace xc{
	class outOfRangeException:public std::exception{};
	class containerEmptyException:public std::exception{};
	using namespace std;
	template<typename T,typename CONTAINER=std::list<T>>
	class IobjContainer{
	public:
		//总数
		virtual unsigned int getObjNum()=0;
		//迭代器开始
		virtual  typename CONTAINER::iterator begin()=0;
		//迭代器结束
		virtual typename CONTAINER::iterator end()=0;
		//为所有内容执行指定函数
		void doFunc(function<void(T&)> fun){
			for_each(begin(),end(),fun);
		}
		//获取指定位置的内容
		virtual T getObjAt(unsigned int idx)=0;
		//添加内容
		virtual void addObj(T obj)=0;
		//消除内容
		virtual void removeObj(T obj)=0;
		//清空容器
		virtual void clearObjs()=0;

	};
}