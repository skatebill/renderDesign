#pragma once
#include<tools/MyTypes.h>
#include<map>
#include<vector>
#include<functional>
#include<fstream>
#include <algorithm>
namespace xc{
	namespace WaterRasterize{

		class waterPoint:public vector2dd{
		public:
			//! 水流方向
			vector2dd waterDir;

			waterPoint operator + (const waterPoint& o){
				waterPoint p;
				p.X = X + o.X;
				p.Y = Y + o.Y; 
				p.waterDir = waterDir + o.waterDir;
				return p;
			}
			waterPoint operator + (const vector2dd& o){
				waterPoint p;
				p.X = X + o.X;
				p.Y = Y + o.Y; 
				p.waterDir = waterDir;
				return p;
			}
			waterPoint operator - (const waterPoint& o){
				waterPoint p;
				p.X = X - o.X;
				p.Y = Y - o.Y; 
				p.waterDir = waterDir - o.waterDir;
				return p;
			}
			waterPoint operator * (const double& o){
				waterPoint p;
				p.X = X * o;
				p.Y = Y * o; 
				p.waterDir = waterDir * o;
				return p;
			}
			waterPoint operator / (const double& o){
				return this->operator*(1/o);
			}
		};
		
		template<typename point2d>
		class waterEnvirMent{
		public:

			virtual bool findPosInfo(point2d* p)=0;

			virtual rectd getArea()=0;
		};

		template<typename point2d>
		class Area{
		public:
			std::vector<point2d> m_AreaPointList;
			shared_ptr<Area> m_subAreas[4];
			class _Compare{
			public:
				point2d p;
				double length;

				bool operator < (const _Compare& o ){
					return length < o.length;
				}
			};
			bool getPointValue(point2d* p){
				if(m_AreaPointList.size()<=0){
					return false;
				}else{
					std::vector<_Compare> plist;
					for(auto ite = m_AreaPointList.begin();ite != m_AreaPointList.end();++ite){
						_Compare c;
						c.p = *ite;
						c.length = (*ite - *p).getLengthSQ();
						plist.push_back(c);
					}
					std::sort(plist.begin(),plist.end());
					if(plist[0].length > 2500){
						return false;
					}
					p->waterDir = plist[0].p.waterDir;
					return true;
				}
			}
		};

		template<typename point2d,int DIVIDE_NUM = 100,bool REGULAR = true>
		class RasterizeWorld2D:public waterEnvirMent<point2d>{
		public:
			rectd m_BoundBox;
			double m_DivideDeltaX;
			double m_DivideDeltaY;
			std::map<vector2di,Area<point2d>>  m_AreaMap;

			void setBoundBox(rectd box){
				if(REGULAR){
					double interval = box.getWidth() > box.getHeight() ? box.getWidth() : box.getHeight();
					m_DivideDeltaX = interval/DIVIDE_NUM;
					m_DivideDeltaY = interval/DIVIDE_NUM;

				}else{
					m_DivideDeltaX = box.getWidth()/DIVIDE_NUM;
					m_DivideDeltaY = box.getHeight()/DIVIDE_NUM;
				}
				m_BoundBox = box;
			}
			vector2di findKey(point2d p){
				vector2di key;
				key.X = int((p.X-m_BoundBox.UpperLeftCorner.X)/m_DivideDeltaX);
				key.Y = int((p.Y-m_BoundBox.UpperLeftCorner.Y)/m_DivideDeltaY);
				return key;
			}
			void addPoint(point2d p){
				vector2di key=findKey(p);
				m_AreaMap[key].m_AreaPointList.push_back(p);
			}
			bool findPosInfo(point2d* p){
				vector2di key=findKey(*p);
				return m_AreaMap[key].getPointValue(p);

			}
			virtual rectd getArea(){
				return m_BoundBox;
			}

		};
		shared_ptr<waterEnvirMent<waterPoint>> createWorld(std::string fileName){
			using namespace xc::WaterRasterize;
			RasterizeWorld2D<waterPoint>* r = new RasterizeWorld2D<waterPoint>;
			std::ifstream inFile(fileName);
			if(!inFile.is_open()){
				return nullptr;
			}
			unsigned long nums;
			inFile>>nums;
			std::list<waterPoint> pList;
			double maxx,maxy,minx,miny;
			bool initial=true;
			nums = nums;
			for(unsigned int i=0;i<nums;++i){
				double x,y;
				double vx,vy;
				inFile>>x>>y>>vx>>vy;
				waterPoint p;
				p.X=x;
				p.Y=y;
				p.waterDir.X=vx;
				p.waterDir.Y=vy;
				pList.push_back(p);
				if(initial){
					initial = false;
					maxx = x;
					minx = x;
					maxy = y;
					miny = y;
				}else{
					maxx = std::max(maxx,x);
					minx = std::min(minx,x);
					maxy = std::max(maxy,y);
					miny = std::min(miny,y);
				}
			}
			r->setBoundBox(xc::rectd(minx,miny,maxx,maxy));
			for(auto ite = pList.begin();ite!= pList.end();++ite){
				r->addPoint(*ite);
			}
			return shared_ptr<waterEnvirMent<waterPoint>>(r);

		}
	}
}