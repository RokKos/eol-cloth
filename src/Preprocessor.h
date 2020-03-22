#pragma once
#ifndef __Preprocessor__
#define __Preprocessor__

#include "boxTriCollision.h"

namespace EOL {

    void preprocess(ARCSim::Mesh& mesh, const Eigen::MatrixXd& boundaries,
        std::vector<std::shared_ptr<btc::Collision> > cls);
    void preprocessPart(ARCSim::Mesh& mesh, const Eigen::MatrixXd& boundaries, const std::vector<std::shared_ptr<btc::Collision> > cls, int& part);
    void preprocessClean(ARCSim::Mesh& mesh);

}

#endif