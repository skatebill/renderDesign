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
			//! 启用灯光
			virtual void activateLight(SLight light,u32 idx)=0;
		};
		class IMaterialPath{
		public:
			//! 设置材质
			virtual void activateMaterial(SMaterial mat)=0;

		};
		class IMaterialLightedPath:public IMaterialPath{
		public:
			//! 启用灯光
			virtual void activateLight(SLight light,u32 idx)=0;
		};
		class IBoneAnimatedPath:public ITexturedPath{
		public:
			//! 上传骨骼变换矩阵
			virtual void uploadBoneMatrix(void* data,u32 size)=0;
		};
		class IBoneAnimatedLightedPath:public ITexturedLightedPath{
		public:
			//! 上传骨骼变换矩阵
			virtual void uploadBoneMatrix(void* data,u32 size)=0;

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