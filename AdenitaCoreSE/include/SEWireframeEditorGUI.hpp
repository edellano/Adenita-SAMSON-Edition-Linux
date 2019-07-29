#pragma once


#include "SBGWindowWidget.hpp" 
#include "ui_SEWireframeEditorGUI.h"

class SEWireframeEditor;

/// This class implements the GUI of the editor

// SAMSON Element generator pro tip: add GUI functionality in this class. 
// The non-GUI functionality (and the mouse and keyboard event handling methods that are specific to the editor) should go in the SEWireframeEditor class

class SEWireframeEditorGUI : public SBGWindowWidget {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEWireframeEditorGUI(SEWireframeEditor* editor);																		///< Constructs a GUI for the editor
	virtual ~SEWireframeEditorGUI();																										///< Destructs the GUI of the editor

	//@}

	/// \name Editor
	//@{

	SEWireframeEditor*												getEditor() const;														///< Returns a pointer to the editor

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const;														///< Returns the widget UUID
	virtual QString												getName() const;														///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const;														///< Returns the widget logo
	int															getFormat() const;														///< Returns the widget format
	virtual QString												getCitation() const;													///< Returns the citation information

	//@}

	///\name Settings
	//@{

	void														loadSettings(SBGSettings* settings);										///< Load GUI settings
	void														saveSettings(SBGSettings* settings);										///< Save GUI settings

	//@}
  public slots:
  void                            onTetrahedronClicked();
  void                            onCubeClicked();
  void                            onCuboidClicked();
  void                            onOctahedronClicked();
  void                            onDodecahedronClicked();
  void                            onCubocahedronClicked();
  void                            onIcosahedronClicked();
  void                            onIcosidodecahedronClicked();
  void                            onRhombicuboctahedronClicked();
  void                            onSnubCubeClicked();
  void                            onTruncatedCubeClicked();
  void                            onTruncatedCuboctahedronClicked();
  void                            onHelixClicked();
  void                            onStickmanClicked();
  void                            onBunnyClicked();
private:

	Ui::SEWireframeEditorGUIClass									ui;
	SEWireframeEditor*												editor;

};

