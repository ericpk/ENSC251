/**
* @file PredatorPrey.cpp
* @author Eric Park
* @Date   10/22/2017
* @version 1.0
*
* @brief <ENSC 251, HW2>
*
* @section DESCRIPTION
* A predator-prey simulation using randomized conditions
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
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "organism.h"
#include "grid.h"

//set constants for the simulation
#define EMPTY 0
#define ANT 1
#define DOODLEBUG 2
#define GRIDSIZE 20
#define NUMANTS 100
#define NUMDOODLEBUGS 5

namespace organisms
{
	class Ant : public Organism
	{
	public:
		void move();
	};

	class Doodlebug : public Organism
	{
	public:
		Doodlebug();
		void move();
		void eat();
		int getEatTime();
	protected:
		int eatTime;
	};

	Organism::Organism()
	{
		alive = false;
		age = 0;
		breedTime = 0;
		loc = -1;
	}

	Organism::~Organism()
	{
		//left empty
	}

	void Organism::move()
	{
		if (alive)
		{
			age++;
			breedTime++;
		}
	}

	void Organism::breed()
	{
		breedTime = 0;
	}

	void Organism::live()
	{
		alive = true;
	}

	void Organism::die()
	{
		alive = false;
	}

	void Organism::setLoc(int location)
	{
		loc = location;
	}

	bool Organism::getDead()
	{
		return alive;
	}

	int Organism::getAge()
	{
		return age;
	}
	int Organism::getBreedTime()
	{
		return breedTime;
	}

	int Organism::getLoc()
	{
		return loc;
	}

	void Ant::move()
	{
		if (alive)
		{
			age++;
			breedTime++;
		}
	}
	Doodlebug::Doodlebug()
	{
		alive = alive;
		loc = -1;
		age = 0;
		breedTime = 0;
		eatTime = 0;
	}

	void Doodlebug::move()
	{
		age++;
		breedTime++;
		eatTime++;
	}

	void Doodlebug::eat()
	{
		eatTime = 0;
	}

	int Doodlebug::getEatTime()
	{
		return eatTime;
	}
}//organisms

namespace grids
{
	class grid2DSim : public grid2D
	{
	public:
		grid2DSim(int dimen);
		void displayGridASCII();
	};

	grid2DSim::grid2DSim(int dimen)
	{
		if (dimen <= 0)
		{
			dimen = 20;
		}
		int size = dimen;
		int numIndex = size * size;
		index = new int[numIndex];

		for (int i = 0; i < numIndex; i++)
		{
			index[i] = 0;
		}
	}

	//override displayGrid function to display using ASCI characters
	void grid2DSim::displayGridASCII()
	{
		int numIndex = size * size;
		cout << endl;
		for (int i = 0; i < numIndex; i++)
		{
			if (index[i] == EMPTY)
			{
				cout << ". ";
			}
			else if (index[i] == ANT)
			{
				cout << "A ";
			}
			else if (index[i] == DOODLEBUG)
			{
				cout << "D ";
			}
			if ((i + 1) % size == 0)
			{
				cout << endl;
			}
		}
	}
}

using namespace std;
using namespace grids;
using namespace organisms;

/*
* Main simulation function
*/
int main()
{
	srand(static_cast<int>(time(NULL)));
	const int NUMELEMENTS = GRIDSIZE * GRIDSIZE;
	bool eaten = false;
	bool bred = false;
	int numAnts = NUMANTS;
	int numDoodles = NUMDOODLEBUGS;
	int move = 0;
	int cX = 0;
	int cY = 0;
	int currLoc = 0;
	int testLoc = 0;
	char discard = '\0';
	vector<int> randArray;

	grid2DSim simulation(GRIDSIZE);

	Ant *ants;
	ants = new Ant[NUMELEMENTS];

	Doodlebug *doodle;
	doodle = new Doodlebug[NUMELEMENTS];

	//used for shuffling the element index and assigning first N values
	//to the corresponding organisms
	for (int i = 0; i < (NUMELEMENTS); i++)
	{
		randArray.push_back(i);
	}
	random_shuffle(randArray.begin(), randArray.end());

	for (int i = 0; i < NUMANTS; i++)
	{
		ants[i].setLoc(randArray[i]);
		ants[i].live();
		simulation.setValue(randArray[i], ANT);
	}

	for (int i = 0; i < NUMDOODLEBUGS; i++)
	{
		doodle[i].setLoc(randArray[i + NUMANTS]);
		doodle[i].live();
		simulation.setValue(randArray[i + NUMANTS], DOODLEBUG);
	}

	cout << "/------------------------------------------------\\\n"
		<< "| 2D grid Predator-Prey simulation               |\n"
		<< "\\------------------------------------------------/\n";

	while (true)
	{
		eaten = false;
		bred = false;
		for (int i = 0; i < numDoodles; i++)
		{
			eaten = false;
			bred = false;
			currLoc = doodle[i].getLoc();
			cX = simulation.getXPos(currLoc);
			cY = simulation.getYPos(currLoc);
			if (currLoc != -1 && simulation(currLoc) == DOODLEBUG)
			{

				move = (rand() % 4) + 1;
				testLoc = simulation.xyToIndex(cX + 1, cY);
				if (simulation(testLoc) != -1
					&& simulation(testLoc) == ANT)
				{
					simulation.setValue(doodle[i].getLoc(), EMPTY);
					doodle[i].setLoc(testLoc);
					simulation.setValue(doodle[i].getLoc(), DOODLEBUG);
					doodle[i].move();
					doodle[i].eat();
					eaten = true;
				}
				testLoc = simulation.xyToIndex(cX, cY - 1);
				if (simulation(testLoc) != -1
					&& simulation(testLoc) == ANT && !eaten)
				{
					simulation.setValue(doodle[i].getLoc(), EMPTY);
					doodle[i].setLoc(testLoc);
					simulation.setValue(doodle[i].getLoc(), DOODLEBUG);
					doodle[i].move();
					doodle[i].eat();
					eaten = true;
				}
				testLoc = simulation.xyToIndex(cX - 1, cY);
				if (simulation(testLoc) != -1
					&& simulation(testLoc) == ANT && !eaten)
				{
					simulation.setValue(doodle[i].getLoc(), EMPTY);
					doodle[i].setLoc(testLoc);
					simulation.setValue(doodle[i].getLoc(), DOODLEBUG);
					doodle[i].move();
					doodle[i].eat();
					eaten = true;
				}
				testLoc = simulation.xyToIndex(cX, cY + 1);
				if (simulation(testLoc) != -1
					&& simulation(testLoc) == ANT && !eaten)
				{
					simulation.setValue(doodle[i].getLoc(), EMPTY);
					doodle[i].setLoc(testLoc);
					simulation.setValue(doodle[i].getLoc(), DOODLEBUG);
					doodle[i].move();
					doodle[i].eat();
					eaten = true;
				}
				if (move == 1)
				{
					testLoc = simulation.xyToIndex(cX + 1, cY);
				}
				else if (move == 2)
				{
					testLoc = simulation.xyToIndex(cX, cY - 1);
				}
				else if (move == 3)
				{
					testLoc = simulation.xyToIndex(cX - 1, cY);
				}
				else
				{
					testLoc = simulation.xyToIndex(cX, cY + 1);
				}
				if (!eaten)
				{
					if (testLoc != -1 && simulation(testLoc) == EMPTY)
					{
						simulation.setValue(doodle[i].getLoc(), EMPTY);
						doodle[i].setLoc(testLoc);
						simulation.setValue(doodle[i].getLoc(), DOODLEBUG);
					}
					doodle[i].move();
				}
			}
			else
			{
				doodle[i].die();
			}
			if (!eaten && doodle[i].getEatTime() >= 3)
			{
				simulation.setValue(doodle[i].getLoc(), EMPTY);
				doodle[i].die();
			}
			cX = simulation.getXPos(currLoc);
			cY = simulation.getYPos(currLoc);
			if (doodle[i].getBreedTime() > 8 && numDoodles < NUMELEMENTS)
			{
				testLoc = simulation.xyToIndex(cX + 1, cY);
				if (!bred && simulation(testLoc) != -1
					&& simulation(testLoc) == EMPTY)
				{
					doodle[i].breed();
					doodle[numDoodles].setLoc(testLoc);
					simulation.setValue(testLoc, DOODLEBUG);
					doodle[numDoodles].live();
					numDoodles++;
					bred = true;
				}
				testLoc = simulation.xyToIndex(cX, cY - 1);
				if (!bred && simulation(testLoc) != -1
					&& simulation(testLoc) == EMPTY)
				{
					doodle[i].breed();
					doodle[numDoodles].setLoc(testLoc);
					simulation.setValue(testLoc, DOODLEBUG);
					doodle[numDoodles].live();
					numDoodles++;
					bred = true;
				}
				testLoc = simulation.xyToIndex(cX - 1, cY);
				if (!bred && simulation(testLoc) != -1
					&& simulation(testLoc) == EMPTY)
				{
					doodle[i].breed();
					doodle[numDoodles].setLoc(testLoc);
					simulation.setValue(testLoc, DOODLEBUG);
					doodle[numDoodles].live();
					numDoodles++;
					bred = true;
				}
				testLoc = simulation.xyToIndex(cX, cY + 1);
				if (!bred && simulation(testLoc) != -1
					&& simulation(testLoc) == EMPTY)
				{
					doodle[i].breed();
					doodle[numDoodles].setLoc(testLoc);
					simulation.setValue(testLoc, DOODLEBUG);
					doodle[numDoodles].live();
					numDoodles++;
					bred = true;
				}
			}
		}
		for (int i = 0; i < numAnts; i++)
		{
			bred = false;
			currLoc = ants[i].getLoc();
			cX = simulation.getXPos(currLoc);
			cY = simulation.getYPos(currLoc);
			if (currLoc != -1 && simulation(currLoc) == ANT)
			{
				move = (rand() % 4) + 1;
				if (move == 1)
				{
					testLoc = simulation.xyToIndex(cX + 1, cY);
				}
				else if (move == 2)
				{
					testLoc = simulation.xyToIndex(cX, cY - 1);
				}
				else if (move == 3)
				{
					testLoc = simulation.xyToIndex(cX - 1, cY);
				}
				else
				{
					testLoc = simulation.xyToIndex(cX, cY + 1);
				}
				if (testLoc != -1 && simulation(testLoc) == EMPTY)
				{
					simulation.setValue(ants[i].getLoc(), EMPTY);
					ants[i].setLoc(testLoc);
					simulation.setValue(ants[i].getLoc(), ANT);
				}
				ants[i].move();
			}
			else
			{
				ants[i].die();
			}
			cX = simulation.getXPos(currLoc);
			cY = simulation.getYPos(currLoc);
			if (ants[i].getBreedTime() > 3 && numAnts < NUMELEMENTS)
			{
				testLoc = simulation.xyToIndex(cX + 1, cY);
				if (!bred && simulation(testLoc) != -1
					&& simulation(testLoc) == EMPTY)
				{
					ants[i].breed();
					ants[numAnts].setLoc(testLoc);
					simulation.setValue(testLoc, ANT);
					ants[numAnts].live();
					numAnts++;
					bred = true;
				}
				testLoc = simulation.xyToIndex(cX, cY - 1);
				if (!bred && simulation(testLoc) != -1
					&& simulation(testLoc) == EMPTY)
				{
					ants[i].breed();
					ants[numAnts].setLoc(testLoc);
					simulation.setValue(testLoc, ANT);
					ants[numAnts].live();
					numAnts++;
					bred = true;
				}
				testLoc = simulation.xyToIndex(cX - 1, cY);
				if (!bred && simulation(testLoc) != -1
					&& simulation(testLoc) == EMPTY)
				{
					ants[i].breed();
					ants[numAnts].setLoc(testLoc);
					simulation.setValue(testLoc, ANT);
					ants[numAnts].live();
					numAnts++;
					bred = true;
				}
				testLoc = simulation.xyToIndex(cX, cY + 1);
				if (!bred && simulation(testLoc) != -1
					&& simulation(testLoc) == EMPTY)
				{
					ants[i].breed();
					ants[numAnts].setLoc(testLoc);
					simulation.setValue(testLoc, ANT);
					ants[numAnts].live();
					numAnts++;
					bred = true;
				}
			}
		}

		simulation.displayGridASCII();

		cout << "Press Enter to continue simulation" << endl;
		discard = cin.get();
	}

	return 0;
}