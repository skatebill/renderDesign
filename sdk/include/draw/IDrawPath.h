#pragma once
#include "IDraw3DBase.h"
namespace xc
{
	namespace draw{
		class IDrawPath{
		public:
			//! 激活path
			virtual void activate()=0;
			//! 注销path
			virtual void deActivate()=0;
		};
		class IColoredPath:public IDrawPath{
		public:
			//! 设置颜色
			virtual void setColor(colorf color)=0;
		};
		class IVertexColorPath:public IDrawPath{
		public:

		};
		class ITexturedPath:public IDrawPath{
		public:

		};
		class ITexturedLightedPath:public ITexturedPath{
		public:

		};
		class IBoneAnimatedPath:public ITexturedPath{

		};
		class IBoneAnimatedLightedPath:public ITexturedLightedPath{

		};
		class IPathContext{
		public:
			//! 获取颜色绘制path
			virtual shared_ptr<IColoredPath> getColorPath()=0;
			//! 获取纹理绘制path
			virtual shared_ptr<ITexturedPath> getTexturePath()=0;
		};
	}
}