#pragma once
#include"IImage.h"
#include"IFile.h"
#include<tools/MyTypes.h>

namespace xc{
	namespace fileservice{
		class IFileService{
		public:
			//! 从文件创建图片
			virtual shared_ptr<IImage> createImageFromFile(const char* filename)=0;
			//! 读取文件
			virtual shared_ptr<IFile> createReadableFile(const char* filename)=0;
			//! 创建可以写入的文件
			virtual shared_ptr<IWriteableFile> createWriteAbleFile(const char* filename)=0;
		};
	}
}