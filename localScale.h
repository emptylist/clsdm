#ifndef LOCAL_SCALE_H
#define LOCAL_SCALE_H

#define EPS_PARTITION_SIZE  50
#define FIRST_SPECTRA_CUT   3/7
#define SECOND_SPECTRA_CUT  1/2
#define THIRD_SPECTRA_CUT   4/7
#define NUM_SUB_SPECTRA     5
#include "distances.h"

typedef std::vector<dataPoint> dataSet;
typedef std::vector<bool> statusVector;
typedef std::vector<double> spectrum;

struct DistPoint {
  double distance;
  dataPoint * point;
};

struct LocalParameters {
  double scale;
  int dimension;
};

LocalParameters local_scaling(const dataSet&, int, int);

#endif
