/*
 * Here are stored all the engine settings
 * This class should be public for every other class
*/

/// MOZNO NEBUDE TREBA, da sa to zrejme nastavit cez context
#pragma once

#include <Urho3D/Urho3D.h>
#include "Urho3D/Core/Object.h"
#include "Urho3D/UI/Font.h"
#include "Urho3D/Resource/XMLFile.h"
#include "Urho3D/Core/Context.h"
#include "Urho3D/Scene/Serializable.h"
#include "Urho3D/Scene/Component.h"

#include "Urho3D/Input/Input.h"



using namespace Urho3D;


class GlobalSettings : public Serializable
{
    OBJECT(GlobalSettings)
    
public:
    GlobalSettings(Context* context);
    ~GlobalSettings();
    
    // loads settings from XML file
    void LoadFromFile();
    // saves settings to XML file
    void SaveToFile();

    // audio
    bool GetSound();
    void SetSound( bool sound );
    
    bool GetStereo();
    bool SetStereo( bool stereo );
    
    int GetWindowWidth();
    int GetWindowHeigth();
    void SetResolution(int index);
    void SetResolution(int width, int heigth);
    
    PODVector<IntVector2> GetFullscreenResolutions();
    void SetFullscreenResolutions(PODVector<IntVector2> resolutions);
    
    bool GetFullscreen();
    void SetFullscreen(bool fullscreen);
    
    XMLFile* GetDefaultStyle();
    void SetDefaultStyle(XMLFile* style);
    
    Font* GetCaptionFont();
    void SetCaptionFont(Font* font); 
    
    Font* GetMenuFont();
    void SetMenuFont(Font* font); 
    
    static String GetFerodd();
    static void SetFerodd(String text);
    
    /// Controls
    int *GetPlayer1Controls();
    void SetPlayer1Controls(int controls[]);
    void SetPlayer1Controls(int playerForward, int playerBackward, int playerLeft, int playerRight );
    
    int *GetPlayer2Controls();
    void SetPlayer2Controls(int controls[]);
    void SetPlayer2Controls(int playerForward, int playerBackward, int playerLeft, int playerRight );
    
    int *GetPlayer3Controls();
    void SetPlayer3Controls(int controls[]);
    void SetPlayer3Controls(int playerForward, int playerBackward, int playerLeft, int playerRight );
    
    int *GetPlayer4Controls();
    void SetPlayer4Controls(int controls[]);
    void SetPlayer4Controls(int playerForward, int playerBackward, int playerLeft, int playerRight );

    
    static void RegisterObject(Context* context);
    

    
private:
    String settingFile = "settings.conf";
    
    // FUTURE when the audio system will be working -> audio should be enabled by default
    // Audio
    bool sound;
    bool stereo;

    // Video
    int windowWidth;
    int windowHeigth;
    bool fullscreen;
    
    // Player controls
    int player1Forward;
    int player1Backward;
    int player1Left;
    int player1Right;
    
    int player2Forward;
    int player2Backward;
    int player2Left;
    int player2Right;
    
    int player3Forward;
    int player3Backward;
    int player3Left;
    int player3Right;
    
    int player4Forward;
    int player4Backward;
    int player4Left;
    int player4Right;
    
    
    Font* captionFont;
    Font* menuFont;
    
    String ferodd = "YYYYYYYY";
    
    XMLFile* style;
    
    PODVector<IntVector2> fullResolutions;
};

