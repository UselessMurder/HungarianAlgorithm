#pragma once
#include <random>
#include <ctime>
#include "Hungarian.h"
#include "Graph.h"

std::vector<std::pair<int, int>> result;
std::vector <std::pair<int, int>> up_graph_coordinates;
std::vector <std::pair<int, int>> down_graph_coordinates;
bool print = false;
bool good_plot = false;
double work_time = 0;
bool clear = false;
bool light = false;


namespace Hungarian_algorithm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Hungarian_face
	/// </summary>
	public ref class Hungarian_face : public System::Windows::Forms::Form
	{
	public:
		Hungarian_face(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>

	private: System::Windows::Forms::TabControl^  in_out_type;
	private: System::Windows::Forms::TabPage^  matrix_page;
	private: System::Windows::Forms::TabPage^  graph_page;
	private: System::Windows::Forms::DataGridView^  Weights_matrix;
	private: System::Windows::Forms::Button^  Calculate_button;
	private: System::Windows::Forms::RadioButton^  max_button;
	private: System::Windows::Forms::RadioButton^  min_button;
	private: System::Windows::Forms::Label^  status_label;
	private: System::Windows::Forms::Button^  Add_column_button;
	private: System::Windows::Forms::Button^  Remove_column_button;
	private: System::Windows::Forms::Button^  Add_row_button;
	private: System::Windows::Forms::Button^  Remove_row_button;
	private: System::Windows::Forms::Button^  Clear_button;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  time_label;
	private: Hungarian * object;
	private: Graph * sked;
	private: bool in_work;
	private: int point_count;
	private: System::Windows::Forms::PictureBox^  Graph_box;
	private: System::Windows::Forms::Panel^  panel1;
	private: bool flag;
	protected:
		~Hungarian_face()
		{
			if (components)
			{
				delete object;
				delete sked;
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected:
	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->in_out_type = (gcnew System::Windows::Forms::TabControl());
			this->matrix_page = (gcnew System::Windows::Forms::TabPage());
			this->Weights_matrix = (gcnew System::Windows::Forms::DataGridView());
			this->graph_page = (gcnew System::Windows::Forms::TabPage());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->Graph_box = (gcnew System::Windows::Forms::PictureBox());
			this->Calculate_button = (gcnew System::Windows::Forms::Button());
			this->max_button = (gcnew System::Windows::Forms::RadioButton());
			this->min_button = (gcnew System::Windows::Forms::RadioButton());
			this->status_label = (gcnew System::Windows::Forms::Label());
			this->Add_column_button = (gcnew System::Windows::Forms::Button());
			this->Remove_column_button = (gcnew System::Windows::Forms::Button());
			this->Add_row_button = (gcnew System::Windows::Forms::Button());
			this->Remove_row_button = (gcnew System::Windows::Forms::Button());
			this->Clear_button = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->time_label = (gcnew System::Windows::Forms::Label());
			this->in_out_type->SuspendLayout();
			this->matrix_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Weights_matrix))->BeginInit();
			this->graph_page->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Graph_box))->BeginInit();
			this->SuspendLayout();
			// 
			// in_out_type
			// 
			this->in_out_type->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->in_out_type->Controls->Add(this->matrix_page);
			this->in_out_type->Controls->Add(this->graph_page);
			this->in_out_type->Location = System::Drawing::Point(13, 13);
			this->in_out_type->Name = L"in_out_type";
			this->in_out_type->SelectedIndex = 0;
			this->in_out_type->Size = System::Drawing::Size(994, 678);
			this->in_out_type->TabIndex = 1;
			this->in_out_type->SelectedIndexChanged += gcnew System::EventHandler(this, &Hungarian_face::in_out_type_SelectedIndexChanged);
			// 
			// matrix_page
			// 
			this->matrix_page->Controls->Add(this->Weights_matrix);
			this->matrix_page->Location = System::Drawing::Point(4, 25);
			this->matrix_page->Name = L"matrix_page";
			this->matrix_page->Padding = System::Windows::Forms::Padding(3);
			this->matrix_page->Size = System::Drawing::Size(986, 649);
			this->matrix_page->TabIndex = 0;
			this->matrix_page->Text = L"Weights matrix";
			this->matrix_page->UseVisualStyleBackColor = true;
			// 
			// Weights_matrix
			// 
			this->Weights_matrix->AllowUserToAddRows = false;
			this->Weights_matrix->AllowUserToDeleteRows = false;
			this->Weights_matrix->BackgroundColor = System::Drawing::Color::Black;
			this->Weights_matrix->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->Weights_matrix->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Weights_matrix->GridColor = System::Drawing::Color::White;
			this->Weights_matrix->Location = System::Drawing::Point(3, 3);
			this->Weights_matrix->Name = L"Weights_matrix";
			this->Weights_matrix->RowTemplate->Height = 24;
			this->Weights_matrix->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
			this->Weights_matrix->Size = System::Drawing::Size(980, 643);
			this->Weights_matrix->TabIndex = 0;
			// 
			// graph_page
			// 
			this->graph_page->AutoScroll = true;
			this->graph_page->BackColor = System::Drawing::Color::Black;
			this->graph_page->Controls->Add(this->panel1);
			this->graph_page->Location = System::Drawing::Point(4, 25);
			this->graph_page->Name = L"graph_page";
			this->graph_page->Padding = System::Windows::Forms::Padding(3);
			this->graph_page->Size = System::Drawing::Size(986, 649);
			this->graph_page->TabIndex = 1;
			this->graph_page->Text = L"Graph";
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panel1->BackColor = System::Drawing::Color::Gray;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->Graph_box);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->ForeColor = System::Drawing::Color::Black;
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(980, 643);
			this->panel1->TabIndex = 0;
			this->panel1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Hungarian_face::panel1_Scroll);
			this->panel1->SizeChanged += gcnew System::EventHandler(this, &Hungarian_face::panel1_SizeChanged);
			// 
			// Graph_box
			// 
			this->Graph_box->BackColor = System::Drawing::Color::Black;
			this->Graph_box->Location = System::Drawing::Point(-1, -1);
			this->Graph_box->Name = L"Graph_box";
			this->Graph_box->Size = System::Drawing::Size(834, 448);
			this->Graph_box->TabIndex = 0;
			this->Graph_box->TabStop = false;
			this->Graph_box->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Hungarian_face::Graph_box_Paint);
			// 
			// Calculate_button
			// 
			this->Calculate_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Calculate_button->BackColor = System::Drawing::Color::Yellow;
			this->Calculate_button->ForeColor = System::Drawing::Color::Black;
			this->Calculate_button->Location = System::Drawing::Point(896, 699);
			this->Calculate_button->Name = L"Calculate_button";
			this->Calculate_button->Size = System::Drawing::Size(111, 23);
			this->Calculate_button->TabIndex = 2;
			this->Calculate_button->Text = L"Calculate";
			this->Calculate_button->UseVisualStyleBackColor = false;
			this->Calculate_button->Click += gcnew System::EventHandler(this, &Hungarian_face::Calculate_button_Click);
			// 
			// max_button
			// 
			this->max_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->max_button->AutoSize = true;
			this->max_button->BackColor = System::Drawing::Color::Black;
			this->max_button->Checked = true;
			this->max_button->ForeColor = System::Drawing::Color::White;
			this->max_button->Location = System::Drawing::Point(770, 700);
			this->max_button->Name = L"max_button";
			this->max_button->Size = System::Drawing::Size(109, 21);
			this->max_button->TabIndex = 3;
			this->max_button->TabStop = true;
			this->max_button->Text = L"Maximization";
			this->max_button->UseVisualStyleBackColor = false;
			// 
			// min_button
			// 
			this->min_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->min_button->AutoSize = true;
			this->min_button->ForeColor = System::Drawing::Color::White;
			this->min_button->Location = System::Drawing::Point(770, 731);
			this->min_button->Name = L"min_button";
			this->min_button->Size = System::Drawing::Size(106, 21);
			this->min_button->TabIndex = 4;
			this->min_button->Text = L"Minimization";
			this->min_button->UseVisualStyleBackColor = true;
			// 
			// status_label
			// 
			this->status_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->status_label->AutoSize = true;
			this->status_label->ForeColor = System::Drawing::Color::White;
			this->status_label->Location = System::Drawing::Point(276, 729);
			this->status_label->Name = L"status_label";
			this->status_label->Size = System::Drawing::Size(49, 17);
			this->status_label->TabIndex = 5;
			this->status_label->Text = L"Ready";
			// 
			// Add_column_button
			// 
			this->Add_column_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Add_column_button->BackColor = System::Drawing::Color::Blue;
			this->Add_column_button->ForeColor = System::Drawing::Color::White;
			this->Add_column_button->Location = System::Drawing::Point(12, 697);
			this->Add_column_button->Name = L"Add_column_button";
			this->Add_column_button->Size = System::Drawing::Size(126, 23);
			this->Add_column_button->TabIndex = 1;
			this->Add_column_button->Text = L"Add Column";
			this->Add_column_button->UseVisualStyleBackColor = false;
			this->Add_column_button->Click += gcnew System::EventHandler(this, &Hungarian_face::Add_column_button_Click);
			// 
			// Remove_column_button
			// 
			this->Remove_column_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Remove_column_button->BackColor = System::Drawing::Color::Blue;
			this->Remove_column_button->ForeColor = System::Drawing::Color::White;
			this->Remove_column_button->Location = System::Drawing::Point(12, 726);
			this->Remove_column_button->Name = L"Remove_column_button";
			this->Remove_column_button->Size = System::Drawing::Size(126, 23);
			this->Remove_column_button->TabIndex = 6;
			this->Remove_column_button->Text = L"Remove Column";
			this->Remove_column_button->UseVisualStyleBackColor = false;
			this->Remove_column_button->Click += gcnew System::EventHandler(this, &Hungarian_face::Remove_column_button_Click);
			// 
			// Add_row_button
			// 
			this->Add_row_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Add_row_button->BackColor = System::Drawing::Color::Red;
			this->Add_row_button->ForeColor = System::Drawing::Color::White;
			this->Add_row_button->Location = System::Drawing::Point(144, 698);
			this->Add_row_button->Name = L"Add_row_button";
			this->Add_row_button->Size = System::Drawing::Size(126, 23);
			this->Add_row_button->TabIndex = 7;
			this->Add_row_button->Text = L"Add Row";
			this->Add_row_button->UseVisualStyleBackColor = false;
			this->Add_row_button->Click += gcnew System::EventHandler(this, &Hungarian_face::Add_row_button_Click);
			// 
			// Remove_row_button
			// 
			this->Remove_row_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Remove_row_button->BackColor = System::Drawing::Color::Red;
			this->Remove_row_button->ForeColor = System::Drawing::Color::White;
			this->Remove_row_button->Location = System::Drawing::Point(144, 726);
			this->Remove_row_button->Name = L"Remove_row_button";
			this->Remove_row_button->Size = System::Drawing::Size(126, 23);
			this->Remove_row_button->TabIndex = 8;
			this->Remove_row_button->Text = L"Remove Row";
			this->Remove_row_button->UseVisualStyleBackColor = false;
			this->Remove_row_button->Click += gcnew System::EventHandler(this, &Hungarian_face::Remove_row_button_Click);
			// 
			// Clear_button
			// 
			this->Clear_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Clear_button->BackColor = System::Drawing::Color::White;
			this->Clear_button->Location = System::Drawing::Point(896, 730);
			this->Clear_button->Name = L"Clear_button";
			this->Clear_button->Size = System::Drawing::Size(111, 23);
			this->Clear_button->TabIndex = 9;
			this->Clear_button->Text = L"Clear";
			this->Clear_button->UseVisualStyleBackColor = false;
			this->Clear_button->Click += gcnew System::EventHandler(this, &Hungarian_face::Clear_button_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Hungarian_face::backgroundWorker1_DoWork);
			// 
			// timer1
			// 
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &Hungarian_face::timer1_Tick);
			// 
			// time_label
			// 
			this->time_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->time_label->AutoSize = true;
			this->time_label->ForeColor = System::Drawing::Color::White;
			this->time_label->Location = System::Drawing::Point(276, 700);
			this->time_label->Name = L"time_label";
			this->time_label->Size = System::Drawing::Size(0, 17);
			this->time_label->TabIndex = 10;
			// 
			// Hungarian_face
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(1019, 763);
			this->Controls->Add(this->time_label);
			this->Controls->Add(this->Clear_button);
			this->Controls->Add(this->Remove_row_button);
			this->Controls->Add(this->Add_row_button);
			this->Controls->Add(this->Remove_column_button);
			this->Controls->Add(this->Add_column_button);
			this->Controls->Add(this->status_label);
			this->Controls->Add(this->min_button);
			this->Controls->Add(this->max_button);
			this->Controls->Add(this->Calculate_button);
			this->Controls->Add(this->in_out_type);
			this->ForeColor = System::Drawing::Color::Black;
			this->Name = L"Hungarian_face";
			this->ShowIcon = false;
			this->Text = L"Hungarian algorithm";
			this->Load += gcnew System::EventHandler(this, &Hungarian_face::Hungarian_face_Load);
			this->in_out_type->ResumeLayout(false);
			this->matrix_page->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Weights_matrix))->EndInit();
			this->graph_page->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Graph_box))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Exit_button_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: void Draw_elipse(int x, int y, Graphics ^ G, System::Drawing::Color c)
	{
		Brush^ brush = gcnew SolidBrush(c);
		Pen^ pen = gcnew Pen(Color::White);
		G->FillEllipse(brush, x, y, 70, 70);
		pen->Width = 3;
		G->DrawEllipse(pen, x, y, 70, 70);
	}
	private: void Draw_text(float x, float y, System::String ^ text, Graphics ^ G)
	{
		Brush^ brush = gcnew SolidBrush(Color::White);
		G->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;
		System::Drawing::Font^ fn = gcnew System::Drawing::Font(FontFamily::GenericSansSerif, 13.0F, FontStyle::Bold);
		G->DrawString(text, fn, brush, x, y);
	}
	private: void Draw_line(int b_x, int b_y, int e_x, int e_y, bool backlight, Graphics ^ G)
	{
		Pen^ pen;
		if (backlight)
			pen = gcnew Pen(Color::Yellow, 2);
		else
			pen = gcnew Pen(Color::Green, 2);
		G->DrawLine(pen, b_x , b_y , e_x, e_y);
	}
	private: void Draw_vertex(int x, int y, System::String ^ text, Graphics ^ G , System::Drawing::Color c)
	{
		Draw_elipse(x, y , G, c);
		Draw_text((float)x + 15 , (float)y + 25, text, G);
	}
	private: void Connect_vertexs(int b_x, int b_y, int e_x, int e_y, bool backlight , Graphics ^ G)
	{
		Draw_line(b_x + 35, b_y, e_x + 35, e_y + 70, backlight, G);
	}
	private: void Counted()
	{
		try
		{
			System::Drawing::Size^ s = Graph_box->Size;
			if (sked->set_parameters(std::pair<int, int>(s->Height, s->Width), Weights_matrix->RowCount, Weights_matrix->ColumnCount))
			{
				std::pair <int, int> parameters;
				if (sked->get_coordinates(parameters, down_graph_coordinates, up_graph_coordinates))
				{
					Graph_box->Size = System::Drawing::Size(parameters.second, parameters.first);
					good_plot = true;
				}
			}
			else
				good_plot = false;
		}
		catch (...)
		{

		}
	}
	private: void Combine_vertex_with_all(int n, Graphics ^ G)
	{
		for (unsigned int i = 0; i < up_graph_coordinates.size(); i++)
			Connect_vertexs(down_graph_coordinates[n].first, down_graph_coordinates[n].second, up_graph_coordinates[i].first, up_graph_coordinates[i].second, false , G);
	}
	private: void Draw_graph(Graphics^ G)
	{
		try
		{
			G->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighQuality;
			if (good_plot && in_out_type->SelectedIndex && !clear)
			{
				for (unsigned int i = 0;i < down_graph_coordinates.size();i++)
					Draw_vertex(down_graph_coordinates[i].first, down_graph_coordinates[i].second, L"D" + System::Convert::ToString(i),G,Color::Red);
				for (unsigned int i = 0;i < up_graph_coordinates.size();i++)
					Draw_vertex(up_graph_coordinates[i].first, up_graph_coordinates[i].second, L"U" + System::Convert::ToString(i),G,Color::Blue);
				for (unsigned int i = 0; i < down_graph_coordinates.size();i++)
					Combine_vertex_with_all(i,G);
				Draw_light(G);
			}
		}
		catch (...)
		{

		}
	}
	private: void Draw_light(Graphics^ G)
	{
		try 
		{
			if (good_plot && in_out_type->SelectedIndex && !clear && light)
				for (unsigned int i = 0; i < result.size(); i++)
					Connect_vertexs(down_graph_coordinates[result[i].first].first, down_graph_coordinates[result[i].first].second, up_graph_coordinates[result[i].second].first, up_graph_coordinates[result[i].second].second, true, G);
		}
		catch(...)
		{ }
	}
	private:void Add_column(){
		try
		{
			light = false;
			System::Windows::Forms::DataGridViewColumn^ newcolumn = (gcnew System::Windows::Forms::DataGridViewColumn());
			newcolumn->HeaderText = L"U" + System::Convert::ToString(Weights_matrix->ColumnCount);
			DataGridViewCell^ cell = gcnew DataGridViewTextBoxCell;
			cell->Style->BackColor = Color::Black;
			cell->Style->ForeColor = Color::White;
			newcolumn->CellTemplate = cell;
			Weights_matrix->Columns->Add(newcolumn);
			for (int i = 0; i < Weights_matrix->RowCount; i++)
				Weights_matrix->Rows[i]->Cells[Weights_matrix->ColumnCount - 1]->Value = (rand()).ToString();
			Graph_box->Refresh();
		}
		catch (...)
		{

		}
	}
	private:void Add_row() {
		try
		{
			light = false;
			if (Weights_matrix->ColumnCount)
			{
				Weights_matrix->Rows->Add();
				for (int i = 0; i < Weights_matrix->ColumnCount; i++)
					Weights_matrix->Rows[Weights_matrix->RowCount - 1]->Cells[i]->Value = (rand()).ToString();
			}
			Graph_box->Refresh();
		}
		catch (...)
		{

		}
	}
	private:void Remove_column()
	{
		try
		{
			light = false;
			if (Weights_matrix->ColumnCount)
				Weights_matrix->Columns->RemoveAt(Weights_matrix->ColumnCount - 1);
			Graph_box->Refresh();
		}
		catch (...)
		{

		}
	}
	private:void Remove_row()
	{
		try
		{
			light = false;
			if (Weights_matrix->RowCount)
				Weights_matrix->Rows->RemoveAt(Weights_matrix->RowCount - 1);
			Graph_box->Refresh();
		}
		catch (...)
		{

		}
	}
	private:void Show_rand()
	{
		for (int i = 0;i < 12; i++)
		{
			Add_column();
			Add_row();
		}
	}
	private: System::Void Hungarian_face_Load(System::Object^  sender, System::EventArgs^  e) {
		this->ClientSize = System::Drawing::Size(1020, 700);
		srand((unsigned int)time(NULL));
		object = new Hungarian;
		sked = new Graph;
		System::Drawing::Size^ s = Graph_box->Size;
		Show_rand();
		in_work = false;
	}
private: System::Void Add_column_button_Click(System::Object^  sender, System::EventArgs^  e) {
	select_disable();
	result.clear();
	Add_column();
}
private: System::Void Remove_column_button_Click(System::Object^  sender, System::EventArgs^  e) {
	select_disable();
	result.clear();
	Remove_column();
}
private: System::Void Add_row_button_Click(System::Object^  sender, System::EventArgs^  e) {
	select_disable();
	result.clear();
	Add_row();
}
private: System::Void Remove_row_button_Click(System::Object^  sender, System::EventArgs^  e) {
	select_disable();
	result.clear();
	Remove_row();
}
private: System::Void Clear_button_Click(System::Object^  sender, System::EventArgs^  e) {
	light = false;
	good_plot = false;
	clear = true;
	select_disable();
	result.clear();
	while (Weights_matrix->ColumnCount)
		Remove_column();
	clear = false;
	Graph_box->Refresh();
}
private: void Disable()
{
	point_count = 0;
	in_out_type->Enabled = false;
	Clear_button->Enabled = false;
	Calculate_button->Enabled = false;
	max_button->Enabled = false;
	min_button->Enabled = false;
	Remove_column_button->Enabled = false;
	Remove_row_button->Enabled = false;
	Add_column_button->Enabled = false;
	Add_row_button->Enabled = false;
	in_work = true;
	timer1->Start();
}
private: void Enable()
{
	in_out_type->Enabled = true;
	Clear_button->Enabled = true;
	Calculate_button->Enabled = true;
	max_button->Enabled = true;
	min_button->Enabled = true;
	Remove_column_button->Enabled = true;
	Remove_row_button->Enabled = true;
	Add_column_button->Enabled = true;
	Add_row_button->Enabled = true;
	timer1->Stop();
	Graph_box->Refresh();
}
private: bool get_values(std::vector <std::vector<int>> &values)
{
	for (int i = 0;i < Weights_matrix->RowCount;i++)
	{
		std::vector<int> buffer;
		for (int j = 0;j < Weights_matrix->ColumnCount;j++)
		{
			try 
			{
				buffer.push_back(System::Convert::ToInt32(Weights_matrix->Rows[i]->Cells[j]->Value));
			}
			catch (...)
			{
				return false;
			}
		}
		values.push_back(buffer);
	}
	return true;
}
private: void select_enable()
{
	try
	{
		if (object->get_time(work_time))
			time_label->Text = L"Time: " + System::Convert::ToString(work_time)+ L" seconds";
		for (unsigned int i = 0; i < result.size(); i++)
		{
			Weights_matrix->Rows[result[i].first]->Cells[result[i].second]->Style->BackColor = Color::Yellow;
			Weights_matrix->Rows[result[i].first]->Cells[result[i].second]->Style->ForeColor = Color::Black;
		}
	}
	catch (...)
	{

	}
}
private: void select_disable()
{
	try
	{
		time_label->Text = L"";
		for (unsigned int i = 0; i < result.size(); i++)
		{
			Weights_matrix->Rows[result[i].first]->Cells[result[i].second]->Style->BackColor = Color::Black;
			Weights_matrix->Rows[result[i].first]->Cells[result[i].second]->Style->ForeColor = Color::White;
		}
	}
	catch (...)
	{

	}
}
private: System::Void Calculate_button_Click(System::Object^  sender, System::EventArgs^  e) {
	Disable();
	select_disable();
	std::vector <std::vector<int>> values;
	if (get_values(values))
	{
		try
		{
			if (!max_button->Checked)
				flag = true;
			else
				flag = false;
			if (object->set_value(values))
				backgroundWorker1->RunWorkerAsync();
			else
			{
				in_work = false;
				MessageBox::Show("Bad proportions!");
			}
		}
		catch (...)
		{
			in_work = false;
			MessageBox::Show("Unknown error!");
		}
	}
	else
	{
		in_work = false;
		MessageBox::Show("Bad values!");
	}
}
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	try
	{
		if (object->get_result(flag, result))
		{
			print = true;
			light = true;
		}
	}
	catch (...)
	{
		MessageBox::Show("Unknown error!");
	}
	in_work = false;
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	if (!in_work)
	{
		status_label->Text = L"Ready";
		if (print)
			select_enable();
		Enable();
	}
	else
	{
		System::String ^ points = L"";
		for (unsigned char i = 0;i < point_count;i++)
			points += L'.';
		point_count++;
		if (point_count > 3)
			point_count = 0;
		status_label->Text = L"Calculating " + points;
	}
}
private: System::Void in_out_type_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//Graph_box->Refresh();
}
private: System::Void panel1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
		//Graph_box->Refresh();
}
private: System::Void Graph_box_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Counted();
	     Draw_graph(e->Graphics);
}
private: System::Void panel1_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
	Graph_box->Size = panel1->Size;
	//Graph_box->Refresh();
}
};
}
