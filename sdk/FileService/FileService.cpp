// FileService.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "FileService.h"
#include"src/CFileService.h"
xc::shared_ptr<xc::fileservice::IFileService> createFileService(){
	return xc::shared_ptr<xc::fileservice::IFileService>(new xc::fileservice::CFileService);
}