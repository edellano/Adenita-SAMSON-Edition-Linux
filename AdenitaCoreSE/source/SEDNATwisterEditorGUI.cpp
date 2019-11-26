#include "SEDNATwisterEditorGUI.hpp"
#include "SEDNATwisterEditor.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEDNATwisterEditorGUI::SEDNATwisterEditorGUI(SEDNATwisterEditor* editor) {

	ui.setupUi( this );
	this->editor = editor;

}

SEDNATwisterEditorGUI::~SEDNATwisterEditorGUI() {

}

SEDNATwisterEditor* SEDNATwisterEditorGUI::getEditor() const { return editor; }

void SEDNATwisterEditorGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;
	
	// SAMSON Element generator pro tip: complete this function so your editor can save its GUI state from one session to the next

}

void SEDNATwisterEditorGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;

	// SAMSON Element generator pro tip: complete this function so your editor can save its GUI state from one session to the next

}

void SEDNATwisterEditorGUI::setUntwistTwist()
{
  SEDNATwisterEditor* t = getEditor();
  t->setBendingType(BendingType::UNTWIST);
}

void SEDNATwisterEditorGUI::setInvisibleVisible()
{
  SEDNATwisterEditor* t = getEditor();
  t->setBendingType(BendingType::SPHEREVISIBILITY);

}

void SEDNATwisterEditorGUI::resetUntwist()
{

}

void SEDNATwisterEditorGUI::resetInvisible()
{

}

SBCContainerUUID SEDNATwisterEditorGUI::getUUID() const { return SBCContainerUUID( "B2208669-EAE5-DEC5-00EB-A241BBA72C29" );}

QPixmap SEDNATwisterEditorGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your editor.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEDNATwisterEditorIcon.png"));

}

QString SEDNATwisterEditorGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your editor inside SAMSON

	return "aDeNitA Teister Editor"; 

}

int SEDNATwisterEditorGUI::getFormat() const {

	// SAMSON Element generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEDNATwisterEditorGUI::getCitation() const {

	// SAMSON Element generator pro tip: modify this function to add citation information

  return ADNAuxiliary::AdenitaCitation();
}
