#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <tuple>

#include "model_map.h"

using namespace std;
const map<string, tuple<uint16_t, uint16_t> > model = {
    {"Anbernic RG503", {0xAAAA, 0x1111} },
    {"Powkiddy RK2023", {0xBBBB, 0x1111} },
    {"Powkiddy RGB10 Max 3", {0x2222, 0x4444} },
};

string get_model() {
    string filename = "/sys/firmware/devicetree/base/model";
    ifstream inputFile(filename);

    string line;
    if (!getline(inputFile, line)) {
        exit(1);
    }
    // remove last charachter to match correctly
    line.pop_back();
    try {
        model.at(line);
    } catch (const out_of_range &) {
        cerr << "No match for model: " << get_model() << endl;
        exit(1);
    } 
    cout << "Found model name: " << line << endl;
    return line;
}

uint16_t get_vendor() {
    uint16_t vid = get<0>(model.at(get_model()));
    cout << "Vendor ID: " << vid << endl;
    return vid;
}

uint16_t get_product() {
    uint16_t pid = get<1>(model.at(get_model()));
    cout << "Product ID: " << pid << endl;
    return pid;
}
