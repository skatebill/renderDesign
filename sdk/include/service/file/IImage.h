#pragma once
namespace xc{
	namespace fileservice{
		//颜色类型
		enum  EnumColorType
		{
			// rgba8 32位数据
			ECT_RGBA8=0

		};
		class IImage{
		public:
			//! 获取宽度
			virtual unsigned int getWitdh()=0;
			//! 获取高度
			virtual unsigned int getHeight()=0;
			//! 获取数据指针
			virtual void* getData()=0;
			//! 获取颜色类型
			virtual EnumColorType getColorType()=0;

			//! 是否拥有alpha分量
			virtual bool hasAlpha()=0;
		};
	}
}