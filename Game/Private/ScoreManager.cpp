#include "Game\Public\ScoreManager.h"
#include "Game/Public/Factory.h"
#include <string>

//Initializing static member outside of the constructor
ScoreManager* Singleton<ScoreManager>::mSingleton = nullptr;

int ScoreManager::score = 0;
int ScoreManager::health = 100;
int ScoreManager::bullets = 25;
std::string ScoreManager::weapon = "Small";
bool ScoreManager::isDone = false;
