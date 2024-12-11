#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <string>
#include <map>

//Object nói chung trong Map
class MapObject {
private:
    int x, y;
    std::string type;
public:
    MapObject(int x, int y, const std::string &type) : x(x), y(y), type(type) {}
};

class BitmapMap {
private:
    std::string filePath;
    int width;
    int height;
    int bitDepth;
    int rowPadding;
    std::vector<uint8_t> pixelData;
    //Định nghĩa Object lấy tọa độ từ file lưu
    std::map<std::pair<int, int>, std::string> coordinateMap;
public:
    BitmapMap(const std::string &filePath) : filePath(filePath), width(0), height(0), bitDepth(0), rowPadding(0) {}
    // Load BMP file
    bool loadBitmap() {
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return false;
        }
        uint8_t header[54];
        file.read(reinterpret_cast<char *>(header), 54);
        //Xét Dimensions của Bit
        width = *reinterpret_cast<int *>(&header[18]);
        height = *reinterpret_cast<int *>(&header[22]);
        bitDepth = *reinterpret_cast<uint16_t *>(&header[28]);
        //Mặc định chỉ có thể đọc 24 hoặc 32
        if (bitDepth != 24 && bitDepth != 32) {
            std::cerr << "Unsupported BMP bit depth: " << bitDepth << std::endl;
            return false;
        }
        rowPadding = (4 - (width * (bitDepth / 8)) % 4) % 4;
        pixelData.resize((width * (bitDepth / 8) + rowPadding) * height);
        file.read(reinterpret_cast<char *>(pixelData.data()), pixelData.size());
        file.close();
        return true;
    }
    //Định vị Object trong Map dùng tọa độ
    void mapObjects() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int pixelIndex = (y * (width * (bitDepth / 8) + rowPadding)) + (x * (bitDepth / 8));
                //Logic Xử lý Object (Block/Character)
            }
        }
    }
    //Lấy đc Map của vật thể
    const std::map<std::pair<int, int>, std::string> &getCoordinateMap() const {
        return coordinateMap;
    }
};