/**
* @file organism.h
* @author Eric Park
* @Date   10/22/2017
* @version 1.0
*
* @brief <ENSC 251, HW2>
*
* @section DESCRIPTION
* Class definition for organism class
*
**/

// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others.  I acknowledged that I have read and
// following the Academic Honesty and Integrity related policies as
// outlined in the syllabus.
//
// Eric Park      Oct. 22
//
// 301319654
#ifndef ORGANISM_H
#define ORGANISM_H

#include "grid.h"

namespace organisms
{	
	class Organism
	{
	public:
		Organism();
		~Organism();
		virtual void move();
		void breed();
		void live();
		void die();
		void setLoc(int location);
		bool getDead();
		int getAge();
		int getBreedTime();
		int getLoc();
	protected:
		bool alive;
		int age;
		int breedTime;
		int loc;
	};
}//organisms

#endif //ORGANISM_H