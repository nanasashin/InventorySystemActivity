#include "UISystem.hpp"

using namespace std;

int main () {
	System system;
	bool running = true;
	while (running) {
		switch (system.front_page())
		{
		case 1:
			system.add_product();
			break;
		case 2:
			system.remove_product();
			break;
		default:
			break;
		}

	}
}