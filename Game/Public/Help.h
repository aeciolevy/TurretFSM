#pragma once
#include "Engine\Public\EngineTypes.h"
#include <random>
#include <string>
#include <vector>

const float CITY_SIZE = 100;


class Help {
public:
	exVector2 static CreateCities(int numberOfCities, int index)
	{
		float spareSpace = kViewPortWidth - (numberOfCities * CITY_SIZE);
		float padding = spareSpace / numberOfCities;
		float xPos = padding * index + padding + index * CITY_SIZE;
		return { xPos, 590.0f };
	}

	int static GenerateRandom(int low, int high)
	{
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 rng(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<int> uni(low, high);
		return uni(rng);
	}

	exVector2 static EnemyMissileStartPosition() 
	{
		exVector2 b1 = { 133.0f, 0.0f };
		exVector2 b2 = { 399.0f, 0.0f };
		exVector2 b3 = { 665.0f, 0.0f };
		std::vector<exVector2> mStartPositionEnemy;
		mStartPositionEnemy.push_back(b1);
		mStartPositionEnemy.push_back(b2);
		mStartPositionEnemy.push_back(b3);

		int location = GenerateRandom(0, (int) mStartPositionEnemy.size() - 1);
		return mStartPositionEnemy[location];
	}
};