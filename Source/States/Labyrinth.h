/*
 * Copyright (c) 2014 empirer <empirer64@gmail.com>
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

#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "Urho3D/Core/Context.h"

#include "State.h"
#include "../Map/LabyrinthMap.h"
#include "../Game/PlayerController.h"
//#include "../Game/Enemy.h"



using namespace Urho3D;

// the class for the labyrinth game
class Labyrinth : public State
{
    OBJECT(Labyrinth)
    
public:
    Labyrinth(Context* context);
    ~Labyrinth();
    
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    
    void SetLevel(int level);
    
    /// Setup after engine initialization and before running the main loop.
    virtual void Start();
    
    void Pause(bool menu = true);
    
    Scene* GetScenePointer();
    
    /* ----- Map -------- */
    int LoadLevel(int level);
    
    int LoadMap( String filename );
    
    void CreateMap(int** map);
    void CreateMap( int mapLength, int mapWidth );

        
    void CreateNavigationMap(Vector<Vector<int> >map);
    // recursive function for finding all the neighbours of the node
    void FindNeighbour( NavigationNode* node, Vector< Vector< int > > map, NavigationMap* navigationMap );
    
    void CreateCoins();
    
    //void Create
    void CreateBlock(int number);
    
    
protected:
    void OnWindowResize();
    SharedPtr<Scene> scene_;
  
private:
    void StartGame();
    
    /// Create static scene content.
    void CreateScene();
    
    void LoadLevel();
    
    void LoadNextLevel();
    
    void CreateFloor( int mapLength, int mapWidth );
    /// Create controllable character.
    void CreatePlayer();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Subscribe to necessary events.
    void SubscribeToEvents();
    /// Handle application update. Set controls to character.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle application post-update. Update camera position after character has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Read input and move the camera.
    void MoveCamera(float timeStep);
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    
    // show menu with score info at the end of every level
    void PostGameMenu();

    /// Box scene nodes.
    Vector<SharedPtr<Node> > boxNodes_;
    /// Animation flag.
    bool animate_;
    /// Group optimization flag.
    bool useGroups_;
    
    PlayerController* playerCtrl_;
    
    LabyrinthMap* map_;

    Input* input;
    
    bool drawDebug_ = false;
    
    int currentLevel = 1;
    
    bool paused = false;
    
    Coin* coin_;
    String levels[];
    Vector<Vector<int> > map_;
    
    /// The controllable character component.
    //WeakPtr<Character> character_;
};

#endif // LABYRINTH_H
