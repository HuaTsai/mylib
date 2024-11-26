#include <myconfig.h>

#include <Eigen/Dense>
#include <boost/program_options.hpp>
#include <format>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  po::options_description desc("Allowed options");
  desc.add_options()("help,h", "Show help message");
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  std::cout << std::format("PROJECT_NAME: {}\n", PROJECT_NAME);
  std::cout << std::format("PROJECT_VERSION: {}.{}.{}\n", PROJECT_VERSION_MAJOR,
                           PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH);
  std::cout << Eigen::MatrixXd::Random(3, 3) << std::endl;
}
