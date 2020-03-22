#include "conversions.h"

namespace EOL {

    ARCSim::Vec2 e2v(const Eigen::Vector2d v) { return ARCSim::Vec2(v(0), v(1)); }

    ARCSim::Vec3 e2v(const Eigen::Vector3d v) {
        return ARCSim::Vec3(v(0), v(1), v(2));
    }

    Eigen::Vector2d v2e(const ARCSim::Vec2 v) {
        return Eigen::Vector2d(v[0], v[1]);
    }

    Eigen::Vector2d v322e(const ARCSim::Vec3 v) {
        return Eigen::Vector2d(v[0], v[1]);
    }

    Eigen::Vector3d v2e(const ARCSim::Vec3 v) {
        return Eigen::Vector3d(v[0], v[1], v[2]);
    }
}