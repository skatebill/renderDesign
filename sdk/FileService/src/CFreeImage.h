#pragma once
#include <service/file/IImage.h>
#include<freeImage/FreeImage.h>
namespace xc{
	namespace fileservice{
		class CFreeImage:public IImage{
		public:
			FIBITMAP *dib;

			unsigned char* m_Data;
			unsigned int m_Width;
			unsigned int m_Height;
			bool m_HasAlpha;
		public:
			explicit CFreeImage();
			~CFreeImage();

			//! 获取宽度
			virtual unsigned int getWitdh();
			//! 获取高度
			virtual unsigned int getHeight();
			//! 获取数据指针
			virtual void* getData();
			//! 获取颜色类型
			virtual EnumColorType getColorType(){
				return ECT_RGBA8;
			}
			//! 是否拥有alpha分量
			virtual bool hasAlpha(){
				return m_HasAlpha;
			}

		};
	}
}