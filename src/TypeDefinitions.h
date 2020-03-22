#pragma once
#ifndef __TypeDefinitions__
#define __TypeDefinitions__

namespace EOL {
	struct Material {
		double density; // area density
		double e;
		double nu;
		double beta;
		double dampingA;
		double dampingB;
	};

	struct Remeshing {
		double refine_angle, refine_compression, refine_velocity;
		double size_min, size_max; // size limits
		double aspect_min; // aspect ratio control
	};

}

#endif