#pragma once
#ifndef __remeshExtension__
#define __remeshExtension__

#include "external/ArcSim/remesh.hpp"

namespace EOL {
	ARCSim::RemeshOp split_edgeForced(ARCSim::Edge* edge, double d, double thresh);
	ARCSim::RemeshOp collapse_edgeForced(ARCSim::Edge& edge, int i);
	ARCSim::RemeshOp split_face(ARCSim::Face* face, ARCSim::Vec3 b);
}
#endif