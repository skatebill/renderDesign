/************************************************************************/
/*    容器模板类
	  自由存储指定类型的内容
	  默认使用list来存储									
	author by 肖驰 @ 2013年11月3日2:37:42								*/
/************************************************************************/
#pragma once
#include"IobjContainer.hpp"
namespace xc{
	template<typename C,typename T,typename CONTAINER=std::list<T>>
	class CobjContainer:public C{
	private:
		CONTAINER m_container;
	public:
		//总数
		unsigned int getObjNum(){
			return m_container.size();
		}
		//迭代器开始
		typename CONTAINER::iterator begin(){
			return m_container.begin();
		}
		//迭代器结束
		typename CONTAINER::iterator end(){
			return m_container.end();
		}
		//为所有内容执行指定函数
		void doFunc(function<void(T&)> fun){
			for_each(begin(),end(),fun);
		}
		//获取指定位置的内容
		T getObjAt(unsigned int idx){
			if(m_container.size()==0){
				throw containerEmptyException();
			}
			auto b = this->begin();
			auto e = this->end();
			for(unsigned int i =0;i<idx;++i){
				b++;
				if(b == e){
					throw outOfRangeException();
				}
			}
			return *b;
		}
		//添加内容
		void addObj(T obj){
			m_container.push_back(obj);
		}
		//消除内容
		void removeObj(T obj){
			if(m_container.size()==0){
				throw containerEmptyException();
			}
			auto b = this->begin();
			auto e = this->end();
			while(b!=e){
				if(*b == obj){
					auto n = b;
					n++;
					m_container.erase(b);
					b=n;
				}else{
					b++;
				}
			}
		}
		//清空容器
		void clearObjs(){
			m_container.clear();
		}

	};
}