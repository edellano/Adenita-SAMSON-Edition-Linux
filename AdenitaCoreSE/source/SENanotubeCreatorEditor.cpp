#include "SENanotubeCreatorEditor.hpp"
#include "SAMSON.hpp"


SENanotubeCreatorEditor::SENanotubeCreatorEditor() {

	// SAMSON Element generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	propertyWidget = new SENanotubeCreatorEditorGUI(this);
	propertyWidget->loadDefaultSettings();

}

SENanotubeCreatorEditor::~SENanotubeCreatorEditor() {

	// SAMSON Element generator pro tip: disconnect from signals you might have connected to.

	propertyWidget->saveDefaultSettings();
	delete propertyWidget;

}

SENanotubeCreatorEditorGUI* SENanotubeCreatorEditor::getPropertyWidget() const { return static_cast<SENanotubeCreatorEditorGUI*>(propertyWidget); }

void SENanotubeCreatorEditor::SetRouting(RoutingType t)
{
  routing_ = t;
}

void SENanotubeCreatorEditor::SetPredefined(bool predefined, double radius, int numBp)
{
  predefined_ = false;
  if (radius > 0.0 && numBp > 0) {
    predefined_ = predefined;
    numBp_ = numBp;
    radius_ = radius;
  }
}

void SENanotubeCreatorEditor::SetRadius(double radius)
{
  radius_ = radius;
}

void SENanotubeCreatorEditor::SetBp(int bp)
{
  numBp_ = bp;
}

ADNPointer<ADNPart> SENanotubeCreatorEditor::generateNanotube(bool mock)
{
  ADNPointer<ADNPart> part = nullptr;

  auto radius = (positions_.ThirdPosition - positions_.SecondPosition).norm();
  auto roundHeight = (positions_.SecondPosition - positions_.FirstPosition).norm();
  auto numNucleotides = round((roundHeight / SBQuantity::nanometer(ADNConstants::BP_RISE)).getValue());
  SBVector3 dir = (positions_.SecondPosition - positions_.FirstPosition).normalizedVersion();
  if (predefined_) {
    numNucleotides = numBp_;
    radius = SBQuantity::nanometer(radius_);
  }

  if (numNucleotides > 0) {
    if (mock) {
      if (positions_.positionsCounter == 1 && !predefined_) {
        radius = SBQuantity::picometer(1);
        part = DASCreator::CreateMockNanotube(radius, positions_.FirstPosition, dir, numNucleotides);
      }
      else if (positions_.positionsCounter == 2 || predefined_) {
        part = DASCreator::CreateMockNanotube(radius, positions_.FirstPosition, dir, numNucleotides);
      }
    }
    else {
      part = DASCreator::CreateNanotube(radius, positions_.FirstPosition, dir, numNucleotides);
    }
    updateGUI(radius, numNucleotides);
  }

  return part;
}

void SENanotubeCreatorEditor::displayNanotube()
{
  ADNDisplayHelper::displayPart(tempPart_);
}

void SENanotubeCreatorEditor::sendPartToAdenita(ADNPointer<ADNPart> nanotube)
{
  if (nanotube != nullptr) {
    SEAdenitaCoreSEApp* adenita = static_cast<SEAdenitaCoreSEApp*>(SAMSON::getApp(SBCContainerUUID("85DB7CE6-AE36-0CF1-7195-4A5DF69B1528"), SBUUID("DDA2A078-1AB6-96BA-0D14-EE1717632D7A")));
    adenita->AddPartToActiveLayer(nanotube);
    adenita->ResetVisualModel();
  }
}

void SENanotubeCreatorEditor::updateGUI(SBQuantity::length radius, int numBp, bool clear)
{
  if (numBp < 1) numBp = 0;

  int minNumDs = 3;
  SBQuantity::length minRadius = ADNVectorMath::CalculateNanotubeRadius(minNumDs);

  int numDs = ADNVectorMath::CalculateNanotubeDoubleStrands(radius);
  if (numDs < minNumDs || radius < minRadius) {
    numDs = minNumDs;
    radius = minRadius;
  }

  SENanotubeCreatorEditorGUI* gui = static_cast<SENanotubeCreatorEditorGUI*>(propertyWidget);
  gui->updateInfo(radius, numDs, numBp, clear);
}

SBCContainerUUID SENanotubeCreatorEditor::getUUID() const { return SBCContainerUUID("F9068FA3-69DE-B6FA-2B42-C80DA5302A0D"); }

QString SENanotubeCreatorEditor::getName() const { 

	// SAMSON Element generator pro tip: this name should not be changed

	return "SENanotubeCreatorEditor"; 

}

QString SENanotubeCreatorEditor::getText() const { 
	
	// SAMSON Element generator pro tip: modify this function to return a user-friendly string that will be displayed in menus

	return QObject::tr("DNA Nanotube Creator"); 

}

QPixmap SENanotubeCreatorEditor::getLogo() const {

	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your editor.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SENanotubeCreatorEditorIcon.png"));

}

QKeySequence SENanotubeCreatorEditor::getShortcut() const { 
	
	// SAMSON Element generator pro tip: modify this function to associate a tentative shortcut to your editor

	return QKeySequence(""); 

}

QString SENanotubeCreatorEditor::getToolTip() const { 
	
	// SAMSON Element generator pro tip: modify this function to have your editor display a tool tip in the SAMSON GUI when the mouse hovers the editor's icon

	return QObject::tr("DNA Nanotube Creator"); 

}

QString SENanotubeCreatorEditor::getDescription() const
{
  return QObject::tr("Adenita | DNA Nanotube Editor");
}

void SENanotubeCreatorEditor::beginEditing() {

	// SAMSON Element generator pro tip: SAMSON calls this function when your editor becomes active. 
	// Implement this function if you need to prepare some data structures in order to be able to handle GUI or SAMSON events.
  string iconPath = SB_ELEMENT_PATH + "/Resource/icons/nanotubeCreator.png";
  SAMSON::setViewportCursor(QCursor(QPixmap(iconPath.c_str())));

}

void SENanotubeCreatorEditor::endEditing() {

	// SAMSON Element generator pro tip: SAMSON calls this function immediately before your editor becomes inactive (for example when another editor becomes active). 
	// Implement this function if you need to clean some data structures.
  SAMSON::unsetViewportCursor();
}

void SENanotubeCreatorEditor::getActions(SBVector<SBAction*>& actionVector) {

	// SAMSON Element generator pro tip: SAMSON calls this function to show the user actions associated to your editor in context menus.
	// Append actions to the actionVector if necessary.
	// Please refer to tutorials for examples.

}

void SENanotubeCreatorEditor::display() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

  SEConfig& config = SEConfig::GetInstance();

  if (display_) {
    SBPosition3 currentPosition = SAMSON::getWorldPositionFromViewportPosition(SAMSON::getMousePositionInViewport());

    if (positions_.positionsCounter == 1) {
      ADNDisplayHelper::displayLine(positions_.FirstPosition, currentPosition);
      positions_.SecondPosition = currentPosition;
    }
    else if (positions_.positionsCounter == 2) {
      ADNDisplayHelper::displayLine(positions_.FirstPosition, positions_.SecondPosition);
      ADNDisplayHelper::displayLine(positions_.SecondPosition, currentPosition);

      positions_.ThirdPosition = currentPosition;
    }

    if (config.preview_editor) tempPart_ = generateNanotube(true);

    if (tempPart_ != nullptr) {

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      displayNanotube();

      glDisable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);

    }
  }

}

void SENanotubeCreatorEditor::displayForShadow() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to compute shadows. 
	// Implement this function if your editor displays things in viewports, so that your editor can cast shadows
	// to other objects in SAMSON, for example thanks to the utility
	// functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SENanotubeCreatorEditor::displayInterface() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to display the editor 2D interface in viewports. 
	// Implement this function if your editor displays a 2D user interface. For example, a rectangle selection editor would display a 2D rectangle in the active viewport. 
	// You may use utility functions provided by SAMSON (e.g. displayLinesOrtho and displayTrianglesOrtho).

}

void SENanotubeCreatorEditor::mousePressEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

  if (positions_.positionsCounter == 0) {
    updateGUI(SBQuantity::nanometer(0.0), 0, true);

    positions_.FirstPosition = SAMSON::getWorldPositionFromViewportPosition(SAMSON::getMousePositionInViewport());
    positions_.positionsCounter++;
  }
  else if (positions_.positionsCounter == 2) {
    positions_.ThirdPosition = SAMSON::getWorldPositionFromViewportPosition(SAMSON::getMousePositionInViewport());
    positions_.positionsCounter++;

    auto radius = (positions_.ThirdPosition - positions_.SecondPosition).norm();

    ADNPointer<ADNPart> part = generateNanotube();
    //DASRouter* router = DASRouter::GetRouter(routing_);
    //router->Route(part);
    sendPartToAdenita(part);

    DASCreatorEditors::resetPositions(positions_);
    display_ = false;
    tempPart_ == nullptr;
  }
}

void SENanotubeCreatorEditor::mouseReleaseEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.
  if (positions_.positionsCounter == 1) {
    positions_.SecondPosition = SAMSON::getWorldPositionFromViewportPosition(SAMSON::getMousePositionInViewport());
    positions_.positionsCounter++;
  }
}

void SENanotubeCreatorEditor::mouseMoveEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

  if (event->buttons() == Qt::LeftButton) {
    display_ = true;
    //SAMSON::requestViewportUpdate();
  }
  SAMSON::requestViewportUpdate();
}

void SENanotubeCreatorEditor::mouseDoubleClickEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SENanotubeCreatorEditor::wheelEvent(QWheelEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SENanotubeCreatorEditor::keyPressEvent(QKeyEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SENanotubeCreatorEditor::keyReleaseEvent(QKeyEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SENanotubeCreatorEditor::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle base events

}

void SENanotubeCreatorEditor::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle document events 

}

void SENanotubeCreatorEditor::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle dynamical events 

}

void SENanotubeCreatorEditor::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Element generator pro tip: implement this function if you need to handle structural events

}
