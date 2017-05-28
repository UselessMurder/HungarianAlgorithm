#include <vector>



class Graph {
private:
	std::pair<int, int> height_width;

	int count;
	int vcount;

	bool ready;

	std::vector<std::pair<int, int>> measure(int input_count , bool up);

	void check_width(int input_count);
public:
	Graph();
	~Graph();

	bool set_parameters(std::pair<int,int> input_height_width, int input_count, int input_vcount);
	bool get_coordinates(std::pair<int, int> &output_height_width, std::vector<std::pair<int, int>> &output_vertexs, std::vector<std::pair<int, int>> &output_v_vertexs);
};
