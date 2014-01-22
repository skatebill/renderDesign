#pragma once
#include"IImage.h"
#include"IFile.h"
#include<tools/MyTypes.h>

namespace xc{
	namespace fileservice{
		class IFileService{
		public:
			//! ���ļ�����ͼƬ
			virtual shared_ptr<IImage> createImageFromFile(const char* filename)=0;
			//! ��ȡ�ļ�
			virtual shared_ptr<IFile> createReadableFile(const char* filename)=0;
			//! ��������д����ļ�
			virtual shared_ptr<IWriteableFile> createWriteAbleFile(const char* filename)=0;
		};
	}
}