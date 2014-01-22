/************************************************************************/
/*	�ļ��ӿ�
	���Զ�ȡ�ļ�
	��ȡ�ļ���С
	��ȡ���ݵ�
	authored by Ф�� @ 2013��11��17��12:22:17*/
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
			//! �ļ���С
			virtual unsigned long getFileSize()=0;
			//! ��ȡ�ļ�
			virtual void read(char* buf,int size)=0;
			//! ��ת��ȡλ��
			virtual void seekTo(EnumSeekPos pos)=0;
			//! ���ݵ�ǰλ����ת��ȡλ��
			virtual void seekBy(int offset)=0;
			//! ��ȡ�ļ���
			virtual string getFileName()=0;
			//! ��ȡ�ļ�λ����
			virtual string getAbsolutePath()=0;
			//! ���ļ�
			virtual void open()=0;
			//! �ر��ļ�
			virtual void close()=0;
		};
		class IWriteableFile{
		public:

			//////////////////////////////////////////////////////////////////////////
			//! ���ļ�
			virtual void open()=0;
			//! �ر��ļ�
			virtual void close()=0;
			//! д������
			virtual void write(char* data,int size)=0;
			//! д���ַ���
			virtual void writeString(const char* str)=0;
			//! ����ļ�(����)
			virtual void clear()=0;

		};
	}
}