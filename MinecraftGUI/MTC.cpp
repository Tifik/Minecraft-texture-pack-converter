#include "MTC.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

//int __stdcall WinMain()
int main()
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MinecraftGUI::MTC form;
	Application::Run(%form);


}































