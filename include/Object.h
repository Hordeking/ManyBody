// Licensed GPL3 By JD Fenech, Copyright 2018. See LICENSE file for details.

#include <Eigen/Sparse>

#ifndef OBJECT_H
	#define OBJECT_H

class Object {

public:
	Object() {
		ident = -1;

		Net_Force = Eigen::Vector3d(0, 0, 0);
		r = Eigen::Vector3d(0, 0, 0);
		p = Eigen::Vector3d(0, 0, 0);

		Net_Torque = Eigen::Vector3d(0, 0, 0);
	}

	~Object() {}

	inline void clearForce() { Net_Force *= 0; /*Eigen::Vector3d(0, 0, 0);*/ }
	inline void clearTorque() { Net_Torque *= 0; /*Eigen::Vector3d(0, 0, 0);*/ }
	inline void ApplyImpulse(double dt) { p += Net_Force * dt;}
	inline void UpdatePosition(double dt) { assert(mass>0); r += p / mass * dt; }

	// This is essentially user settable, and will influence things like thrust, drag, and lift.
	Eigen::Vector3d orientation;	//needs to be forward, up, and rightward

	unsigned int ident;

	// These parameters are state parameters
	Eigen::Vector3d r;		// Position
	Eigen::Vector3d p;		// Momentum
	double mass = 0;			// We will handle this being able to change later.
	Eigen::Vector3d Net_Force;	// This is the special sauce that makes it all work. Net force.


	//These are rotational variables. We'll work them in later.

	Eigen::Matrix3d I; //Moment of Inertia is a tensor. We'll figure this one out later.
	Eigen::Vector3d L;				// Angular momentum, not used yet
	Eigen::Vector3d Net_Torque;		//Not used yet, but we'll find a way.


protected:

	//Our objects should definitely have hulls for collision detection.

};

#endif
