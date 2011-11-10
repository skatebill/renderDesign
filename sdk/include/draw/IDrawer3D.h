#pragma once
#include<draw/IDrawPath.h>
#include<draw/IDraw3DBase.h>
namespace xc{
	namespace draw{
		class IDrawFeatureConfig{
		public:
			// 模板设置
			virtual void stencil_test_enable()=0;
			virtual void stencil_test_disable()=0;
			virtual void stencil_buffer_enable()=0;
			virtual void stencil_buffer_disable()=0;
			virtual void stencil_test_compare(enumCompare sCompare)=0;
		public:
			// alpha设置
			virtual void alpha_test_enable()=0;
			virtual void alpha_test_disable()=0;
			virtual void alpha_test_compare(enumCompare sCompare)=0;
		public:
			// 深度缓存设置
			virtual void depth_test_enable()=0;
			virtual void depth_test_disable()=0;
			virtual void depth_buffer_enable()=0;
			virtual void depth_buffer_disable()=0;
			virtual void depth_test_compare(enumCompare sCompare)=0;
		public:
			// 混合设置
			virtual void blend_enable()=0;
			virtual void blend_disable()=0;
			virtual void blend_src_factor(enumBlendFunc bFactor)=0;
			virtual void blend_dst_factor(enumBlendFunc bFactor)=0;
		private:
			IDrawFeatureConfig(const IDrawFeatureConfig& other){

			}
		};
		class IDrawer3D{
		public:
			virtual void pushRTT(shared_ptr<ITextureTarget> rtt)=0;
			virtual void popRTT()=0;
			virtual void setViewPort(recti viewport)=0;
		//	virtual void enableFeature()=0;
		//	virtual void disableFeature()=0;
			// 获取绘制设置器
			virtual const IDrawFeatureConfig& getFeatureConfiger()=0;
			//! 渲染
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawVertexBufferOBject> vbo,EnumPrimityType pt=EPT_TRIANGLES)=0;
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf,EnumPrimityType pt=EPT_TRIANGLES)=0;
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawBuffer> vbuf,u32 num,EnumPrimityType pt=EPT_TRIANGLES)=0;
		};
	}
}