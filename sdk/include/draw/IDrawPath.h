#pragma once
#include "IDraw3DBase.h"
namespace xc
{
	namespace draw{
		class IDrawPath{
		public:
			//! ����path
			virtual void activate()=0;
			//! ע��path
			virtual void deActivate()=0;
		};
		class IColoredPath:public IDrawPath{
		public:
			//! ������ɫ
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
			//! ��ȡ��ɫ����path
			virtual shared_ptr<IColoredPath> getColorPath()=0;
			//! ��ȡ�������path
			virtual shared_ptr<ITexturedPath> getTexturePath()=0;
		};
	}
}