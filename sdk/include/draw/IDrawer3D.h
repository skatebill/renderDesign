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
			virtual void stencil_test_compare(enumCompare sCompare,int ref_value,int mask)=0;
		//public:
		//	// alpha设置
		//	virtual void alpha_test_enable()=0;
		//	virtual void alpha_test_disable()=0;
		//	virtual void alpha_test_compare(enumCompare sCompare)=0;
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
			virtual void blend_src_factor(Blend::enumBlendFunc bFactor)=0;
			virtual void blend_dst_factor(Blend::enumBlendFunc bFactor)=0;
		};
		class IDrawer3D{
		public:
			//! 查询功能是否被支持
			virtual bool isFunctionSupported(EnumDrawFunctions request)=0;
			//! 设置当前渲染目标
			virtual void pushRTT(shared_ptr<ITextureTarget> rtt)=0;
			//! 恢复上一层渲染目标
			virtual void popRTT()=0;
			//! 设置视口
			virtual void setViewPort(recti viewport)=0;
		//	virtual void enableFeature()=0;
		//	virtual void disableFeature()=0;
			// 获取绘制设置器
			virtual const IDrawFeatureConfig& getFeatureConfiger()=0;
			//! 渲染
			virtual void render(shared_ptr<IDrawVertexBufferOBject> vbo,EnumPrimaryType pt=EPT_TRIANGLES)=0;
			virtual void render(shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf,EnumPrimaryType pt=EPT_TRIANGLES)=0;
			virtual void render(shared_ptr<IDrawBuffer> vbuf,u32 num,EnumPrimaryType pt=EPT_TRIANGLES)=0;
			//! 获取path
			virtual shared_ptr<IPathContext> getPathContext()=0;
		};
	}
}