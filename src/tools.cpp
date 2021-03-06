#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth)
{
  VectorXd rmse(4);
  VectorXd ResidualSum(4);
  rmse << 0, 0, 0, 0;
  ResidualSum << 0, 0, 0, 0;

  if(  (estimations.size()  != ground_truth.size())
     ||(estimations.size()  == 0                  )
     ||(ground_truth.size() == 0                  )) 
  {
    cout << "Invalid estimation or ground_truth data" << endl;
    return rmse;
  }
  //accumulate squared residuals
  for (unsigned int i = 0; i < estimations.size(); ++i) {

    VectorXd residual = estimations[i] - ground_truth[i];

    //coefficient-wise multiplication
    residual = residual.array()*residual.array();
    ResidualSum += residual;
  }

  //calculate the mean
  rmse = ResidualSum / estimations.size();

  //calculate the squared root
  rmse = rmse.array().sqrt();

  //return the result
  return rmse;
}