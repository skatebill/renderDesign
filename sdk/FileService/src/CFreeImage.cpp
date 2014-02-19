#include"CFreeImage.h"

namespace xc{
	namespace fileservice{

		CFreeImage::CFreeImage():dib(0),m_HasAlpha(false){
			
		}
		CFreeImage::~CFreeImage(){
			if(dib) FreeImage_Unload(dib);
		}

		//! 获取宽度
		unsigned int CFreeImage::getWitdh(){
			return m_Width;
		}
		//! 获取高度
		unsigned int CFreeImage::getHeight(){
			return m_Height;
		}
		//! 获取数据指针
		void* CFreeImage::getData(){
			return m_Data;
		}
	}
}