#pragma once
#include<draw/IDrawPath.h>
#include<draw/IDraw3DBase.h>
namespace xc{
	namespace draw{
		class IDrawFeatureConfig{
		public:
			// ģ������
			virtual void stencil_test_enable()=0;
			virtual void stencil_test_disable()=0;
			virtual void stencil_buffer_enable()=0;
			virtual void stencil_buffer_disable()=0;
			virtual void stencil_test_compare(enumCompare sCompare,int ref_value,int mask)=0;
		//public:
		//	// alpha����
		//	virtual void alpha_test_enable()=0;
		//	virtual void alpha_test_disable()=0;
		//	virtual void alpha_test_compare(enumCompare sCompare)=0;
		public:
			// ��Ȼ�������
			virtual void depth_test_enable()=0;
			virtual void depth_test_disable()=0;
			virtual void depth_buffer_enable()=0;
			virtual void depth_buffer_disable()=0;
			virtual void depth_test_compare(enumCompare sCompare)=0;
		public:
			// �������
			virtual void blend_enable()=0;
			virtual void blend_disable()=0;
			virtual void blend_src_factor(Blend::enumBlendFunc bFactor)=0;
			virtual void blend_dst_factor(Blend::enumBlendFunc bFactor)=0;
		};
		class IDrawer3D{
		public:
			//! ��ѯ�����Ƿ�֧��
			virtual bool isFunctionSupported(EnumDrawFunctions request)=0;
			//! ���õ�ǰ��ȾĿ��
			virtual void pushRTT(shared_ptr<ITextureTarget> rtt)=0;
			//! �ָ���һ����ȾĿ��
			virtual void popRTT()=0;
			//! �����ӿ�
			virtual void setViewPort(recti viewport)=0;
		//	virtual void enableFeature()=0;
		//	virtual void disableFeature()=0;
			// ��ȡ����������
			virtual const IDrawFeatureConfig& getFeatureConfiger()=0;
			//! ��Ⱦ
			virtual void render(shared_ptr<IDrawVertexBufferOBject> vbo,EnumPrimaryType pt=EPT_TRIANGLES)=0;
			virtual void render(shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf,EnumPrimaryType pt=EPT_TRIANGLES)=0;
			virtual void render(shared_ptr<IDrawBuffer> vbuf,u32 num,EnumPrimaryType pt=EPT_TRIANGLES)=0;
			//! ��ȡpath
			virtual shared_ptr<IPathContext> getPathContext()=0;
		};
	}
}