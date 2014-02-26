#include"ESDrawer.h"
#include<GLES2/gl2.h>
#include"ESPath.h"
namespace xc{
	namespace draw{
		GLuint getCompareFunc(enumCompare sCompare){
			GLuint compare;
			switch (sCompare)
			{
			case xc::draw::NEVER:
				compare = GL_NEVER;
				break;
			case xc::draw::ALWAYS:
				compare = GL_ALWAYS;
				break;
			case xc::draw::LESS:
				compare = GL_LESS;
				break;
			case xc::draw::GREATER:
				compare = GL_GREATER;
				break;
			case xc::draw::EQUAL:
				compare = GL_EQUAL;
				break;
			case xc::draw::LEQUAL:
				compare = GL_LEQUAL;
				break;
			case xc::draw::GEQUAL:
				compare = GL_GEQUAL;
				break;
			case xc::draw::NOTEQUAL:
				compare = GL_NOTEQUAL;
				break;
			default:
				return 0;
				break;
			}
			return compare;
		}

		ESDrawer::ESDrawer(){
			m_PathConext = shared_ptr<IPathContext>(new ESPathContext);
		}
		//! 检查是否支持某种特性
		bool ESDrawer::isFunctionSupported(EnumDrawFunctions request){
			return false;
		}
		void ESDrawer::pushRTT(shared_ptr<ITextureTarget> rtt){

		}
		void ESDrawer::popRTT(){

		}
		void ESDrawer::setViewPort(recti viewport){

		}
		// 获取绘制设置器
		const IDrawFeatureConfig& ESDrawer::getFeatureConfiger(){
			return m_esdfc;
		}
		void adaptGLTypes(GLuint& pType,EnumPrimaryType pt){

			switch (pt)
			{
			case xc::draw::EPT_DOTS:
				pType = GL_POINTS;
				break;
			case xc::draw::EPT_LINES:
				pType = GL_LINES;
				break;
			case xc::draw::EPT_LINE_STRIP:
				pType = GL_LINE_STRIP;
				break;
			case xc::draw::EPT_TRIANGLES:
				pType = GL_TRIANGLES;
				break;
			case xc::draw::EPT_TRIANGLE_STRIP:
				pType = GL_TRIANGLE_STRIP;
				break;
			case xc::draw::EPT_TRIANGLE_FAN:
				pType = GL_TRIANGLE_FAN;
				break;
			default:
				break;
			}
		}
		void adaptGLTypes(GLuint& iType, EnumIndexType it){

			switch (it)
			{
			case xc::draw::EIT_UBYTE:
				iType = GL_UNSIGNED_BYTE;
				break;
			case xc::draw::EIT_USHORT:
				iType = GL_UNSIGNED_SHORT;
				break;
			case xc::draw::EIT_UINT:
				iType = GL_UNSIGNED_INT;
				break;
			default:
				break;
			}
		}
		void adaptGLTypes(GLuint& pType,GLuint& iType,EnumPrimaryType pt, EnumIndexType it){
			adaptGLTypes(pType,pt);
			adaptGLTypes(iType,it);
		}
		//! 渲染
		void ESDrawer::render(shared_ptr<IDrawVertexBufferOBject> vbo,EnumPrimaryType pt){
			vbo->use();
			GLuint pType,iType;
			EnumIndexType it = vbo->getIndexType();
			adaptGLTypes(pType,iType,pt,it);
			glDrawElements(pType,vbo->getIndexNums(),iType,0);
			vbo->unUse();
		}
		void ESDrawer::render(shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf,EnumPrimaryType pt){
			GLuint pType,iType;
			EnumIndexType it = ibuf->getIndexType();
			adaptGLTypes(pType,iType,pt,it);
			vbuf->use(0);
			ibuf->use();
			glDrawElements(pType,ibuf->getIndexNums(),iType,0);
		}
		void ESDrawer::render(shared_ptr<IDrawBuffer> vbuf,u32 num,EnumPrimaryType pt){
			GLuint pType;
			adaptGLTypes(pType,pt);
			vbuf->use(0);
			glDrawArrays(pType,0,num);
		}
		shared_ptr<IPathContext> ESDrawer::getPathContext(){
			return m_PathConext;
		}


		void ESDrawFeatureConfig::stencil_test_enable()
		{
			glEnable(GL_STENCIL_TEST);
		}

		void ESDrawFeatureConfig::stencil_test_disable()
		{
			glDisable(GL_STENCIL_TEST);

		}

		void ESDrawFeatureConfig::stencil_buffer_enable()
		{
			glEnable(GL_STENCIL_BUFFER_BIT);
		}

		void ESDrawFeatureConfig::stencil_buffer_disable()
		{
			glDisable(GL_STENCIL_TEST);

		}

		void ESDrawFeatureConfig::stencil_test_compare( enumCompare sCompare,int ref_value,int mask )
		{
			GLuint compare=getCompareFunc(sCompare);
			if(compare){
				glStencilFunc(compare,ref_value,mask);
			}
		}

		//void ESDrawFeatureConfig::alpha_test_enable()
		//{
		//	glEnable(GL_ALPHA_TEST)
		//}

		//void ESDrawFeatureConfig::alpha_test_disable()
		//{

		//}

		//void ESDrawFeatureConfig::alpha_test_compare( enumCompare sCompare )
		//{

		//}

		void ESDrawFeatureConfig::depth_test_enable()
		{
			glEnable(GL_DEPTH_TEST);
		}

		void ESDrawFeatureConfig::depth_test_disable()
		{
			glDisable(GL_DEPTH_TEST);
		}

		void ESDrawFeatureConfig::depth_buffer_enable()
		{
			glEnable(GL_DEPTH_BUFFER_BIT);

		}

		void ESDrawFeatureConfig::depth_buffer_disable()
		{
			glDisable(GL_DEPTH_BUFFER_BIT);
		}

		void ESDrawFeatureConfig::depth_test_compare( enumCompare sCompare )
		{
			GLuint compare=getCompareFunc(sCompare);
			if(compare){
				glDepthFunc(compare);
			}
		}

		void ESDrawFeatureConfig::blend_enable()
		{
			glEnable(GL_BLEND);
		}

		void ESDrawFeatureConfig::blend_disable()
		{
			glDisable(GL_BLEND);
		}

		void ESDrawFeatureConfig::blend_src_factor( Blend::enumBlendFunc bFactor )
		{
			srcFac = bFactor;
			glBlendFunc(srcFac,desFac);
		}

		void ESDrawFeatureConfig::blend_dst_factor( Blend::enumBlendFunc bFactor )
		{
			desFac = bFactor;
			glBlendFunc(srcFac,desFac);
		}

		ESDrawFeatureConfig::ESDrawFeatureConfig()
		{
			srcFac = Blend::SRC_ALPHA;
			desFac = Blend::ONE_MINUS_SRC_ALPHA;
		}

	}
}