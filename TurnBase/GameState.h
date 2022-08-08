#pragma once
#include <string>
#include <vector>
#include "Properties.h"
struct TexttureFileHandler
{
	std::string textureID;
	std::string fileAddress;
	std::string className;
	Properties* pros;
};
class GameState
{
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;
	virtual std::string GetStateID() const = 0;
	//virtual void LoadedTextTureManager(std::vector<TexttureFileHandler> textureList) = 0;
	virtual void Handle_LoadedTexture_Object(std::vector<TexttureFileHandler> textureList) = 0;
protected:
	std::vector<TexttureFileHandler> m_textureList;
};