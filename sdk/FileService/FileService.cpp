// FileService.cpp : 定义 DLL 应用程序的导出函数。
//

#include "FileService.h"
#include"src/CFileService.h"
xc::shared_ptr<xc::fileservice::IFileService> createFileService(){
	return xc::shared_ptr<xc::fileservice::IFileService>(new xc::fileservice::CFileService);
}