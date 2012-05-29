#include "MainForm.h"

#include "SimulationSettingForm.h"
#include "ObjectSettingForm.h"
#include "ParticleObserveForm.h"
#include "BoundarySettingForm.h"
#include "GraphicsSettingForm.h"
#include "ExportSettingForm.h"

using namespace Crystal::Command;
using namespace Crystal::UI;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::IO;

MainForm::MainForm()
{
	InitializeComponent();

	pictureBox1->Image = gcnew Bitmap( pictureBox1->Width, pictureBox1->Height );
	command = gcnew MainCommand( pictureBox1 );
}

MainForm::~MainForm()
{
	if (components) {
		delete components;
	}
}

System::Void MainForm::MainForm_Load(System::Object^  sender, System::EventArgs^  e)
{
}

System::Void MainForm::buttonNextStep_Click(System::Object ^sender, System::EventArgs ^e) {
	command->proceedSimulation();
	command->displayInformation( listBoxInformation );
}

System::Void MainForm::timerSimulation_Tick(System::Object^  sender, System::EventArgs^  e)
{
	command->proceedSimulation();
	command->displayInformation( listBoxInformation );
}

System::Void MainForm::buttonStart_Click(System::Object ^sender, System::EventArgs ^e) {
	timerSimulation->Enabled = !timerSimulation->Enabled;
}

System::Void MainForm::buttonSimulationRefresh_Click(System::Object ^sender, System::EventArgs ^e) {
	command->refreshSimulation();
	command->displayInformation( listBoxInformation );
}

System::Void MainForm::simulationSettingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	SimulationSettingForm^ form = gcnew SimulationSettingForm( command->getSimulationSettingCommand() );
	form->Show();
}

System::Void MainForm::sToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	SimulationSettingForm^ form = gcnew SimulationSettingForm( command->getSimulationSettingCommand() );
	form->Show();
}

System::Void MainForm::objectSettingToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e)
{
	ObjectSettingForm^ form = gcnew ObjectSettingForm( command->getObjectSettingCommand() );
	form->Show();
}

System::Void MainForm::toolStripMenuItemOpen_Click(System::Object^  sender, System::EventArgs^  e)
{
	command->getFileIOCommand()->fileOpen();
}

System::Void MainForm::toolStripMenuItemSaveAs_Click(System::Object^  sender, System::EventArgs^  e)
{
	command->getFileIOCommand()->fileSave();
}

System::Void MainForm::toolStripMenuItemSave_Click(System::Object^  sender, System::EventArgs^  e)
{
	command->getFileIOCommand()->fileSaveOverride();
}

System::Void MainForm::toolStripMenuItemClose_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}

System::Void MainForm::MainForm_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e){
	if( e->Data->GetDataPresent( System::Windows::Forms::DataFormats::FileDrop ) ) {
		e->Effect = System::Windows::Forms::DragDropEffects::All;
	}
}

System::Void MainForm::MainForm_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e ) {
	array<String^>^ files = dynamic_cast<array<String^>^>(
		e->Data->GetData( DataFormats::FileDrop ) );
	String^ path = files[0];

	if( !command->getFileIOCommand()->fileOpen( path ) ) {
		MessageBox::Show("Unexpected File Format");
	}
	System::String^ fileName = path;
}

System::Void MainForm::particleInfoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	ParticleObserveForm^ form = gcnew ParticleObserveForm( command->getParticleInfoCommand() );
	form->Show();
	form->onDisplay();
}

System::Void MainForm::objectInfoOToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
}

System::Void MainForm::boundarySettingBToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	BoundarySettingForm^ form = gcnew BoundarySettingForm( command->getBoundarySettingCommand() );
	form->Show();
}

System::Void MainForm::graphicsSettingGToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	GraphicsSettingForm^ form = gcnew GraphicsSettingForm( command );
	form->Show();
}

System::Void MainForm::saveImagesIToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e) {
	ExportSettingForm^ form = gcnew ExportSettingForm( command->getExportSettingCommand() );
	form->Show();
}

System::Void MainForm::exportParticleEToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	ExportSettingForm^ form = gcnew ExportSettingForm( command->getParticleExportSettingCommand() );
	form->Show();
}

System::Void MainForm::simulationSettingSToolStripMenuItem_Click(System::Object ^sender, System::EventArgs ^e){
	simulationSettingToolStripMenuItem_Click(sender, e );
}

System::Void MainForm::MainForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e){
	switch( e->KeyCode ) {
	case System::Windows::Forms::Keys::D :
		command->zoom(0.1);
		break;
	case System::Windows::Forms::Keys::Z :
		command->zoom(-0.1);
		break;
	}
}

System::Void MainForm::MainForm_MouseWheel(System::Object^ , System::Windows::Forms::MouseEventArgs^ e){
	const double zoom = -e->Delta / 240.0;
	command->zoom(zoom);
}

System::Void MainForm::pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if( isLeftDown && ( e->Button == System::Windows::Forms::MouseButtons::Left ) ) {
		double diffX = -(previousPoint.X - e->Location.X) / 1000.0;
		double diffY = -(previousPoint.Y - e->Location.Y) / 1000.0;
		System::Diagnostics::Debug::WriteLine( "diffX = " + diffX + "diffY = " + diffY );
		command->move( diffX, diffY );
		previousPoint = e->Location;
	}
	else if( isRightDown && ( e->Button == System::Windows::Forms::MouseButtons::Right ) ) {
		int angleY = -(previousPoint.X - e->Location.X);
		int angleX = -(previousPoint.Y - e->Location.Y);
		command->rotateX(angleX);
		command->rotateY(angleY);
		previousPoint = e->Location;
	}
}

System::Void MainForm::pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if( e->Button == System::Windows::Forms::MouseButtons::Left ) {
		previousPoint = e->Location;
		isLeftDown = true;
	}
	if( e->Button == System::Windows::Forms::MouseButtons::Right ) {
		previousPoint = e->Location;
		isRightDown = true;
	}
}

System::Void MainForm::pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
	isLeftDown = false;
	isRightDown = false;
}

System::Void MainForm::buttonViewReset_Click(System::Object^  sender, System::EventArgs^  e) {
	command->viewReset();
}

System::Void MainForm::buttonParticleInfo_Click(System::Object^  sender, System::EventArgs^  e) {
	ParticleObserveForm^ form = gcnew ParticleObserveForm( command->getParticleInfoCommand() );
	form->Show();
	form->onDisplay();
}