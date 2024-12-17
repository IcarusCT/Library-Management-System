#include "gateway.hpp"
#include <thread>

using namespace lklibs;

int main() {
    Gateway gateway;
    gateway.startThreads();

    return 0;
}
