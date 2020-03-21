// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "cotmatrix.h"


// For error printing

#include "cotmatrix_entries.h"

// Bug in unsupported/Eigen/SparseExtra needs iostream first


template <typename DerivedV, typename DerivedF, typename Scalar>
IGL_INLINE void igl::cotmatrix(
  const Eigen::MatrixBase<DerivedV> & V, 
  const Eigen::MatrixBase<DerivedF> & F, 
  Eigen::SparseMatrix<Scalar>& L)
{
  using namespace Eigen;
  using namespace std;

  L.resize(V.rows(),V.rows());
  Matrix<int,Dynamic,2> edges;
  int simplex_size = F.cols();
  // 3 for triangles, 4 for tets
  assert(simplex_size == 3 || simplex_size == 4);
  if(simplex_size == 3)
  {
    // This is important! it could decrease the comptuation time by a factor of 2
    // Laplacian for a closed 2d manifold mesh will have on average 7 entries per
    // row
    L.reserve(10*V.rows());
    edges.resize(3,2);
    edges << 
      1,2,
      2,0,
      0,1;
  }else if(simplex_size == 4)
  {
    L.reserve(17*V.rows());
    edges.resize(6,2);
    edges << 
      1,2,
      2,0,
      0,1,
      3,0,
      3,1,
      3,2;
  }else
  {
    return;
  }
  // Gather cotangents
  Matrix<Scalar,Dynamic,Dynamic> C;
  cotmatrix_entries(V,F,C);
  
  vector<Triplet<Scalar> > IJV;
  IJV.reserve(F.rows()*edges.rows()*4);
  // Loop over triangles
  for(int i = 0; i < F.rows(); i++)
  {
    // loop over edges of element
    for(int e = 0;e<edges.rows();e++)
    {
      int source = F(i,edges(e,0));
      int dest = F(i,edges(e,1));
      IJV.push_back(Triplet<Scalar>(source,dest,C(i,e)));
      IJV.push_back(Triplet<Scalar>(dest,source,C(i,e)));
      IJV.push_back(Triplet<Scalar>(source,source,-C(i,e)));
      IJV.push_back(Triplet<Scalar>(dest,dest,-C(i,e)));
    }
  }
  L.setFromTriplets(IJV.begin(),IJV.end());
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template void igl::cotmatrix<Eigen::Matrix<double, -1, -1, 1, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, double>(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 1, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::SparseMatrix<double, 0, int>&);
template void igl::cotmatrix<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 4, 0, -1, 4>, double>(Eigen::MatrixBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, 4, 0, -1, 4> > const&, Eigen::SparseMatrix<double, 0, int>&);
template void igl::cotmatrix<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 3, 0, -1, 3>, double>(Eigen::MatrixBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&, Eigen::SparseMatrix<double, 0, int>&);
template void igl::cotmatrix<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, double>(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::SparseMatrix<double, 0, int>&);
#endif
