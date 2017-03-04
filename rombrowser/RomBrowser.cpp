#include "RomBrowser.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	rombrowser::RomBrowser ui;
	Application::Run(%ui);
}

namespace rombrowser {
	System::Void RomBrowser::ui_open_button_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->InitialDirectory = System::IO::Directory::GetCurrentDirectory();
		openFileDialog->RestoreDirectory = true;
		openFileDialog->Title = "Select a ROM file";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			rom = new ROM(openFileDialog->FileName);
			ui_rom_tree->BeginUpdate();
			RomBrowser::ParseRom(rom);
			ui_rom_tree->EndUpdate();
		}
	}
	System::Void RomBrowser::ui_close_button_Click(System::Object^  sender, System::EventArgs^  e) {
		ui_rom_tree->BeginUpdate();
		ui_rom_tree->Nodes->Clear();
		ui_rom_tree->EndUpdate();
	}
	System::Void RomBrowser::ui_expand_button_Click(System::Object^  sender, System::EventArgs^  e) {
		ui_rom_tree->BeginUpdate();
		ui_rom_tree->ExpandAll();
		ui_rom_tree->EndUpdate();
	}
	System::Void RomBrowser::ui_collapse_button_Click(System::Object^  sender, System::EventArgs^  e) {
		ui_rom_tree->BeginUpdate();
		ui_rom_tree->CollapseAll();
		ui_rom_tree->EndUpdate();
	}
	
	System::Void RomBrowser::ui_rom_tree_AfterSelect(
		System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
		if (e->Node->Tag) {
			int entryAdr = (int)e->Node->Tag;
			TRomEntry* entry = (TRomEntry*)rom->getPointerTo(entryAdr);
			
			ui_textbox->Text = "iSize: 0x" + entry->iSize.ToString("X") + "\r\n"
				+ "iAddressLin: " + entry->iAddressLin.ToString("X") + "\r\n"
				+ "iAtt:" + entry->iAtt.ToString("X") + "\r\n"
				+ "iNameLength: 0x" + entry->iNameLength.ToString("X") + "\r\n"
				+ "iName: " + String(entry->name).ToString() + "\r\n";
			ui_textbox->Text += "========" + "\r\n";
			
			for (UInt32 it = 0; it < entry->iSize; it++) {
				if (it % 16 == 0) {
					ui_textbox->Text += "\r\n" + (entry->iAddressLin + it).ToString("X") + ": ";
				}
				UInt8 x = rom->read8(entry->iAddressLin + it);
				ui_textbox->Text += x.ToString("X2") + " ";
				if (it > 254) {
					ui_textbox->Text += "\r\n" + "...... ";
					break;
				}
			}
		}
	}
	
	System::Void RomBrowser::ParseRom(ROM* rom) {

		TRomRootDirectoryList* tRomRootDirectoryList = (TRomRootDirectoryList*)
			rom->getPointerTo(rom->getHeaderAddress()->iRomRootDirectoryList);

		//Console::WriteLine(rom->getHeaderAddress()->iRomRootDirectoryList.ToString("X"));
		//Console::WriteLine(tRomRootDirectoryList->iNumRootDirs.ToString("X"));
		//Console::WriteLine(tRomRootDirectoryList->iHardwareVariant.ToString("X"));
		//Console::WriteLine(tRomRootDirectoryList->iAddressLin.ToString("X"));
		//Console::WriteLine("========");
	
		array<PathElement^>^ path = gcnew array<PathElement^>(128);
		for (int i = 0; i < 128; i++) {
			path[i] = gcnew PathElement();
		}
		// add root node
		int pathLevel = 0;
		path[pathLevel]->parentNode = ui_rom_tree->Nodes->Add("Z:");
		pathLevel++;

		path[pathLevel]->address = tRomRootDirectoryList->iAddressLin;
		path[pathLevel]->sizeT = rom->read(tRomRootDirectoryList->iAddressLin);
		path[pathLevel]->offset = 4;
				
		while (pathLevel > 0) {

			while (path[pathLevel]->offset < path[pathLevel]->sizeT) {

				int entryAdr = path[pathLevel]->address + path[pathLevel]->offset;
				TRomEntry* entry = (TRomEntry*) rom->getPointerTo(entryAdr);

				for (int i = 0; i < entry->iNameLength; i++) {
					entry->name[i] = *(&entry->iName + 2 * i);
				}
				entry->name[entry->iNameLength] = 0;

				//Console::WriteLine("iSize:" + entry->iSize.ToString("X"));
				//Console::WriteLine("iAddressLin:" + entry->iAddressLin.ToString("X"));
				//Console::WriteLine("iAtt:" + entry->iAtt.ToString("X"));
				//Console::WriteLine("iNameLength:" + entry->iNameLength.ToString("X"));
				//Console::WriteLine("iName:" + String(entry->name).ToString());

				path[pathLevel]->offset += 10/*sz+adr+att+len*/ + entry->iNameLength * 2/*name*/;
				if (path[pathLevel]->offset & 0x03)
					path[pathLevel]->offset += 4 - (path[pathLevel]->offset & 0x03); // align to 4 bytes

				if (entry->iAtt == 0x10) { // director
					path[pathLevel]->parentNode = path[pathLevel - 1]->parentNode->Nodes->Add(String(entry->name).ToString());
					path[pathLevel]->parentNode->Tag = entryAdr;

					pathLevel++;
					path[pathLevel]->address = entry->iAddressLin;
					path[pathLevel]->sizeT = rom->read(entry->iAddressLin);
					path[pathLevel]->offset = 4;
					pathLevel++;
					break;
				}
				else if (entry->iAtt == 0x01) { // file
					TreeNode^ node = path[pathLevel - 1]->parentNode->Nodes->Add(String(entry->name).ToString());
					node->Tag = entryAdr;
				}
			}
			pathLevel--;
		}
	}
}