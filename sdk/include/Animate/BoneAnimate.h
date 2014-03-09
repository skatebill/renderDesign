#pragma once
#include<string>
#include<vector>
#include<map>
#include<tools/MyTypes.h>
#include <algorithm>
#include"Interp.h"
#include<functional>
namespace xc{
	namespace draw{
		using namespace std;

		struct keyScale{
			f32 keyPos;
			vector3df scaleInfo;
			bool operator == (keyScale &o ){
				return keyPos == o.keyPos;
			}
		};
		struct keyRotate
		{
			f32 keyPos;
			quaternion rotateInfo;
			bool operator == (keyRotate &o ){
				return keyPos == o.keyPos;
			}
		};
		struct keyTranslate{
			f32 keyPos;
			vector3df translateInfo;
			bool operator == (keyTranslate &o ){
				return keyPos == o.keyPos;
			}
		};
		//! 对于每一个骨骼来说的动画部分
		struct boneActionPart{
			//! 对应的骨骼名称
			string boneName;
			//! 对应骨骼的idx
			u32 boneIdx;
			//! 插值器
			shared_ptr<Iinterper> interper;
			//! 动作优先级别
			u32 actionLevel;
			//! 起始帧数
			f32 startFrame;
			//! 结束帧数
			f32 endFrame;
		};
		//! 骨骼的类
		class Bone{
		private:
			//! 缓存的当前帧变换矩阵
			mat4 currentMatrix;
			//! 当前设置的帧数
			f32 curFrame;
			//! 获取相对变化矩阵
			mat4 getPreTranslateMatrix(f32 frame);
		public:
			//! 骨骼名称
			string boneName;
			//! 父骨骼
			shared_ptr<Bone> mParent;
			//! 骨骼最终需要附加的变换矩阵
			mat4 boneOffset;
			//! 不知道有啥用
			mat4 nodeTranslatation;
			//! 当前骨骼动画的最大帧数
			f32 maxFrame;
			//! 骨骼动画数据
			vector<keyScale> scaleList;
			vector<keyTranslate> translateList;
			vector<keyRotate> rotateList;

			Bone(shared_ptr<Bone> parent);
			//! 获取骨骼在某帧的变换矩阵
			mat4 getTranslateMatrix(f32 frame);
		};

		//! 骨骼组
		class BoneGroup{
		public:
			vector<shared_ptr<Bone>> mBoneList;
			//! 最大帧数
			f32 maxFrames;
			//! 每秒帧数
			f32 framesPersecond;
			//! 向其中添加一块骨骼
			void addBone(shared_ptr<Bone> bone);
			//! 获取某块骨骼的索引
			u32 getBoneIdx(shared_ptr<Bone> dstBone);
			u32 getBoneIdx(string boneName);
			//! 找到某块骨骼
			shared_ptr<Bone> getBone(u32 idx);
			shared_ptr<Bone> getBone(string boneName);
		};
		//! 骨骼动画的数据回调接口
		class BoneAnimeCallback{
		public:
			vector<u32> boneLevel;
			vector<f32> boneFrames;
		};
		//! 骨骼动画播放器
		//! 保存了某个动作的信息
		//! 比如行走这个动画
		//! 其中的骨骼是从10-20帧
		//! 优先级是2,控制全身
		//! 而攻击动画
		//! 控制上半身
		//! 优先级是3
		//! 那么上半身的攻击动画就会覆盖掉上半身的行走动画
		//! 而下半身的行走动画不会有影响将会继续播放
		class BoneAnimePlayer{
		public:
			BoneAnimePlayer(){
				loopFlag = false;
				playing = false;
				currentTime = 0;
			}
			//! 动作名称
			string actionName;
			//! 此动作所需要的骨骼列表
			vector<boneActionPart> actionPartList;
			//! 此动作是否循环播放
			bool loopFlag;
			//! 此动作是否正在播放
			bool playing;
			//! 此动作的持续时间
			f32 lastTime;
			//! 当前播放到什么时间点
			f32 currentTime;
			//! 更新动画
			void update(f32 t,BoneAnimeCallback* callback);
			//! 播放动画
			void playAction(){
				playing = true;
			}
			//! 停止播放动画
			void stopAction(){
				playing =false;
				currentTime = 0;
			}
			//!　暂停播放动画
			void pauseAction(){
				playing = false;
			}
		};
		//! 骨骼动画的播放器
		//! 内涵一个对骨骼的索引
		//! 缓存了一份matrix uniformbuffer
		//! 用map保存了所有的动作数据
		//! 当需要播放一个动画的时候只需要传入动画的名字就可以了
		class BoneAnimeController:public BoneAnimeCallback{
		private:
			//! 更新unifombuffer用的函数
			tr1::function<void()> mUnifomUpdateFunc;
		public:
			
			BoneAnimeController();
			//! 骨骼动画数据索引
			shared_ptr<BoneGroup> mDstBones;
			//! 动画列表
			map<string,shared_ptr<BoneAnimePlayer>> mActionList;
			//! buffer
			vector<mat4> mUniformBuffers;
			//! 缓存是否需要更新的标志位
			bool updateFlag;
			//! 动画更新
			void update(f32 t);
			//! 播放指定动画
			void playAction(string actionName);
			//! 获取unifom buffer数据供绘制阶段使用
			void getBoneUnifomBuff(void*& bufPtr,u32& size);
		};
	}
}