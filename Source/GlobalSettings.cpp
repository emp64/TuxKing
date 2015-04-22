#include <Urho3D/Urho3D.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Graphics.h>
#include "Urho3D/Graphics/Renderer.h"
#include "Urho3D/Graphics/GPUObject.h"
#include "Urho3D/Audio/Audio.h"
#include "Urho3D/Input/Input.h"

#include "Urho3D/IO/File.h"
#include "Urho3D/Resource/XMLFile.h"
#include "Urho3D/Resource/XMLElement.h"
#include "Urho3D/IO/FileSystem.h"
#include "Urho3D/DebugNew.h"
#include <Urho3D/IO/Log.h>

#include "GlobalSettings.h"


GlobalSettings::GlobalSettings(Context* context) : 
    Serializable(context),
    sound(false),
    stereo(false),
    windowWidth(1024),
    windowHeigth(768),
    fullscreen(false),
    player1Forward(0),
    player1Backward(0),
    player1Left(0),
    player1Right(0),
    player2Forward(0),
    player2Backward(0),
    player2Left(0),
    player2Right(0),
    player3Forward(0),
    player3Backward(0),
    player3Left(0),
    player3Right(0),
    player4Forward(0),
    player4Backward(0),
    player4Left(0),
    player4Right(0)
{
    LOGDEBUG("GlobalSettings::GlobalSettings(Context* context) : Component(context)");
    
    Graphics* grap = GetSubsystem<Graphics>();
    SetFullscreenResolutions(grap->GetResolutions());
    // TODO remove to small resolutions (lower than 1024x768)
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    
    captionFont = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");
    
    
    // TODO CURRENT Init
    
    
    
    // TODO Audio init
    
    
    //LoadFromFile();
    
    // FUTURE when the audio system will be working -> audio should be enabled by default
    /*sound = false;
    stereo = false;
    
    windowWidth = 1024;
    windowHeigth = 768;
    fullscreen = false;
    
    player1Forward = KEY_UP;*/
    
    this->RegisterObject(context_);
    
        
    /*sound = false;
    stereo = false;
    
    windowWidth = 1024;
    windowHeigth = 768;
    fullscreen = false;
    
    player1Forward = Urho3D::KEY_UP;
    player1Backward = KEY_DOWN;
    player1Left = KEY_LEFT;
    player1Right = KEY_RIGHT;
    
    player2Forward = KEY_W;
    player2Backward = KEY_S;
    player2Left = KEY_A;
    player2Right = KEY_D;
    
    player3Forward = KEY_KP_8;
    player3Backward = KEY_KP_5;
    player3Left = KEY_KP_4;
    player3Right = KEY_KP_6;
    
    player4Forward = KEY_I;
    player4Backward = KEY_K;*/
    
    
    
    
    
    /*ATTRIBUTE(GlobalSettings, VAR_FLOAT, "Controls Pitch", controls_.pitch_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(GlobalSettings, VAR_BOOL, "On Ground", onGround_, false, AM_DEFAULT);
    ATTRIBUTE(GlobalSettings, VAR_BOOL, "OK To Jump", okToJump_, true, AM_DEFAULT);
    ATTRIBUTE(GlobalSettings, VAR_FLOAT, "In Air Timer", inAirTimer_, 0.0f, AM_DEFAULT);*/
}

GlobalSettings::~GlobalSettings()
{
    
    SaveToFile();    
    
    // FUTURE BUG
    // serves for restoring the highest possible resolution. If you are using smaller
    // resolution in the game than you are using elsewhere outside the game it can break
    // also your resolution outside the game (tested in KDE in linux). This should help.
    /*if (fullscreen) {
	PODVector<IntVector2> vec = GetFullscreenResolutions();
	SetResolution(vec[vec.Size()-1].x_, vec[vec.Size()-1].y_);
	SetFullscreen(false);
	

 
   }*/
    /*File fileConf(context_, settingFile, Urho3D::FILE_WRITE);
    XMLFile* xmlConf = new XMLFile(context_); 

    xmlConf->CreateRoot("settings");
    XMLElement elSettings = xmlConf->GetRoot("settings");

    SaveXML(elSettings);
    
    xmlConf->Save(fileConf);*/
    
    LOGDEBUG("GlobalSettings::~GlobalSettings()");
}


// NOTE v Setteroch zapisuje hodnoty atributov dobre, akurat potom sa nieco pokazi

// BUG viac krat zapisuje to iste
// BUG nvm preco ale ak dam do settera normalne cisla (nie KEY ...) tak to zapise OK
// ale ak pouzijem KEY... tak nezapise nic :/
// Asi by bolo dobre naimplementova vlastny XML ukladac



/// TODO dorobit tieto somariny, pozri TKing (Source, Source) -> prejst na novu verziu Urha a tam skusit skompilovat
// BUG chyba s tym zapisovanim do suboru zrejme bolo to, že nevie zapisovať KEY_* veci ale iba int-y, Zrejme ?!

void GlobalSettings::LoadFromFile()
{
    
    //sound = false;
    //SetSound(false);
    SetStereo(false);
    
    SetResolution(1024, 768);
    // BUG if there is SetFullscreen true it crashes sometimes when you click Options
    SetFullscreen(false);
    
    SetPlayer1Controls(1, 2, 3, 4);
    SetPlayer2Controls(KEY_W, KEY_S, KEY_A, KEY_D);
    SetPlayer3Controls(KEY_KP_8, KEY_KP_5, KEY_KP_4, KEY_KP_6);
    SetPlayer4Controls(KEY_I, KEY_K, KEY_J, KEY_L);
    LOGDEBUG("GlobalSettings::LoadFromFile()");
    
    /*File fileConf(context_, settingFile, Urho3D::FILE_READ);
    XMLFile* xmlConf = new XMLFile(context_); 
    xmlConf->Load(fileConf);
    
   
    XMLElement elSettings = xmlConf->GetRoot();

    
    LoadXML(elSettings);*/
}

void GlobalSettings::SaveToFile()
{
    // BUG zapisuje data 2 krat
    LOGDEBUG("GlobalSettings::SaveToFile()");
    
    // TODO CURRENT
    File fileConf(context_, settingFile, Urho3D::FILE_WRITE);
    XMLFile* xmlConf = new XMLFile(context_); 

    xmlConf->CreateRoot("settings");
    XMLElement elSettings = xmlConf->GetRoot("settings");

    
    SaveXML(elSettings);

    
    xmlConf->Save(fileConf);
}


String GlobalSettings::GetFerodd()
{

}

bool GlobalSettings::GetSound()
{
    return sound;
}

void GlobalSettings::SetSound(bool sound)
{
    this->sound = sound;
    
    Audio* audio = GetSubsystem<Audio>();
    audio->Stop();
}

bool GlobalSettings::GetStereo()
{
    return stereo;
}

bool GlobalSettings::SetStereo(bool stereo)
{
    this->stereo = stereo;
    
    Audio* audio = GetSubsystem<Audio>();
    audio->SetMode(100, audio->GetMixRate(), true);
}

int GlobalSettings::GetWindowWidth()
{
    return windowWidth;
}


int GlobalSettings::GetWindowHeigth()
{
    return windowHeigth;
}

void GlobalSettings::SetResolution(int index)
{
    PODVector<IntVector2> vec = GetFullscreenResolutions();
    SetResolution(vec[index].x_, vec[index].y_);
}


void GlobalSettings::SetResolution(int width, int heigth)
{
    this->windowHeigth = heigth;
    this->windowWidth = width;
    
    Graphics* grap = GetSubsystem<Graphics>();
    grap->SetMode(width, heigth);
}

PODVector< IntVector2 > GlobalSettings::GetFullscreenResolutions()
{
    return fullResolutions;
}

void GlobalSettings::SetFullscreenResolutions(PODVector< IntVector2 > resolutions)
{
    for (int i = resolutions.Size()-1; i > 0; i--)
    {
	if (resolutions[i].x_ < 1024 || resolutions[i].y_ < 576)
	{
	    resolutions.Erase(i, 1);
	}
	    
    }
    this->fullResolutions = resolutions;
}


bool GlobalSettings::GetFullscreen()
{
    LOGDEBUG("GlobalSettings::GetFullscreen()");
    
    Graphics* grap = GetSubsystem<Graphics>();
    fullscreen = grap->GetFullscreen();
    
    return fullscreen;
}

void GlobalSettings::SetFullscreen(bool fullscreen)
{
    ///this->fullscreen = fullscreen;
    
    Graphics* grap = GetSubsystem<Graphics>();

    if ((fullscreen == true && this->GetFullscreen() == false) || (fullscreen == false && this->GetFullscreen() == true))
    {
	grap->ToggleFullscreen();
    }
    
    this->fullscreen = fullscreen;
}

XMLFile* GlobalSettings::GetDefaultStyle()
{
    return style;
}

void GlobalSettings::SetDefaultStyle(XMLFile* style)
{
    this->style = style;
}

Font* GlobalSettings::GetCaptionFont()
{
    return captionFont;
}

void GlobalSettings::SetCaptionFont(Font* font)
{
    captionFont = font;
}

Font* GlobalSettings::GetMenuFont()
{
    return menuFont;
}

void GlobalSettings::SetMenuFont(Font* font)
{
    menuFont = font;
}



void GlobalSettings::SetFerodd(String text)
{

}


/* Controls */
int* GlobalSettings::GetPlayer1Controls()
{
    int ctrls[4];
    ctrls[0] = player1Forward;
    ctrls[1] = player1Backward;
    ctrls[2] = player1Left;
    ctrls[3] = player1Right;
    
    return ctrls;
}

void GlobalSettings::SetPlayer1Controls(int controls[])
{
    SetPlayer1Controls(controls[0], controls[1], controls[2], controls[3]);
}

void GlobalSettings::SetPlayer1Controls (int playerForward, int playerBackward, int playerLeft, int playerRight)
{
    this->player1Forward = playerForward;
    this->player1Backward = playerBackward;
    this->player1Left = playerLeft;
    this->player1Right = playerRight;
}

int* GlobalSettings::GetPlayer2Controls()
{
    int ctrls[4];
    ctrls[0] = player2Forward;
    ctrls[1] = player2Backward;
    ctrls[2] = player2Left;
    ctrls[3] = player2Right;
    
    return ctrls;
}

void GlobalSettings::SetPlayer2Controls(int controls[])
{
    SetPlayer2Controls(controls[0], controls[1], controls[2], controls[3]);
}

void GlobalSettings::SetPlayer2Controls(int playerForward, int playerBackward, int playerLeft, int playerRight)
{
    this->player2Forward = playerForward;
    this->player2Backward = playerBackward;
    this->player2Left = playerLeft;
    this->player2Right = playerRight;
}

int* GlobalSettings::GetPlayer3Controls()
{
    int ctrls[4];
    ctrls[0] = player3Forward;
    ctrls[1] = player3Backward;
    ctrls[2] = player3Left;
    ctrls[3] = player3Right;
    
    return ctrls;
}

void GlobalSettings::SetPlayer3Controls(int controls[])
{
    SetPlayer3Controls(controls[0], controls[1], controls[2], controls[3]);
}

void GlobalSettings::SetPlayer3Controls(int playerForward, int playerBackward, int playerLeft, int playerRight)
{
    this->player3Forward = playerForward;
    this->player3Backward = playerBackward;
    this->player3Left = playerLeft;
    this->player3Right = playerRight;
}

int* GlobalSettings::GetPlayer4Controls()
{
    int ctrls[4];
    ctrls[0] = player4Forward;
    ctrls[1] = player4Backward;
    ctrls[2] = player4Left;
    ctrls[3] = player4Right;
    
    return ctrls;
}

void GlobalSettings::SetPlayer4Controls(int controls[])
{
    SetPlayer4Controls(controls[0], controls[1], controls[2], controls[3]);
}

void GlobalSettings::SetPlayer4Controls(int playerForward, int playerBackward, int playerLeft, int playerRight)
{
    this->player4Forward = playerForward;
    this->player4Backward = playerBackward;
    this->player4Left = playerLeft;
    this->player4Right = playerRight;
}


void GlobalSettings::RegisterObject(Context* context)
{
    LOGDEBUG("GlobalSettings::RegisterObject(Context* context)");
    
    context->RegisterFactory<GlobalSettings>();
    
    // ATRIBUTES
    // Audio
    ATTRIBUTE("sound", bool, sound, false, AM_DEFAULT);
    ATTRIBUTE("stereo", bool, stereo, false, AM_DEFAULT);
    
    // Video
    ATTRIBUTE("windowWidth", int, windowWidth, 1024, AM_DEFAULT);
    ATTRIBUTE("windowHeigth", int, windowHeigth, 768, AM_DEFAULT);
    ATTRIBUTE("fullscreen", bool, fullscreen, false, AM_DEFAULT);
    
    // Player controls
    ATTRIBUTE("player1Forward", int, player1Forward, Urho3D::KEY_UP, AM_DEFAULT);
    ATTRIBUTE("player1Backward", int, player1Backward, KEY_DOWN, AM_DEFAULT);
    ATTRIBUTE("player1Left", int, player1Left, KEY_LEFT, AM_DEFAULT);
    ATTRIBUTE("player1Right", int, player1Right, KEY_RIGHT, AM_DEFAULT);
    
    ATTRIBUTE("player2Forward", int, player2Forward, KEY_W, AM_DEFAULT);
    ATTRIBUTE("player2Backward", int, player2Backward, KEY_S, AM_DEFAULT);
    ATTRIBUTE("player2Left", int, player2Left, KEY_A, AM_DEFAULT);
    ATTRIBUTE("player2Right", int, player2Right, KEY_D, AM_DEFAULT);
    
    ATTRIBUTE("player3Forward", int, player3Forward, KEY_KP_8, AM_DEFAULT);
    ATTRIBUTE("player3Backward", int, player3Backward, KEY_KP_5, AM_DEFAULT);
    ATTRIBUTE("player3Left", int, player3Left, KEY_KP_4, AM_DEFAULT);
    ATTRIBUTE("player3Right", int, player3Right, KEY_KP_6, AM_DEFAULT);
    
    ATTRIBUTE("player4Forward", int, player4Forward, KEY_I, AM_DEFAULT);
    ATTRIBUTE("player4Backward", int, player4Backward, KEY_K, AM_DEFAULT);
    ATTRIBUTE("player4Left", int, player4Left, KEY_J, AM_DEFAULT);
    ATTRIBUTE("player4Right", int, player4Right, KEY_L, AM_DEFAULT);
}
