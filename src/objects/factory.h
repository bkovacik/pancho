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

class Factory;

typedef GameObject* (*funcptr)(int, int, int, int);

class Factory {
	static std::map<std::string, funcptr> funcmap_;

	static class InitFactory {
		public:
			InitFactory();
	} init;

	template<typename T> static GameObject* createObject(int a0, int a1, int a2, int a3) {return new T(a0, a1, a2, a3);}

	public:
		static GameObject* getNewObject(std::string type, int a0, int a1, int a2, int a3) {return funcmap_[type](a0, a1, a2, a3);}


};

#endif
