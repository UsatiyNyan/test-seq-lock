#include "workers.h"

#include <iostream>

int main() {
    SharedState ss{std::latch{2}};
    std::thread writer{increment_worker, std::ref(ss)};
    std::thread reader{reader_worker, std::ref(ss)};

    std::string anything;
    std::cout << "type anything and ENTER to stop\n";
    std::cin >> anything;
    ss.run = false;

    writer.join();
    reader.join();

    return 0;
}
