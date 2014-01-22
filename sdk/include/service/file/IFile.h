/************************************************************************/
/*	文件接口
	可以读取文件
	获取文件大小
	读取数据等
	authored by 肖驰 @ 2013年11月17日12:22:17*/
/************************************************************************/
#pragma once
#include <tools/MyTypes.h>
namespace xc{
	namespace fileservice{
		enum EnumSeekPos{
			ESP_BEGIN,
			ESP_END
		};
		class IFile{
		public:
			//! 文件大小
			virtual unsigned long getFileSize()=0;
			//! 读取文件
			virtual void read(char* buf,int size)=0;
			//! 跳转读取位置
			virtual void seekTo(EnumSeekPos pos)=0;
			//! 根据当前位置跳转读取位置
			virtual void seekBy(int offset)=0;
			//! 获取文件名
			virtual string getFileName()=0;
			//! 获取文件位置名
			virtual string getAbsolutePath()=0;
			//! 打开文件
			virtual void open()=0;
			//! 关闭文件
			virtual void close()=0;
		};
		class IWriteableFile{
		public:

			//////////////////////////////////////////////////////////////////////////
			//! 打开文件
			virtual void open()=0;
			//! 关闭文件
			virtual void close()=0;
			//! 写入数据
			virtual void write(char* data,int size)=0;
			//! 写入字符串
			virtual void writeString(const char* str)=0;
			//! 清空文件(慎用)
			virtual void clear()=0;

		};
	}
}