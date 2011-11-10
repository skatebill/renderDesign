/************************************************************************/
/*    ����ģ����
	  ���ɴ洢ָ�����͵�����
	  Ĭ��ʹ��list���洢									
	author by Ф�� @ 2013��11��3��2:37:42								*/
/************************************************************************/
#pragma once
#include"IobjContainer.hpp"
namespace xc{
	enum EnumPos{
		front,
		back,
		after,
		center
	};
	class cnull{

	};
	template<typename T,typename C=cnull,typename CONTAINER=std::list<T>>
	class CobjContainer:public C{
	public:
		typedef typename CONTAINER::iterator cIte;
		CONTAINER m_container;
		//����
		unsigned int getObjNum(){
			return m_container.size();
		}
		//��������ʼ
		typename CONTAINER::iterator begin(){
			return m_container.begin();
		}
		//����������
		typename CONTAINER::iterator end(){
			return m_container.end();
		}
		//Ϊ��������ִ��ָ������
		void doFunc(function<void(T&)> fun){
			for_each(begin(),end(),fun);
		}
		//��ȡָ��λ�õ�����
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
		//�������
		void addObj(T obj){
			m_container.push_back(obj);
		}
		//��������
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
		//�������
		void clearObjs(){
			m_container.clear();
		}

	};
}