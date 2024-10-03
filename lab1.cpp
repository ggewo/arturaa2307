#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Pipe {
    std::string name;
    double length;
    double diameter;
    bool underRepair;

    void input() {
        std::cout << "Enter pipe name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter pipe length: ";
        std::cin >> length;
        std::cout << "Enter pipe diameter: ";
        std::cin >> diameter;
        std::cout << "Is the pipe under repair? (1 - yes, 0 - no): ";
        std::cin >> underRepair;
    }

    void output() const {
        std::cout << "Pipe name: " << name << std::endl;
        std::cout << "Length: " << length << " km" << std::endl;
        std::cout << "Diameter: " << diameter << " m" << std::endl;
        std::cout << "Under repair: " << (underRepair ? "Yes" : "No") << std::endl;
    }

    void changeRepairStatus() {
        std::cout << "Enter new repair status (1 - yes, 0 - no): ";
        std::cin >> underRepair;
    }
};

struct CompressorStation {
    std::string name;
    int totalShops;
    int activeShops;
    double efficiency;

    void input() {
        std::cout << "Enter station name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter total number of shops: ";
        std::cin >> totalShops;
        std::cout << "Enter number of active shops: ";
        std::cin >> activeShops;
        while (activeShops > totalShops || activeShops < 0) {
            std::cout << "Invalid value. Active shops cannot exceed total number or be less than 0." << std::endl;
            std::cout << "Enter number of active shops: ";
            std::cin >> activeShops;
        }
        std::cout << "Enter station efficiency: ";
        std::cin >> efficiency;
    }

    void output() const {
        std::cout << "Station name: " << name << std::endl;
        std::cout << "Total number of shops: " << totalShops << std::endl;
        std::cout << "Active shops: " << activeShops << std::endl;
        std::cout << "Efficiency: " << efficiency << std::endl;
    }

    void startShop() {
        if (activeShops < totalShops) {
            activeShops++;
            std::cout << "Shop started. Active shops: " << activeShops << std::endl;
        } else {
            std::cout << "All shops are already active." << std::endl;
        }
    }

    void stopShop() {
        if (activeShops > 0) {
            activeShops--;
            std::cout << "Shop stopped. Active shops: " << activeShops << std::endl;
        } else {
            std::cout << "No active shops to stop." << std::endl;
        }
    }
};

void saveToFile(const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& stations) {
    std::ofstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file for saving!" << std::endl;
        return;
    }

    file << pipes.size() << std::endl;
    for (const auto& pipe : pipes) {
        file << pipe.name
             << std::endl << pipe.length
             << std::endl << pipe.diameter
             << std::endl << pipe.underRepair << std::endl;
    }

    file << stations.size() << std::endl;
    for (const auto& station : stations) {
        file << station.name
             << std::endl << station.totalShops
             << std::endl << station.activeShops
             << std::endl << station.efficiency << std::endl;
    }

    file.close();
    std::cout << "Data successfully saved." << std::endl;
}

void loadFromFile(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations) {
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file for loading!" << std::endl;
        return;
    }

    size_t pipeCount, stationCount;
    file >> pipeCount;
    pipes.clear();
    pipes.resize(pipeCount);
    file.ignore();
    for (auto& pipe : pipes) {
        std::getline(file, pipe.name);
        file >> pipe.length >> pipe.diameter >> pipe.underRepair;
        file.ignore();
    }

    file >> stationCount;
    stations.clear();
    stations.resize(stationCount);
    file.ignore();
    for (auto& station : stations) {
        std::getline(file, station.name);
        file >> station.totalShops >> station.activeShops >> station.efficiency;
        file.ignore();
    }

    file.close();
    std::cout << "Data successfully loaded." << std::endl;
}

int main() {
    std::vector<Pipe> pipes;
    std::vector<CompressorStation> stations;
    int choice;

    while (true) {
        std::cout << "1. Add pipe" << std::endl;
        std::cout << "2. Add compressor station" << std::endl;
        std::cout << "3. View all objects" << std::endl;
        std::cout << "4. Change pipe repair status" << std::endl;
        std::cout << "5. Start/Stop shop" << std::endl;
        std::cout << "6. Save" << std::endl;
        std::cout << "7. Load" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {
                Pipe pipe;
                pipe.input();
                pipes.push_back(pipe);
                break;
            }
            case 2: {
                CompressorStation station;
                station.input();
                stations.push_back(station);
                break;
            }
            case 3: {
                std::cout << "Pipes:" << std::endl;
                for (const auto& pipe : pipes) {
                    pipe.output();
                    std::cout << "----------------------" << std::endl;
                }
                std::cout << "Compressor stations:" << std::endl;
                for (const auto& station : stations) {
                    station.output();
                    std::cout << "----------------------" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "Enter the pipe index for editing: ";
                size_t index;
                std::cin >> index;
                if (index < pipes.size()) {
                    pipes[index].changeRepairStatus();
                } else {
                    std::cerr << "Invalid index." << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "Enter the compressor station index for editing: ";
                size_t index;
                std::cin >> index;
                if (index < stations.size()) {
                    std::cout << "1. Start shop" << std::endl;
                    std::cout << "2. Stop shop" << std::endl;
                    std::cout << "Choose an option: ";
                    int action;
                    std::cin >> action;
                    if (action == 1) {
                        stations[index].startShop();
                    } else if (action == 2) {
                        stations[index].stopShop();
                    } else {
                        std::cerr << "Invalid option." << std::endl;
                    }
                } else {
                    std::cerr << "Invalid index." << std::endl;
                }
                break;
            }
            case 6: {
                saveToFile(pipes, stations);
                break;
            }
            case 7: {
                loadFromFile(pipes, stations);
                break;
            }
            default:
                std::cerr << "Invalid option. Try again." << std::endl;
        }
    }

    return 0;
}

