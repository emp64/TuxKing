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

#include "NavigationNode.h"

NavigationNode::NavigationNode(int x, int y)
{

}

NavigationNode::~NavigationNode()
{

}

int NavigationNode::GetX()
{

}

int NavigationNode::GetY()
{

}

Urho3D::List< NavigationNode* > NavigationNode::GetNeighbours()
{

}

void NavigationNode::AddNeighbour(NavigationNode *newNeighbour)
{
    this->neighbours.Push(newNeighbour);
}


/* -------- NavigationMap ----------------------------------- */
void NavigationMap::AddNode(NavigationNode* node)
{
    map.Push(node);
}


NavigationNode* NavigationMap::Find(int x, int y)
{
    for (int i = 0; i < map.Size(); i++)
    {
	if (map[i]->GetX() == x && map[i]->GetY() == y)
	{
	    return map[i];
	}
    }
    return NULL;
}
