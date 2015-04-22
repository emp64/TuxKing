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
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>

#include "CreateNodes.h"

/// DELETE

CreateNodes::CreateNodes(Context* context) : Object(context)
{

}

CreateNodes::~CreateNodes()
{

}

Node* CreateNodes::CreateCoin(Node* node)
{
    LOGDEBUG("CreateNodes::CreateCoin");
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    // Create the floor object
    //Node* floorNode = scene_->CreateChild("Floor");
    //this->SetPosition(Vector3(0.0f, -0.5f, 0.0f));
    //node->SetScale(Vector3(2.0f, 1.0f, 2.0f));
    StaticModel* object = node->CreateComponent<StaticModel>();
    object->SetModel(cache->GetResource<Model>("Urho resources/Models/Coin.mdl"));
    object->SetMaterial(cache->GetResource<Material>("Urho resources/Materials/matCoin.xml"));
    object->SetCastShadows(true);

    RigidBody* body = node->CreateComponent<RigidBody>();
    body->SetCollisionLayer(1);
    //body->SetMass(1.0f);
    // Use collision layer bit 2 to mark world scenery. This is what we will raycast against to prevent camera from going
    // inside geometry
    body->SetCollisionLayer(2);
    CollisionShape* shape = node->CreateComponent<CollisionShape>();
    shape->SetCapsule(2.0f, 2.0f, Vector3(0.0f, 0.0f, 0.0f));
}

Node* CreateNodes::CreatePlayer(Node* node)
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


Node* CreateNodes::CreateEnemyGreen()
{

}
