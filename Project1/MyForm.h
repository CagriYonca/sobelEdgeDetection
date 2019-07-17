#pragma once

#include <Windows.h>
#include "imge_bmp.h"
#include <string>
#include <atlstr.h>

#define TIP_SAYISI 3
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;



	private: System::Windows::Forms::ToolStripMenuItem^  negativeToolStripMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  blurToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  binaryToolStripMenuItem;

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;


	private: System::Windows::Forms::ToolStripMenuItem^  imageToolStripMenuItem;

	private:
		/// <summary>
		/// Required designer variable.
		BYTE * Buffer,*raw_intensity, *Binary, *Collision, *Bound, *Edge, *Current;
		int *Etiketli, *histogram1;
		int Width, Height, bayrak = 0;
		long Size;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripMenuItem^  dilationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  erotionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  edgeDetectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  smoothToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  yatayTurevToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dikeyTurevToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kenarToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  houghDonusumuToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  nonMaximumToolStripMenuItem;

			 /// </summary>

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->negativeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->blurToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->binaryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->imageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->erotionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->edgeDetectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->yatayTurevToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dikeyTurevToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kenarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->houghDonusumuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->smoothToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->nonMaximumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->fileToolStripMenuItem,
					this->negativeToolStripMenuItem, this->blurToolStripMenuItem, this->binaryToolStripMenuItem, this->imageToolStripMenuItem, this->dilationToolStripMenuItem,
					this->erotionToolStripMenuItem, this->edgeDetectionToolStripMenuItem, this->smoothToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(900, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			this->fileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::fileToolStripMenuItem_Click);
			// 
			// negativeToolStripMenuItem
			// 
			this->negativeToolStripMenuItem->Name = L"negativeToolStripMenuItem";
			this->negativeToolStripMenuItem->Size = System::Drawing::Size(66, 20);
			this->negativeToolStripMenuItem->Text = L"Negative";
			this->negativeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::negativeToolStripMenuItem_Click);
			// 
			// blurToolStripMenuItem
			// 
			this->blurToolStripMenuItem->Name = L"blurToolStripMenuItem";
			this->blurToolStripMenuItem->Size = System::Drawing::Size(123, 20);
			this->blurToolStripMenuItem->Text = L"Laplace of Gaussian";
			this->blurToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::blurToolStripMenuItem_Click);
			// 
			// binaryToolStripMenuItem
			// 
			this->binaryToolStripMenuItem->Name = L"binaryToolStripMenuItem";
			this->binaryToolStripMenuItem->Size = System::Drawing::Size(88, 20);
			this->binaryToolStripMenuItem->Text = L"Binary Image";
			this->binaryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::binaryToolStripMenuItem_Click);
			// 
			// imageToolStripMenuItem
			// 
			this->imageToolStripMenuItem->Name = L"imageToolStripMenuItem";
			this->imageToolStripMenuItem->Size = System::Drawing::Size(104, 20);
			this->imageToolStripMenuItem->Text = L"Object Classifier";
			this->imageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::imageToolStripMenuItem_Click);
			// 
			// dilationToolStripMenuItem
			// 
			this->dilationToolStripMenuItem->Name = L"dilationToolStripMenuItem";
			this->dilationToolStripMenuItem->Size = System::Drawing::Size(60, 20);
			this->dilationToolStripMenuItem->Text = L"Dilation";
			this->dilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem_Click);
			// 
			// erotionToolStripMenuItem
			// 
			this->erotionToolStripMenuItem->Name = L"erotionToolStripMenuItem";
			this->erotionToolStripMenuItem->Size = System::Drawing::Size(57, 20);
			this->erotionToolStripMenuItem->Text = L"Erotion";
			this->erotionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erotionToolStripMenuItem_Click);
			// 
			// edgeDetectionToolStripMenuItem
			// 
			this->edgeDetectionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->yatayTurevToolStripMenuItem,
					this->dikeyTurevToolStripMenuItem, this->kenarToolStripMenuItem, this->houghDonusumuToolStripMenuItem, this->nonMaximumToolStripMenuItem
			});
			this->edgeDetectionToolStripMenuItem->Name = L"edgeDetectionToolStripMenuItem";
			this->edgeDetectionToolStripMenuItem->Size = System::Drawing::Size(99, 20);
			this->edgeDetectionToolStripMenuItem->Text = L"Edge Detection";
			this->edgeDetectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::edgeDetectionToolStripMenuItem_Click);
			// 
			// yatayTurevToolStripMenuItem
			// 
			this->yatayTurevToolStripMenuItem->Name = L"yatayTurevToolStripMenuItem";
			this->yatayTurevToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->yatayTurevToolStripMenuItem->Text = L"Yatay Turev";
			this->yatayTurevToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::yatayTurevToolStripMenuItem_Click);
			// 
			// dikeyTurevToolStripMenuItem
			// 
			this->dikeyTurevToolStripMenuItem->Name = L"dikeyTurevToolStripMenuItem";
			this->dikeyTurevToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->dikeyTurevToolStripMenuItem->Text = L"Dikey Turev";
			this->dikeyTurevToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dikeyTurevToolStripMenuItem_Click);
			// 
			// kenarToolStripMenuItem
			// 
			this->kenarToolStripMenuItem->Name = L"kenarToolStripMenuItem";
			this->kenarToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->kenarToolStripMenuItem->Text = L"Kenar";
			this->kenarToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kenarToolStripMenuItem_Click);
			// 
			// houghDonusumuToolStripMenuItem
			// 
			this->houghDonusumuToolStripMenuItem->Name = L"houghDonusumuToolStripMenuItem";
			this->houghDonusumuToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->houghDonusumuToolStripMenuItem->Text = L"Hough Donusumu";
			this->houghDonusumuToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::houghDonusumuToolStripMenuItem_Click);
			// 
			// smoothToolStripMenuItem
			// 
			this->smoothToolStripMenuItem->Name = L"smoothToolStripMenuItem";
			this->smoothToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->smoothToolStripMenuItem->Text = L"Smooth";
			this->smoothToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::smoothToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 30);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(450, 450);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(450, 30);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(450, 450);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// chart2
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea1);
			this->chart2->Location = System::Drawing::Point(452, 480);
			this->chart2->Name = L"chart2";
			series1->ChartArea = L"ChartArea1";
			series1->Name = L"Series1";
			this->chart2->Series->Add(series1);
			this->chart2->Size = System::Drawing::Size(450, 200);
			this->chart2->TabIndex = 4;
			this->chart2->Text = L"chart2";
			this->chart2->Visible = false;
			// 
			// chart1
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			this->chart1->Location = System::Drawing::Point(0, 480);
			this->chart1->Name = L"chart1";
			series2->ChartArea = L"ChartArea1";
			series2->Name = L"Series1";
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(450, 200);
			this->chart1->TabIndex = 4;
			this->chart1->Text = L"chart1";
			this->chart1->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(800, 8);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 6;
			// 
			// nonMaximumToolStripMenuItem
			// 
			this->nonMaximumToolStripMenuItem->Name = L"nonMaximumToolStripMenuItem";
			this->nonMaximumToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->nonMaximumToolStripMenuItem->Text = L"NonMaximum";
			this->nonMaximumToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::nonMaximumToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 671);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void fileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Controls->Clear();
		this->InitializeComponent();
		LPCTSTR input;
		CString str;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			pictureBox1->ImageLocation = openFileDialog1->FileName;
			pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
			str = openFileDialog1->FileName;		//Burdan koda resmin adresini alıcaz, sonra
			input = (LPCTSTR)str;
			Buffer = LoadBMP(Width, Height, Size, input);
			raw_intensity = ConvertBMPToIntensity(Buffer, Width, Height);
			Current = raw_intensity;
			BYTE* histEq = histogramEq(Current, Width, Height);
			Bitmap^ surface = gcnew Bitmap(Width, Height);
			pictureBox2->Image = surface;
			this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;

			histogram1 = histogramGonder(Current, Width, Height);

			for (int i = 0; i < 256; i++) {
				this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
			}
			this->chart1->Visible = true;

			Color c;
			int temp;
			for (int row = 0; row < Height; row++) {
				for (int column = 0; column < Width; column++) {
					temp = row * Width + column;
					c = Color::FromArgb(histEq[temp], histEq[temp], histEq[temp]);
					surface->SetPixel(column, row, c);
				}
			}
	
			histogram1 = histogramGonder(histEq, Width, Height);

			for (int i = 0; i < 256; i++) {
				this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
			}
			this->chart2->Visible = true;

		}
	}
private: System::Void negativeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Controls->Clear();
	this->InitializeComponent();
	
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	Color c;
	int temp;
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(column, row, c);
		}
	}

	Current = Negative(Current, Width, Height);
	Bitmap^ surface2 = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface2;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface2->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void logativeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Controls->Clear();
	this->InitializeComponent();
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	Color c;
	int temp;
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	Current = Logative(Current, Width, Height, 10);
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);

	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;

}
private: System::Void powerativeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Controls->Clear();
	this->InitializeComponent();
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	Color c;
	int temp;
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);

	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	Current = Powerative(Current, Width, Height, 10);
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}
	
	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void blurToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Controls->Clear();
	this->InitializeComponent();
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	Color c;
	int temp;

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);

	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	Current = LoGFilter(Current, Width, Height);

	Width -= 4;
	Height -= 4;

	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void binaryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Controls->Clear();
	this->InitializeComponent();
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	Color c;
	int temp;

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);

	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	Current = Euclid(Current, Width, Height);
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	
	histogram1 = histogramGonder(Current, Width, Height);

	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}	 
private: System::Void mahalanobisIntToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Controls->Clear();
	this->InitializeComponent();
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	raw_intensity = ConvertBMPToIntensity(Buffer, Width, Height);
	Color c;
	int temp;
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(raw_intensity[temp], raw_intensity[temp], raw_intensity[temp]);
			surface1->SetPixel(column, row, c);
		}
	}

	BYTE* mahalanobis_photo = Mahalanobis(raw_intensity, Width, Height);					//Gelen dizi (width-2) * (height - 2)

	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;


	for (int row = 0; row < (Height); row++) {
		for (int column = 0; column < (Width); column++) {
			temp = row * (Width)+column;
			c = Color::FromArgb(mahalanobis_photo[temp], mahalanobis_photo[temp], mahalanobis_photo[temp]);
			surface->SetPixel(column, row, c);
		}
	}
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	histogram1 = histogramGonder(raw_intensity, Width, Height);

	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	histogram1 = histogramGonder(mahalanobis_photo, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;

}
private: System::Void imageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;

	Current = Euclid(Current, Width, Height);

	int temp;
	Color c;

	for (int row = 0; row < Height; row++) {
		for (int col = 0; col < Width; col++) {
			temp = row * Width + col;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(col, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	Etiketli = Etiketle(Current, Width, Height);
	/*int Adet = Say(Etiketli, Width, Height);
	Etiketli = EtiketSirala(Etiketli, Width, Height, Adet);
	*/
	int Adet = Say(Etiketli, Width, Height);
	Current = Yazdir(Etiketli, Width, Height);	//Nesne olanlar etiket rengine, olmayanlar 255'e atanir, bu sayede binary görüntü elde edilir 
	Current = Boundary(Etiketli, Width, Height, Adet);
	this->label1->Text = Adet.ToString();
	//Boundary cikartildiktan sonra simdi elinde bulunan feature'lara gore ortalama hesaplayip hangi nesnenin ne oldugunu ogren
	//Feature(Etiketli, Width, Height, Adet, TIP_SAYISI);

	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void dilationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Current = Dilation(Current, Width, Height);
	Etiketli = Etiketle(Current, Width, Height);
	Current = Yazdir(Etiketli, Width, Height);
	int Adet = Say(Etiketli, Width, Height);

	this->label1->Text = Adet.ToString();

	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	int temp;
	Color c;

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void erotionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Current = Erotion(Current, Width, Height);
	Etiketli = Etiketle(Current, Width, Height);
	Current = Yazdir(Etiketli, Width, Height);
	int Adet = Say(Etiketli, Width, Height);

	this->label1->Text = Adet.ToString();

	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	int temp;
	Color c;

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}


	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void edgeDetectionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
}
private: System::Void smoothToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Controls->Clear();
	this->InitializeComponent();
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	Color c;
	int temp;

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(column, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);

	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	Current = Smooth(Current, Width, Height);

	Width -= 4;
	Height -= 4;

	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;


	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void yatayTurevToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	int temp;
	Color c;

	for (int row = 0; row < Height; row++) {
		for (int col = 0; col < Width; col++) {
			temp = row * Width + col;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(col, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	int xYonunde[9] = { 1,2,1,0,0,0,-1,-2,-1 };			//Burdan gelen matristeki degerler 256dan buyuk
	BYTE* yatay = TaraBMP(Euclid(raw_intensity, Width, Height), Width, Height, xYonunde);
	Bitmap^ surface = gcnew Bitmap(Width - 2, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	for (int row = 0; row < Height - 2; row++) {
		for (int column = 0; column < Width - 2; column++) {
			temp = row * (Width-2) + column;
			c = Color::FromArgb(yatay[temp], yatay[temp], yatay[temp]);
			surface->SetPixel(column, row, c);
		}
	}


	histogram1 = histogramGonder(yatay, Width - 2, Height - 2);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void dikeyTurevToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	int temp;
	Color c;

	for (int row = 0; row < Height; row++) {
		for (int col = 0; col < Width; col++) {
			temp = row * Width + col;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(col, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	int yYonunde[9] = { -1,0,1,-2,0,2,-1,0,1 };			//Burdan gelen matristeki degerler 256dan buyuk
	BYTE* dikey = TaraBMP(Euclid(raw_intensity, Width, Height), Width, Height, yYonunde);
	Bitmap^ surface = gcnew Bitmap(Width - 2, Height - 2);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	for (int row = 0; row < Height - 2; row++) {
		for (int column = 0; column < Width - 2; column++) {
			temp = row * (Width-2) + column;
			c = Color::FromArgb(dikey[temp], dikey[temp], dikey[temp]);
			surface->SetPixel(column, row, c);
		}
	}


	histogram1 = histogramGonder(dikey, Width - 2, Height - 2);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void kenarToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	//Bundan önce feature çıkart
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	int temp;
	Color c;

	for (int row = 0; row < Height; row++) {
		for (int col = 0; col < Width; col++) {
			temp = row * Width + col;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(col, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;


	int deneme[9] = {1/4,1/2,1/4,1/2,1,1/2,1/4,1/2,1/4};
	BYTE* resim = TaraBMP(raw_intensity, Width, Height,deneme);
	resim = TaraBMP(resim, Width - 2, Height - 2,deneme);
	resim = TaraBMP(resim, Width - 4, Height - 4, deneme);
	Current = Gradient(Current, Width, Height);
	Width -= 6;
	Height -= 6;
	Current = Birlestir(resim, Current, Width, Height);
		
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}


	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void houghDonusumuToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	//Bundan önce feature çıkart
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	int temp;
	Color c;

	for (int row = 0; row < Height; row++) {
		for (int col = 0; col < Width; col++) {
			temp = row * Width + col;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(col, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;

	Current = Gradient(Current, Width, Height);
	Width -= 6;
	Height -= 6;
	Current = HoughUzayi(Current, Width, Height);
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	for (int row = 0; row < Height; row++) {
		for (int column = 0; column < Width; column++) {
			temp = row * Width + column;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface->SetPixel(column, row, c);
		}
	}


	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
private: System::Void nonMaximumToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	//Bundan önce feature çıkart
	Bitmap^ surface1 = gcnew Bitmap(Width, Height);
	pictureBox1->Image = surface1;
	this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
	int temp;
	Color c;

	for (int row = 0; row < Height; row++) {
		for (int col = 0; col < Width; col++) {
			temp = row * Width + col;
			c = Color::FromArgb(Current[temp], Current[temp], Current[temp]);
			surface1->SetPixel(col, row, c);
		}
	}

	histogram1 = histogramGonder(Current, Width, Height);
	for (int i = 0; i < 256; i++) {
		this->chart1->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart1->Visible = true;


	BYTE* nonMaximumGoruntu = NonMaximum(raw_intensity,Width,Height);
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	this->pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
	for (int row = 0; row < Height - 6; row++) {
		for (int column = 0; column < Width - 6; column++) {
			temp = row * (Width -6)+ column;
			c = Color::FromArgb(nonMaximumGoruntu[temp], nonMaximumGoruntu[temp], nonMaximumGoruntu[temp]);
			surface->SetPixel(column, row, c);
		}
	}


	histogram1 = histogramGonder(nonMaximumGoruntu, Width-6, Height-6);
	for (int i = 0; i < 256; i++) {
		this->chart2->Series["Series1"]->Points->AddXY(i, histogram1[i]);
	}
	this->chart2->Visible = true;
}
};
}
