#pragma once
#include "../Minecraft_converter/Minecraft_converter/Minecraft_converter.h"
#include <msclr\marshal_cppstd.h>

	std::string To_string(System::String^ String_) {

		std::string string_ = msclr::interop::marshal_as<std::string>(String_);
		return string_;
	}


namespace MinecraftGUI {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;




	/// <summary>
	/// Zusammenfassung für MTC
	/// </summary>
	public ref class MTC : public System::Windows::Forms::Form
	{
	public:
		MTC(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~MTC()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  java_path;


	private: System::Windows::Forms::FolderBrowserDialog^  java_folder;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  destination_path;


	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  pack_name;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TextBox^  log_box;

	private: System::Windows::Forms::FolderBrowserDialog^  destination_folder;
	private: System::Windows::Forms::ComboBox^ comboBox1;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MTC::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->java_path = (gcnew System::Windows::Forms::TextBox());
			this->java_folder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->destination_path = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pack_name = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->log_box = (gcnew System::Windows::Forms::TextBox());
			this->destination_folder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(281, 103);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(27, 20);
			this->button1->TabIndex = 0;
			this->button1->Text = L"...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MTC::button1_Click);
			// 
			// java_path
			// 
			this->java_path->Location = System::Drawing::Point(108, 103);
			this->java_path->Name = L"java_path";
			this->java_path->Size = System::Drawing::Size(167, 20);
			this->java_path->TabIndex = 1;
			this->java_path->TextChanged += gcnew System::EventHandler(this, &MTC::java_path_TextChanged);
			// 
			// java_folder
			// 
			this->java_folder->ShowNewFolderButton = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label1->Location = System::Drawing::Point(13, 106);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Java Pack Folder";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label2->Location = System::Drawing::Point(13, 143);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(92, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Destination Folder";
			// 
			// destination_path
			// 
			this->destination_path->Location = System::Drawing::Point(108, 140);
			this->destination_path->Name = L"destination_path";
			this->destination_path->Size = System::Drawing::Size(167, 20);
			this->destination_path->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(281, 140);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(27, 20);
			this->button2->TabIndex = 5;
			this->button2->Text = L"...";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MTC::button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label3->Location = System::Drawing::Point(13, 177);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(63, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Pack Name";
			// 
			// pack_name
			// 
			this->pack_name->Location = System::Drawing::Point(108, 177);
			this->pack_name->Name = L"pack_name";
			this->pack_name->Size = System::Drawing::Size(167, 20);
			this->pack_name->TabIndex = 7;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(153, 226);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(70, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"Start";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MTC::button3_Click);
			// 
			// log_box
			// 
			this->log_box->Location = System::Drawing::Point(13, 262);
			this->log_box->Multiline = true;
			this->log_box->Name = L"log_box";
			this->log_box->ReadOnly = true;
			this->log_box->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->log_box->Size = System::Drawing::Size(382, 229);
			this->log_box->TabIndex = 9;
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Java 1.12", L"Java 1.13", L"Java 1.14" });
			this->comboBox1->Location = System::Drawing::Point(108, 64);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(167, 21);
			this->comboBox1->TabIndex = 10;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MTC::ComboBox1_SelectedIndexChanged);
			// 
			// MTC
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DimGray;
			this->ClientSize = System::Drawing::Size(406, 546);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->log_box);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->pack_name);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->destination_path);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->java_path);
			this->Controls->Add(this->button1);
			this->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MTC";
			this->Text = L"MTC";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



	private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{


		java_folder->ShowDialog();
// catch  wenn kein Ordner ausgewählz --> MSG kein Pfad ausgewählt

		if (!String::IsNullOrWhiteSpace(java_folder->SelectedPath))
		{
			
			java_path->Text = java_folder->SelectedPath;
			
		
		}
		
		

	}
//public: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

	//}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		destination_folder->ShowDialog();

		if (!String::IsNullOrWhiteSpace(destination_folder->SelectedPath))
		{

			destination_path->Text = destination_folder->SelectedPath;

		}

		

	}

private: System::Void ComboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void java_path_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

	if (java_path->Text == "" /*||*/&& destination_path->Text == "" /*||*/&& pack_name->Text == "") log_box->Text = "Fill out the Filds";
	else if (!convert::check(To_string(java_path->Text)) || !convert::check(To_string(destination_path->Text))) log_box->Text = "The Path does not exist";
	else convert::func(To_string(java_path->Text), To_string(destination_path->Text), To_string(pack_name->Text), comboBox1->SelectedIndex); log_box->Text = "Succsesfuly Converted";
	
	

}

};
}
