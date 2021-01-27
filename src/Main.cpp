// Licensed GPL3 By JD Fenech, Copyright 2018. See LICENSE file for details.

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>

#include <Eigen/Sparse>

#include <World.h>
#include <Object.h>

// Use glew.h instead of gl.h to get all the GL prototypes declared
//#include <GL/glew.h>
// Using SDL2 for the base window and OpenGL context init
//#include <SDL.h>

class Main {

public:
	Main() {};
	void Run(double duration, double dt = 60);
	~Main();

protected:

};

void Main::Run(double duration, double dt)
{
	//This is where the real program happens.

	//Establish our universe
	World myWorld;

	// Set up our objects


	Object sun;
	sun.ident = 0;
	sun.mass = 1.99e30;
	//sun.r = Eigen::Vector3d(-449550.407883699,0,0);
	sun.r = Eigen::Vector3d(-455088.245493414,0,0);
	sun.p = sun.mass * Eigen::Vector3d(0,-0.090671098983839,0);

	Object earth;
	earth.ident = 1;
	earth.mass = 5.98e24;
	//earth.r = Eigen::Vector3d(149.6e9d-449550.407883699+(0-4665823.72635316), 0, 0);
	earth.r = Eigen::Vector3d(-455088.245493414+149.6e9, 0, 0);
	earth.p = earth.mass * Eigen::Vector3d(0, 29805.9887921832, 0);

	Object moon;
	moon.mass = 7.347673e22;
	//moon.r = Eigen::Vector3d(-455088.245493414+149600000000+384400000, 0, 0);
	moon.r = Eigen::Vector3d(-455088.245493414+149.6e9+384400000, 0, 0);
	moon.p = moon.mass * Eigen::Vector3d(0, 29805.9887921832+986.251734869594, 0);

	Object ISS;
	ISS.ident = 2;
	ISS.mass = 417289e0;
	ISS.r = Eigen::Vector3d(-455088.245493414+149.6e9+6371000+408000, 0, 0);
	ISS.p = ISS.mass * Eigen::Vector3d(0, 29805.9887921832+7670, 0);

	Object Sat;
	Sat.ident = 3;
	Sat.mass = 27500;
	Sat.r = Eigen::Vector3d(-455088.245493414+149.6e9+6371000+100000, 0, 0);
	Sat.p = Sat.mass * Eigen::Vector3d(0, 29805.9887921832+7852.81659539524, 0);

	//Add the objects to the universe
	myWorld.AddObject(sun);
	myWorld.AddObject(earth);
	myWorld.AddObject(moon);
	myWorld.AddObject(ISS);
	myWorld.AddObject(Sat);

	std::cout << std::setprecision(15);

	clock_t begin_time = clock();

	// Output initial point
		for(auto & obj: myWorld.Objlist){
		std::cout	<< obj.r[0] << "\t" << obj.r[1] << "\t" << obj.r[2] << "\t";
		}
//		std::cerr	<< myWorld.UnivGrav(sun.mass, earth.mass, (149.6*149.6e18)) << std::endl;
		std::cout	<< std::endl;

	//Run the simulation for one year.

	//This for loop should be altered to just be called once per time slice and update the world
	for(int t = 0; t < duration; t+=dt)
	{
		//Cycle through ALL of the objects and find their influences on one another.
		myWorld.DetermineGrav();

		// Each object gets updated once we know the forces at the end of each time slice.
		myWorld.Update(dt);

		for(auto & obj: myWorld.Objlist){
//		auto & obj = myWorld.Objlist[0];
		std::cout	<< obj.r[0] << "\t" << obj.r[1] << "\t" << obj.r[2] << "\t";
//		std::cout	<< obj.p[0] << "\t" << obj.p[1] << "\t" << obj.p[2] << "\t" << std::endl;
//		std::cout	<< obj.Net_Force[0] << "\t" << obj.Net_Force[1] << "\t" << obj.Net_Force[2] << "\t" << std::endl;
		/* << obj.Net_Force[0] << "\t" << obj.Net_Force[1] << "\t"*/;
		}
		std::cout	<< std::endl;

	}

	clock_t end_time = clock();

	std::cerr << double(end_time - begin_time) / CLOCKS_PER_SEC << std::endl;

}

Main::~Main()
{
	//dtor
}

int main(int argc, char * argv[]){

	double dt = 1;
	double duration = 365*86400;

	if (argc < 1) return 0;
	if (argc >= 1) dt = strtod(argv[1], nullptr);
	if (argc > 1) duration = strtod(argv[2], nullptr);

	Main().Run(duration, dt);

	return 0;
}
