/************************************************************************/
/*    监听器工具模板类
	  用于观察者模型
	  使用模板来填充指定类型的监听器									
	author by 肖驰 @ 2013年11月3日2:37:42								*/
/************************************************************************/
#pragma once
#include"Ilistener.hpp"
namespace xc{
	//用来保存监听器的模板类
	namespace listener{
		//只保存一个监听器的模板
		//使用 regiester和 unregiester 来注册（反注册）监听器
		//监听器必须使用 shared_ptr保存
		template<typename T>
		class singleContainer:public ISingleContainer<T>{
		private:
			shared_ptr<T> m_Listener;
		public:
			//获取监听器
			inline shared_ptr<T> getListener(){
				return m_Listener;
			}
			//注册监听器
			void registerListener(shared_ptr<T> l){
				m_Listener = l;
			}
			//反注册监听器
			void unregister(){
				m_Listener = 0;
			}
		};

		//有许多监听器的容器
		//主要用于观察者模型
		//默认使用list作为保存类型 可以自定义容器
		template<typename T,typename strorage = list<shared_ptr<T>>>
		class multipulContainer:public IMultipulContainer<T,strorage>{
		private:
			strorage m_Listener;
		public:
			typedef std::function<void(shared_ptr<T>)> functype;
			//获取第i个监听器
			shared_ptr<T> getListenerAt(int idx){
				if(m_Listener.size() == 0)
					throw out_of_range("no elements");;
				auto b = beginListener();
				auto e = endListener();
				for (int i=0;i<idx;++i)
				{
					b++;
					if(b == e){
						throw out_of_range("out of range");
					}
				}
				return *b;
			}
			//注册监听器
			void registerListener(shared_ptr<T> l){
				m_Listener.push_back(l);
			}
			//反注册监听器
			void unregister(shared_ptr<T> l){
				auto b = beginListener();
				auto p = b;
				auto e = endListener();
				while(b!=e){
					if(*b==l){
						auto p = b;
						p++;
						m_Listener.erase(b);
						b=p;
						continue;
					}
					b++;
				}
			}
			//为所有监听器执行指定命令
			void doFunc(functype f){
				for_each(beginListener(),endListener(),f);
			}
			//监听器容器迭代器的开始位置
			inline typename strorage::iterator beginListener(){
				return m_Listener.begin();
			}
			//监听器容器迭代器的结束位置
			inline typename strorage::iterator endListener(){
				return  m_Listener.end();
			}
		};
	}
}