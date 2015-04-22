/*
 * 
 * 
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
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/IO/Log.h>

#include "PlayerController.h"


PlayerController::PlayerController(Context* context) : LogicComponent(context),
    onGround_(false),
    okToJump_(true),
    inAirTimer_(0.0f)
{
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

PlayerController::~PlayerController()
{
    
}

void PlayerController::RegisterObject(Context* context)
{
    context->RegisterFactory<PlayerController>();
    
    // These macros register the class attributes to the Context for automatic load / save handling.
    // We specify the Default attribute mode which means it will be used both for saving into file, and network replication
    ATTRIBUTE("Controls Yaw", float, controls_.yaw_, 0.0f, AM_DEFAULT);
    ATTRIBUTE("Controls Pitch", float, controls_.pitch_, 0.0f, AM_DEFAULT);
    ATTRIBUTE("On Ground", bool, onGround_, false, AM_DEFAULT);
    ATTRIBUTE("OK To Jump", bool, okToJump_, true, AM_DEFAULT);
    ATTRIBUTE("In Air Timer", float, inAirTimer_, 0.0f, AM_DEFAULT);
}

void PlayerController::CreateNode(Node *node)
{
    LOGDEBUG("CreateNodes::CreatePlayer");
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Create the rendering component + animation controller
    AnimatedModel* object = node->CreateComponent<AnimatedModel>();
    object->SetModel(cache->GetResource<Model>("Urho resources/Models/trpaslik.mdl"));
    object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/matPlatno.xml"));
    object->SetCastShadows(true);
    node->CreateComponent<AnimationController>();

    // Set the head bone for manual control
    //object->GetSkeleton().GetBone("Bip01_Head")->animated_ = false;

    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    RigidBody* body = node->CreateComponent<RigidBody>();
    body->SetCollisionLayer(1);
    body->SetMass(1.0f);

    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body->SetAngularFactor(Vector3::ZERO);

    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body->SetCollisionEventMode(COLLISION_ALWAYS);

    // Set a capsule shape for collision
    CollisionShape* shape = node->CreateComponent<CollisionShape>();
    shape->SetCapsule(4.5f, 7.0f, Vector3(0.0f, 1.5f, 0.0f));
    
    node->SetScale(0.5);
    node->SetRotation(Quaternion(0, 90, 0));
}


void PlayerController::Start()
{
    // Subscribe to collisions with PlayerController node
    SubscribeToEvent(GetNode(), E_NODECOLLISION, HANDLER(PlayerController, HandleNodeCollision));
}


// TODO
void PlayerController::GoForward()
{

}

// TODO
void PlayerController::GoBackward()
{

}

// TODO
void PlayerController::GoLeft()
{

}

// TODO
void PlayerController::GoRight()
{

}

void PlayerController::FixedUpdate(float timeStep)
{
    // TODO treba prerobiť na správne klávesy na ovládanie - možno vytvoriť na zadanie controls 
    // nejaky SetParameters alebo to spraviť cez Labyrinth::HandlPostUpdate 
    using namespace Update;

    //Input* input = GetSubsystem<Input>();
    Input* input = GetSubsystem<Input>();
    
    // Clear previous controls
    // TODO pozri, naco to tu je ? mozno by netrebalo pri kazdom update znova nastavovat controller
    this->controls_.Set(CTRL_FORWARD | CTRL_BACK | CTRL_LEFT | CTRL_RIGHT | CTRL_JUMP, false);
    this->controls_.Set(CTRL_FORWARD, input->GetKeyDown(KEY_W));
    this->controls_.Set(CTRL_BACK, input->GetKeyDown(KEY_S));
    this->controls_.Set(CTRL_LEFT, input->GetKeyDown(KEY_A));
    this->controls_.Set(CTRL_RIGHT, input->GetKeyDown(KEY_D));
    
    
    
    /// \todo Could cache the components for faster access instead of finding them each frame
    RigidBody* body = GetComponent<RigidBody>();
    AnimationController* animCtrl = GetComponent<AnimationController>();
    
    // Update the in air timer. Reset if grounded
    if (!onGround_)
        inAirTimer_ += timeStep;
    else
        inAirTimer_ = 0.0f;
    // When character has been in air less than 1/10 second, it's still interpreted as being on ground
    bool softGrounded = inAirTimer_ < INAIR_THRESHOLD_TIME;
    
    // Update movement & animation
    const Quaternion& rot = node_->GetRotation();
    Vector3 moveDir = Vector3::ZERO;
    const Vector3& velocity = body->GetLinearVelocity();
    // Velocity on the XZ plane
    Vector3 planeVelocity(velocity.x_, 0.0f, velocity.z_);
    
    if (controls_.IsDown(CTRL_FORWARD))
        moveDir += Vector3::FORWARD;
    if (controls_.IsDown(CTRL_BACK))
        moveDir += Vector3::BACK;
    if (controls_.IsDown(CTRL_LEFT))
        moveDir += Vector3::LEFT;
    if (controls_.IsDown(CTRL_RIGHT))
        moveDir += Vector3::RIGHT;
    
    // Normalize move vector so that diagonal strafing is not faster
    if (moveDir.LengthSquared() > 0.0f)
        moveDir.Normalize();
    
    // If in air, allow control, but slower than when on ground
    body->ApplyImpulse(rot * moveDir * (softGrounded ? MOVE_FORCE : INAIR_MOVE_FORCE));
    
    if (softGrounded)
    {
        // When on ground, apply a braking force to limit maximum ground velocity
        Vector3 brakeForce = -planeVelocity * BRAKE_FORCE;
        body->ApplyImpulse(brakeForce);
        
        // Jump. Must release jump control inbetween jumps
        if (controls_.IsDown(CTRL_JUMP))
        {
            if (okToJump_)
            {
                body->ApplyImpulse(Vector3::UP * JUMP_FORCE);
                okToJump_ = false;
            }
        }
        else
            okToJump_ = true;
    }
    
    // Play walk animation if moving on ground, otherwise fade it out
    /*if (softGrounded && !moveDir.Equals(Vector3::ZERO))
        animCtrl->PlayExclusive("Models/Jack_Walk.ani", 0, true, 0.2f);
    else
        animCtrl->Stop("Models/Jack_Walk.ani", 0.2f);
    // Set walk animation speed proportional to velocity
    animCtrl->SetSpeed("Models/Jack_Walk.ani", planeVelocity.Length() * 0.3f);*/
    
    // Reset grounded flag for next frame
    onGround_ = false;
}

void PlayerController::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;
    
    Node* OtherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
    String name = OtherNode->GetName();
    //LOGERRORF("something collided with: %s",OtherNode->GetName().CString());
    // TODO treba doplnit ine typy a raobehat to
    // TODO treba spravit aby ho ta kolizia nespomalila
    if (name == "Cherry")
    {
	LOGDEBUG("PlayerController-Coin collision");
	/*if (clausCollided_ == false)
	{
	    clausCollided_ = true;
	    elapsedTime_ = 0.0f;
	    resetDelay_ = 0.0f;
	    resetClaus_ = true;
	    points++;
	    text_->SetText("Children Saved: " + String(points));
	    return;
	}*/
    }
    
    if (name == "Coin")
    {
	LOGDEBUG("PlayerController-Coin collision");
	/*if (clausCollided_ == false)
	{
	    clausCollided_ = true;
	    elapsedTime_ = 0.0f;
	    resetDelay_ = 0.0f;
	    resetClaus_ = true;
	    points++;
	    text_->SetText("Children Saved: " + String(points));
	    return;
	}*/
    }
    
    if (name == "Coin")
    {
	LOGDEBUG("PlayerController-Coin collision");
	/*if (clausCollided_ == false)
	{
	    clausCollided_ = true;
	    elapsedTime_ = 0.0f;
	    resetDelay_ = 0.0f;
	    resetClaus_ = true;
	    points++;
	    text_->SetText("Children Saved: " + String(points));
	    return;
	}*/
    }
    
    // Check collision contacts and see if character is standing on ground (look for a contact that has near vertical normal)
    
    MemoryBuffer contacts(eventData[P_CONTACTS].GetBuffer());
    
    RefCounted* otherNode = eventData["OtherNode"].GetPtr();
    RefCounted* otherBody = eventData["OtherBody"].GetPtr();
    //PODVector<unsigned int> *contacts = eventData["Contacts"].GetBuffer();
    
    while (!contacts.IsEof())
    {
        Vector3 contactPosition = contacts.ReadVector3();
        Vector3 contactNormal = contacts.ReadVector3();
        float contactDistance = contacts.ReadFloat();
        float contactImpulse = contacts.ReadFloat();
        
        // If contact is below node center and mostly vertical, assume it's a ground contact
        if (contactPosition.y_ < (node_->GetPosition().y_ + 1.0f))
        {
            float level = Abs(contactNormal.y_);
            if (level > 0.75)
                onGround_ = true;
        }
    }
}
