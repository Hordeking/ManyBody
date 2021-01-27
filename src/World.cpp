// Licensed GPL3 By JD Fenech, Copyright 2018. See LICENSE file for details.

#include <iostream>
#include <World.h>


void World::Update(double dt){

	for(auto &current: Objlist){
		current.ApplyImpulse(dt);
		current.UpdatePosition(dt);
	}
}

void World::AddObject(Object & obj){

	Objlist.push_back(obj);

}

void World::DetermineGrav(){

	size_t max = Objlist.size();

	for(auto &obj: Objlist){
		obj.clearForce();
	}

	//This is the actual n-body calculator. Can this be tightened up?
	for(size_t i = 0; i < max; ++i)
	{

		//Object * obj1 = &( Objlist.at(i) );

		for(size_t j = i+1; j < max; ++j)
		{

			//Object * obj2 = &( Objlist.at(j) );

			// This happens for each pair.
			PairwiseGrav( Objlist[i], Objlist[j] );
			// End of this happens for each pair.
		}
	}
	//End of n-body work
}

inline void World::PairwiseGrav(Object & primary, Object & secondary){

	Eigen::Vector3d R = primary.r-secondary.r;	//Vec from secondary to primary.
	double R_len_sq = R.dot(R);					//Distance from sec to primary.

	//if (R_len_sq < 1) return;

	Eigen::Vector3d R_hat = R/sqrt(R_len_sq);	//R_hat points towards the primary.

	//Fg on secondary by primary
	Eigen::Vector3d Force = UnivGrav(primary.mass, secondary.mass, R_len_sq) * R_hat;

	//if (primary.ident==0) std::cerr << Force[0] << std::endl;

	// Add the force to both on this loop. We'll update positions and momenta
	// once all of the force has been applied.
	secondary.Net_Force += Force;
	primary.Net_Force -= Force;		//Subbed because secondary applies eq&opp force.

}

inline double World::UnivGrav(double M, double m, double r_squared)
{

	// This needs to check that r_squared != 0 i.e. the object acting on itself
	// or two objects occupying the same space point.

	const double G = 6.67e-11d;

	//if (r_squared < 1) return 0;

	return G*M*m/r_squared;
}
