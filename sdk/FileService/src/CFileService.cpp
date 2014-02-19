#include "CFileService.h"
#include "CFreeImage.h"
#include "CFile.hpp"
namespace xc{
	namespace fileservice{

		CFileService::CFileService(){
			FreeImage_Initialise();
		}
		CFileService::~CFileService(){
			FreeImage_DeInitialise();
		}

		//! 从文件创建图片
		 shared_ptr<IImage> CFileService::createImageFromFile(const char* filename){
			 if(!boost::filesystem::exists(boost::filesystem::path(filename)))
				 throw std::exception();

			 CFreeImage* image = new CFreeImage;
			 FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);
			 FIBITMAP *dib(0);
			 //pointer to the image data

			 if(fif == FIF_UNKNOWN) 
				 fif = FreeImage_GetFIFFromFilename(filename);

			 if(fif == FIF_UNKNOWN)
				 throw std::exception();

			 if(FreeImage_FIFSupportsReading(fif))
				 dib = FreeImage_Load(fif, filename);
			 if(!dib){
				 throw std::exception();
			 }
			 image->dib=dib;
			// FreeImage_FlipVertical(dib);
			 //retrieve the image data
			 image->m_Data = FreeImage_GetBits(dib);
			 //get the image width and height
			 image->m_Width = FreeImage_GetWidth(dib);
			 image->m_Height = FreeImage_GetHeight(dib);
			/* FREE_IMAGE_COLOR_TYPE t = FreeImage_GetColorType(dib);
			 if(t == FIC_RGBALPHA){
				 image->m_HasAlpha=true;
			 }*/
			 int Bpp = FreeImage_GetBPP(dib);
			 switch (Bpp)
			 {
			 case 24:
				 {
					int n = image->m_Width * image->m_Height*3;
					for(int i=0;i<n;i+=3){
						unsigned char t = image->m_Data[i];
						image->m_Data[i] =image->m_Data[i+2];
						image->m_Data[i+2] = t;
					}
				 }
				 image->m_HasAlpha=false;
				 break;
			 case 32:
				 image->m_HasAlpha=true;
				 break;
			 default:
				 break;
			 }
			 return shared_ptr<IImage>(image);
		 }
		 //! 读取文件
		 shared_ptr<IFile> CFileService::createReadableFile(const char* filename){
			 return shared_ptr<IFile>(new CFile(filename));
		 }
		 //! 创建可以写入的文件
		 shared_ptr<IWriteableFile> CFileService::createWriteAbleFile(const char* filename){
			 return shared_ptr<IWriteableFile>(new CWriteAbleFile(filename));
		 }
	}
}