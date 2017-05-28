#include "Hungarian.h"
#include <chrono>

Hungarian::Hungarian()
{
	good_values = false;

	time_ready = false;
	time = 0;

	height = 0;
	width = 0;
}
Hungarian::~Hungarian()
{

}

bool Hungarian::set_value(std::vector<std::vector<int>> input_values)
{
	if (this->control_values(input_values))
	{
		values = input_values;
		this->set_height_and_width();
		good_values = true;
		time = 0;
		time_ready = false;
		return true;
	}
	return false;
}

bool Hungarian::control_values(std::vector<std::vector<int>> &input_values)
{
	if (input_values.size() > 0)
	{
		if (input_values[0].size() > 0)
		{
			if (this->control_width(input_values))
			{
				if(input_values.size()<=input_values[0].size())
					return true;
			}
		}
	}
	return false;
}
bool Hungarian::control_width(std::vector<std::vector<int>> &input_values)
{
	unsigned int general_width = input_values[0].size();
	for (unsigned int i = 0; i < input_values.size(); i++)
	{
		if (input_values[i].size() != general_width)
			return false;
	}
	return true;
}

void Hungarian::set_height_and_width()
{
	height = values.size();
	width = values[0].size();
}

bool Hungarian::get_result(bool max, std::vector<std::pair<int, int>> &output_values)
{
	if (good_values)
	{
		this->resize_parameters_1();
		if (max)
			this->calculate(values);
		else
			this->calculate(this->inversion());
		output_values = get_result();
		return true;
	}
	return false;
}

void Hungarian::resize_parameters_1()
{
	subtrahend_lines.clear();
	subtrahend_columns.clear();
	mark_indices.clear();
	subtrahend_lines.resize(height, 0);
	subtrahend_columns.resize(width, 0);
	mark_indices.resize(width, -1);
}

std::vector<std::vector<int>> Hungarian::inversion()
{
	std::vector<std::vector<int>> inversion_values;
	for (unsigned int i = 0; i < values.size(); i++)
		inversion_values.push_back(this->inversion_buffer(values[i]));
	return inversion_values;
}
std::vector<int> Hungarian::inversion_buffer(std::vector<int> buffer)
{
	int max = this->find_max(buffer);
	for (unsigned int i = 0;i < buffer.size();i++)
		buffer[i] = max - buffer[i];
	return buffer;
}
int Hungarian::find_max(const std::vector<int> &buffer)
{
	int max = INT_MIN;
	for (unsigned int i = 0;i < buffer.size();i++)
		if (buffer[i] > max)
			max = buffer[i];
	return max;
}

void Hungarian::calculate(std::vector<std::vector<int>> &matrix)
{
	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
	for (int i = 0; i < height; i++) {
		this->resize_parameters_2();
		int markedI = i, markedJ = -1, j;
		while (markedI != -1) {
			j = -1;
			for (int j1 = 0; j1 < width; j1++)
				if (!visited[j1]) {
					if (matrix[markedI][j1] - subtrahend_lines[markedI] - subtrahend_columns[j1] < mins[j1]) {
						mins[j1] = matrix[markedI][j1] - subtrahend_lines[markedI] - subtrahend_columns[j1];
						links[j1] = markedJ;
					}
					if (j == -1 || mins[j1] < mins[j])
						j = j1;
				}
			int delta = mins[j];
			for (int j1 = 0; j1 < width; j1++)
				if (visited[j1]) {
					subtrahend_lines[mark_indices[j1]] += delta;
					subtrahend_columns[j1] -= delta;
				}
				else {
					mins[j1] -= delta;
				}
				subtrahend_lines[i] += delta;
				visited[j] = 1;
				markedJ = j;
				markedI = mark_indices[j];
		}
		for (; links[j] != -1; j = links[j])
			mark_indices[j] = mark_indices[links[j]];
		mark_indices[j] = i;
	}
	std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	time = time_span.count();
	time_ready = true;
}

void Hungarian::resize_parameters_2()
{
	links.clear();
	mins.clear();
	visited.clear();
	links.resize(width, -1);
	mins.resize(width, inf);
	visited.resize(width, 0);
}

std::vector<std::pair<int, int>> Hungarian::get_result()
{
	std::vector<std::pair<int, int>> result;
	for (int j = 0; j < width; j++)
		if (mark_indices[j] != -1)
			result.push_back(std::pair<int,int>(mark_indices[j], j));
	return result;
}

bool Hungarian::get_time(double &output_time)
{
	if (time_ready)
	{
		output_time = time;
		return true;
	}
	else
	{
		return false;
	}
}
