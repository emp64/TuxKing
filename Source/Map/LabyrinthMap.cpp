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
#include "Urho3D/Resource/ResourceCache.h"
#include "Urho3D/Scene/Node.h"
#include "Urho3D/Container/Vector.h"
#include "Urho3D/Graphics/StaticModel.h"
#include "Urho3D/Physics/CollisionShape.h"
#include "Urho3D/Physics/RigidBody.h"
#include "Urho3D/Scene/Scene.h"
#include "Urho3D/Graphics/Material.h"
#include "Urho3D/Graphics/Model.h"


#include "LabyrinthMap.h"
#include "../Game/CreateNodes.h"
#include "../Functions.h"



LabyrinthMap::LabyrinthMap(Context* context, Scene* scene) : Object(context)
{
    scene_ = scene;
    context_ = context;
    CreateMap(32, 20);
    LoadMap("labyrinth/Level01.lvl");
    
    // TODO nacitanie "kampane" - zoznamu levelov
}

LabyrinthMap::~LabyrinthMap()
{
    
}

int LabyrinthMap::LoadLevel(int level)
{
    LoadMap(levels[level]);
}

// TODO CURRENT
int LabyrinthMap::LoadMap(String filename)
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

void LabyrinthMap::CreateMap(int** map)
{
    for (int x = 0; x < map_.Capacity(); x++)
    {
	for (int y = 0; y < map_[x].Capacity(); y++)
	{
	    CreateBlock(map_[x][y]);
	}
    }
}


void LabyrinthMap::CreateMap(int mapLength, int mapWidth)
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
void LabyrinthMap::CreateNavigationMap(Vector< Vector< int > > map)
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
void LabyrinthMap::FindNeighbour(NavigationNode *node, Vector<Vector<int> >map, NavigationMap *navigationMap)
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


void LabyrinthMap::CreateCoins()
{
    Node* objectNode = scene_->CreateChild("Apple");
    objectNode->SetPosition(Vector3(6.0f, 3.0f, 0.0f));
    objectNode->SetScale(0.5f);
    
    Apple *apple = new Apple(context_);
    apple->CreateNode(objectNode, scene_->GetNode());
    apple = objectNode->CreateComponent<Apple>();
}


void LabyrinthMap::CreateBlock(int number)
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