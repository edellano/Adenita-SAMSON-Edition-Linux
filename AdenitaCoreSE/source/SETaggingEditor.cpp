#include "SETaggingEditor.hpp"
#include "SAMSON.hpp"
#include <QInputDialog>


SETaggingEditor::SETaggingEditor() {

	// SAMSON Element generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	propertyWidget = new SETaggingEditorGUI(this);
	propertyWidget->loadDefaultSettings();
	SAMSON::addWidget(propertyWidget);

}

SETaggingEditor::~SETaggingEditor() {

	// SAMSON Element generator pro tip: disconnect from signals you might have connected to.

	propertyWidget->saveDefaultSettings();
	delete propertyWidget;

}

SETaggingEditorGUI* SETaggingEditor::getPropertyWidget() const { return static_cast<SETaggingEditorGUI*>(propertyWidget); }

SBCContainerUUID SETaggingEditor::getUUID() const { return SBCContainerUUID("2A1B195E-3E38-BD20-1B61-70A3CA6761C8"); }

QString SETaggingEditor::getName() const { 

	// SAMSON Element generator pro tip: this name should not be changed

	return "SETaggingEditor"; 

}

QString SETaggingEditor::getText() const { 
	
	// SAMSON Element generator pro tip: modify this function to return a user-friendly string that will be displayed in menus

	return QObject::tr("Tagging Editor"); 

}

QPixmap SETaggingEditor::getLogo() const {

	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your editor.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/Icons/SETaggingEditorIcon.png"));

}

QKeySequence SETaggingEditor::getShortcut() const { 
	
	// SAMSON Element generator pro tip: modify this function to associate a tentative shortcut to your editor

	return QKeySequence(""); 

}

QString SETaggingEditor::getToolTip() const { 
	
	// SAMSON Element generator pro tip: modify this function to have your editor display a tool tip in the SAMSON GUI when the mouse hovers the editor's icon

	return QObject::tr("Tag nucleotides or change their base. The tag will appear when exporting sequences."); 

}

QString SETaggingEditor::getDescription() const
{
  return QObject::tr("Adenita | Tagging Editor");
}

void SETaggingEditor::beginEditing() {

	// SAMSON Element generator pro tip: SAMSON calls this function when your editor becomes active. 
	// Implement this function if you need to prepare some data structures in order to be able to handle GUI or SAMSON events.

  string iconPath = SB_ELEMENT_PATH + "/Resource/icons/cursor_tagging.png";
  SAMSON::setViewportCursor(QCursor(QPixmap(iconPath.c_str())));
}

void SETaggingEditor::endEditing() {

	// SAMSON Element generator pro tip: SAMSON calls this function immediately before your editor becomes inactive (for example when another editor becomes active). 
	// Implement this function if you need to clean some data structures.

}

void SETaggingEditor::getActions(SBVector<SBAction*>& actionVector) {

	// SAMSON Element generator pro tip: SAMSON calls this function to show the user actions associated to your editor in context menus.
	// Append actions to the actionVector if necessary.
	// Please refer to tutorials for examples.

}

void SETaggingEditor::display() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

  if (mode_ == TaggingMode::Base) {
    std::string base(1, ADNModel::GetResidueName(ntType_));
    SBPosition3 pos = SAMSON::getWorldPositionFromViewportPosition(SAMSON::getMousePositionInViewport());
    ADNDisplayHelper::displayText(pos, base);
  }
}


void SETaggingEditor::displayForShadow() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to compute shadows. 
	// Implement this function if your editor displays things in viewports, so that your editor can cast shadows
	// to other objects in SAMSON, for example thanks to the utility
	// functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SETaggingEditor::displayInterface() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to display the editor 2D interface in viewports. 
	// Implement this function if your editor displays a 2D user interface. For example, a rectangle selection editor would display a 2D rectangle in the active viewport. 
	// You may use utility functions provided by SAMSON (e.g. displayLinesOrtho and displayTrianglesOrtho).

}

void SETaggingEditor::mousePressEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.


}

void SETaggingEditor::mouseReleaseEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

  auto nt = GetHighlightedNucleotide();

  if (nt != nullptr) {
    if (mode_ == TaggingMode::Tags) {
      bool ok;
      QString text = QInputDialog::getText(this, tr("Enter Nucleotide Tag"),
        tr("Tag:"), QLineEdit::Normal, QString(), &ok);
      if (ok && !text.isEmpty()) {
        nt->setTag(text.toStdString());
        nt->setSelectionFlag(true);
      }
    }
    else if (mode_ == TaggingMode::Base) {
      ADNBasicOperations::MutateNucleotide(nt, ntType_);
    }
    getAdenitaApp()->ResetVisualModel();
  }
}

void SETaggingEditor::mouseMoveEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.


}

void SETaggingEditor::mouseDoubleClickEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SETaggingEditor::wheelEvent(QWheelEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

  QPoint numDegrees = event->angleDelta() / 8;
  if (!numDegrees.isNull()) {
    QPoint numSteps = numDegrees / 15;
    ntType_ = GetNtType(numSteps);
  }
}

void SETaggingEditor::keyPressEvent(QKeyEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SETaggingEditor::keyReleaseEvent(QKeyEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SETaggingEditor::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle base events

}

void SETaggingEditor::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle document events 

}

void SETaggingEditor::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle dynamical events 

}

void SETaggingEditor::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Element generator pro tip: implement this function if you need to handle structural events

}

ADNPointer<ADNNucleotide> SETaggingEditor::GetHighlightedNucleotide()
{
  ADNPointer<ADNNucleotide> nt = nullptr;
  auto highlightedNucleotides = getAdenitaApp()->GetNanorobot()->GetHighlightedNucleotides();

  if (highlightedNucleotides.size() == 1) {
    nt = highlightedNucleotides[0];
  }


  return nt;
}

void SETaggingEditor::changeMode(int mode)
{
  mode_ = TaggingMode(mode);
}

SEAdenitaCoreSEApp * SETaggingEditor::getAdenitaApp() const
{
  return static_cast<SEAdenitaCoreSEApp*>(SAMSON::getApp(SBCContainerUUID("85DB7CE6-AE36-0CF1-7195-4A5DF69B1528"), SBUUID("DDA2A078-1AB6-96BA-0D14-EE1717632D7A")));
}

DNABlocks SETaggingEditor::GetNtType(QPoint numSteps)
{
  DNABlocks t = ntType_;

  std::map<int, DNABlocks> values = {
    {0, DNABlocks::DA},
    {1, DNABlocks::DT},
    {2, DNABlocks::DC},
    {3, DNABlocks::DG},
    {4, DNABlocks::DI}
  };

  std::map<DNABlocks, int> indices = {
    {DNABlocks::DA, 0},
    {DNABlocks::DT, 1},
    {DNABlocks::DC, 2},
    {DNABlocks::DG, 3},
    {DNABlocks::DI, 4}
  };

  int currIndex = indices[t];
  int newIndex = currIndex + numSteps.y();
  // keep new index between 0 and 4
  size_t numValues = values.size();
  if (newIndex < 0) {
    int turns = abs(newIndex);
    std::div_t divresult;
    divresult = std::div(turns, numValues);
    newIndex = numValues - divresult.rem + 1;
  }
  else if (newIndex > 4) {
    int turns = newIndex + 1; // take into account 0
    std::div_t divresult;
    divresult = std::div(turns, numValues);
    newIndex = divresult.rem;
  }
  t = values[newIndex];
  return t;
}

