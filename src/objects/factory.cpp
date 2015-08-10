#include "factory.h"

std::map<std::string, funcptr> Factory::funcmap_;
Factory::InitFactory Factory::init;

Factory::InitFactory::InitFactory() {
	funcmap_["pancho"] = Factory::createObject<Pancho>;
	funcmap_["block"] = Factory::createObject<Block>;
	funcmap_["crumble"] = Factory::createObject<Crumble>;
	funcmap_["spikes"] = Factory::createObject<Spikes>;
	funcmap_["jumpthrough"] = Factory::createObject<JumpThrough>;
}
