#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stderror>

#include "localScale.h"
#include "distances.h"

using namespace std;

bool compare(const DistPoint x&, const DistPoint y&)
{
  //To be passed to the library QuickSort function to order the 
  // data points with respect to their distance from the data point
  // of interest.

  return x.distance < y.distance;
}

vector<DistPoint> distances_from_point(const int index, const dataSet X&)
{
  //Takes an integer index value and a reference to the dataSet struct
  // of interest.  Computes the distance from each point in the data set
  // to the point of interest denoted by the index value.
  
  dataSet::size_type sz = dataSet.size();

  vector<DistPoint> distances(sz); // Runtime pre-allocate the memory needed.
  dataPoint target = X[index];  //The data point we're interested in.
  
  for (dataSet::size_type i = 0; i < sz; ++i) {
    distances[i] = DistPoint {rmsd(target, X[i]), dataPoint * X[i]}
  }
  
  return distances;
}

vector<double> partition_eps(const double eps)
{
  vector<double> eps_partition(EPS_PARTITION_SIZE);

  for (vector<double>::size_type i = 0; i < EPS_PARTITION_SIZE; ++i) {
    eps_partition[i] = (i/EPS_PARITION_SIZE) * eps;
  }
  
  return eps_partition;
}

vector<dataPoint *> compute_eps_ball(const vector<DistPoint>& distances, const double eps)
{
  vector<dataPoint *> eps_ball;
  double dist = 0.0;
  vector<DistPoint>::size_type index = 0;

  while(dist < eps) {
    eps_ball.push_back(distances[index].point);
    ++index;
    dist = distances[index].distance;
  }
    
  return eps_ball;
}

//TODO: Fill these functions in.
spectrum compute_normalized_spectrum(const vector<dataPoint *>& X)
{
  //Uses SLEPc to compute singular value spectra for a data set, and returns them normalized
  // by the square root of the number of points in the data set.
  spectrum spec;
  return spec;
}

//Status Vector Functions: These are somewhat ugly.  They compare the spectral values to determine
// the local dimension about a data point.  Several functions define various levels of abstraction for
// this operation, so as to keep the main status vector function from getting overloaded or repetetive.

bool compare_spectra(const spectrum& base_spectrum, 
		     const vector<spectrum>& sub_spectra, int cut_location)
{
  vector<int> spectrum_gap_status(NUM_SUB_SPECTRA);
  for(vector<int>::size_type i = 0; i < NUM_SUB_SPECTRA; ++i) {
    if (base_spectrum[cut_location] > (2 * sub_spectra[i][cut_location])) {
      spectrum_gap_status[i] = 1;
    }
    else {
      spectrum_gap_status[i] = 0;
    }
  }
  if (accumulate(spectrum_gap_status.begin(), spectrum_gap_status.end(), 0) = NUM_SUB_SPECTRA)
    return 1;
  else
    return 0;
}

bool compute_status(const vector<spectrum>& spectra, int index, 
		    int loc_first_cut, int loc_second_cut, int loc_third_cut)
{
  if (index >= spectra.size() - NUM_SUB_SPECTRA)
    throw domain_error("Invalid spectrum index.");
  
  spectrum base_spectrum = spectra[index];

  spectrum first_spectrum = spectra[index + 1];
  spectrum second_spectrum = spectra[index + 2];
  spectrum third_spectrum = spectra[index + 3];
  spectrum fourth_spectrum = spectra[index + 4];
  spectrum fifth_spectrum = spectra[index + 5];
  

  if (first_spectrum[loc_first_cut] > (2 * second_spectrum[loc_second_cut]) ||
      first_spectrum[loc_second_cut] > (2 * second_spectrum[loc_second_cut]) ||
      first_spectrum[loc_third_cut] > (2 * second_spectrum[loc_third_cut]))
    status = 1;
  return 0;
}

statusVector compute_status_vector(const vector<spectrum>& spectra, double eps)
{
  statusVector status(spectra.size() - 1);
  statusVector::size_type sz = status.size();
  for (vector<spectrum>::size_type i = 0; i < sz; ++i) {
    status[i] = compute_status(spectra, i, loc_first_cut, loc_second_cut, loc_third_cut);
  }
  return status;
}

int compute_local_dimension(const vector<spectrum>& spectra, double eps)
{
  //Computes a status vector by categorizing the singular value spectra into noise and 
  // non-noise.
  int local_dimension;
  return local_dimension;
}

double compute_local_scale(const vector<spectrum>& spectra, int local_dimension, double cutoff)
{
  int local_dimension;
  return local_dimension;
}

//This is the primary logic function.  This accepts a data set X, index, and max dimension
// max_dim and returns the local scaling parameter and local dimension for the data point 
// indicated by X[index], assuming the local dimension is no greater than max_dim. 

LocalParameters local_scaling(const dataSet X&, int index, int max_dim)
{
  LocalParameters     params;
  vector<DistPoint>   distances;
  statusVector        status;
  double              eps;
  vector<double>      eps_partition;
  vector<spectrum>    spectra;

  // Compute vector<DistPoint> distances
  distances = distances_from_point(index, X);

  // Sort the data points by their distances from the target point
  sort(distances.begin(), distances.end(), compare);

  // For increasing values of eps, choose the points with rmsd(target, x) < eps
  // and compute the singular values of the generated matrix.

  eps_partition = partition_eps(eps);
  vector<dataPoint *> eps_ball;

  for (int i = 0; i < EPS_PARTITION_SIZE; ++i) { //These are all wishful-thinking functions
    eps_ball = compute_eps_ball(distances, eps_partition[i]);
    spectra[i] = compute_normalized_spectrum(data_segment, max_dim);
  }

  //This section will need to be rewritten
  status = compute_status_vector(spectra, eps);

  params.scale = eps_partition[find(status.first(), status.end(), 1]; // I think this is wrong...
  params.dimension = compute_local_dimension(spectra, status, cutoff);
  
  return params;
}
