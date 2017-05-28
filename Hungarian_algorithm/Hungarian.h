#include <vector>
#include <limits>


class Hungarian {
private:

	bool good_values;

	int height, 
		width;

	std::vector<int> subtrahend_lines, 
		subtrahend_columns,
		mark_indices,
		links,
		mins,
		visited;

	std::vector<std::vector<int>> values;

	bool time_ready;

	double time;

	const int inf = std::numeric_limits<int>::max();

	bool control_values(std::vector<std::vector<int>> &input_values);
	bool control_width(std::vector<std::vector<int>> &input_values);

	void set_height_and_width();
	void resize_parameters_1();
	void resize_parameters_2();

	std::vector <std::vector<int>> inversion();
	std::vector<int> inversion_buffer(std::vector<int> buffer);
	int find_max(const std::vector<int> &buffer);

	void calculate(std::vector<std::vector<int>> &matrix);
	std::vector<std::pair<int, int>> get_result();
public:

	Hungarian();
	~Hungarian();

	bool set_value(std::vector<std::vector<int>> input_values);

	bool get_result(bool max, std::vector<std::pair<int, int>> &output_values);

	bool get_time(double &output_time);
};
