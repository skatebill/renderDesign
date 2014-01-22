/************************************************************************/
/*    ����������ģ����
	  ���ڹ۲���ģ��
	  ʹ��ģ�������ָ�����͵ļ�����									
	author by Ф�� @ 2013��11��3��2:37:42								*/
/************************************************************************/
#pragma once
#include"Ilistener.hpp"
namespace xc{
	//���������������ģ����
	namespace listener{
		//ֻ����һ����������ģ��
		//ʹ�� regiester�� unregiester ��ע�ᣨ��ע�ᣩ������
		//����������ʹ�� shared_ptr����
		template<typename T>
		class singleContainer:public ISingleContainer<T>{
		private:
			shared_ptr<T> m_Listener;
		public:
			//��ȡ������
			inline shared_ptr<T> getListener(){
				return m_Listener;
			}
			//ע�������
			void registerListener(shared_ptr<T> l){
				m_Listener = l;
			}
			//��ע�������
			void unregister(){
				m_Listener = 0;
			}
		};

		//����������������
		//��Ҫ���ڹ۲���ģ��
		//Ĭ��ʹ��list��Ϊ�������� �����Զ�������
		template<typename T,typename strorage = list<shared_ptr<T>>>
		class multipulContainer:public IMultipulContainer<T,strorage>{
		private:
			strorage m_Listener;
		public:
			typedef std::function<void(shared_ptr<T>)> functype;
			//��ȡ��i��������
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
			//ע�������
			void registerListener(shared_ptr<T> l){
				m_Listener.push_back(l);
			}
			//��ע�������
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
			//Ϊ���м�����ִ��ָ������
			void doFunc(functype f){
				for_each(beginListener(),endListener(),f);
			}
			//�����������������Ŀ�ʼλ��
			inline typename strorage::iterator beginListener(){
				return m_Listener.begin();
			}
			//�����������������Ľ���λ��
			inline typename strorage::iterator endListener(){
				return  m_Listener.end();
			}
		};
	}
}