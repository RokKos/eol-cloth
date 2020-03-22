#pragma once
#ifndef __Collisions__
#define __Collisions__

#include "boxTriCollision.h"
#include "Obstacles.h"

namespace EOL {

    void CD(const ARCSim::Mesh& mesh, const std::shared_ptr<Obstacles> obs, std::vector<std::shared_ptr<btc::Collision> >& cls);

    void CD2(const ARCSim::Mesh& mesh, const std::shared_ptr<Obstacles> obs,
        std::vector<std::shared_ptr<btc::Collision> >& cls);
}
#endif