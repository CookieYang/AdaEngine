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
	else {
		return "";
	}
}

bool Config::asBool(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetBool();
	}
	else {
		return 0;
	}
}

unsigned Config::asUInt(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetUint();
	}
	else {
		return 0;
	}
}

uint64_t Config::asUint64(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetUint64();
	}
	else {
		return 0;
	}
}

int Config::asInt(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetInt();
	}
	else {
		return 0;
	}
}

int64_t Config::asInt64(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetInt64();
	} 
	else {
		return 0;
	}
}

double Config::asDouble(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetDouble();
	}
	else {
		return 0;
	}
}

float Config::asFloat(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return itr->value.GetFloat();
	}
	else {
		return 0;
	}
}

const rapidjson::Value& Config::asArray(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return document->operator[](key);
	}
	else {
		return rapidjson::Value();
	}
}

const rapidjson::Value& Config::asMap(const char* key) {
	rapidjson::Value::ConstMemberIterator itr = document->FindMember(key);
	if (itr != document->MemberEnd()) {
		return document->operator[](key);
	}
	else {
		return rapidjson::Value();
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