#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>
#include <stdexcept>

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm11 : public System::Windows::Forms::Form
	{
	public:
		MyForm11(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		int amountOfEdges;
		bool canCreateGraph = false;
	private: System::Windows::Forms::FolderBrowserDialog^ folderDialog;
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm11()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^ CBedges;
	private: System::Windows::Forms::TextBox^ amountEdges;
	private: System::Windows::Forms::TextBox^ enterEdges;
	private: System::Windows::Forms::Label^ or ;
	private: System::Windows::Forms::OpenFileDialog^ openEnterFile;
	private: System::Windows::Forms::Button^ loadFile;
	private: System::Windows::Forms::Button^ generateButton;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->CBedges = (gcnew System::Windows::Forms::CheckBox());
			this->amountEdges = (gcnew System::Windows::Forms::TextBox());
			this->enterEdges = (gcnew System::Windows::Forms::TextBox());
			this-> or = (gcnew System::Windows::Forms::Label());
			this->openEnterFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->loadFile = (gcnew System::Windows::Forms::Button());
			this->generateButton = (gcnew System::Windows::Forms::Button());
			this->folderDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->SuspendLayout();
			// 
			// CBedges
			// 
			this->CBedges->AutoSize = true;
			this->CBedges->Checked = true;
			this->CBedges->CheckState = System::Windows::Forms::CheckState::Checked;
			this->CBedges->Location = System::Drawing::Point(45, 42);
			this->CBedges->Name = L"CBedges";
			this->CBedges->Size = System::Drawing::Size(217, 24);
			this->CBedges->TabIndex = 0;
			this->CBedges->Text = L"Все рёбра одной длины";
			this->CBedges->UseVisualStyleBackColor = true;
			this->CBedges->CheckedChanged += gcnew System::EventHandler(this, &MyForm11::CBedges_CheckedChanged);
			// 
			// amountEdges
			// 
			this->amountEdges->Location = System::Drawing::Point(332, 43);
			this->amountEdges->Name = L"amountEdges";
			this->amountEdges->Size = System::Drawing::Size(224, 26);
			this->amountEdges->TabIndex = 1;
			this->amountEdges->Text = L"Введите количество рёбер";
			// 
			// enterEdges
			// 
			this->enterEdges->Location = System::Drawing::Point(45, 121);
			this->enterEdges->Name = L"enterEdges";
			this->enterEdges->Size = System::Drawing::Size(217, 26);
			this->enterEdges->TabIndex = 2;
			this->enterEdges->Text = L"Введите длины рёбер";
			this->enterEdges->Visible = false;
			// 
			// or
			// 
			this-> or ->AutoSize = true;
			this-> or ->Location = System::Drawing::Point(278, 124);
			this-> or ->Name = L"or";
			this-> or ->Size = System::Drawing::Size(37, 20);
			this-> or ->TabIndex = 3;
			this-> or ->Text = L"или";
			this-> or ->Visible = false;
			// 
			// openEnterFile
			// 
			this->openEnterFile->FileName = L"Enter Edges";
			// 
			// loadFile
			// 
			this->loadFile->Location = System::Drawing::Point(332, 117);
			this->loadFile->Name = L"loadFile";
			this->loadFile->Size = System::Drawing::Size(224, 34);
			this->loadFile->TabIndex = 4;
			this->loadFile->Text = L"Выберите файл";
			this->loadFile->UseVisualStyleBackColor = true;
			this->loadFile->Visible = false;
			this->loadFile->Click += gcnew System::EventHandler(this, &MyForm11::loadFile_Click);
			// 
			// generateButton
			// 
			this->generateButton->Location = System::Drawing::Point(45, 187);
			this->generateButton->Name = L"generateButton";
			this->generateButton->Size = System::Drawing::Size(511, 34);
			this->generateButton->TabIndex = 5;
			this->generateButton->Text = L"Сгенерировать графы";
			this->generateButton->UseVisualStyleBackColor = true;
			this->generateButton->Click += gcnew System::EventHandler(this, &MyForm11::generateButton_Click);
			// 
			// MyForm11
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(578, 294);
			this->Controls->Add(this->generateButton);
			this->Controls->Add(this->loadFile);
			this->Controls->Add(this-> or );
			this->Controls->Add(this->enterEdges);
			this->Controls->Add(this->amountEdges);
			this->Controls->Add(this->CBedges);
			this->MaximumSize = System::Drawing::Size(600, 350);
			this->MinimumSize = System::Drawing::Size(600, 350);
			this->Name = L"MyForm11";
			this->Text = L"MyForm11";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CBedges_CheckedChanged(System::Object^ sender, System::EventArgs^ e);

	private: System::Void ParseAmountOfEdges(System::Object^ sender, System::EventArgs^ e);

	private: System::Void ParseEnterEdges(System::Object^ sender, System::EventArgs^ e);

	private: System::Void generateButton_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void loadFile_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::String^ CreateDotFile(int numberOfGraph, std::vector<std::pair<int, int>>& graph);

	private: System::String^ CreateDotFile(int numberOfGraph, std::vector<std::pair<int, int>>& graph, std::vector<double> transposes);
};
}
