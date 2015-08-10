#include "factory.h"

std::map<std::string, funcptr4> Factory::funcmap4_;
std::map<std::string, funcptr2> Factory::funcmap2_;
Factory::InitFactory Factory::init;

Factory::InitFactory::InitFactory() {
	funcmap4_["pancho"] = Factory::createObject<Pancho>;
	funcmap4_["block"] = Factory::createObject<Block>;
	funcmap4_["crumble"] = Factory::createObject<Crumble>;
	funcmap4_["spikes"] = Factory::createObject<Spikes>;
	funcmap4_["jumpthrough"] = Factory::createObject<JumpThrough>;
}
