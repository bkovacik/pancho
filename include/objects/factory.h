//factory.h

#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include "position.h"
#include "pancho.h"
#include "block.h"
#include "crumble_block.h"
#include "spikes_block.h"
#include "jumpthrough_block.h"
#include "ladder_block.h"
#include "blob_enemy.h"

class Factory;

typedef GameObject* (*funcptr4)(int, int, int, int);
typedef GameObject* (*funcptr2)(int, int);

class Factory {
	static std::map<std::string, funcptr4> funcmap4_;
	static std::map<std::string, funcptr2> funcmap2_;

	static class InitFactory {
		public:
			InitFactory();
	} init;

	template<typename T> static GameObject* createObject(int a0, int a1, int a2, int a3) {return new T(a0, a1, a2, a3);}
	template<typename T> static GameObject* createObject(int a0, int a1) {return new T(a0, a1);}

	public:
		static GameObject* getNewObject(std::string type, int a0, int a1, int a2, int a3) {return funcmap4_[type](a0, a1, a2, a3);}
		static GameObject* getNewObject(std::string type, int a0, int a1) {return funcmap2_[type](a0, a1);}
};

#endif
