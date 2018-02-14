#include "PhysicsSceneApp.h"
PhysicsSceneApp* dirty;

int main() {
	
	// allocation
	auto app = new PhysicsSceneApp();
	dirty = app;
	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}