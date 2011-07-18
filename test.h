#include "plot_lib.h"
#include <iostream>
#include <vector>
#include <string>
#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/algorithm/string/split.hpp"


#define VERSION "1.0"

#define _ROOT_VERSION "5.30/00"

#define _BOOST_VERSION "1.47.0"

namespace bf = boost;

myoptions menu();
myoptions parse_batch(std::string bfn, bool &single);
