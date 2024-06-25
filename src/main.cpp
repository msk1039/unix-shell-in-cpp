#include <iostream>

int main()
{
  
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true)
  {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    size_t start = 0;
    size_t end = input.length() - 1;

    std::string firstWord = input.substr(0, input.find(" "));

    if (input == "exit 0")
      return 0;
    else if(firstWord == "echo"){
      std::string echo = input.substr(5);
      std::cout << echo << std::endl;
    }
    else{
    std::cout << input << ": command not found" << std::endl;

    }
  
  }
}
