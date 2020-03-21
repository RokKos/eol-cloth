#pragma once
#ifndef __CONVERSIONS__
#define __CONVERSIONS__

// These conversions translate ArcSim vectors to Eigen vectors

// Eigen 2 vec
ARCSim::Vec2 e2v(const Eigen::Vector2d);
ARCSim::Vec3 e2v(const Eigen::Vector3d);

// Vec 2 Eigen
Eigen::Vector2d v2e(const ARCSim::Vec2);
Eigen::Vector3d v2e(const ARCSim::Vec3);

// Vec 3D to Eigen 2D
Eigen::Vector2d v322e(const ARCSim::Vec3 v);

#endif