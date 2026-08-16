#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct RoomInfo {
    int room_number;
    std::string room_type;
    int beds;
};

int main() {
    // Define rooms and bed counts – adjust to match the expected total (38)
    std::vector<RoomInfo> rooms = {
        {101, "General", 5},
        {102, "General", 6},
        {103, "General", 5},
        {201, "Private", 8},
        {202, "Private", 7},
        {301, "ICU", 7}
    };

    std::ofstream outfile("data/bed_config.json");
    if (!outfile) {
        std::cerr << "Failed to open output file" << std::endl;
        return 1;
    }
    outfile << "[\n";
    for (size_t i = 0; i < rooms.size(); ++i) {
        const auto &r = rooms[i];
        outfile << "  {\"room_number\": " << r.room_number
                << ", \"room_type\": \"" << r.room_type << "\", \"beds\": " << r.beds << "}";
        if (i + 1 < rooms.size()) outfile << ",";
        outfile << "\n";
    }
    outfile << "]\n";
    std::cout << "Bed configuration written to data/bed_config.json" << std::endl;
    return 0;
}
