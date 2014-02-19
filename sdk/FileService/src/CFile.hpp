#pragma once
#include<service/file/IFile.h>
#include<boost/filesystem.hpp>
#include<fstream>
namespace xc{
	namespace fileservice{
		class CFile:public IFile{
		private:
			std::fstream mFile;
			
			boost::filesystem::path mPath;
			unsigned long mFileSize;
			bool mIsopened;
		public:
			CFile(const char* filename){
				mPath = boost::filesystem::path(filename);
				if(!boost::filesystem::exists(mPath))
				{
					throw std::exception();
				}
				mFileSize = (unsigned long)boost::filesystem::file_size(mPath);
				mIsopened=false;
			}
			~CFile(){
				close();
			}
			inline void checkOpened(){
				if(!mIsopened){
					throw std::exception();
				}
			}
			//! 文件大小
			virtual unsigned long getFileSize(){
				return mFileSize;
			}
			//! 读取文件
			virtual void read(char* buf,int size){
				//checkOpened();
				mFile.read(buf,size);
			}
			//! 跳转读取位置
			virtual void seekTo(EnumSeekPos pos){
				//checkOpened();
				switch (pos)
				{
				case xc::fileservice::ESP_BEGIN:
					mFile.seekg(0,std::ios_base::beg);
					break;
				case xc::fileservice::ESP_END:
					mFile.seekg(std::ios_base::end);
					break;
				default:
					break;
				}
			}
			//! 根据当前位置跳转读取位置
			virtual void seekBy(int offset){
				//checkOpened();
				mFile.seekg(offset);
			}
			//! 获取文件名
			virtual string getFileName(){
				return string(mPath.filename().c_str());
			}
			//! 获取文件位置名
			virtual string getAbsolutePath(){
				return string(boost::filesystem::system_complete(mPath).c_str());
			}
			//! 打开文件
			virtual void open(){
				if(!mFile.is_open()){
					mFile.open(mPath.c_str(),std::ios_base::binary);
				}
				mIsopened=true;
			}
			//! 关闭文件
			virtual void close(){
				if(mFile.is_open()) mFile.close();
				mIsopened=false;
			}
		};
		class CWriteAbleFile:public IWriteableFile{
		private:
			boost::filesystem::path mFilename;
			std::fstream mFile;
		public:
			explicit CWriteAbleFile(const char* filename):mFilename(filename){
				boost::filesystem::path::iterator mdir= mFilename.begin();
				boost::filesystem::path dir;
				while(1){
					auto next = mdir;
					next ++;
					if(next == mFilename.end()){break;}
					dir+=(*mdir);
					boost::filesystem::create_directory(dir);
					mdir++;
				}
				mFile.open(filename,std::ios_base::out|std::ios_base::app);
				if(!mFile){
					throw std::exception();
				}
				mFile.close();
			}
			~CWriteAbleFile(){
				if(mFile.is_open()) mFile.close();
			}
			//! 打开文件
			virtual void open(){
				mFile.open(mFilename.c_str(),std::ios_base::out|std::ios_base::app);
			}
			//! 关闭文件
			virtual void close(){
				mFile.close();
			}
			//! 写入数据
			virtual void write(char* data,int size){
				mFile.write(data,size);
			}
			//! 写入字符串
			virtual void writeString(const char* str){
				mFile<<str;
			}
			//! 清空文件(慎用)
			virtual void clear(){
				if(mFile.is_open()) mFile.close();
				boost::filesystem::remove(mFilename);
				open();
				close();
			}

		};
	}
}