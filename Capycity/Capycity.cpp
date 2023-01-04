#include <iostream>

enum AreaType {
	EMPTY = ' ',
	WATER_ENERGY_PLANT = 'W',
	SOLAR_ENERGY_PLANT = 'S',
	WIND_ENERGY_PLANT = 'I',
};

void placeBuilding();
void deleteArea();
void showConstructionPlan();
void menu();
AreaType menuBuilding();


int main(int argc, char** argv) {

	/*
	std::cout << "Welcome to Capycity" << '\n';
	std::cout << "First we need to figure out a size for our city!" << '\n';

	int length;
	int width;

	std::cout << "Please enter a length: " << '\n';
	std::cin >> length;
	std::cout << "Please enter a width: " << '\n';
	std::cin >> width;

	int areaSize[length][width];*/
	//als komandozeilenargument




}

void menu() {

	std::cout << "Welcome to Capycity, please select an option: " << '\n';
	std::cout << "1) Place Building" << '\n';
	std::cout << "2) Delete Area" << '\n';
	std::cout << "3) Show current construction plan" << '\n';
	std::cout << "4) Quit" << '\n';
	std::cout << '\n';

	char option;
	std::cin >> option;

	switch (option) {
	case 1: placeBuilding(); //das funktioniert ohne übergabe natürlich auch nicht ;-;
		break;
	case 2: deleteArea();
		break;
	case 3: showConstructionPlan();
		break;
	case 4: exit(0);
	default: std::cout << "Not a valid option" << '\n';
	}
}

AreaType menuBuilding() {
	std::cout << "Please select a building to place:" << '\n';
	std::cout << "W) Water energy plant" << '\n';
	std::cout << "S) Solar energy plant" << '\n';
	std::cout << "I) Wind energy plant" << '\n';
	std::cout << "B) Back" << '\n';

	char buildingSelected;
	std::cin >> buildingSelected;

	switch (buildingSelected) {
	case 'W': return WATER_ENERGY_PLANT;
		break;
	case 'S': return SOLAR_ENERGY_PLANT;
		break;
	case 'I': return WIND_ENERGY_PLANT;
		break;
	case 'B': menu();
	default: std::cout << "Not a valid option";
		menuBuilding();
	}
}

void placeBuilding(AreaType type, int length, int width, int position) {
	//need:
	//startpunkt
	//ist der platz überhaupt frei

	AreaType selectedBuildingType = menuBuilding();




}

void deleteArea() {
	//need:
	//wenn feld besetzt löschen
	//löschen = verkleinern

}

void showConstructionPlan() {
	//need:
	//wie groß ist feld eingabe
	//welche gebäude sind gebaut
	//ausgabe

}

//alles andere übersteigt meine kompetenzen
//aber zumindest ist es mein code :)