#pragma once
#include <iostream>
#include <msclr\marshal_cppstd.h>
namespace winform {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::IO::Compression;
	using namespace System::Text;
	

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ button3;

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(208, 108);
			this->button1->TabIndex = 0;
			this->button1->Text = L"ќткрыть файл";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(265, 12);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(442, 471);
			this->richTextBox1->TabIndex = 2;
			this->richTextBox1->Text = L"";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 126);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(208, 128);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Save";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 260);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(208, 105);
			this->button3->TabIndex = 4;
			this->button3->Text = L"compile";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(83)), static_cast<System::Int32>(static_cast<System::Byte>(88)),
				static_cast<System::Int32>(static_cast<System::Byte>(117)));
			this->ClientSize = System::Drawing::Size(822, 523);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
		

	
	private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}
	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
		String^ FileName = "";
		
		if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			FileName = openFileDialog1->FileName;
		}
		//FileName = "C:\\papka\\programms\\Git\\SVI-2021\\lp_lab13\\in.txt";
		try
		{
			StreamReader^ file = File::OpenText(FileName);
			richTextBox1->Text = file->ReadToEnd();
			file->Close();
		}
		catch (Exception^ e)
		{

		}

	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
{
	
	String^ FileName = openFileDialog1->FileName;
	//StreamWriter^ file = File::OpenWrite(FileName);
	//richTextBox1->Text = filename;
	//File::WriteAllText(filename, richTextBox1->Text);
	File::WriteAllText(FileName, richTextBox1->Text);
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) 
{
	String^ line = "call C:\papka\programms\Git\SVI-2021\Debug\lp_lab13.exe -in:" + openFileDialog1->FileName;
	msclr::interop::marshal_context context;
	std::string command = context.marshal_as<std::string>(line);

	//std::string command = "call C:\papka\programms\Git\SVI-2021\Debug\lp_lab13.exec -in:" + line;
	std::system(command.c_str());

}
};
}
