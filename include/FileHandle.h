/*#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<map>

using namespace std;

class FileHandle {
private:
    // A map to store different types of data (settings, game state, map data)
    map<string, map<string, string>> data;
public:
    // Load data from a file based on the specified type(settings, game, map)
    void load(const string& fileName, const string& type);

    // Save data to a file based on the specified type (settings, game, map)   
    void save(const string& fileName, const string& type) const;

    // Get a specific setting by key
    const string& getSetting(const string& key) const;

    // Set a specific setting by key and value
    void setSetting(const string& key, const string& value);
};*/