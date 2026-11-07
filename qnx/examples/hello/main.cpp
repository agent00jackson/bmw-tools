// SPDX-License-Identifier: MIT
#include <stdio.h>
#include <string>
#include <vector>
int main() {
    std::vector<int> values;
    values.push_back(6);
    std::string message("Hello from QNX");
    printf("%s %d\n", message.c_str(), values[0]);
}
