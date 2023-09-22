#include <iostream>
#include <cmath>
#include <string>
#include <boost/lambda/lambda.hpp>
#include <iterator>
#include <algorithm>

int main(int argc, char* argv[]) {
    // if (argc < 2) {
    //     // report version
    //     std::cout << "Usage: " << argv[0] << " number" << std::endl;
    //     return 1;
    // }

    // // convert input to double
    // // TODO 4: Replace atof(argv[1]) with std::stod(argv[1])
    // const double inputValue = std::stod(argv[1]);

    // // calculate square root
    // const double outputValue = sqrt(inputValue);
    // std::cout << "The square root of " << inputValue << " is " << outputValue
    //           << std::endl;

    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 4) << " " );
    std::cout << std::endl;
    return 0;
}
