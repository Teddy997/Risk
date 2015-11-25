#pragma once
#include "StatisticsView.h"
class StatisticsDecorator : public StatisticsView
{
protected:
	StatisticsView* view;
public:
	StatisticsDecorator(StatisticsView* v) {
		this->view = v;
	}
	void Update() {

		view->Update();
	}
	StatisticsDecorator(GameState* g) : StatisticsView(g) {};
	StatisticsDecorator();
	~StatisticsDecorator();
};

