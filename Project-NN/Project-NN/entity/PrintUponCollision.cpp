#include "PrintUponCollision.h"

#include <iostream>
using namespace std;


void PrintUponCollision::HandleCollision(GameObject* other) {
	cout << "I collided with an object! " << other << endl;
}