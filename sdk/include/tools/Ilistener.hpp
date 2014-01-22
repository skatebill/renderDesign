/************************************************************************/
/*    ����������ģ����
	  ���ڹ۲���ģ��
	  ʹ��ģ�������ָ�����͵ļ�����									
	author by Ф�� @ 2013��11��3��2:37:42								*/
/************************************************************************/
#pragma once
#include<memory>
#include<list>
#include <algorithm>
#include <functional>
namespace xc{
	using namespace std;
	using namespace std::tr1;
	//���������������ģ����
	namespace listener{
		//ֻ����һ����������ģ��
		//ʹ�� regiester�� unregiester ��ע�ᣨ��ע�ᣩ������
		//����������ʹ�� shared_ptr����
		template<typename T>
		class ISingleContainer{
		public:
			//��ȡ������
			virtual shared_ptr<T> getListener()=0;
			//ע�������
			virtual void registerListener(shared_ptr<T> l)=0;
			//��ע�������
			virtual void unregister()=0;
		};

		//����������������
		//��Ҫ���ڹ۲���ģ��
		//Ĭ��ʹ��list��Ϊ�������� �����Զ�������
		template<typename T,typename strorage = list<shared_ptr<T>>>
		class IMultipulContainer{
		public:
			typedef std::function<void(shared_ptr<T>)> functype;
			//��ȡ��i��������
			virtual shared_ptr<T> getListenerAt(int idx)=0;
			//ע�������
			virtual void registerListener(shared_ptr<T> l)=0;
			//��ע�������
			virtual void unregister(shared_ptr<T> l)=0;
			//Ϊ���м�����ִ��ָ������
			void doFunc(functype f){
				for_each(beginListener(),endListener(),f);
			}
			//�����������������Ŀ�ʼλ��
			virtual typename strorage::iterator beginListener()=0;
			//�����������������Ľ���λ��
			virtual typename strorage::iterator endListener()=0;
		};
	}
}