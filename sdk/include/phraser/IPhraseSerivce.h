#pragma once
#include<tools/MyTypes.h>
#include<Animate/BoneAnimate.h>
namespace xc{
	namespace phraser{
		class IPhraserService{
			public:
				virtual shared_ptr<draw::BoneAnimeController> loadBoneFromFile(const char* filename)=0;
		};
	}
}