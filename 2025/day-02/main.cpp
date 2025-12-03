#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

bool isInvalidID(std::string str) {
  int halfStrLength = str.length() / 2;
  return str.substr(0, halfStrLength) ==
         str.substr(halfStrLength, str.length());
}

long long part1(std::vector<std::string> segments) {
  long long total = 0;

  for (std::string range : segments) {
    size_t pos = range.find('-');
    std::string start = range.substr(0, pos);
    long long startPos = std::stoll(start);

    std::string end = range.substr(pos + 1, range.length());
    long long endPos = std::stoll(end);

    for (long long i = startPos; i <= endPos; i++) {
      if (isInvalidID(std::to_string(i))) {
        total += i;
      }
    }
  }

  return total;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Argc is too low (" << argc << ")" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cout << "Failed to open " << argv[1] << std::endl;
  }
  std::string str;
  std::vector<std::string> segments;
  while (std::getline(file, str, ',')) {
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    segments.push_back(str);
  }
  file.close();

  std::cout << "Result part1: " << part1(segments) << std::endl;
  return 0;
}
