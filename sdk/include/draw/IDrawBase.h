#pragma once
#include <tools/MyTypes.h>
#include <draw/IDraw3DBase.h>
namespace xc{
	namespace draw{
		class IDrawer2D{

		};
		class IRenderToolSet{
		public:
			//! 查询功能是否被支持
			virtual bool isFunctionSupported(EnumDrawFunctions request)=0;
			//! 获取3d绘制器
			virtual IDrawer3D* getDrawer3D()=0;
			//! 获取2d绘制器
			virtual IDrawer2D* getDrawer2D()=0;
			//! 获取3d的context
			virtual IContext3D getConext3D()=0;
		};
	}
}