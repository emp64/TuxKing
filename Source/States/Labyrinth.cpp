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

#include <Urho3D/Urho3D.h>
#include "Urho3D/Engine/Application.h"
#include "Urho3D/Graphics/Camera.h"
#include "Urho3D/Engine/Console.h"
#include "Urho3D/UI/Cursor.h"
#include "Urho3D/Engine/DebugHud.h"
#include "Urho3D/Graphics/DebugRenderer.h"
#include "Urho3D/Engine/Engine.h"
#include "Urho3D/IO/FileSystem.h"
#include "Urho3D/Graphics/Graphics.h"
#include "Urho3D/Input/Input.h"
#include "Urho3D/Input/InputEvents.h"
#include "Urho3D/Graphics/Renderer.h"
#include "Urho3D/Resource/ResourceCache.h"
#include "Urho3D/Scene/Scene.h"
#include "Urho3D/Scene/SceneEvents.h"
#include "Urho3D/UI/Sprite.h"
#include "Urho3D/Graphics/Texture2D.h"
#include "Urho3D/Core/Timer.h"
#include "Urho3D/UI/UI.h"
#include "Urho3D/Resource/XMLFile.h"
#include "Urho3D/Graphics/Zone.h"

#include "Urho3D/Graphics/AnimatedModel.h"
#include "Urho3D/Graphics/AnimationController.h"
#include "Urho3D/Core/Context.h"
#include "Urho3D/Physics/CollisionShape.h"
#include "Urho3D/Input/Controls.h"
#include "Urho3D/Scene/Component.h"
#include "Urho3D/Core/CoreEvents.h"
#include "Urho3D/Engine/Engine.h"
#include "Urho3D/IO/FileSystem.h"
#include "Urho3D/UI/Font.h"
#include "Urho3D/Input/Input.h"
#include "Urho3D/Graphics/Light.h"
#include "Urho3D/Graphics/Material.h"
#include "Urho3D/Graphics/Model.h"
#include "Urho3D/Graphics/Octree.h"
#include "Urho3D/Physics/PhysicsWorld.h"
#include "Urho3D/Core/ProcessUtils.h"
#include "Urho3D/Graphics/Renderer.h"
#include "Urho3D/Physics/RigidBody.h"
#include "Urho3D/Resource/ResourceCache.h"
#include "Urho3D/Scene/Scene.h"
#include "Urho3D/Graphics/StaticModel.h"
#include "Urho3D/UI/Text.h"
#include "Urho3D/UI/UI.h"
#include "Urho3D/Graphics/Zone.h"


#include "Urho3D/UI/Font.h"
#include "Urho3D/UI/Text.h"

#include "Urho3D/DebugNew.h"

#include "../Game/CreateNodes.h"


#include "DebugNew.h"

#include "Labyrinth.h"

#include "State.h"

#include "../Game/PlayerController.h"
#include "../Game/Coin.h"
#include "../Game/Apple.h"
#include "../Game/Banana.h"
#include "../Game/Cherry.h"

#include "../HUD/MainMenu.h"


/*
  TODO CURRENT BUG NOTE CHECK VSETKO - TUNA TREBA ALE VELKY PORIADOK SPRAVIŤ A NEJAKY SYSTEM
 */



Labyrinth::Labyrinth(Context* context) : State(context)
{
    // CHECK je to treba ?
    //context_ = context;

    Apple::RegisterObject(context);
    Banana::RegisterObject(context);
    Cherry::RegisterObject(context);
    Coin::RegisterObject(context);
    PlayerController::RegisterObject(context);
    
    
    //SubscribeToEvents();
    //MainMenu::RegisterObject(context);
    // TODO treba prerobit aby fungovalo cez RegisterObject
    // TREBA tu odtestovať či by tu fungoval Coin (teda či ide start, sledovanie kolizii ...)
    Start();
    
    
    input = GetSubsystem<Input>();
}

Labyrinth::~Labyrinth()
{

}

void Labyrinth::Start()
{
    State::Start();
    
    StartGame();
    
    // TODO spravit prepinanie medzi kamerami, statickou a free
    SetupViewport();
    // Subscribe to necessary events
    SubscribeToEvents();
    
    // TODO mozno zobrazi instrukcie mozno nie zavisi od Tutorial modu / v prvom leveli vzdy zobrazi / ked je hrac novy tak zobrazi
    /*if (currentLevel == 1)
    {
	Pause(false);
	CreateInstructions();
    }*/
    
    // TODO prec s tymto do nastaveni
    Renderer* renderer = GetSubsystem<Renderer>();
    
    
    renderer->SetTextureQuality(QUALITY_HIGH);
    renderer->SetMaterialQuality(QUALITY_HIGH);
    renderer->SetSpecularLighting(true);

}

Scene* Labyrinth::GetScenePointer()
{
    return scene_;
}

void Labyrinth::SetLevel(int level)
{
    // TODO prerob na pocet levelov
    if (level < 1 || level > 100)
    {
	currentLevel = 1;
    }
    else
    {
	currentLevel = level;
    }
    
    LoadLevel();
}


void Labyrinth::StartGame()
{
    CreateScene();
    
    CreatePlayer();
    
    
}


void Labyrinth::CreateScene()
{
    // ADDED
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    scene_ = new Scene(context_);
    
    // TODO vzdialenost kamery podla rozlisenia obrazovky
    
    // Create scene subsystem components
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<PhysicsWorld>();
    scene_->CreateComponent<DebugRenderer>();
    
    // Create camera and define viewport. We will be doing load / save, so it's convenient to create the camera outside the scene,
    // so that it won't be destroyed and recreated, and we don't have to redefine the viewport on load
    // TODO treb vytunit poziciu kamery a jej rotaciu
    cameraNode_ = new Node(context_);
    cameraNode_->SetName("cameraNode");
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);
    // aby to vyzeralo ako 2.5D treba prepnut ortho na true
    /*camera->SetOrthographic(false);
    cameraNode_->SetPosition(Vector3(10, 90, 10));
    cameraNode_->SetRotation(Quaternion(75, 0, 0));
    GetSubsystem<Renderer>()->SetViewport(0, new Viewport(context_, scene_, camera));*/
    
    camera->SetOrthographic(false);
    cameraNode_->SetPosition(Vector3(0, 10, 0));
    cameraNode_->SetRotation(Quaternion(90, 0, 0));
    
   
    
    // Create static scene content. First create a zone for ambient lightning and fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(1000.0f);
    zone->SetFogEnd(1000.0f);
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));

    // Create a directional light with cascaded shadow mapping
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.3f, -0.5f, 0.425f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetSpecularIntensity(1.0f);
    
    // ------------------------------------------
    
    CreateFloor(20, 14);
}

void Labyrinth::LoadLevel()
{
    // CURRENT TODO nacitanie levelu z textaku, poslanie map infa do Map -> vytvorenie mapy
    // vytvorenie hračov
    String filename;
    /*
     * switch ()
     * {
	    case: ...
	}
     */
    
    //CreateScene();
    //Map
    ResourceCache *cache = GetSubsystem<ResourceCache>();
    
    File *file = new File(context_, filename, Urho3D::FILE_READ);
    String sMap = file->ReadString();
    String s;
	
    s.Find("map=");
}

void Labyrinth::LoadNextLevel()
{
    currentLevel++;
    
    LoadLevel();
}


// DELETE ??? TODO treba prerobit vstupne parametre
void Labyrinth::CreateFloor(int mapLength, int mapWidth)
{
    map_ = new LabyrinthMap(context_, scene_);

    
}

// TODO nacitanie a vykreslenie obrazka s instrukciami
void Labyrinth::CreateInstructions()
{
    /*ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
        "Use WASD keys and mouse/touch to move\n"
        "Space to jump, F to toggle 1st/3rd person\n"
        "F5 to save scene, F7 to load"
    );
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText->SetTextAlignment(HA_CENTER);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);*/
}

void Labyrinth::CreatePlayer()
{
    Node* objectNode = scene_->CreateChild("Player");
    objectNode->SetPosition(Vector3(0.0f, 10.0f, 0.0f));
    
    //CreateNodes* nodes = new CreateNodes(context_);
    playerCtrl_ = objectNode->CreateComponent<PlayerController>();
    playerCtrl_->CreateNode(objectNode);
    
    
}

void Labyrinth::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;
    
    Input* input = GetSubsystem<Input>();
    input->SetMouseVisible(false);
    
    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;
    
    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);
    
    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    
    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown(KEY_UP))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_DOWN))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_LEFT))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_RIGHT))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
}


void Labyrinth::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();
    
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    //GetComponent<Camera>()->SetOrthographic(true);
    renderer->SetViewport(0, viewport);
}


void Labyrinth::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    // Toggle animation with space
    Input* input = GetSubsystem<Input>();
    if (input->GetKeyPress(KEY_SPACE))
        animate_ = !animate_;

    // Toggle grouped / ungrouped mode
    // TODO CHECK treba dorobit tak aby vedel dat bloky do jednej grupy, a tiez treba zistit ako to funguje ???
    if (input->GetKeyPress('G'))
    {
        useGroups_ = !useGroups_;
        CreateScene();
    }
    
    if (input->GetKeyPress(KEY_SPACE))
    {
        drawDebug_ = !drawDebug_;
	//scene_->GetComponent<PhysicsWorld>()->DrawDebugGeometry(true);
    }
    
    // CAMERA Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

void Labyrinth::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    Input* input = GetSubsystem<Input>();
    if (input->GetKeyDown(KEY_PAUSE))
	Pause();
    
    // DELETE ???
    /*using namespace Update;

    

    if (playerCtrl_)
    {
        // Clear previous controls
        playerCtrl_->controls_.Set(CTRL_FORWARD | CTRL_BACK | CTRL_LEFT | CTRL_RIGHT | CTRL_JUMP, false);

	playerCtrl_->controls_.Set(CTRL_FORWARD, input->GetKeyDown('W'));
        playerCtrl_->controls_.Set(CTRL_BACK, input->GetKeyDown('S'));
        playerCtrl_->controls_.Set(CTRL_LEFT, input->GetKeyDown('A'));
        playerCtrl_->controls_.Set(CTRL_RIGHT, input->GetKeyDown('D'));
    }*/

}

void Labyrinth::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw physics debug geometry. Use depth test to make the result easier to interpret
    if (drawDebug_)
        scene_->GetComponent<PhysicsWorld>()->DrawDebugGeometry(true);
}


void Labyrinth::SubscribeToEvents()
{
    // Subscribe to Update event for setting the character controls before physics simulation
    SubscribeToEvent(E_UPDATE, HANDLER(Labyrinth, HandleUpdate));

    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent(E_POSTUPDATE, HANDLER(Labyrinth, HandlePostUpdate));

    SubscribeToEvent(E_POSTRENDERUPDATE, HANDLER(Labyrinth, HandlePostRenderUpdate));
    
    // Unsubscribe the SceneUpdate event from base class as the camera node is being controlled in HandlePostUpdate() in this sample
    //UnsubscribeFromEvent(E_SCENEUPDATE);
}

void Labyrinth::PostGameMenu()
{
    // TODO
}

void Labyrinth::Pause(bool menu)
{
    if (paused == false) 
    {
	paused = true;
	UnsubscribeFromAllEvents();
    }
    else
    {
	paused = false;
    }
    
    // show the ingame MainMenu
    
}


void Labyrinth::RegisterObject(Context* context)
{
    context->RegisterFactory<Labyrinth>();
}

void Labyrinth::OnWindowResize()
{

}


// ***** MAP ********
Labyrinth::Labyrinth(Context* context, Scene* scene) : Object(context)
{
    scene_ = scene;
    context_ = context;
    CreateMap(32, 20);
    LoadMap("labyrinth/Level01.lvl");
    
    // TODO nacitanie "kampane" - zoznamu levelov
}

Labyrinth::~Labyrinth()
{
    
}

int Labyrinth::LoadLevel(int level)
{
    LoadMap(levels[level]);
}

// TODO CURRENT
int Labyrinth::LoadMap(String filename)
{
    ResourceCache *cache = GetSubsystem<ResourceCache>();
    
    File *file = new File(context_, filename, Urho3D::FILE_READ);
    String sMap = file->ReadString();
    String n;
    
    
    //Vector<String> sMap.Split('\n');
    
    // TODO
    /*int player01Spawn, player02Spawn, player03Spawn, player04Spawn;
    
    int s = sMap.Find("Player01Spawn=");
    int e = sMap.Find("Map");
    
    
     coordinates;
    coordinates = sMap.Split(',');
    for (int ; i < sMap.Capacity(); i++)
    {
	if (sMap[i] == 'j');
    }
    
    sMap.Find("Player02Spawn=");
    sMap.Find("Player03Spawn=");
    sMap.Find("Player04Spawn=");*/

    unsigned int s = sMap.Find("Map=");
    sMap.Erase(0, s + 4);


    /*for (int i = 0; i < sMap.Capacity(); i++)
    {
	char c = sMap[i];
	if (isdigit(c))
	{
	        n += c;
	}
	else if(c == ' ')
	{
	    StringToNumbersVector(n);
	}
    }*/
    map_ = StringToNumbersVector(sMap);
}

void Labyrinth::CreateMap(int** map)
{
    for (int x = 0; x < map_.Capacity(); x++)
    {
	for (int y = 0; y < map_[x].Capacity(); y++)
	{
	    CreateBlock(map_[x][y]);
	}
    }
}


void Labyrinth::CreateMap(int mapLength, int mapWidth)
{
    
    // TODO
    //Scene* scene_ = context_->GetSubsystem<Scene>();
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    // Create the floor object
    Node* floorNode = scene_->CreateChild("Floor");
    floorNode->SetPosition(Vector3(0.0f, -0.5f, 0.0f));
    floorNode->SetScale(Vector3(200.0f, 1.0f, 200.0f));
    StaticModel* object = floorNode->CreateComponent<StaticModel>();
    object->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Grass.xml"));

    RigidBody* body = floorNode->CreateComponent<RigidBody>();
    // Use collision layer bit 2 to mark world scenery. This is what we will raycast against to prevent camera from going
    // inside geometry
    body->SetCollisionLayer(2);
    CollisionShape* shape = floorNode->CreateComponent<CollisionShape>();
    shape->SetBox(Vector3::ONE);
    
    
    // Create movable boxes. Let them fall from the sky at first
    const unsigned NUM_BOXES = 100;
    const float SCALE = 0.5;
    int numberX = (float)mapLength/SCALE;
    int numberZ = (float)mapWidth/SCALE;
    int beginX = (0 - mapLength/2);
    int beginZ = (0 - mapWidth/2);
    
    // TODO vzdialenost kamery podla rozlisenia obrazovky
    
    for (unsigned i = 0; i < numberX; i++)
    {
	for (int j = 0; j < numberZ; j++)
	{
	    //float scale = Random(2.0f) + 0.5f;
	    //float scale = 1;

	    Node* objectNode = scene_->CreateChild("Floor");
	    objectNode->SetPosition(Vector3(i, 0, j));
	    //objectNode->SetRotation(Quaternion(Random(360.0f), Random(360.0f), Random(360.0f)));
	    objectNode->SetScale(SCALE);
	    StaticModel* object = objectNode->CreateComponent<StaticModel>();
	    object->SetModel(cache->GetResource<Model>("Urho resources/Models/Block.mdl"));
	    //object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Hedge.xml"));
	    object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/GrassA.xml"));
	    //object->SetCastShadows(true);

	    RigidBody* body = objectNode->CreateComponent<RigidBody>();
	    body->SetCollisionLayer(2);
	    // Bigger boxes will be heavier and harder to move
	    //body->SetMass(scale * 2.0f);
	    CollisionShape* shape = objectNode->CreateComponent<CollisionShape>();
	    shape->SetBox(Vector3(2,2,2));
	}
    }
    
    for (unsigned i = 0; i < numberX; i++)
    {
	for (int j = 0; j < numberZ; j++)
	{
	    //float scale = Random(2.0f) + 0.5f;
	    //float scale = 1;

	    if (i == 0 || j == 0 || i == numberX-1 || j == numberZ-1) {
		Node* objectNode = scene_->CreateChild("Floor");
		objectNode->SetPosition(Vector3(i, 1, j));
		//objectNode->SetRotation(Quaternion(Random(360.0f), Random(360.0f), Random(360.0f)));
		objectNode->SetScale(SCALE);
		StaticModel* object = objectNode->CreateComponent<StaticModel>();
		object->SetModel(cache->GetResource<Model>("Urho resources/Models/Block.mdl"));
		//object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Hedge.xml"));
		object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/GrassA.xml"));
		//object->SetCastShadows(true);

		RigidBody* body = objectNode->CreateComponent<RigidBody>();
		body->SetCollisionLayer(2);
		// Bigger boxes will be heavier and harder to move
		//body->SetMass(scale * 2.0f);
		CollisionShape* shape = objectNode->CreateComponent<CollisionShape>();
		shape->SetBox(Vector3(2, 2, 2));
	    }
	}
    }
    
    CreateCoins();
    
    CreateBlock(1);
}

// CHECK
void Labyrinth::CreateNavigationMap(Vector< Vector< int > > map)
{
    NavigationMap *navigationMap;
    
    for (int i = 0; i < map.Capacity(); i++)
    {
	for (int j = 0; j < map[i].Capacity(); j++)
	{
	    // TODO check if it is a "walkable" block (where enemy can walk, w-block)
	    if (map[i][j] == 1 || map[i][j] == 2 || map[i][j] == 3)
	    {
		NavigationNode* node;
		
		// if the NavigationNode already exists do nothing
		if (navigationMap->Find(i, j) != NULL)
		{
		    //navigationMap->AddNode(n);
		}
		// otherwise create new node
		else
		{
		    node = new NavigationNode(i,j);
		    navigationMap->AddNode(node);
		    FindNeighbour(node, map, navigationMap);
		}
	    }
	}
    }
}

// CHECK
void Labyrinth::FindNeighbour(NavigationNode *node, Vector<Vector<int> >map, NavigationMap *navigationMap)
{
    //if (node->GetX() > 0 && node->GetX() < map.Capacity()-1)
    // pozera hore, vpravo, dole, vlavo a pridava susedov
    
    // checking the block above
    if (node->GetY() > 0)
    {
	NavigationNode *n;
	
	if ((n = navigationMap->Find(node->GetX(), node->GetY()-1)) != NULL)
	{
	    node->AddNeighbour(n);
	}
	else
	{
	    n = new NavigationNode(node->GetX(), node->GetY()-1);
	    node->AddNeighbour(n);
	    FindNeighbour(n, map, navigationMap);
	}
    }
    
    // checking the block on the right side
    if (node->GetX() < map.Capacity()-1)
    {
	NavigationNode *n;
	
	if ((n = navigationMap->Find(node->GetX()+1, node->GetY())) != NULL)
	{
	    node->AddNeighbour(n);
	}
	else
	{
	    n = new NavigationNode(node->GetX()+1, node->GetY());
	    node->AddNeighbour(n);
	    FindNeighbour(n, map, navigationMap);
	}
    }
    
    // checking the block below
    if (node->GetY() < map[0].Capacity()-1)
    {
	NavigationNode *n;
	
	if ((n = navigationMap->Find(node->GetX(), node->GetY()+1)) != NULL)
	{
	    node->AddNeighbour(n);
	}
	else
	{
	    n = new NavigationNode(node->GetX(), node->GetY()+1);
	    node->AddNeighbour(n);
	    FindNeighbour(n, map, navigationMap);
	}
    }
    
    // checking the block on the left side
    if (node->GetX() > 0)
    {
	NavigationNode *n;
	
	if ((n = navigationMap->Find(node->GetX()-1, node->GetY())) != NULL)
	{
	    node->AddNeighbour(n);
	}
	else
	{
	    n = new NavigationNode(node->GetX()-1, node->GetY());
	    node->AddNeighbour(n);
	    FindNeighbour(n, map, navigationMap);
	}
    }
}


void Labyrinth::CreateCoins()
{
    Node* objectNode = scene_->CreateChild("Apple");
    objectNode->SetPosition(Vector3(6.0f, 3.0f, 0.0f));
    objectNode->SetScale(0.5f);
    
    Apple *apple = new Apple(context_);
    apple->CreateNode(objectNode, scene_->GetNode());
    apple = objectNode->CreateComponent<Apple>();
}


void Labyrinth::CreateBlock(int number)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    Node* objectNode = scene_->CreateChild("Floor");
    objectNode->SetPosition(Vector3(0, 0, 5));
    objectNode->SetRotation(Quaternion(0, 0, -90));
    objectNode->SetScale(1);
    StaticModel* object = objectNode->CreateComponent<StaticModel>();
    object->SetModel(cache->GetResource<Model>("Urho resources/Models/BlockFence.mdl"));
    //object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Hedge.xml"));
    object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/BrickA.xml"));
    //object->SetCastShadows(true);
    
    RigidBody* body = objectNode->CreateComponent<RigidBody>();
    body->SetCollisionLayer(2);
    // Bigger boxes will be heavier and harder to move
    //body->SetMass(scale * 2.0f);
    CollisionShape* shape = objectNode->CreateComponent<CollisionShape>();
    shape->SetBox(Vector3(2, 2, 2));
    
    
    Node* nodeApple = scene_->CreateChild("Apple");
    nodeApple->SetPosition(Vector3(0, 3, 9));
    nodeApple->SetRotation(Quaternion(0, 0, -90));
    nodeApple->SetScale(1);
    StaticModel* apple = nodeApple->CreateComponent<StaticModel>();
    apple->SetModel(cache->GetResource<Model>("Urho resources/Models/Apple.mdl"));
    //apple->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Hedge.xml"));
    apple->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Apple.xml"));
    //apple->SetCastShadows(true);
    
    RigidBody* bodyApple = nodeApple->CreateComponent<RigidBody>();
    bodyApple->SetCollisionLayer(2);
    // Bigger boxes will be heavier and harder to move
    //bodyApple->SetMass(scale * 2.0f);
    CollisionShape* shapeApple = nodeApple->CreateComponent<CollisionShape>();
    shapeApple->SetBox(Vector3(2, 2, 2));
    
    
    Node* nodeCherry = scene_->CreateChild("Cherry");
    nodeCherry->SetPosition(Vector3(9, 3, 0));
    nodeCherry->SetRotation(Quaternion(0, 0, -90));
    nodeCherry->SetScale(1);
    StaticModel* cherry = nodeCherry->CreateComponent<StaticModel>();
    cherry->SetModel(cache->GetResource<Model>("Urho resources/Models/Cherry.mdl"));
    //cherry->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Hedge.xml"));
    cherry->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Cherry.xml"));
    //cherry->SetCastShadows(true);
    
    RigidBody* bodyCherry = nodeCherry->CreateComponent<RigidBody>();
    bodyCherry->SetCollisionLayer(2);
    // Bigger boxes will be heavier and harder to move
    //bodyCherry->SetMass(scale * 2.0f);
    CollisionShape* shapeCherry = nodeCherry->CreateComponent<CollisionShape>();
    shapeCherry->SetBox(Vector3(2, 2, 2));
    
    
    Node* nodeBanana = scene_->CreateChild("Banana");
    nodeBanana->SetPosition(Vector3(0, 3, 15));
    nodeBanana->SetRotation(Quaternion(0, 0, -90));
    nodeBanana->SetScale(1);
    StaticModel* banana = nodeBanana->CreateComponent<StaticModel>();
    banana->SetModel(cache->GetResource<Model>("Urho resources/Models/Banana.mdl"));
    //banana->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Hedge.xml"));
    banana->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Banana.xml"));
    //banana->SetCastShadows(true);
    
    RigidBody* bodyBanana = nodeBanana->CreateComponent<RigidBody>();
    bodyBanana->SetCollisionLayer(2);
    // Bigger boxes will be heavier and harder to move
    //bodyBanana->SetMass(scale * 2.0f);
    CollisionShape* shapeBanana = nodeBanana->CreateComponent<CollisionShape>();
    shapeBanana->SetBox(Vector3(2, 2, 2));
    
    /*switch (number)
    {
	// TODO
	//case
    }*/
}

