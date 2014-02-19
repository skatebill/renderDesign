#pragma once
#include <service/file/IFileService.h>
namespace xc{
	namespace fileservice{
		class CFileService:public IFileService{
		public:
			explicit CFileService();

			~CFileService();

			//! 从文件创建图片
			virtual shared_ptr<IImage> createImageFromFile(const char* filename);
			//! 读取文件
			virtual shared_ptr<IFile> createReadableFile(const char* filename);
			//! 创建可以写入的文件
			virtual shared_ptr<IWriteableFile> createWriteAbleFile(const char* filename);

		};
	}
}