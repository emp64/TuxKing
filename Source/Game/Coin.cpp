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
#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsEvents.h>

#include "Coin.h"



Coin::Coin(Context* context) : LogicComponent(context)
{
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

Coin::~Coin()
{

}

void Coin::RegisterObject(Context* context)
{
    context->RegisterFactory<Coin>();
}

void Coin::Start()
{
    // TODO DELETE ??? je toto potrebne ???
    Urho3D::LogicComponent::Start();
    
    // Subscribe to collisions with Coin node
    SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(Coin, HandleNodeCollision));
}

void Coin::FixedUpdate(float timeStep)
{
    Urho3D::LogicComponent::FixedUpdate(timeStep);
    
    /*RigidBody* body = GetComponent<RigidBody>();
    body->SetRotation(Quaternion(30));*/
    // TODO moc rýchlo sa to točí, treba to nejako regulovať pomocou času
    //float rotation = 0.10f * timeStep;
    //node_->Rotate(Quaternion(100, 0, 1.0, 0));
    static double j;
    j += 0.03;
    Vector3 coord = node_->GetPosition();
    coord.y_ = 2 + sin(j)/8;
    node_->SetPosition(Vector3(coord));
}

void Coin::Disappear()
{
    node_->Remove();
}


void Coin::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;
    
    Node* OtherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
    String name = OtherNode->GetName();
    //LOGERRORF("something collided with: %s",OtherNode->GetName().CString());
    if (name == "Ferdo")
    {
	LOGDEBUG("Ferdo COLLISION !!!!!");
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

