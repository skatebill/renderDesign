#include "ESTexture.h"
namespace xc{
	namespace draw{
		ESTexture::ESTexture(){
			m_TexHandle = 0;
			m_CurrentSlot = -1;
		}
		ESTexture::~ESTexture(){
			if(m_TexHandle){
				glDeleteTextures(1,&m_TexHandle);
			}
		}
		vector2di ESTexture::getTextureSize()
		{
			return m_TexSize;
		}

		void ESTexture::use( int slot )
		{
			if(m_TexHandle){
				glActiveTexture(GL_TEXTURE0+slot);
				m_CurrentSlot = slot;
				glBindTexture(GL_TEXTURE_2D,m_TexHandle);
			}	
		}

		void ESTexture::unUse()
		{
			if(m_CurrentSlot>0){
				glActiveTexture(GL_TEXTURE0+m_CurrentSlot);
				glBindTexture(GL_TEXTURE_2D,0);
				m_CurrentSlot = -1;
			}
			
		}


		shared_ptr<ITexture> ESTextureFactory::createTextureFromImage( shared_ptr<fileservice::IImage> image)
		{
			auto tex = new ESTexture;
			tex->m_TexSize.X=image->getWitdh();
			tex->m_TexSize.Y=image->getHeight();
			GLuint colorType=GL_RGB;
			if(image->hasAlpha()) 
				colorType=GL_RGBA;

			glGenTextures(1,&tex->m_TexHandle);
			tex->use(0);
			glTexImage2D(GL_TEXTURE_2D,0,colorType,tex->m_TexSize.X,tex->m_TexSize.Y,0,colorType,GL_UNSIGNED_BYTE,image->getData());
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glGenerateMipmap(GL_TEXTURE_2D);
			tex->unUse();
			return  shared_ptr<ITexture>(tex);
		}

		shared_ptr<ITextureTarget> ESTextureFactory::createTextureTarget( int width,int height,bool depth/*=true*/,bool stencil/*=true */ )
		{
			return nullptr;
		}

	}
}