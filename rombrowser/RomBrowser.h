#pragma once
#include "TRomHeader.h"

namespace rombrowser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class RomBrowser : public System::Windows::Forms::Form {
	public:
		RomBrowser(void) {
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RomBrowser()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  ui_open_button;
	private: System::Windows::Forms::TreeView^  ui_rom_tree;
	private: System::Windows::Forms::TextBox^  ui_textbox;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::Button^  ui_close_button;
	private: System::Windows::Forms::Button^  ui_expand_button;
	private: System::Windows::Forms::Button^  ui_collapse_button;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ui_open_button = (gcnew System::Windows::Forms::Button());
			this->ui_rom_tree = (gcnew System::Windows::Forms::TreeView());
			this->ui_textbox = (gcnew System::Windows::Forms::TextBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->ui_close_button = (gcnew System::Windows::Forms::Button());
			this->ui_expand_button = (gcnew System::Windows::Forms::Button());
			this->ui_collapse_button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// ui_open_button
			// 
			this->ui_open_button->Location = System::Drawing::Point(12, 12);
			this->ui_open_button->Name = L"ui_open_button";
			this->ui_open_button->Size = System::Drawing::Size(75, 23);
			this->ui_open_button->TabIndex = 0;
			this->ui_open_button->Text = L"&Open";
			this->ui_open_button->UseVisualStyleBackColor = true;
			this->ui_open_button->Click += gcnew System::EventHandler(this, &RomBrowser::ui_open_button_Click);
			// 
			// ui_rom_tree
			// 
			this->ui_rom_tree->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ui_rom_tree->Location = System::Drawing::Point(3, 3);
			this->ui_rom_tree->Name = L"ui_rom_tree";
			this->ui_rom_tree->Size = System::Drawing::Size(195, 322);
			this->ui_rom_tree->TabIndex = 1;
			this->ui_rom_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &RomBrowser::ui_rom_tree_AfterSelect);
			// 
			// ui_textbox
			// 
			this->ui_textbox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ui_textbox->Font = (gcnew System::Drawing::Font(L"Lucida Console", 8));
			this->ui_textbox->Location = System::Drawing::Point(3, 3);
			this->ui_textbox->Multiline = true;
			this->ui_textbox->Name = L"ui_textbox";
			this->ui_textbox->Size = System::Drawing::Size(420, 322);
			this->ui_textbox->TabIndex = 2;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->splitContainer1->Location = System::Drawing::Point(12, 41);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->ui_rom_tree);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->ui_textbox);
			this->splitContainer1->Size = System::Drawing::Size(631, 328);
			this->splitContainer1->SplitterDistance = 201;
			this->splitContainer1->TabIndex = 3;
			// 
			// ui_close_button
			// 
			this->ui_close_button->Location = System::Drawing::Point(95, 12);
			this->ui_close_button->Name = L"ui_close_button";
			this->ui_close_button->Size = System::Drawing::Size(75, 23);
			this->ui_close_button->TabIndex = 4;
			this->ui_close_button->Text = L"&Close";
			this->ui_close_button->UseVisualStyleBackColor = true;
			this->ui_close_button->Click += gcnew System::EventHandler(this, &RomBrowser::ui_close_button_Click);
			// 
			// ui_expand_button
			// 
			this->ui_expand_button->Location = System::Drawing::Point(176, 12);
			this->ui_expand_button->Name = L"ui_expand_button";
			this->ui_expand_button->Size = System::Drawing::Size(23, 23);
			this->ui_expand_button->TabIndex = 5;
			this->ui_expand_button->Text = L"+";
			this->ui_expand_button->UseVisualStyleBackColor = true;
			this->ui_expand_button->Click += gcnew System::EventHandler(this, &RomBrowser::ui_expand_button_Click);
			// 
			// ui_collapse_button
			// 
			this->ui_collapse_button->Location = System::Drawing::Point(205, 12);
			this->ui_collapse_button->Name = L"ui_collapse_button";
			this->ui_collapse_button->Size = System::Drawing::Size(23, 23);
			this->ui_collapse_button->TabIndex = 6;
			this->ui_collapse_button->Text = L"-";
			this->ui_collapse_button->UseVisualStyleBackColor = true;
			this->ui_collapse_button->Click += gcnew System::EventHandler(this, &RomBrowser::ui_collapse_button_Click);
			// 
			// RomBrowser
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(655, 381);
			this->Controls->Add(this->ui_collapse_button);
			this->Controls->Add(this->ui_expand_button);
			this->Controls->Add(this->ui_close_button);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->ui_open_button);
			this->Name = L"RomBrowser";
			this->Text = L"rombrowser";
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: ROM *rom = nullptr;

	private: System::Void ui_open_button_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ui_close_button_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ParseRom(ROM*);
	private: System::Void ui_rom_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
	private: System::Void ui_expand_button_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ui_collapse_button_Click(System::Object^  sender, System::EventArgs^  e);

};
}
