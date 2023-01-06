#include <iostream>

enum AreaType: char {
	EMPTY = 'E',
	WATER_ENERGY_PLANT = 'W',
	SOLAR_ENERGY_PLANT = 'S',
	WIND_ENERGY_PLANT = 'I',
};

void placeBuilding();
void deleteArea();
void showConstructionPlan();
void menu();
AreaType menuBuilding();


int length;
int width;
AreaType** plan;

int main(int argc, char** argv) {


	if(argc != 3){
        std::cout << "Usage: " << std::endl;
        std::cout << "\tcapycity <length> <width>" << std::endl;
        return 1;
    }


    try{
        length = std::stoi(argv[1]);
        width = std::stoi(argv[2]);
    }
    catch(std::invalid_argument const& ex){
        std::cout << "Input must be of 2 integer numbers." << std::endl;
        return 2;
    }
    catch(std::out_of_range const& ex){
        std::cout << "The number is too big." << std::endl;
        return 3;
    }

    plan = new AreaType * [length];
    for(int x = 0; x < length; x++){
        plan[x] = new AreaType[width];
        for(int y = 0; y < length; y++){
            plan[x][y] = AreaType::EMPTY;
        }
    }
    std::cout << "Welcome to Capycity, please select an option: " << std::endl;

    while(true){
        menu();
    }
}

void menu() {
	std::cout << "1) Place Building" << std::endl;
	std::cout << "2) Delete Area" << std::endl;
	std::cout << "3) Show current construction plan" << std::endl;
	std::cout << "4) Quit" << std::endl;
	std::cout << std::endl;

	int option;
	std::cin >> option;

	switch (option) {
	case 1:
        placeBuilding();
		break;
	case 2:
        deleteArea();
		break;
	case 3:
        showConstructionPlan();
		break;
	case 4:
        exit(0);
	    default: std::cout << "Not a valid option" << std::endl;
	}
}

AreaType menuBuilding() {
	std::cout << "Please select a building to place:" << std::endl;
	std::cout << "W) Water energy plant" << std::endl;
	std::cout << "S) Solar energy plant" << std::endl;
	std::cout << "I) Wind energy plant" << std::endl;
	std::cout << "B) Back" << std::endl;

	char buildingSelected;
	std::cin >> buildingSelected;

	switch (toupper(buildingSelected)) {
	case 'W': return WATER_ENERGY_PLANT;
		break;
	case 'S': return SOLAR_ENERGY_PLANT;
		break;
	case 'I': return WIND_ENERGY_PLANT;
		break;
	case 'B': menu();
    default: std::cout << "Not a valid option" << std::endl;
		menuBuilding();
	}
}

void placeBuilding() {

	AreaType selectedBuildingType = menuBuilding();

    int startPositionX;
    int startPositionY;
    int x;
    int y;

    //Position X
    while(true) {
        std::cout << "Enter a start position X: " << std::endl;
        if(!(std::cin >> startPositionX)){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
            continue;
        }
        if(0 <= startPositionX  && startPositionX < length){
            break;
        }
        else{
            std::cout << "Please enter a number between 0 and " << (length - 1) << std::endl;
        }

    }

    //Position Y
    while(true) {
        std::cout << "Enter a start position Y: " << std::endl;
        if(!(std::cin >> startPositionY)){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
            continue;
        }
        if(0 <= startPositionY && startPositionY < width){
            break;
        }
        else{
            std::cout << "Please enter a number between 0 and " << (width - 1) << std::endl;
        }

    }

    //x = length
    while(true) {
        std::cout << "Enter the length of the Building: " << std::endl;
        if(!(std::cin >> x)){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
            continue;
        }
        if(0 <= (startPositionX + x) && (startPositionX + x) < length){
            break;
        }
        else{
            std::cout << "Please enter a number between 0 and " << (length - 1) << std::endl;
        }

    }

    //y = width
    while(true) {
        std::cout << "Enter the width of the Building: " << std::endl;
        if(!(std::cin >> y)){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
            continue;
        }
        if(0 <= (startPositionY + y) && (startPositionY + y) < length){
            break;
        }
        else{
            std::cout << "Please enter a number between 0 and " << (width - 1) << std::endl;
        }

    }

    //check if empty
    for(int i = startPositionX; i <= (startPositionX + x); i++){
        for(int j = startPositionY; j <= (startPositionY + y); j++){
            if(plan[i][j] != EMPTY){
                std::cout << "Space is already occupied!" << std::endl;
                return placeBuilding();
            }
        }
    }

    //place building
    for(int i = startPositionX; i <= (startPositionX + x); i++){
        for(int j = startPositionY; j <= y; j++){
            plan[i][j] = selectedBuildingType;
        }
    }
}

void deleteArea() {

    std::cout << "Delete Area: " << std::endl;

    int startPositionX;
    int startPositionY;
    int x;
    int y;

    //Position X
    while(true) {
        std::cout << "Enter a start position X: " << std::endl;
        if(!(std::cin >> startPositionX)){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
            continue;
        }
        if(0 <= startPositionX  && startPositionX < length){
            break;
        }
        else{
            std::cout << "Please enter a number between 0 and " << (length - 1) << std::endl;
        }

    }

    //Position Y
    while(true) {
        std::cout << "Enter a start position Y: " << std::endl;
        if(!(std::cin >> startPositionY)){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
            continue;
        }
        if(0 <= startPositionY && startPositionY < width){
            break;
        }
        else{
            std::cout << "Please enter a number between 0 and " << (width - 1) << std::endl;
        }

    }

    //x = length
    while(true) {
        std::cout << "Enter the length of the Building: " << std::endl;
        if(!(std::cin >> x)){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
            continue;
        }
        if(0 <= (startPositionX + x) && (startPositionX + x) < length){
            break;
        }
        else{
            std::cout << "Please enter a number between 0 and " << (length - 1) << std::endl;
        }

    }

    //y = width
    while(true) {
        std::cout << "Enter the width of the Building: " << std::endl;
        if(!(std::cin >> y)){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
            continue;
        }
        if(0 <= (startPositionY + y) && (startPositionY + y) < length){
            break;
        }
        else{
            std::cout << "Please enter a number between 0 and " << (width - 1) << std::endl;
        }

    }

    //clear area
    for(int i = startPositionX; i <= (startPositionX + x); i++){
        for(int j = startPositionY; j <= y; j++){
            if(plan[i][j] != EMPTY){
                plan[i][j] = EMPTY;
            }
        }
    }
}

void showConstructionPlan() {
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            std::cout << plan[i][j];
        }
        std::cout << std::endl;
    }
}

//hilfe ich werde in einer schokoladenfabrik gefangen gehalten