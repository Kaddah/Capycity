#include <iostream>
#include <vector>
#include <set>

void placeBuilding();
void deleteArea();
void showConstructionPlan();
void menu();

class Material {
protected:
    int price;
    char *name;
public:
    Material(int price, char *name){
        this->price = price;
        this->name = name;
    }

    char *getName() {
        return name;
    }
    int getPrice(){
        return price;
    }
};

class Wood : public Material {
public:
    Wood() : Material(1, "Wood"){

    }
};

class Plastic : public Material {
public:
    Plastic() : Material(2, "Plastic"){

    }

};

class Metal : public Material {
public:
    Metal() : Material(3, "Metal"){

    }
};

class Building{
protected:
    int price;
    char label;
    char *name;
    std::vector<Material*> materials;

public:
    Building(int price, char label, char *name){
        this->price = price;
        this->label = label;
        this->name = name;
    }

    char *getName() {
        return name;
    }

    char getLabel() {
        return label;
    }

    int getPrice() {
        return price;
    }

    std::vector<Material*> getMaterials() {
        return materials;
    }
};

class WaterEnergyPlant : public Building{
public:
    WaterEnergyPlant() : Building(1, 'W', "WaterEngeryPlant"){
        materials = std::vector<Material*>();
        materials.push_back(new Wood());
        materials.push_back(new Wood());
        materials.push_back(new Plastic());
        materials.push_back(new Plastic());
        materials.push_back(new Metal());
    }
};

class SolarEnergyPlant : public Building{
public:
    SolarEnergyPlant() : Building(1, 'S', "SolarEnegeryPlant"){
        materials = std::vector<Material*>();
        materials.push_back(new Plastic());
        materials.push_back(new Plastic());
        materials.push_back(new Plastic());
        materials.push_back(new Metal());
        materials.push_back(new Metal());
    }
};

class WindEnergyPlant : public Building{
public:
    WindEnergyPlant() : Building(1, 'I', "WindEnergyPlant"){
        materials = std::vector<Material*>();
        materials.push_back(new Wood());
        materials.push_back(new Wood());
        materials.push_back(new Plastic());
        materials.push_back(new Metal());
        materials.push_back(new Metal());
    }
};

Building *menuBuilding();

int length;
int width;

class CapycitySim {
private:
    int length;
    int width;
    Building ***plan;

    bool isValidRectangle(int x, int y, int length, int width) {
        return 0 <= x
               && x < this->length
               && 0 <= y
               && y < this->width
               && 0 <= length
               && (x + length) <= this->length
               && 0 <= width
               && (y + width) <= this->width;
    }

public:
    CapycitySim(int length, int width) {
        this->length = length;
        this->width = width;

        plan = new Building **[length];
        for (int x = 0; x < length; x++) {
            plan[x] = new Building*[width];
            for (int y = 0; y < width; y++) {
                plan[x][y] = nullptr;
            }
        }
    }

    bool placeBuilding(Building * building, int startPositionX, int startPositionY, int length, int width) {
        if (!isValidRectangle(startPositionX,startPositionY, length, width)) {
            return false;
        }

        //check if empty
        for (int i = startPositionX; i < (startPositionX + length); i++) {
            for (int j = startPositionY; j < (startPositionY + width); j++) {
                if (plan[i][j] != nullptr) {
                    return false;
                }
            }
        }

        //place building
        for (int i = startPositionX; i < (startPositionX + length); i++) {
            for (int j = startPositionY; j < (startPositionY + width); j++) {
                plan[i][j] = building;
            }
        }
        return true;
    }

    bool deleteArea(int startPositionX, int startPositionY, int x, int y) {
        if (!isValidRectangle(startPositionX,startPositionY, x, y)) {
            return false;
        }

        for (int i = startPositionX; i < (startPositionX + x); i++) {
            for (int j = startPositionY; j < (startPositionY + y); j++) {
                // hehe memory leak, but i don't care
                plan[i][j] = nullptr;
            }
        }
        return true;
    }

    Building  ***getPlan() {
        return plan;
    }

};

CapycitySim *sim = nullptr;

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "Usage: " << std::endl;
        std::cout << "\tcapycity <length> <width>" << std::endl;
        return 1;
    }

    try {
        length = std::stoi(argv[1]);
        width = std::stoi(argv[2]);

    }
    catch (std::invalid_argument const &ex) {
        std::cout << "Input must be of 2 integer numbers." << std::endl;
        return 2;
    }
    catch (std::out_of_range const &ex) {
        std::cout << "The number is too big." << std::endl;
        return 3;
    }

    sim = new CapycitySim(length, width);

    std::cout << "Welcome to Capycity, please select an option: " << std::endl;

    while (true) {
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
        default:
            std::cout << "Not a valid option" << std::endl;
    }
}

Building *menuBuilding() {
    std::cout << "Please select a building to place:" << std::endl;
    std::cout << "W) Water energy plant" << std::endl;
    std::cout << "S) Solar energy plant" << std::endl;
    std::cout << "I) Wind energy plant" << std::endl;
    std::cout << "B) Back" << std::endl;

    char buildingSelected;
    std::cin >> buildingSelected;

    switch (toupper(buildingSelected)) {
        case 'W':
            return new WaterEnergyPlant();
            break;
        case 'S':
            return new SolarEnergyPlant();
            break;
        case 'I':
            return new WindEnergyPlant();
            break;
        case 'B':
            menu();
        default:
            std::cout << "Not a valid option" << std::endl;
            menuBuilding();
    }
}

int getInteger(char* prompt){
    int result;
    do {
        std::cout << prompt << std::endl;
        std::cin >> result;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Invalid input: must be a number" << std::endl;
        }
    } while(std::cin.fail());
    return result;
}

void placeBuilding() {

    Building * building = menuBuilding();

    int startPositionX = getInteger("Enter a start position X: ");
    int startPositionY = getInteger(("Enter a start position Y: "));
    int x = getInteger("Enter the length of the building: ");
    int y = getInteger(("Enter the width of the building: "));

    bool placed = sim->placeBuilding(building, startPositionX, startPositionY, x, y);
    if (!placed) {
        std::cout << "This place is already occupied or input is invalid!" << std::endl;
        placeBuilding();
    }

}

void deleteArea() {

    std::cout << "Delete Area: " << std::endl;

    int startPositionX = getInteger("Enter a start position X: ");
    int startPositionY = getInteger(("Enter a start position Y: "));
    int x = getInteger("Enter the length of the building: ");
    int y = getInteger(("Enter the width of the building: "));

    bool deleted = sim->deleteArea(startPositionX, startPositionY, x, y);
    if(!deleted){
        std::cout << "This place is already empty or input is invalid!" << std::endl;
        deleteArea();
    }

}

void showConstructionPlan() {
    std::set<Building*> uniqueBuildings;

    for (int row = 0; row < width; row++) {
        for (int column = 0; column < length; column++) {
            Building *building = sim->getPlan()[column][row];
            if (building == nullptr) {
                std::cout << 'E';
            } else {
                uniqueBuildings.insert(building);
                std::cout << building->getLabel();
            }

        }
        std::cout << std::endl;
    }

    int totalCost = 0;
    for(Building *building : uniqueBuildings) {
        int totalCostForBuilding = building->getPrice();
        for(Material* material : building->getMaterials()) {
            totalCostForBuilding += material->getPrice();
        }
        std::cout << building->getName() << " for " << totalCostForBuilding << " geld" << std::endl;
        for(Material* material : building->getMaterials()) {
            std::cout << "  - " << material->getName() << " for " << material->getPrice() << " geld" << std::endl;
        }
        totalCost += totalCostForBuilding;
    }

    std::cout << "Total cost " << totalCost << " geld" << std::endl;
}

//so viel schoki hier :o