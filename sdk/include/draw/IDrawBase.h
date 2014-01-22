#pragma once
#include <tools/MyTypes.h>
namespace xc{
	namespace draw{
		enum EnumDrawFunctions{
			EDF_2d_base=0,
			EDF_3d_base,
			EDF_3d_more_pipeline,
			EDF_3d_feedbackBuffer
		};
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
		};
	}
}