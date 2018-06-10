#pragma once
#include "Game\Public\Singleton.h"
#include "Engine\Public\EngineTypes.h"
#include "Engine\Public\EngineInterface.h"
#include <string>
class ScoreManager : public Singleton<ScoreManager>
{
public:
	friend class Singleton<ScoreManager>;
	static int score;
	static int health;
	static int bullets;
	static std::string weapon;
	static bool isDone;
private:

};