#include "MyForm11.h"
//#include <Windows.h>
#include "CombinatoryWork.h"
#include "WorkWithNode.h"
#include <fstream>

using namespace Project1; // Название проекта

std::vector<double> edgesLength;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Project1::MyForm11 form;
	Application::Run(%form);
	return 0;
}

System::Void Project1::MyForm11::ParseAmountOfEdges(System::Object^ sender, System::EventArgs^ e) 
{
	String^ text = amountEdges->Text;
	std::string tx = msclr::interop::marshal_as<std::string>(text);
	try {
		amountOfEdges = std::stoi(tx);
		canCreateGraph = true;
	}
	catch (std::invalid_argument ex)
	{
		System::Windows::Forms::MessageBox::Show("Пожалуйста, введите количество рёбер в виде целого числа");
	}
	catch (std::out_of_range)
	{
		System::Windows::Forms::MessageBox::Show("Введённое число рёбер вне границ диапазона");
	}
}

System::Void Project1::MyForm11::CBedges_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (CBedges->Checked == false)
	{
		canCreateGraph = false;
		amountEdges->Text = "Введите количество рёбер";
		amountEdges->Visible = false;
		enterEdges->Visible = true;
		or ->Visible = true;
		loadFile->Visible = true;
	}
	else {
		canCreateGraph = false;
		enterEdges->Text = "Введите длины рёбер";
		amountEdges->Visible = true;
		enterEdges->Visible = false;
		or ->Visible = false;
		loadFile->Visible = false;
	}
}

System::Void Project1::MyForm11::ParseEnterEdges(System::Object^ sender, System::EventArgs^ e) {
	String^ text = enterEdges->Text;
	std::string tx = msclr::interop::marshal_as<std::string>(text);
	tx += ";";
	std::string number = "";
	for (unsigned int i = 0; i < tx.size(); ++i)
	{
		canCreateGraph = true;
		if (tx[i] != ' ' && tx[i] != ';') {
			number += tx[i];
		}
		else {
			try {
				(edgesLength).push_back(std::stof(number));
				number = "";
			}
			catch (std::invalid_argument ex)
			{
				System::Windows::Forms::MessageBox::Show("Пожалуйста, введите рёбра в виде последовательности чисел, разделённых пробелом");
				canCreateGraph = false;
				break;
			}
			catch (std::out_of_range)
			{
				System::Windows::Forms::MessageBox::Show("Введённое число вне границ диапазона");
				canCreateGraph = false;
				break;
			}
		}
	}
}

System::Void Project1::MyForm11::loadFile_Click(System::Object^ sender, System::EventArgs^ e) {
	openEnterFile->Filter = "xml files (*.xml)|*.xml";
	if (openEnterFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		canCreateGraph = true;
		String^ file = openEnterFile->FileName;
		DataSet^ ds = gcnew DataSet();
		try {
			ds->ReadXml(file);
		}
		catch (...)
		{
			System::Windows::Forms::MessageBox::Show("Ошибка при чтении файла");
			canCreateGraph = false;
			return;
		}
		for (int i = 0; i < ds->Tables->Count; ++i)
		{
			for (int j = 0; j < ds->Tables[i]->Rows->Count; ++j) {
				try {
					std::string tx = msclr::interop::marshal_as<std::string>(ds->Tables[i]->Rows[j] -> ItemArray[0]->ToString());
					(edgesLength).push_back(std::stof(tx));
				}
				catch (...)
				{
					System::Windows::Forms::MessageBox::Show("Ошибка при чтении файла");
					canCreateGraph = false;
					return;
				}
			}
		}
		if (canCreateGraph) {
			System::Windows::Forms::MessageBox::Show("Файл загружен, граф будет генерироваться из него");
		}
	}
}

System::String^ Project1::MyForm11::CreateDotFile(int numberOfGraph, std::vector<std::pair<int, int>>& graph)
{
	System::String^ textFile;
	textFile += "graph number";
	textFile += numberOfGraph.ToString();
	textFile += " { \n";
	for (unsigned int i = 0; i < graph.size(); ++i)
	{
		textFile += graph[i].first;
		textFile += " -- ";
		textFile += graph[i].second;
		textFile += "; \n";
	}
	textFile += "}";
	return textFile;
}

System::String^ Project1::MyForm11::CreateDotFile(int numberOfGraph, std::vector<std::pair<int, int>>& graph, std::vector<double> transpose)
{
	System::String^ textFile;
	textFile += "graph number";
	textFile += numberOfGraph.ToString();
	textFile += " { \n";
	for (unsigned int i = 0; i < graph.size(); ++i)
	{
		textFile += graph[i].first;
		textFile += " -- ";
		textFile += graph[i].second;
		textFile += "[label=";
		textFile += transpose[i];
		textFile += "] \n";
	}
	textFile += "}";
	return textFile;
}

System::Void Project1::MyForm11::generateButton_Click(System::Object^ sender, System::EventArgs^ e) {
	System::String^ path = System::Environment::CurrentDirectory;
	if (folderDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		path = folderDialog->SelectedPath->ToString();
		if (CBedges->Checked == true)
		{
			ParseAmountOfEdges(sender, e);
			if (canCreateGraph)
			{
				std::vector<std::vector<std::pair<int, int>>> collection = ConvertIntoPairs(CreateGraphs_(amountOfEdges));
				for (unsigned int i = 0; i < (collection).size(); ++i)
				{
					try
					{
						String^ text = CreateDotFile(i, (collection)[i]);
						std::string myText = msclr::interop::marshal_as<std::string>(text);
						std::string fileName = msclr::interop::marshal_as<std::string>(path + "/graph" + i.ToString() + ".dot");
						std::ofstream fout(fileName);
						fout << myText; // запись строки в файл
						fout.close(); // закрываем файл
					}
					catch (...)
					{
						System::Windows::Forms::MessageBox::Show("Ошибка при записи в файл");
						return;
					}
				}
				System::Windows::Forms::MessageBox::Show("Программа закончила добавление графов");
			}
			else
			{
				System::Windows::Forms::MessageBox::Show("Введите корректные данные");
			}
		}
		else {
			if (canCreateGraph)
			{
				std::vector<std::vector<std::pair<int, int>>> collection = ConvertIntoPairs(CreateGraphs_(edgesLength.size()));
				std::vector<std::vector<double>> transposes = CreateTranspositions(edgesLength, edgesLength.size());
				for (unsigned int i = 0; i < (collection).size(); ++i)
				{
					try
					{
						for (int j = 0; j < transposes.size(); ++j) {
							String^ text = CreateDotFile(i, (collection)[i], transposes[j]);
							std::string myText = msclr::interop::marshal_as<std::string>(text);
							std::string fileName = msclr::interop::marshal_as<std::string>(path + "/graph" + i.ToString() + "tr" + j.ToString() + ".dot");
							std::ofstream fout(fileName);
							fout << myText; // запись строки в файл
							fout.close(); // закрываем файл
						}
					}
					catch (...)
					{
						System::Windows::Forms::MessageBox::Show("Ошибка при записи в файл");
						return;
					}
				}
				System::Windows::Forms::MessageBox::Show("Программа закончила добавление графов");
			}
			else {
				ParseEnterEdges(sender, e);
				if (canCreateGraph)
				{
					std::vector<std::vector<std::pair<int, int>>> collection = ConvertIntoPairs(CreateGraphs_(edgesLength.size()));
					std::vector<std::vector<double>> transposes = CreateTranspositions(edgesLength, edgesLength.size());
					for (unsigned int i = 0; i < (collection).size(); ++i)
					{
						try
						{
							for (int j = 0; j < transposes.size(); ++j) {
								String^ text = CreateDotFile(i, (collection)[i], transposes[j]);
								std::string myText = msclr::interop::marshal_as<std::string>(text);
								std::string fileName = msclr::interop::marshal_as<std::string>(path + "/graph" + i.ToString() + "tr" + j.ToString() + ".dot");
								std::ofstream fout(fileName);
								fout << myText; // запись строки в файл
								fout.close(); // закрываем файл
							}
						}
						catch (...)
						{
							System::Windows::Forms::MessageBox::Show("Ошибка при записи в файл");
							return;
						}
					}
					System::Windows::Forms::MessageBox::Show("Программа закончила добавление графов");
				}
				else
				{
					System::Windows::Forms::MessageBox::Show("Введите корректные данные");
				}
			}
		}
	}
	else {
		System::Windows::Forms::MessageBox::Show("Выберите папку для сохранения полученных результатов");
	}
}