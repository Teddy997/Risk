#pragma once
#include "StatisticsDecorator.h"
class StatisticsWorld : public StatisticsDecorator
{
public:
	StatisticsWorld(StatisticsView* v) : StatisticsDecorator(v) {};
	StatisticsWorld();
	void Update();
	~StatisticsWorld();
};

