#pragma once
#include<draw/IDrawer3D.h>
namespace xc{
	namespace draw{
		class ESDrawFeatureConfig:public IDrawFeatureConfig{
		private:
			Blend::enumBlendFunc srcFac;
			Blend::enumBlendFunc desFac;
		public:
			ESDrawFeatureConfig();


			// ģ������
			virtual void stencil_test_enable();
			virtual void stencil_test_disable();
			virtual void stencil_buffer_enable();
			virtual void stencil_buffer_disable();
			virtual void stencil_test_compare(enumCompare sCompare,int ref_value,int mask);
		//public:
		//	// alpha����
		//	virtual void alpha_test_enable();
		//	virtual void alpha_test_disable();
		//	virtual void alpha_test_compare(enumCompare sCompare);
		public:
			// ��Ȼ�������
			virtual void depth_test_enable();
			virtual void depth_test_disable();
			virtual void depth_buffer_enable();
			virtual void depth_buffer_disable();
			virtual void depth_test_compare(enumCompare sCompare);
		public:
			// �������
			virtual void blend_enable();
			virtual void blend_disable();
			virtual void blend_src_factor(Blend::enumBlendFunc bFactor);
			virtual void blend_dst_factor(Blend::enumBlendFunc bFactor);

		};
		//! OGLES2 �汾�Ļ�����
		class ESDrawer:public IDrawer3D{
		public:
			ESDrawFeatureConfig m_esdfc;

			//! ����Ƿ�֧��ĳ������
			virtual bool isFunctionSupported(EnumDrawFunctions request);
			virtual void pushRTT(shared_ptr<ITextureTarget> rtt);
			virtual void popRTT();
			virtual void setViewPort(recti viewport);
			// ��ȡ����������
			virtual const IDrawFeatureConfig& getFeatureConfiger();
			//! ��Ⱦ
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawVertexBufferOBject> vbo,EnumPrimaryType pt=EPT_TRIANGLES);
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf,EnumPrimaryType pt=EPT_TRIANGLES);
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawBuffer> vbuf,u32 num,EnumPrimaryType pt=EPT_TRIANGLES);

		};
	}
}