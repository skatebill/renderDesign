#pragma once
#include<tools/MyTypes.h>
#include<list>
#include <random>
#include"Rasterize.h"
#include<functional>
namespace water{
	using namespace xc;
	using namespace xc::WaterRasterize;
	template<int MAXPARTICLENUMS = 3000>
	class waterParticle{
	public:
		struct Particle{
			waterPoint p;
		};
		enum {maxParticles = MAXPARTICLENUMS};
		std::uniform_real_distribution<> randomer;
		std::mt19937 gen;
		std::list<Particle> m_Particles;
		shared_ptr<waterEnvirMent<waterPoint>> m_EnvSource;
		std::tr1::function<void()> mRenderFunc;
		double width;
		double height;
		double left;
		double top;
		waterParticle(shared_ptr<waterEnvirMent<waterPoint>> envSource):m_EnvSource(envSource)
		{
			 std::random_device rd;
			gen = std::mt19937(rd());
			width = m_EnvSource->getArea().getWidth();
			height = m_EnvSource->getArea().getHeight();
			left = m_EnvSource->getArea().UpperLeftCorner.X;
			top = m_EnvSource->getArea().UpperLeftCorner.Y;
		}
		waterPoint getRandomPoint(){
			waterPoint p;
			do 
			{
				p.X = randomer(gen) * width + left; 
				p.Y = randomer(gen) * height + top;
			} while (!m_EnvSource->findPosInfo(&p));
			
			return p;
		}
		void update(double dt){
			while(m_Particles.size()<MAXPARTICLENUMS)
			{
				Particle c;
				c.p=getRandomPoint();
				m_Particles.push_back(c);

			}
			std::list<std::list<Particle>::iterator> eraseList;
			for (auto ite = m_Particles.begin();ite != m_Particles.end();++ite)
			{
				if(m_EnvSource->findPosInfo(&ite->p))
				{
					ite->p = ite->p + ite->p.waterDir * dt;
				}else
				{
					eraseList.push_back(ite);
				}
			}
			for (auto ite = eraseList.begin();ite != eraseList.end();++ite){
				m_Particles.erase(*ite);
			}
		}
	};
}