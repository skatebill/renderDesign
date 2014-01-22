#pragma once
namespace xc{
	namespace fileservice{
		//��ɫ����
		enum  EnumColorType
		{
			// rgba8 32λ����
			ECT_RGBA8=0

		};
		class IImage{
		public:
			//! ��ȡ���
			virtual unsigned int getWitdh()=0;
			//! ��ȡ�߶�
			virtual unsigned int getHeight()=0;
			//! ��ȡ����ָ��
			virtual void* getData()=0;
			//! ��ȡ��ɫ����
			virtual EnumColorType getColorType()=0;

			//! �Ƿ�ӵ��alpha����
			virtual bool hasAlpha()=0;
		};
	}
}