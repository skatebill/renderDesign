//#pragma once
#include<tools/MyTypes.h>
#include<tools/CobjContainer.hpp>
#include<iostream>
namespace xc{

	class rule{
	private:
		string mName;
	public:
		rule(string name):mName(name){
		}
		virtual void run()=0;
		virtual const string& getName(){
			return mName;
		}
	};
	typedef long IDCard;
	class universe:public rule{
	public:
		IDCard mIdAllocator;
		CobjContainer<shared_ptr<rule>> mRuleList;
		universe():rule("universe"){
			mIdAllocator = 0;
		}
		void addRule(shared_ptr<rule> r,EnumPos pos = back,string id="null"){
			//Ìí¼ÓÄÚÈÝ
			switch(pos)
			{
			case after:
				{
					CobjContainer<shared_ptr<rule>>::cIte ite=std::find_if(mRuleList.m_container.begin(),mRuleList.m_container.end(),[&id](shared_ptr<rule>& r2)->bool{return r2->getName()==id;});
					if(ite != mRuleList.m_container.end()){
						mRuleList.m_container.insert(++ite,1,r);
					}
				}
				break;
			case back:
				mRuleList.m_container.push_back(r);
				break;
			case front:
				mRuleList.m_container.push_front(r);
				break;
			case center:
				mRuleList.m_container.insert(--mRuleList.end(),1,r);
				break;
			}
		}
		void run(){
			mRuleList.doFunc([](shared_ptr<rule>& r){r->run();});
		}

		IDCard createNewObject(){
			return mIdAllocator++;
		}
	};
	class outputUniverse:public rule{
	private:
		universe* mUniverse;
		std::function<void()> mRunFunc;
	public:
		outputUniverse(universe* u):rule("outputUniverse"){
			mUniverse=u;
			mRunFunc = [this]()
			{
				mUniverse->mRuleList.doFunc([](shared_ptr<rule>& r){
					std::cout<<r->getName().c_str()<<std::endl;
				});
				mRunFunc = nullptr;
			};
		}
		~outputUniverse(){
			std::cout<<"end of outputUniverse"<<std::endl;
		}
		void run(){
			if(mRunFunc != nullptr){
				mRunFunc();
			}
		}
	};
}

void main(){
	using namespace xc;
	universe u;
	shared_ptr<outputUniverse> ou = shared_ptr<outputUniverse>(new outputUniverse(&u));
	u.addRule(ou);
	u.run();
}