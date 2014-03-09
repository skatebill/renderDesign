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
		//! ����ÿһ��������˵�Ķ�������
		struct boneActionPart{
			//! ��Ӧ�Ĺ�������
			string boneName;
			//! ��Ӧ������idx
			u32 boneIdx;
			//! ��ֵ��
			shared_ptr<Iinterper> interper;
			//! �������ȼ���
			u32 actionLevel;
			//! ��ʼ֡��
			f32 startFrame;
			//! ����֡��
			f32 endFrame;
		};
		//! ��������
		class Bone{
		private:
			//! ����ĵ�ǰ֡�任����
			mat4 currentMatrix;
			//! ��ǰ���õ�֡��
			f32 curFrame;
			//! ��ȡ��Ա仯����
			mat4 getPreTranslateMatrix(f32 frame);
		public:
			//! ��������
			string boneName;
			//! ������
			shared_ptr<Bone> mParent;
			//! ����������Ҫ���ӵı任����
			mat4 boneOffset;
			//! ��֪����ɶ��
			mat4 nodeTranslatation;
			//! ��ǰ�������������֡��
			f32 maxFrame;
			//! ������������
			vector<keyScale> scaleList;
			vector<keyTranslate> translateList;
			vector<keyRotate> rotateList;

			Bone(shared_ptr<Bone> parent);
			//! ��ȡ������ĳ֡�ı任����
			mat4 getTranslateMatrix(f32 frame);
		};

		//! ������
		class BoneGroup{
		public:
			vector<shared_ptr<Bone>> mBoneList;
			//! ���֡��
			f32 maxFrames;
			//! ÿ��֡��
			f32 framesPersecond;
			//! ���������һ�����
			void addBone(shared_ptr<Bone> bone);
			//! ��ȡĳ�����������
			u32 getBoneIdx(shared_ptr<Bone> dstBone);
			u32 getBoneIdx(string boneName);
			//! �ҵ�ĳ�����
			shared_ptr<Bone> getBone(u32 idx);
			shared_ptr<Bone> getBone(string boneName);
		};
		//! �������������ݻص��ӿ�
		class BoneAnimeCallback{
		public:
			vector<u32> boneLevel;
			vector<f32> boneFrames;
		};
		//! ��������������
		//! ������ĳ����������Ϣ
		//! ���������������
		//! ���еĹ����Ǵ�10-20֡
		//! ���ȼ���2,����ȫ��
		//! ����������
		//! �����ϰ���
		//! ���ȼ���3
		//! ��ô�ϰ���Ĺ��������ͻḲ�ǵ��ϰ�������߶���
		//! ���°�������߶���������Ӱ�콫���������
		class BoneAnimePlayer{
		public:
			BoneAnimePlayer(){
				loopFlag = false;
				playing = false;
				currentTime = 0;
			}
			//! ��������
			string actionName;
			//! �˶�������Ҫ�Ĺ����б�
			vector<boneActionPart> actionPartList;
			//! �˶����Ƿ�ѭ������
			bool loopFlag;
			//! �˶����Ƿ����ڲ���
			bool playing;
			//! �˶����ĳ���ʱ��
			f32 lastTime;
			//! ��ǰ���ŵ�ʲôʱ���
			f32 currentTime;
			//! ���¶���
			void update(f32 t,BoneAnimeCallback* callback);
			//! ���Ŷ���
			void playAction(){
				playing = true;
			}
			//! ֹͣ���Ŷ���
			void stopAction(){
				playing =false;
				currentTime = 0;
			}
			//!����ͣ���Ŷ���
			void pauseAction(){
				playing = false;
			}
		};
		//! ���������Ĳ�����
		//! �ں�һ���Թ���������
		//! ������һ��matrix uniformbuffer
		//! ��map���������еĶ�������
		//! ����Ҫ����һ��������ʱ��ֻ��Ҫ���붯�������־Ϳ�����
		class BoneAnimeController:public BoneAnimeCallback{
		private:
			//! ����unifombuffer�õĺ���
			tr1::function<void()> mUnifomUpdateFunc;
		public:
			
			BoneAnimeController();
			//! ����������������
			shared_ptr<BoneGroup> mDstBones;
			//! �����б�
			map<string,shared_ptr<BoneAnimePlayer>> mActionList;
			//! buffer
			vector<mat4> mUniformBuffers;
			//! �����Ƿ���Ҫ���µı�־λ
			bool updateFlag;
			//! ��������
			void update(f32 t);
			//! ����ָ������
			void playAction(string actionName);
			//! ��ȡunifom buffer���ݹ����ƽ׶�ʹ��
			void getBoneUnifomBuff(void*& bufPtr,u32& size);
		};
	}
}