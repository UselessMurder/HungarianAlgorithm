#include "Hungarian_face.h"



using namespace Hungarian_algorithm;



[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew Hungarian_face());
	return 0;
}
