/************************************************************************/
/*    监听器工具模板类
	  用于观察者模型
	  使用模板来填充指定类型的监听器									
	author by 肖驰 @ 2013年11月3日2:37:42								*/
/************************************************************************/
#pragma once
#include<memory>
#include<list>
#include <algorithm>
#include <functional>
namespace xc{
	using namespace std;
	using namespace std::tr1;
	//用来保存监听器的模板类
	namespace listener{
		//只保存一个监听器的模板
		//使用 regiester和 unregiester 来注册（反注册）监听器
		//监听器必须使用 shared_ptr保存
		template<typename T>
		class ISingleContainer{
		public:
			//获取监听器
			virtual shared_ptr<T> getListener()=0;
			//注册监听器
			virtual void registerListener(shared_ptr<T> l)=0;
			//反注册监听器
			virtual void unregister()=0;
		};

		//有许多监听器的容器
		//主要用于观察者模型
		//默认使用list作为保存类型 可以自定义容器
		template<typename T,typename strorage = list<shared_ptr<T>>>
		class IMultipulContainer{
		public:
			typedef std::function<void(shared_ptr<T>)> functype;
			//获取第i个监听器
			virtual shared_ptr<T> getListenerAt(int idx)=0;
			//注册监听器
			virtual void registerListener(shared_ptr<T> l)=0;
			//反注册监听器
			virtual void unregister(shared_ptr<T> l)=0;
			//为所有监听器执行指定命令
			void doFunc(functype f){
				for_each(beginListener(),endListener(),f);
			}
			//监听器容器迭代器的开始位置
			virtual typename strorage::iterator beginListener()=0;
			//监听器容器迭代器的结束位置
			virtual typename strorage::iterator endListener()=0;
		};
	}
}