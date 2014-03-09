#pragma once
#include<string>
#include<vector>
#include<tools/MyTypes.h>
#include <algorithm>
namespace xc{
	namespace draw{
		using namespace std;
		class Iinterper{
		public:
			//! ��[0,1]���в�ֵ
			virtual f32 interp(f32)=0;
		};
		class AvergeInterper:public Iinterper{
		public:
			//! ��[0,1]���в�ֵ
			virtual f32 interp(f32 i){
				return i;
			}

		};
	}
}