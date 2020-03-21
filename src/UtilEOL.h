#pragma once
#ifndef __UTILEOL__
#define __UTILEOL__






Eigen::MatrixXd deform_grad(const Face *f);

Eigen::MatrixXd deform_grad_v(const Vert* v);

#endif