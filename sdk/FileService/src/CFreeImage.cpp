#include"CFreeImage.h"

namespace xc{
	namespace fileservice{

		CFreeImage::CFreeImage():dib(0),m_HasAlpha(false){
			
		}
		CFreeImage::~CFreeImage(){
			if(dib) FreeImage_Unload(dib);
		}

		//! ��ȡ���
		unsigned int CFreeImage::getWitdh(){
			return m_Width;
		}
		//! ��ȡ�߶�
		unsigned int CFreeImage::getHeight(){
			return m_Height;
		}
		//! ��ȡ����ָ��
		void* CFreeImage::getData(){
			return m_Data;
		}
	}
}