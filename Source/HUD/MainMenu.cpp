/*
 * Copyright (c) 2014 empirer <email>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 40

#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/BorderImage.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIElement.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/IO/Log.h>

#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

//#include >DropDownMenu.h>

#include <Urho3D/UI/DropDownList.h>

#include <Urho3D/DebugNew.h>

#include "MainMenu.h"
#include <Urho3D/UI/ListView.h>


#include "../GUI/TMenu.h"
#include "../GUI/ComboBox.h"
#include "../GUI/ColorPicker.h"
#include "../GlobalSettings.h"
#include "../GUI/KeyControls.h"
#include "../TEvents.h"


/// TODO treba spravit funkciu ktora vytvori hlavne menu -> aby sa dalo pouzivat window_ pocas hry
///


MainMenu::MainMenu(Context *context) : 
    HUD(context),
    uiRoot_(GetSubsystem<UI>()->GetRoot())
{
    TMenu::RegisterObject(context_);
    ColorPicker::RegisterObject(context_);
    ComboBox::RegisterObject(context_);
    KeyControls::RegisterObject(context_);
}

MainMenu::~MainMenu()
{
    CleanMainMenu();
    wMainMenu->SetVisible(false);
    
    /// CHECK
    wMainMenu = NULL;
}

void MainMenu::Start()
{
    HUD::Start();
    
    // Initialize Window
    InitMainMenuWindow();
    
    // Create and add some controls to the Window
    InitControls();
    
    CreateMainMenu();
}

// DELETE
void MainMenu::InitControls()
{

}

void MainMenu::InitMainMenuWindow()
{
    // Create the Window and add it to the UI's root node
    wMainMenu = new Window(context_);
    uiRoot_->AddChild(wMainMenu);

    // Set Window size and layout settings
    wMainMenu->SetMinSize(100, 100);
    //window_->SetMaxSize(110, 440);
    wMainMenu->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    wMainMenu->SetAlignment(Urho3D::HA_LEFT, VA_CENTER);
    wMainMenu->SetPosition(50, 0);
    wMainMenu->SetName("window_");
    
    // Apply styles
    wMainMenu->SetStyleAuto();
    //window_->SetColor(Color(0, 0, 0, 0));
}

// ------ MENUS --------------------------------------------------------------
void MainMenu::CreateMainMenu()
{
    // Play
    Button* btPlay = CreateButton(wMainMenu, "Play", "Play", BUTTON_WIDTH, BUTTON_HEIGHT);
    btPlay->SetStyle("Button");
    // Options
    Button* btOptions = CreateButton(wMainMenu, "Options", "Options", BUTTON_WIDTH, BUTTON_HEIGHT);
    btOptions->SetStyle("Button");
    // TODO Map editor
    /*Button* btMapEditor = CreateButton(window_, "MapEditor", "MapEditor", BUTTON_WIDTH, BUTTON_HEIGHT);
    btMapEditor->SetEnabled(false);*/
    // Credits
    Button* btCredits = CreateButton(wMainMenu, "Credits", "Credits", BUTTON_WIDTH, BUTTON_HEIGHT);
    btCredits->SetStyle("Button");
    //btCredits->SetEnabled(false);
    // Quit
    Button* btQuit = CreateButton(wMainMenu, "Quit", "Quit", BUTTON_WIDTH, BUTTON_HEIGHT);
    btQuit->SetStyle("Button");
    
    // Subscribe also to all UI mouse clicks just to see where we have clicked
    SubscribeToEvent(btPlay, E_RELEASED, HANDLER(MainMenu, HandlePlayClicked));
    SubscribeToEvent(btOptions, E_RELEASED, HANDLER(MainMenu, HandleOptionsClicked));
    //SubscribeToEvent(btMapEditor, E_RELEASED, HANDLER(MainMenu, HandleMapEditorClicked));
    SubscribeToEvent(btCredits, E_RELEASED, HANDLER(MainMenu, HandleCreditsClicked));
    SubscribeToEvent(btQuit, E_RELEASED, HANDLER(MainMenu, HandleQuitClicked));
}

void MainMenu::CreatePlayMenu()
{
    // Labyrinth game button
    Button* btLabyrinth = CreateButton(wMainMenu, "Labyrinth", "Labyrinth", BUTTON_WIDTH, BUTTON_HEIGHT);
    btLabyrinth->SetMaxSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    
    // Dance game button
    Button* btDance = CreateButton(wMainMenu, "Dance", "Dance", BUTTON_WIDTH, BUTTON_HEIGHT);
    btDance->SetMaxSize(BUTTON_WIDTH, BUTTON_HEIGHT);

    // Back to main menu
    Button* btBack = CreateButton(wMainMenu, "Back", "Back to Main menu", BUTTON_WIDTH, BUTTON_HEIGHT);
    btBack->SetMaxSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    
    
    SubscribeToEvent(btLabyrinth, E_RELEASED, HANDLER(MainMenu, HandleLabyrinthClicked));
    //SubscribeToEvent(btDance, E_RELEASED, HANDLER(MainMenu, HandleDanceClicked));
    SubscribeToEvent(btBack, E_RELEASED, HANDLER(MainMenu, HandleMainMenuClicked));
}

void MainMenu::CreateOptionsWindow()
{
    
    // TODO pridat Translations
    wOptions = new Window(context_);
    wOptions->SetName("wAudio");
    wOptions->SetMinSize(500, 750);
    wOptions->SetMaxSize(500, 750);
    wOptions->SetPosition(-20, 0);
    wOptions->SetAlignment(Urho3D::HA_RIGHT, Urho3D::VA_CENTER);
    uiRoot_->AddChild(wOptions);
    wOptions->SetStyleAuto();
    
    // TODO divne umiestnenie txOption
    Text* txOption = CreateCaption("Options", "Options");
    wOptions->AddChild(txOption);
    txOption->SetPosition(15, 15);
    
    /* Audio Settings */
    // Sound ON/OFF
    CheckBox* cbSound = CreateCheckbox(wOptions, "Sound", "Sound", 20, 20, -30, 40);
    cbSound->SetStyle("CheckBox");
    
    // Sound stereo
    CheckBox* cbStereo = CreateCheckbox(wOptions, "Stereo", "Stereo", 20, 20, -30, 70);
    
    /* Video Settings */
    // Sound stereo
    CheckBox* cbFullscreen = CreateCheckbox(wOptions, "Fullscreen", "Fullscreen", 20, 20, -30, 140);
    
    
    ComboBox* cbxResolution = new ComboBox(context_);
    cbxResolution->SetParameters("cbxResolution", "Resolution", 20, 170);
    cbxResolution->SetHorizontalAlignment(Urho3D::HA_RIGHT);
    wOptions->AddChild(cbxResolution);
    cbxResolution->SetStyle("ComboBox");
    cbxResolution->SetPosition(-30, 170);
    
    // TODO dorobiť rozlíšenia obrazovky
    GlobalSettings* gs = GetSubsystem<GlobalSettings>();
    PODVector<IntVector2> fullResolutions = gs->GetFullscreenResolutions();
    
    gs->GetFullscreen();
    
    Vector<String> resolutions;

    String temp = "";
    for (int i = 0; i < fullResolutions.Size(); i++) {
	Variant x(fullResolutions[i].x_);
	Variant y(fullResolutions[i].y_);
	
	temp = x.ToString() + "x" + y.ToString();
	resolutions.Push(temp);
    }
    
    cbxResolution->SetItemsVector(resolutions);
    
    
    Text* txPlayer1 = new Text(context_);
    txPlayer1->SetName("txPlayer1");
    txPlayer1->SetStyleAuto();
    wOptions->AddChild(txPlayer1);
    txPlayer1->SetHorizontalAlignment(Urho3D::HA_CENTER);
    txPlayer1->SetText("Player 01");
    txPlayer1->SetColor(Color(0.9, 0.9, 0.9, 1));
    txPlayer1->SetPosition(-180 ,270);
    
    KeyControls *keyCtrl1 = new KeyControls(context_);
    keyCtrl1->SetName("keyCtrl1");
    keyCtrl1->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
    wOptions->AddChild(keyCtrl1);
    keyCtrl1->SetParameters("Player 01", KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
    keyCtrl1->SetPosition(-170, 280);
    
    
    Text* txPlayer2 = new Text(context_);
    txPlayer2->SetName("txPlayer2");
    txPlayer2->SetStyleAuto();
    wOptions->AddChild(txPlayer2);
    txPlayer2->SetHorizontalAlignment(Urho3D::HA_CENTER);
    txPlayer2->SetText("Player 02");
    txPlayer2->SetColor(Color(0.9, 0.9, 0.9, 1));
    txPlayer2->SetPosition(60 ,270);
    
    KeyControls *keyCtrl2 = new KeyControls(context_);
    keyCtrl2->SetName("keyCtrl2");
    keyCtrl2->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
    wOptions->AddChild(keyCtrl2);
    keyCtrl2->SetParameters("Player 02", KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
    keyCtrl2->SetPosition(70, 280);
    
    
    Text* txPlayer3 = new Text(context_);
    txPlayer3->SetName("txPlayer3");
    txPlayer3->SetStyleAuto();
    wOptions->AddChild(txPlayer3);
    txPlayer3->SetHorizontalAlignment(Urho3D::HA_CENTER);
    txPlayer3->SetText("Player 03");
    txPlayer3->SetColor(Color(0.9, 0.9, 0.9, 1));
    txPlayer3->SetPosition(-180 ,420);
    
    KeyControls *keyCtrl3 = new KeyControls(context_);
    keyCtrl3->SetName("keyCtrl3");
    keyCtrl3->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
    wOptions->AddChild(keyCtrl3);
    keyCtrl3->SetParameters("Player 03", KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
    keyCtrl3->SetPosition(-170, 430);
    

    Text* txPlayer4 = new Text(context_);
    txPlayer4->SetName("txPlayer4");
    txPlayer4->SetStyleAuto();
    wOptions->AddChild(txPlayer4);
    txPlayer4->SetHorizontalAlignment(Urho3D::HA_CENTER);
    txPlayer4->SetText("Player 04");
    txPlayer4->SetColor(Color(0.9, 0.9, 0.9, 1));
    txPlayer4->SetPosition(60 ,420);
    
    KeyControls *keyCtrl4 = new KeyControls(context_);
    keyCtrl4->SetName("keyCtrl4");
    keyCtrl4->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
    wOptions->AddChild(keyCtrl4);
    keyCtrl4->SetParameters("Player 04", KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
    keyCtrl4->SetPosition(70, 430);
    
    
    Button* btApply = CreateButton(wOptions, "Apply", "Apply", 120, 30);
    btApply->SetAlignment(Urho3D::HA_RIGHT, Urho3D::VA_BOTTOM);
    btApply->SetPosition(-15, -15);
    btApply->SetStyle("Buttonn");
    
    
    SubscribeToEvent(btApply, E_RELEASED, HANDLER(MainMenu, HandleOptionsApplyClicked));
    /* Language Settings */
}

void MainMenu::CreateCreditsWindow()
{
    wCredits = new Window(context_);
    wCredits->SetName("wAudio");
    wCredits->SetSize(500, 750);
    wCredits->SetPosition(-20, 0);
    wCredits->SetAlignment(Urho3D::HA_RIGHT, Urho3D::VA_CENTER);
    uiRoot_->AddChild(wCredits);
    wCredits->SetStyleAuto();
    
    Text* txOption = CreateCaption("Credits", "Credits");
    wCredits->AddChild(txOption);
    txOption->SetPosition(15, 15);
    
    Text* txCredits = new Text(context_);
    wCredits->AddChild(txCredits);
    txCredits->SetStyleAuto();
    txCredits->SetPosition(15, 50);
    // TODO
    String sCredits = "Programming/Artwork/Design\n\
empirer64\n\n\
3D artwork\n\
MystikCz\n\n\
Many thanks belongs to the AWESOME Urho3D developers\n\
and guys on Urho IRC channel and forum, especialy to:\n\n\
hd_\n\
dahlia aka badpixels\n\
ChrisMan\n\
carnalis\n\
practicing01\n\
Thebluefish\n\
Stinkfist\n\
Weitjong\n\
viviennea\n\
Araq\n\n\
Thanks belongs also to the developers of third party libraries\n\
used in Urho and also to\n\n\
OpenFonts";
// TODO doplnit fonty
    txCredits->SetText(sCredits);
    txCredits->SetColor(Color(0.9, 0.9, 0.9, 1));
}

// bočný panel podobne ako Credits alebo Options, v ktorom si vyberie hráč
// počet hráčov a ich farby
void MainMenu::CreatePreGameMenu()
{
    wPreGame = new Window(context_);
    wPreGame->SetName("wAudio");
    wPreGame->SetSize(900, 700);
    wPreGame->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    uiRoot_->AddChild(wPreGame);
    wPreGame->SetStyleAuto();
    
    
    CheckBox *cbPlayer1 = CreateCheckbox(wPreGame, "cbPlayer1", "");
    cbPlayer1->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    cbPlayer1->SetSize(30, 30);
    cbPlayer1->SetPosition(60, 60);
    cbPlayer1->SetChecked(true);
    
    LineEdit *lePlayer1 = new LineEdit(context_);
    lePlayer1->SetName("lePlayer1");
    lePlayer1->SetStyle("LineEdit");
    wPreGame->AddChild(lePlayer1);
    lePlayer1->SetSize(200, 30);
    lePlayer1->SetText("Player 1");
    lePlayer1->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    lePlayer1->SetPosition(130, 60);
    lePlayer1->GetTextElement()->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_CENTER);
    lePlayer1->GetTextElement()->SetPosition(10, 10);
    
    ColorPicker* colorPicker1 = new ColorPicker(context_);
    colorPicker1->SetParameters(wPreGame, "colorPicker1", Color::BLUE, 80, 40, 80, 40);
    colorPicker1->SetStyle("ColorPicker");
    colorPicker1->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    colorPicker1->SetPosition(370, 55);
    
    
    CheckBox *cbPlayer2 = CreateCheckbox(wPreGame, "cbPlayer2", "");
    cbPlayer2->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    cbPlayer2->SetSize(30, 30);
    cbPlayer2->SetPosition(60, 120);
    
    LineEdit *lePlayer2 = new LineEdit(context_);
    lePlayer2->SetName("lePlayer2");
    lePlayer2->SetStyle("LineEdit");
    wPreGame->AddChild(lePlayer2);
    lePlayer2->SetSize(200, 30);
    lePlayer2->SetText("Player 2");
    lePlayer2->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    lePlayer2->SetPosition(130, 120);
    lePlayer2->GetTextElement()->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_CENTER);
    lePlayer2->GetTextElement()->SetPosition(10, 10);
    
    ColorPicker* colorPicker2 = new ColorPicker(context_);
    colorPicker2->SetParameters(wPreGame, "colorPicker2", Color::RED, 80, 40, 80, 40);
    colorPicker2->SetStyle("ColorPicker");
    colorPicker2->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    colorPicker2->SetPosition(370, 115);
    
    
    CheckBox *cbPlayer3 = CreateCheckbox(wPreGame, "cbPlayer3", "");
    cbPlayer3->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    cbPlayer3->SetSize(30, 30);
    cbPlayer3->SetPosition(60, 180);
    
    LineEdit *lePlayer3 = new LineEdit(context_);
    lePlayer3->SetName("lePlayer3");
    lePlayer3->SetStyle("LineEdit");
    wPreGame->AddChild(lePlayer3);
    lePlayer3->SetSize(200, 30);
    lePlayer3->SetText("Player 3");
    lePlayer3->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    lePlayer3->SetPosition(130, 180);
    lePlayer3->GetTextElement()->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_CENTER);
    lePlayer3->GetTextElement()->SetPosition(10, 10);
    
    ColorPicker* colorPicker3 = new ColorPicker(context_);
    colorPicker3->SetParameters(wPreGame, "colorPicker3", Color::GREEN, 80, 40, 80, 40);
    colorPicker3->SetStyle("ColorPicker");
    colorPicker3->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    colorPicker3->SetPosition(370, 175);
    
    
    CheckBox *cbPlayer4 = CreateCheckbox(wPreGame, "cbPlayer4", "");
    cbPlayer4->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    cbPlayer4->SetSize(30, 30);
    cbPlayer4->SetPosition(60, 240);
    
    LineEdit *lePlayer4 = new LineEdit(context_);
    lePlayer4->SetName("lePlayer4");
    lePlayer4->SetStyle("LineEdit");
    wPreGame->AddChild(lePlayer4);
    lePlayer4->SetSize(200, 30);
    lePlayer4->SetText("Player 4");
    lePlayer4->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    lePlayer4->SetPosition(130, 240);
    lePlayer4->GetTextElement()->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_CENTER);
    lePlayer4->GetTextElement()->SetPosition(10, 10);
    
    ColorPicker* colorPicker4 = new ColorPicker(context_);
    colorPicker4->SetParameters(wPreGame, "colorPicker4", Color::YELLOW, 80, 40, 80, 40);
    colorPicker4->SetStyle("ColorPicker");
    colorPicker4->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_TOP);
    colorPicker4->SetPosition(370, 235);
    

    Button* btPlay = CreateButton(wPreGame, "btPlay", "Play", BUTTON_WIDTH, BUTTON_HEIGHT);
    btPlay->SetMaxSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    btPlay->SetAlignment(Urho3D::HA_RIGHT, Urho3D::VA_BOTTOM);
    btPlay->SetPosition(-30, -20);
    
    // Back to main menu
    Button* btBack = CreateButton(wPreGame, "btBack", "Back to Play menu", BUTTON_WIDTH, BUTTON_HEIGHT);
    btBack->SetMaxSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    btBack->SetAlignment(Urho3D::HA_RIGHT, Urho3D::VA_BOTTOM);
    btBack->SetPosition(-260, -20);
    
    SubscribeToEvent(btBack, E_RELEASED, HANDLER(MainMenu, HandlePlayMenuClicked));
    SubscribeToEvent(btPlay, E_RELEASED, HANDLER(MainMenu, HandleLevelMenuClicked));
}

void MainMenu::CreateLevelMenu()
{
    wLevelMenu = new Window(context_);
    wLevelMenu->SetName("wAudio");
    wLevelMenu->SetSize(900, 700);
    wLevelMenu->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    uiRoot_->AddChild(wLevelMenu);
    wLevelMenu->SetStyleAuto();
    
    Button *btLevel01 = CreateButton(wLevelMenu, "btLevel01", "1", 50, 50);
    btLevel01->SetPosition(30, 30);
    
    Button *btLevel02 = CreateButton(wLevelMenu, "btLevel02", "2", 50, 50);
    btLevel02->SetPosition(100, 30);
    
    Button *btLevel03 = CreateButton(wLevelMenu, "btLevel03", "3", 50, 50);
    btLevel03->SetPosition(170, 30);
    
    // Back to main menu
    Button* btBack = CreateButton(wLevelMenu, "btBack", "Back to Play menu", BUTTON_WIDTH, BUTTON_HEIGHT);
    btBack->SetMaxSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    btBack->SetAlignment(Urho3D::HA_RIGHT, Urho3D::VA_BOTTOM);
    btBack->SetPosition(-30, -20);
    
    SubscribeToEvent(btBack, E_RELEASED, HANDLER(MainMenu, HandlePlayMenuClicked));
    
    
    SubscribeToEvent(btLevel01, E_RELEASED, HANDLER(MainMenu, HandleLevel01Clicked));
}

void MainMenu::CreateIntroWindow()
{

}

void MainMenu::CreateQuitWindow()
{
    // TODO vyrobit MessageBox classu z tohoto
    Window* w;
    w = new Window(context_);
    w->SetName("QuitWindow");
    w->SetSize(400, 200);
    w->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    w->SetModal(true);
    w->SetMovable(true);
    w->SetFixedHeightResizing(true);
    w->SetFixedWidthResizing(true);
    w->SetStyleAuto();
    uiRoot_->AddChild(w);
    
    Button* btCancel = CreateButton(w, "btCancel", "Cancel", 120, 40);
    btCancel->SetMaxSize(120, 40);
    btCancel->SetStyle("NoButton");
    btCancel->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);
    btCancel->SetPosition(80, -20);
    
    Button* btQuit = CreateButton(w, "btQuit2", "Quit", 120, 40);
    btQuit->SetMaxSize(120, 40);
    btQuit->SetStyle("YesButton");
    btQuit->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_BOTTOM);
    btQuit->SetPosition(-80, -20);
    
    Text* txMessage = new Text(context_);
    w->AddChild(txMessage);
    txMessage->SetStyle("Text");
    txMessage->SetColor(Color(0.9, 0.9, 0.9, 1));
    txMessage->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
    txMessage->SetPosition(0, 40);
    txMessage->SetName("txMessage");
    txMessage->SetText("Do you really want\nto Quit this game ?");
    txMessage->SetTextAlignment(Urho3D::HA_CENTER);
    txMessage->SetTextEffect(Urho3D::TE_STROKE);
    
    
    SubscribeToEvent(btCancel, E_RELEASED, HANDLER(MainMenu, HandleCancelExitClicked));
    SubscribeToEvent(btQuit, E_RELEASED, HANDLER(MainMenu, HandleExitClicked));
}

// TODO
void MainMenu::CreateInGameMenu()
{
    // Play
    Button* btPlay = CreateButton(wMainMenu, "Play", "Play", BUTTON_WIDTH, BUTTON_HEIGHT);
    btPlay->SetStyle("Button");
    // Options
    Button* btOptions = CreateButton(wMainMenu, "Options", "Options", BUTTON_WIDTH, BUTTON_HEIGHT);
    btOptions->SetStyle("Button");
    // TODO Map editor
    /*Button* btMapEditor = CreateButton(window_, "MapEditor", "MapEditor", BUTTON_WIDTH, BUTTON_HEIGHT);
    btMapEditor->SetEnabled(false);*/
    // Credits
    Button* btCredits = CreateButton(wMainMenu, "Credits", "Credits", BUTTON_WIDTH, BUTTON_HEIGHT);
    btCredits->SetStyle("Button");
    //btCredits->SetEnabled(false);
    // Quit
    Button* btQuit = CreateButton(wMainMenu, "Quit", "Quit", BUTTON_WIDTH, BUTTON_HEIGHT);
    btQuit->SetStyle("Button");
    
    // Subscribe also to all UI mouse clicks just to see where we have clicked
    SubscribeToEvent(btPlay, E_RELEASED, HANDLER(MainMenu, HandlePlayClicked));
    SubscribeToEvent(btOptions, E_RELEASED, HANDLER(MainMenu, HandleOptionsClicked));
    //SubscribeToEvent(btMapEditor, E_RELEASED, HANDLER(MainMenu, HandleMapEditorClicked));
    SubscribeToEvent(btCredits, E_RELEASED, HANDLER(MainMenu, HandleCreditsClicked));
    SubscribeToEvent(btQuit, E_RELEASED, HANDLER(MainMenu, HandleQuitClicked));
}

// TODO
void MainMenu::HideInGameMenu()
{
    wMainMenu->RemoveAllChildren();
    wMainMenu->Remove();
    wMainMenu = NULL;
}


void MainMenu::CleanMainMenu ()
{
    if (wMainMenu != NULL) 
    {
	this->wMainMenu->RemoveAllChildren();
    }
}

void MainMenu::DeleteWindows()
{
    // BUG the uninitialized windows should have NULL value, but they dont have
    if (wOptions != NULL)
    {
	wOptions->Remove();
    }
    if (wCredits != NULL)
    {
	wCredits->Remove();
    }
    if (wPreGame != NULL) 
    {
	wPreGame->Remove();
    }
    if (wLevelMenu != NULL)
    {
	wLevelMenu->Remove();
    }
}

void MainMenu::DeleteMainMenu()
{
    wMainMenu->RemoveAllChildren();
    wMainMenu->Remove();
    wMainMenu = NULL;
}

void MainMenu::DeletePreGameMenu()
{
    wPreGame->RemoveAllChildren();
    wPreGame->Remove();
    wPreGame = NULL;
}


// -------- HANDLERS -----------------------------------------------------------
void MainMenu::HandlePlayClicked ( StringHash eventType, VariantMap& eventData )
{
    CleanMainMenu();
    DeleteWindows();
    
    CreatePlayMenu();
}

void MainMenu::HandleOptionsClicked ( StringHash eventType, VariantMap& eventData )
{
    DeleteWindows();
    CreateOptionsWindow();
}

void MainMenu::HandleOptionsApplyClicked(StringHash eventType, VariantMap& eventData)
{
    // CURRENT
    Vector<SharedPtr<UIElement> > fero = wOptions->GetChildren();
    
    CheckBox* cbSound = (CheckBox*) wOptions->GetChild("cbSound", false);
    CheckBox* cbStereo = (CheckBox*) this->wOptions->GetChild("cbStereo", false);
    CheckBox* cbFullscreen = (CheckBox*) wOptions->GetChild("cbFullscreen", false);
    ComboBox* cbxResolution = (ComboBox*) wOptions->GetChild("cbxResolution", false);
    KeyControls* keyCtrl1 = (KeyControls*) wOptions->GetChild("keyCtrl1", false);
    KeyControls* keyCtrl2 = (KeyControls*) wOptions->GetChild("keyCtrl2", false);
    KeyControls* keyCtrl3 = (KeyControls*) wOptions->GetChild("keyCtrl3", false);
    KeyControls* keyCtrl4 = (KeyControls*) wOptions->GetChild("keyCtrl4", false);
    
    GlobalSettings* gs = context_->GetSubsystem<GlobalSettings>();
    gs->SetSound(cbSound->IsChecked());
    gs->SetStereo(cbStereo->IsChecked());
    gs->SetFullscreen(cbFullscreen->IsChecked());
    
    unsigned index = cbxResolution->GetSelection();
    gs->SetResolution(index);

    gs->SetPlayer1Controls(keyCtrl1->GetKeys());
    gs->SetPlayer2Controls(keyCtrl2->GetKeys());
    gs->SetPlayer3Controls(keyCtrl3->GetKeys());
    gs->SetPlayer4Controls(keyCtrl4->GetKeys());
}

void MainMenu::HandleMapEditorClicked ( StringHash eventType, VariantMap& eventData )
{
    CleanMainMenu();
    DeleteWindows();
    // TODO prepnutie do editora map
}

void MainMenu::HandleCreditsClicked ( StringHash eventType, VariantMap& eventData )
{
    //CleanWindow();
    DeleteWindows();
    CreateCreditsWindow();
}

// TODO
void MainMenu::HandleQuitClicked ( StringHash eventType, VariantMap& eventData )
{
    CreateQuitWindow();
}

// TODO switch to Labyrinth state
void MainMenu::HandleLabyrinthClicked(StringHash eventType, VariantMap& eventData)
{
    // Deletes the menu and creates a Pre-game menu
    // TODO vyvola event switchToLabyrinth
    //using namespace LabyrinthSpace;
    

    //Define where globally accessable by all users (some header file):
    
    //Sender
    
    // TODO bude posielat event ale aj s levelom, ktory ma nacitat
    //SendEvent(E_SWITCHTOLABYRINTH);
    
    DeleteMainMenu();
    CreatePreGameMenu();
    
    //Listener
    //SubscribeToEvent(E_SWITCHTOLABYRINTH, HANDLER(Urho3DPlayer, ResetHeli));*/
}

// TODO swtich to Dance state
void MainMenu::HandleDanceClicked(StringHash eventType, VariantMap& eventData)
{

}

void MainMenu::HandleMainMenuClicked(StringHash eventType, VariantMap& eventData)
{
    CleanMainMenu();
    DeleteWindows();
    InitMainMenuWindow();
    CreateMainMenu();
}

void MainMenu::HandlePlayMenuClicked(StringHash eventType, VariantMap& eventData)
{
    CleanMainMenu();
    DeleteWindows();
    InitMainMenuWindow();
    CreatePlayMenu();
}

void MainMenu::HandleLevelMenuClicked(StringHash eventType, VariantMap& eventData)
{
    DeletePreGameMenu();
    CreateLevelMenu();
    static const StringHash E_SWITCHTOLABYRINTH("SwitchToLabyrinth");
}


void MainMenu::HandleControlClicked ( StringHash eventType, VariantMap& eventData )
{

}

// DELETE
void MainMenu::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    UI* ui = GetSubsystem<UI>();
    UIElement* root = ui->GetRoot();

    Input* input = GetSubsystem<Input>();

    unsigned n = input->GetNumTouches();
    for (unsigned i = 0; i < n; i++)
    {
        Text* t = (Text*)root->GetChild("Touch " + String(i));
        TouchState* ts = input->GetTouch(i);
        t->SetText("Touch " + String(ts->touchID_));

        IntVector2 pos = ts->position_;
        pos.y_ -= 30;

        t->SetPosition(pos);
        t->SetVisible(true);
    }

    for (unsigned i = n; i < 10; i++)
    {
        Text* t = (Text*)root->GetChild("Touch " + String(i));
        t->SetVisible(false);
    }
}

void MainMenu::HandleCancelExitClicked(StringHash eventType, VariantMap& eventData)
{
    String s;
    s = "QuitWindow";
    Window* w = (Window*)uiRoot_->GetChild(s, false);
   
    if (w != NULL) 
    {
	w->RemoveAllChildren();
	w->SetVisible(false); 
	w->Remove();
    }
}

void MainMenu::HandleExitClicked(StringHash eventType, VariantMap& eventData)
{
    Engine* e = context_->GetSubsystem<Engine>();
    e->Exit();
}


void MainMenu::HandleLevel01Clicked(StringHash eventType, VariantMap& eventData)
{
    
    VariantMap& eData = GetEventDataMap();
    eData[0] = 1;
    SendEvent(E_SWITCHTOLABYRINTH, eData);
}



void MainMenu::RegisterObject ( Context* context )
{
    context->RegisterFactory<MainMenu>();
}

