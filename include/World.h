// Licensed GPL3 By JD Fenech, Copyright 2018. See LICENSE file for details.

#include <Object.h>

#ifndef WORLD_H
	#define WORLD_H

class World {

public:
	World() {}
	~World() {}

	void DetermineGrav();
	void Update(double dt);
	void AddObject(Object & obj);
	//How do we remove an object from the world?

	std::vector<Object> Objlist;

public:
//protected:

	void PairwiseGrav(Object & primary, Object & secondary);
	static double UnivGrav(double M, double m, double r);

};

#endif
