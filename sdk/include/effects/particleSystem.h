#pragma once
#include<vector>
#include<functional>
#include <algorithm>
namespace effect{


	template<typename particleStruct>
	class IParticleSystemContrller{
	public:
		//! 添加一个粒子
		virtual void addParticle(particleStruct p)=0;
		//! 获取粒子总数
		virtual unsigned int getParticleNums()=0;
	};

	template<typename particleStruct,typename IController=IParticleSystemContrller<particleStruct>>
	class particleSystem:public IController{
		struct particleData{
			particleStruct ps;
			bool isAlive;
		};
	public:
		std::vector<particleData> m_Particles;
		std::vector<int> m_DeadParticles;
		std::tr1::function<bool(particleStruct&)> m_UpdateFunc;
		std::tr1::function<void(IController*)> m_RuleFunc;
		unsigned int m_CurrentParticles;


		particleSystem():m_CurrentParticles(0){

		}
		void update(){
			m_RuleFunc(this);
			for(auto p = m_Particles.begin();p != m_Particles.end(); p++){
				if( p->isAlive && !m_UpdateFunc(p->ps) ){
					p->isAlive=false;
					m_CurrentParticles--;
				}
			}
		}
		//! 添加一个粒子
		virtual void addParticle(particleStruct p){
			auto m = std::find_if(m_Particles.begin(),m_Particles.end(),[](particleData& pd){return pd.isAlive==false;});
			if(m != m_Particles.end())
			{
				m->ps=p;
				m->isAlive=true;
			}else
			{
				particleData np;
				np.isAlive=true;
				np.ps=p;
				m_Particles.push_back(np);
			}
			m_CurrentParticles++;
		}
		//! 获取粒子总数
		virtual unsigned int getParticleNums(){
			return m_CurrentParticles;
		}
	};
}