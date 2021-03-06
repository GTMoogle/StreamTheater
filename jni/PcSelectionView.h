/************************************************************************************

Filename    :   PcSelectionView.h
Content     :
Created     :	6/19/2014
Authors     :   Jim Dos�

Copyright   :   Copyright 2014 Oculus VR, LLC. All Rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the Cinema/ directory. An additional grant 
of patent rights can be found in the PATENTS file in the same directory.

*************************************************************************************/

#if !defined( PcSelectionView_h )
#define PcSelectionView_h

#include "Kernel/OVR_Array.h"
#include "Lerp.h"
#include "SelectionView.h"
#include "CarouselBrowserComponent.h"
#include "PcManager.h"
#include "UI/UITexture.h"
#include "UI/UIMenu.h"
#include "UI/UIContainer.h"
#include "UI/UILabel.h"
#include "UI/UIImage.h"
#include "UI/UITextButton.h"
#include "UI/UIButton.h"

using namespace OVR;

namespace VRMatterStreamTheater {

class CinemaApp;
class CarouselBrowserComponent;
class MovieSelectionComponent;

class PcSelectionView : public SelectionView
{
public:
										PcSelectionView( CinemaApp &cinema );
	virtual 							~PcSelectionView();

	virtual void 						OneTimeInit( const char * launchIntent );
	virtual void						OneTimeShutdown();

	virtual void 						OnOpen();
	virtual void 						OnClose();

	virtual Matrix4f 					DrawEyeView( const int eye, const float fovDegrees );
	virtual Matrix4f 					Frame( const VrFrame & vrFrame );
	virtual bool						Command( const char * msg );
	virtual bool 						OnKeyEvent( const int keyCode, const int repeatCount, const KeyEventType eventType );

	void 								SetPcList( const Array<const PcDef *> &movies, const PcDef *nextMovie );

	virtual void 						Select( void );
	virtual void 						SelectionHighlighted( bool isHighlighted );
    virtual void 						SetCategory( const PcCategory category );
	virtual void								SetError( const char *text, bool showSDCard, bool showErrorIcon );
	virtual void								ClearError();

private:
	class PcCategoryButton
	{
	public:
		PcCategory 	Category;
		String			Text;
		UILabel *		Button;
		float			Width;
		float			Height;

					PcCategoryButton( const PcCategory category, const String &text ) :
						Category( category ), Text( text ), Button( NULL ), Width( 0.0f ), Height( 0.0f ) {}
	};

private:
	CinemaApp &							Cinema;

	UITexture 							SelectionTexture;
	UITexture							Is3DIconTexture;
	UITexture							ShadowTexture;
	UITexture							BorderTexture;
	UITexture							SwipeIconLeftTexture;
	UITexture							SwipeIconRightTexture;
	UITexture							ResumeIconTexture;
	UITexture							ErrorIconTexture;
	UITexture							SDCardTexture;
	UITexture							CloseIconTexture;

	UIMenu *							Menu;

	UIContainer *						CenterRoot;

	UILabel * 							ErrorMessage;
	UILabel * 							SDCardMessage;
	UILabel * 							PlainErrorMessage;
	
	bool								ErrorMessageClicked;

	UIContainer *						MovieRoot;
	UIContainer *						CategoryRoot;
	UIContainer *						TitleRoot;

	UILabel	*							MovieTitle;

	UIImage *							SelectionFrame;

	UIImage *							CenterPoster;
	UPInt								CenterIndex;
	Vector3f							CenterPosition;

	UIImage *							LeftSwipes[ 3 ];
	UIImage * 							RightSwipes[ 3 ];

	UILabel	*							ResumeIcon;
	UIButton *							CloseAppButton;

	UILabel *							TimerIcon;
	UILabel *							TimerText;
	double								TimerStartTime;
	int									TimerValue;
	bool								ShowTimer;

	UILabel *							MoveScreenLabel;
	Lerp								MoveScreenAlpha;

	Lerp								SelectionFader;

	CarouselBrowserComponent *			MovieBrowser;
	Array<CarouselItem *> 				MovieBrowserItems;
	Array<PanelPose>					MoviePanelPositions;

	Array<CarouselItemComponent *>	 	MoviePosterComponents;

	Array<PcCategoryButton>				Categories;
    PcCategory			 				CurrentCategory;
	
	Array<const PcDef *> 				MovieList;
	int									MoviesIndex;

	const PcDef *						LastMovieDisplayed;

	bool								RepositionScreen;
	bool								HadSelection;

	int									newPCWidth;
	int									newPCHeight;
	GLuint								newPCTex;

	UIContainer *						newPCMenu;
	UITexture							bgTintTexture;
	UIImage								newPCbg;
	UILabel								newPCIPLabel;
	Array<UITextButton*>				newPCIPButtons;
	int 								IPoctets[4];
	int									currentOctet;
	String								IPString;

private:
	const PcDef *						GetSelectedPc() const;

	void 								CreateMenu( OvrGuiSys & guiSys );
	Vector3f 							ScalePosition( const Vector3f &startPos, const float scale, const float menuOffset ) const;
	void 								UpdateMenuPosition();

	void								StartTimer();

	void								UpdatePcTitle();
	void								UpdateSelectionFrame( const VrFrame & vrFrame );

	bool								ErrorShown() const;

	friend void							NewPCIPButtonCallback( UITextButton *button, void *object );
	void								NewPCIPButtonPressed( UITextButton *button );

	friend void							CloseAppButtonCallback( UIButton *button, void *object );
	void								CloseAppButtonPressed();

	bool								BackPressed();

};

} // namespace VRMatterStreamTheater

#endif // PcSelectionView_h
