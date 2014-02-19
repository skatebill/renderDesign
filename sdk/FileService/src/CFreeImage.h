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

			//! ��ȡ���
			virtual unsigned int getWitdh();
			//! ��ȡ�߶�
			virtual unsigned int getHeight();
			//! ��ȡ����ָ��
			virtual void* getData();
			//! ��ȡ��ɫ����
			virtual EnumColorType getColorType(){
				return ECT_RGBA8;
			}
			//! �Ƿ�ӵ��alpha����
			virtual bool hasAlpha(){
				return m_HasAlpha;
			}

		};
	}
}