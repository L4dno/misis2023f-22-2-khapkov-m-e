#include <vector>

class Grid {
private:
    std::vector<Hexagon> grid;
public:
    void init();
    void AddHexToGrid();
};
std::array<int, 3> GetNearestHexesToPoint(std::vector<Hexagon>& grid, Vertex p);
void InitGrid(std::vector<Hexagon>& grid);