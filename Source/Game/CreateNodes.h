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

#ifndef CREATENODES_H
#define CREATENODES_H

#include <Urho3D/Scene/Node.h>
#include <Urho3D/Core/Object.h>

using namespace Urho3D;


class CreateNodes : public Object
{
    OBJECT(CreateNodes)
    
public:
    CreateNodes( Context* context );
    ~CreateNodes();
    
    Node* CreateCoin( Node* node );
    Node* CreatePlayer( Node* node );
    
    Node* CreateEnemyRed();
    Node* CreateEnemyPurple();
    Node* CreateEnemyGreen();
    
};

#endif // CREATENODES_H
