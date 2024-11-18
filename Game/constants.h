#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <vector>
#include <string>
#include <iostream>
enum class Resource {CAFF, LAB, LEC, STD, TUT, UM};

struct Hand {
    std::vector <Resource> cards;
};

struct Producer {
    Resource prod = Resource::UM;
    int amount = 0;
};

int hsize(Hand* h);

void hclear(Hand* h);

void hadd(Hand* h, Resource r);

void hsub(Hand* h, Resource r);

int herr(Hand* h, Resource r);

class ResourceCollection {
public:
    int resources[5];

    ResourceCollection() {
        // Initialize all resources to 0
        for (int i = 0; i < 5; ++i) {
            resources[i] = 0;
        }
    }

    void inputResources() {
        std::cout << "Enter the quantities of resources (Caffeine, Lab, Lecture, Study, Tutorial):\n";

        // Loop through each resource and prompt for input
        for (int i = 0; i < 5; ++i) {
            std::cout << "Enter quantity for " << getResourceName(static_cast<Resource>(i)) << ": ";
            std::cin >> resources[i];
        }
    }

    // Function to get the name of the resource as a string
    std::string getResourceName(Resource r) const {
        switch (r) {
            case Resource::CAFF: return "Caffeine";
            case Resource::LAB: return "Lab";
            case Resource::LEC: return "Lecture";
            case Resource::STD: return "Study";
            case Resource::TUT: return "Tutorial";
            default: return "Unknown";
        }
    }

    // Function to display the resources
    void displayResources() const {
        for (int i = 0; i < 5; ++i) {
            std::cout << getResourceName(static_cast<Resource>(i)) << ": " << resources[i] << std::endl;
        }
    }

    Hand get_hand() {
        Hand temp;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < resources[i]; j++) {
                hadd(&temp, static_cast<Resource>(i));
            }
        }
        return temp;
    }
};

std::ostream& operator<<(std::ostream& os, const Resource resource);
std::ostream& operator<<(std::ostream& os, const std::vector<Resource> resources);

#endif
