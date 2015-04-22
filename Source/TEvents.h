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

#pragma once

#include <Urho3D/Core/Object.h>

namespace Urho3D
{

/// Switch to Labyrinth state event.
EVENT(E_SWITCHTOLABYRINTH, SwitchToLabyrinth)
{
    //PARAM(P_FRAMENUMBER, FrameNumber);      // unsigned
    //PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Signals when Player collides with Coin.
EVENT(E_COINCOLLISION, CoinCollision)
{
    //PARAM(P_FRAMENUMBER, FrameNumber);      // unsigned
    //PARAM(P_TIMESTEP, TimeStep);            // float
}

}

