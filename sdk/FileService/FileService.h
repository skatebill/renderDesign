// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� FILESERVICE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// FILESERVICE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef _WINDOWS
#ifdef FILESERVICE_EXPORTS
#define FILESERVICE_API __declspec(dllexport)
#else
#define FILESERVICE_API __declspec(dllimport)
#endif
#else
#define FILESERVICE_API
#endif

#include <service/file/IFileService.h>

FILESERVICE_API xc::shared_ptr<xc::fileservice::IFileService> createFileService();
