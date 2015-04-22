/*
 * Copyright (c) 2015 empirer <empirer64@gmail.com>
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
/*
 * Copyright (c) 2015 empirer <empirer64@gmail.com>
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
#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Material.h>

#include "Apple.h"

Apple::Apple(Context *context) : LogicComponent(context)
{
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

Apple::~Apple()
{

}

void Apple::RegisterObject(Context* context)
{
    context->RegisterFactory<Apple>();
}

void Apple::CreateNode(Node* node, Vector3 cameraPosition)
{
    LOGDEBUG("Apple::CreateNode");
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    // Create the floor object
    //Node* floorNode = scene_->CreateChild("Floor");
    //this->SetPosition(Vector3(0.0f, -0.5f, 0.0f));
    //node->SetScale(Vector3(2.0f, 0.001f, 2.0f));
    StaticModel* object = node->CreateComponent<StaticModel>();
    object->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    
    object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/Apple.xml"));
    object->SetCastShadows(true);
    //node->Rotate(Quaternion(45, 0, 0, 1.0));
    RigidBody* body = node->CreateComponent<RigidBody>();
    body->SetCollisionLayer(1);
    //body->SetMass(1.0f);
    // Use collision layer bit 2 to mark world scenery. This is what we will raycast against to prevent camera from going
    // inside geometry
    body->SetCollisionLayer(2);
    CollisionShape* shape = node->CreateComponent<CollisionShape>();
    shape->SetBox(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f));
    
    //TODO look at camera
    node->LookAt(cameraPosition);
}


void Apple::Start()
{
    // TODO DELETE ??? je toto potrebne ???
    Urho3D::LogicComponent::Start();
    
    // Subscribe to collisions with Apple node
    SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(Apple, HandleNodeCollision));
}

void Apple::FixedUpdate(float timeStep)
{
    Urho3D::LogicComponent::FixedUpdate(timeStep);
    
    static double j;
    j += 0.03;
    Vector3 coord = node_->GetPosition();
    coord.y_ = 2 + sin(j)/8;
    node_->SetPosition(Vector3(coord));
}

void Apple::Disappear()
{
    node_->Remove();
}

// TODO
void Apple::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;
    
    Node* OtherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
    String name = OtherNode->GetName();
    //LOGERRORF("something collided with: %s",OtherNode->GetName().CString());
    if (name == "Player")
    {
	LOGDEBUG(name + "-Apple COLLISION !!!!!");
	Disappear();
	/*if (clausCollided_ == false)
	{
	    clausCollided_ = true;
	    elapsedTime_ = 0.0f;
	    resetDelay_ = 0.0f;
	    resetClaus_ = true;
	    score_++;
	    text_->SetText("Children Saved: " + String(score_));
	    return;
	}*/
    }
}