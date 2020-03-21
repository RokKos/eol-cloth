// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "writeOFF.h"



// write mesh to an ascii off file
template <typename DerivedV, typename DerivedF>
IGL_INLINE bool igl::writeOFF(
  const std::string fname,
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F)
{
  using namespace std;
  using namespace Eigen;
  assert(V.cols() == 3 && "V should have 3 columns");
  ofstream s(fname);
  if(!s.is_open())
  {
    fprintf(stderr,"IOError: writeOFF() could not open %s\n",fname.c_str());
    return false;
  }

  s<<
    "OFF\n"<<V.rows()<<" "<<F.rows()<<" 0\n"<<
    V.format(IOFormat(FullPrecision,DontAlignCols," ","\n","","","","\n"))<<
    (F.array()).format(IOFormat(FullPrecision,DontAlignCols," ","\n","3 ","","","\n"));
  return true;
}

// write mesh and colors-by-vertex to an ascii off file
template <typename DerivedV, typename DerivedF, typename DerivedC>
IGL_INLINE bool igl::writeOFF(
  const std::string fname,
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  const Eigen::PlainObjectBase<DerivedC>& C)
{
  using namespace std;
  using namespace Eigen;
  assert(V.cols() == 3 && "V should have 3 columns");
  assert(C.cols() == 3 && "C should have 3 columns");

  if(V.rows() != C.rows())
  {
    fprintf(stderr,"IOError: writeOFF() Only color per vertex supported. V and C should have same size.\n");
    return false;
  }

  ofstream s(fname);
  if(!s.is_open())
  {
    fprintf(stderr,"IOError: writeOFF() could not open %s\n",fname.c_str());
    return false;
  }

  //Check if RGB values are in the range [0..1] or [0..255]
  int rgbScale = (C.maxCoeff() <= 1.0)?255:1;
  // Use RGB_Array instead of RGB because of clash with mingw macro 
  // (https://github.com/libigl/libigl/pull/679)
  Eigen::MatrixXd RGB_Array = rgbScale * C;

  s<< "COFF\n"<<V.rows()<<" "<<F.rows()<<" 0\n";
  for (unsigned i=0; i< V.rows(); i++)
  {
    s <<V.row(i).format(IOFormat(FullPrecision,DontAlignCols," "," ","","",""," "));
    s << unsigned(RGB_Array(i,0)) << " " << unsigned(RGB_Array(i,1)) << " " << unsigned(RGB_Array(i,2)) << " 255\n";
  }

  s<<(F.array()).format(IOFormat(FullPrecision,DontAlignCols," ","\n","3 ","","","\n"));
  return true;
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template bool igl::writeOFF<Eigen::Matrix<float, -1, 3, 1, -1, 3>, Eigen::Matrix<int, -1, 3, 1, -1, 3> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<float, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 1, -1, 3> > const&);
// generated by autoexplicit.sh
template bool igl::writeOFF<Eigen::Matrix<double, 8, 3, 0, 8, 3>, Eigen::Matrix<int, 12, 3, 0, 12, 3> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<double, 8, 3, 0, 8, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, 12, 3, 0, 12, 3> > const&);
// generated by autoexplicit.sh
template bool igl::writeOFF<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&);
template bool igl::writeOFF<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1> > const&);
template bool igl::writeOFF<Eigen::Matrix<float, -1, 3, 1, -1, 3>, Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<float, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1> > const&);
template bool igl::writeOFF<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 3, 0, -1, 3> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&);
template bool igl::writeOFF<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, 3, 0, -1, 3> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&);
template bool igl::writeOFF<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<int, -1, 3, 1, -1, 3> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 1, -1, 3> > const&);
template bool igl::writeOFF<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<int, -1, 3, 1, -1, 3>, Eigen::Matrix<double, -1, 3, 1, -1, 3> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&);
template bool igl::writeOFF<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<unsigned int, -1, 3, 1, -1, 3>, Eigen::Matrix<double, -1, 3, 1, -1, 3> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<unsigned int, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&);
#endif
