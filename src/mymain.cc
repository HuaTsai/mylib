#include <myconfig.h>

#include <Eigen/Dense>
#include <format>
#include <iostream>

int main() {
  std::cout << std::format("PROJECT_NAME: {}\n", PROJECT_NAME);
  std::cout << std::format("PROJECT_VERSION: {}.{}.{}\n", PROJECT_VERSION_MAJOR,
                           PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH);
  std::cout << Eigen::MatrixXd::Random(3, 3) << std::endl;
}
