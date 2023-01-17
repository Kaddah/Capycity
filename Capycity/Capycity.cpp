#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>

/**
 * Es wurde Carlas Methode genutzt, weil eine auslagerung in eine extra Klasse bei diesem Umfang nicht viel Sinn macht
 */

void placeBuilding();
void deleteArea();
void showConstructionPlan();
void menu();


class Material {
protected:
    int price;
    char* name;
public:
    Material(int price, char* name) {
        this->price = price;
        this->name = name;
    }

    char* getName() {
        return name;
    }
    int getPrice() {
        return price;
    }
};

class Wood : public Material {
public:
    Wood() : Material(1, "Wood") {

    }
};

class Plastic : public Material {
public:
    Plastic() : Material(2, "Plastic") {
    }

};

class Metal : public Material {
public:
    Metal() : Material(3, "Metal") {

    }
};

class Building {
protected:
    int price;
    char label;
    char* name;
    std::map<Material*, int> materials;
    int capacity;

public:
    Building(int price, char label, char* name, int capacity) {
        this->price = price;
        this->label = label;
        this->name = name;
        this->capacity = capacity;
    }

    char* getName() {
        return name;
    }

    char getLabel() {
        return label;
    }

    int getPrice() {
        return price;
    }
    int getCapacity() {
        return capacity;
    }

    int getTotalCost() {
        int totalCost = price;
        for (auto iterator : materials) {
            auto material = iterator.first;
            auto count = iterator.second;
            totalCost += material->getPrice() * count;
        }
        return totalCost;
    }

    std::map<Material*, int> getMaterials() {
        return materials;
    }
};

class WaterEnergyPlant : public Building {
public:
    WaterEnergyPlant() : Building(1, 'W', "WaterEngeryPlant", 20) {
        materials = std::map<Material*, int>();
        materials.insert({ new Wood(), 2 });
        materials.insert({ new Plastic(), 2 });
        materials.insert({ new Metal(), 1 });
    }

};

class SolarEnergyPlant : public Building {
public:
    SolarEnergyPlant() : Building(1, 'S', "SolarEnegeryPlant", 10) {
        materials = std::map<Material*, int>();
        materials.insert({ new Plastic(), 3 });
        materials.insert({ new Metal(), 2 });
    }

};

class WindEnergyPlant : public Building {
public:
    WindEnergyPlant() : Building(1, 'I', "WindEnergyPlant", 30) {
        materials = std::map<Material*, int>();
        materials.insert({ new Wood(), 2 });
        materials.insert({ new Plastic(), 1 });
        materials.insert({ new Metal(), 2 });
    }
};

class Blueprint {
private:
    const int length;
    const int width;
    Building*** plan;

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

    Blueprint(int length, int width) :length(length), width(width) {

        plan = new Building * *[length];
        for (int x = 0; x < length; x++) {
            plan[x] = new Building * [width];
            for (int y = 0; y < width; y++) {
                plan[x][y] = nullptr;
            }
        }
    }

    ~Blueprint() {
        for (int x = 0; x < length; x++) {
            for (int y = 0; y < width; y++) {
                delete plan[x][y];
            }
            delete plan[x];
        }
        delete plan;
    }
    bool placeBuilding(Building* building, int startPositionX, int startPositionY, int length, int width) {
        if (!isValidRectangle(startPositionX, startPositionY, length, width)) {
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
        if (!isValidRectangle(startPositionX, startPositionY, x, y)) {
            return false;
        }

        for (int i = startPositionX; i < (startPositionX + x); i++) {
            for (int j = startPositionY; j < (startPositionY + y); j++) {
                plan[i][j] = nullptr;
            }
        }
        return true;
    }

    Building*** getPlan() {
        return plan;
    }

    float getK() {
        float k = 0;
        int capacity = 0;
        int price = 0;
        int area = width * length;


        for (int x = 0; x < length; x++) {
            for (int y = 0; y < width; y++) {
                if (plan[x][y] == nullptr) {
                    continue;
                }
                capacity += plan[x][y]->getCapacity();
                price += plan[x][y]->getPrice();



            }
        }
        if (price * area != 0) {
            k = (float)capacity / (float)(price * area);
        }
        return k;

    }

    bool operator()(Blueprint& blueprint) {
        if (length != blueprint.length || width != blueprint.width) {
            return false;
        }
        for (int x = 0; x < length; x++) {
            for (int y = 0; y < width; y++) {
                if (plan[x][y] == blueprint.plan[x][y] && plan[x][y] == nullptr) {
                    continue;
                }
                if (plan[x][y] == nullptr && blueprint.plan[x][y] != nullptr || plan[x][y] != nullptr && blueprint.plan[x][y] == nullptr) {
                    return false;
                }
                if (plan[x][y]->getLabel() == blueprint.plan[x][y]->getLabel()) {
                    continue;
                }
                return false;
            }
        }
        return true;
    }
};


Building* menuBuilding();

int length;
int width;

class CapycitySim {
    const int length;
    const int width;
    Blueprint* blueprint;
public:
    CapycitySim(int length, int width) : length(length), width(width) {
        addBlueprint();

    }

    std::vector<Blueprint*> blueprints;



    void menu() {
        std::cout << "1) Add new construction plan" << std::endl;
        std::cout << "2) Place Building" << std::endl;
        std::cout << "3) Delete Area" << std::endl;
        std::cout << "4) Show current construction plan" << std::endl;
        std::cout << "5) Quit" << std::endl;
        std::cout << std::endl;

        int option;
        std::cin >> option;

        switch (option) {
        case 1:
            addBlueprint();
            break;
        case 2:
            placeBuilding();
            break;
        case 3:
            deleteArea();
            break;
        case 4:
            std::sort(blueprints.begin(), blueprints.end(), [](Blueprint* a, Blueprint* b) { return a->getK() > b->getK(); });
            for (auto blueprint : blueprints) {
                showConstructionPlan(blueprint);
            }
            break;
        case 5:
            exit(0);
        default:
            std::cout << "Not a valid option" << std::endl;
        }
    }
    void addBlueprint() {
        int i = 0;
        for (auto blueprint : blueprints) {
            if (this->blueprint != blueprint && this->blueprint ->operator()(*blueprint)) {
                std::cout << "This Plan already exists." << std::endl;
                blueprints.erase(blueprints.begin() + i);
                break;
            }
            i++;

        }

        Blueprint* blueprint = new Blueprint(length, width);
        blueprints.push_back(blueprint);
        this->blueprint = blueprint;

    }
    int getInteger(char* prompt) {
        int result;
        do {
            std::cout << prompt << std::endl;
            std::cin >> result;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore();
                std::cerr << "Invalid input: must be a number" << std::endl;
            }
        } while (std::cin.fail());
        return result;
    }

    void placeBuilding() {

        Building* building = menuBuilding();

        int startPositionX = getInteger("Enter a start position X: ");
        int startPositionY = getInteger(("Enter a start position Y: "));
        int x = getInteger("Enter the length of the building: ");
        int y = getInteger(("Enter the width of the building: "));

        bool placed = blueprint->placeBuilding(building, startPositionX, startPositionY, x, y);
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

        bool deleted = blueprint->deleteArea(startPositionX, startPositionY, x, y);
        if (!deleted) {
            std::cout << "This place is already empty or input is invalid!" << std::endl;
            deleteArea();
        }

    }

    void showConstructionPlan(Blueprint* blueprint) {
        std::set<Building*> uniqueBuildings;

        for (int row = 0; row < width; row++) {
            for (int column = 0; column < length; column++) {
                Building* building = blueprint->getPlan()[column][row];
                if (building == nullptr) {
                    std::cout << 'E';
                }
                else {
                    uniqueBuildings.insert(building);
                    std::cout << building->getLabel();
                }

            }
            std::cout << std::endl;
        }

        int totalCost = 0;

        std::cout << "Index: " << blueprint->getK() << std::endl;
        for (Building* building : uniqueBuildings) {
            int totalCostForBuilding = building->getTotalCost();
            std::cout << building->getName() << " for " << totalCostForBuilding << " geld" << std::endl;
            for (auto iter : building->getMaterials()) {
                auto material = iter.first;
                auto count = iter.second;
                std::cout << "  - " << count << "x " << material->getName() << " for " << material->getPrice() << " geld" << std::endl;
            }
            totalCost += totalCostForBuilding;
        }

        std::cout << "Total cost " << totalCost << " geld" << std::endl;
    }



};



int main(int argc, char** argv) {


    if (argc != 3) {
        std::cout << "Usage: " << std::endl;
        std::cout << "\tcapycity <length> <width>" << std::endl;
        return 1;
    }

    try {
        length = std::stoi(argv[1]);
        width = std::stoi(argv[2]);

    }
    catch (std::invalid_argument const& ex) {
        std::cout << "Input must be of 2 integer numbers." << std::endl;
        return 2;
    }
    catch (std::out_of_range const& ex) {
        std::cout << "The number is too big." << std::endl;
        return 3;
    }

    CapycitySim sim(length, width);

    std::cout << "Welcome to Capycity, please select an option: " << std::endl;

    while (true) {
        sim.menu();
    }
}



Building* menuBuilding() {
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
        return nullptr;
    default:
        std::cout << "Not a valid option" << std::endl;
        menuBuilding();
    }
}



//zu viel schoki (rest in piece)