#include "Config.h"
#include "ResourceManager.h"

bool Config::loadJson(const std::string& path) {
	std::string jsonString = ResourceManager::readFileAsString(path);
	document = new rapidjson::Document();
	document->Parse(jsonString.c_str());
	if (document->IsObject())
	{
		return true;
	}
	else {
		return false;
	}
}

std::string Config::asString(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetString();
	}
}

bool Config::asBool(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetBool();
	}
}

unsigned Config::asUInt(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetUint();
	}
}

uint64_t Config::asUint64(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetUint64();
	}
}

int Config::asInt(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetInt();
	}
}

int64_t Config::asInt64(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetInt64();
	}
}

double Config::asDouble(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetDouble();
	}
}

float Config::asFloat(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetFloat();
	}
}

const rapidjson::Value& Config::asArray(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return document->operator[](key);
	}
}

const rapidjson::Value& Config::asMap(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return document->operator[](key);
	}
}

EngineConfig::EngineConfig() {
	loadJson("config/Config.json");
	windowFrame = DMath::makeVect(0, 0, 1024, 720);
	bUseRenderingThread = false;
}

void EngineConfig::loadConfig() {
	const rapidjson::Value& renderSetting = asMap("RenderConfig");
	const rapidjson::Value& winFrame = renderSetting["WindowFrame"];
	windowFrame = DMath::makeVect(winFrame[0].GetFloat(), winFrame[1].GetFloat(), winFrame[2].GetInt(), winFrame[3].GetInt());
	bUseRenderingThread = renderSetting["UseMultiThread"].GetBool();
}