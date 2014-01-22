/************************************************************************/
/*    ����ģ����
	  ���ɴ洢ָ�����͵�����
	  Ĭ��ʹ��list���洢									
	author by Ф�� @ 2013��11��3��2:37:42								*/
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
		//����
		virtual unsigned int getObjNum()=0;
		//��������ʼ
		virtual  typename CONTAINER::iterator begin()=0;
		//����������
		virtual typename CONTAINER::iterator end()=0;
		//Ϊ��������ִ��ָ������
		void doFunc(function<void(T&)> fun){
			for_each(begin(),end(),fun);
		}
		//��ȡָ��λ�õ�����
		virtual T getObjAt(unsigned int idx)=0;
		//�������
		virtual void addObj(T obj)=0;
		//��������
		virtual void removeObj(T obj)=0;
		//�������
		virtual void clearObjs()=0;

	};
}