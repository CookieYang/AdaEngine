#pragma once
#include "document.h"
#include <string>
#include "AdaMath.h"
#include <map>

class  Config {
public:
	Config() {};
	virtual ~Config() {
		delete document;
	};
	bool loadJson(const std::string& path);
	std::string asString(const char* key);
	bool asBool(const char* key);
	unsigned asUInt(const char* key);
	uint64_t asUint64(const char* key);
	int asInt(const char* key);
	int64_t asInt64(const char* key);
	double asDouble(const char* key);
	float asFloat(const char* key);
	const rapidjson::Value& asArray(const char* key);
	const rapidjson::Value& asMap(const char* key);
private:
	rapidjson::Document* document;
};

class EngineConfig : public Config {
public:
	EngineConfig();
	~EngineConfig() {};
	// render Settings
	DMath::vec_t windowFrame;
	bool bUseRenderingThread;
	void loadConfig();
};
