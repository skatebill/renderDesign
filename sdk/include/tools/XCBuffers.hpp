#pragma once
#include <wchar.h>
#include <exception>
#define UINT unsigned int
namespace xc{
	using namespace std;

	class outOfRangeException:public std::exception{};
	
	class buffer{
	private:
		unsigned char* m_data;
		UINT m_CurPos;
		UINT m_MaxSize;
		bool m_AllocFlag;
	public:
		explicit buffer(int size=0):m_data(0),m_CurPos(0),m_MaxSize(size),m_AllocFlag(false){

		}
		~buffer(){
			if(m_data && m_AllocFlag) free(m_data);
			m_data=0;
		}
		//获取指定位置缓冲区
		void* get(UINT pos=0){
			if(pos>m_MaxSize || pos<0){
				throw outOfRangeException();
			}
			return m_data + pos;
		}
		void setSrc(void* src){
			if(m_data && m_AllocFlag) free(m_data);
			m_data=(unsigned char*)src;
			m_AllocFlag=false;
		}
		void setPos(UINT pos){
			m_CurPos = pos;
		}
		void resizeBuffer(UINT size){
			if(m_data && m_AllocFlag) free(m_data);
			m_AllocFlag = true;
			m_data = (unsigned char*)malloc(size);
		}
		template<typename T>
		void push(T& data){
			memmove(m_data+m_CurPos,&data,sizeof(T));
			m_CurPos+=sizeof(T);
		}
	};
}