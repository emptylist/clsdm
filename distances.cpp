#include <stdexcept>
#include <cmath>
#include "distances"

using namespace std;

double rmsd(const dataPoint x&, const dataPoint y&)
{
  dataPoint::size_type sz = x.size();

  if (sz != y.size()) 
    throw domain_error("Vectors are not the same size.");

  double sqdist = 0.0;
  double diff;

  for (dataPoint::size_type i = 0; i < sz; ++i) {

    diff = x[i] - y[i];
    sqdist += diff * diff;

  }

  return sqrt(sqdist/sz);
}
