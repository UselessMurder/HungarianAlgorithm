#include "Graph.h"

#define vertex_size 90
#define vertex_offset 10


Graph::Graph()
{
	height_width.first = 0;
	height_width.second = 0;
	count = 0;
	vcount = 0;
	ready = false;
}
Graph::~Graph()
{

}

bool Graph::set_parameters(std::pair<int, int> input_height_width, int input_count, int input_vcount)
{
	if (input_height_width.first > 0 && input_height_width.second > 0 && input_count >= 0 && input_vcount >= 0)
	{
		height_width = input_height_width;
		count = input_count;
		vcount = input_vcount;
		ready = true;
		return true;
	}
	return false;
}
bool Graph::get_coordinates(std::pair<int, int> &output_height_width, std::vector<std::pair<int, int>> &output_vertexs, std::vector<std::pair<int, int>> &output_v_vertexs)
{
	if (ready)
	{
		if (count > vcount)
		{
			output_vertexs = this->measure(count, false);
			output_v_vertexs = this->measure(vcount, true);
		}
		else
		{
			output_v_vertexs = this->measure(vcount, true);
			output_vertexs = this->measure(count, false);
		}
		output_height_width = height_width;
		return true;
	}
	return false;
}

std::vector<std::pair<int, int>> Graph::measure(int input_count, bool up)
{
	std::vector<std::pair<int, int>> result;
	if (input_count == 0)
		return result;
	if (height_width.first < ((vertex_size + vertex_offset) * 5))
		height_width.first = (vertex_size + vertex_offset) * 5;
	this->check_width(input_count);
	int y = 0;
	if (up)
		y = vertex_offset;
	else
		y = height_width.first - (vertex_offset + vertex_size);
	for (int i = 0;i < input_count;i++)
		result.push_back(std::pair<int, int>(vertex_offset + (vertex_size + vertex_offset) * i, y));
	return result;
}

void Graph::check_width(int input_count)
{
	int width = height_width.second;
	for (int i = 0;i < input_count;i++)
		width -= (vertex_size + vertex_offset);
	if (width <= 0)
		height_width.second += (-width + vertex_offset);
}