#pragma once
#include<tools/MyTypes.h>
#include<drawBasement/IModel.h>
namespace xc{
	namespace phraser{
		class IPhraserService{
			public:
				//! ¶ÁÈ¡Ä£ÐÍ
				virtual shared_ptr<drawBasement::IModel> loadModelFromFile(const char* filename)=0;
		};
	}
}