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


#ifndef LABYRINTHMAP_H
#define LABYRINTHMAP_H

#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Container/List.h>

#include "../Game/Coin.h".
#include "../Game/Apple.h"
#include "../Game/Banana.h"
#include "../Map/NavigationNode.h"


using namespace Urho3D;

// LabyrinthMap class, includes all the static and dynamic map parts and assets. For example blocks, trees, ground ...
class LabyrinthMap : public Object
{
    OBJECT(LabyrinthMap)

public:
    LabyrinthMap(Context* context, Scene* scene);
    ~LabyrinthMap();
    
    
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
    
    
private:
    Scene* scene_;
    Coin* coin_;
    String levels[];
    Vector<Vector<int> > map_;
};

#endif // LABYRINTHMAP_H
