#include <iostream>
#include <sstream>
#include <filesystem>
#include <string>
#include <fstream>

std::string get_path(std::string command)
{
  std::string path_env = std::getenv("PATH");
  std::stringstream ss(path_env);
  std::string path;
  while (!ss.eof())
  {
    getline(ss, path, ':');
    std::string abs_path = path + '/' + command;
    if (std::filesystem::exists(abs_path))
    {
      return abs_path;
    }
  }
  return "";
}

void handleType(std::string input)
{

  input.erase(0, input.find(" ") + 1);
  if (input == "echo" || input == "type" || input == "exit" || input == "pwd")
  {
    std::cout << input << " is a shell builtin\n";
  }
  else
  {

    std::string path = get_path(input);
    if (path.empty())
    {
      std::cout << input << ": not found\n";
    }
    else
    {
      std::cout << input << " is " << path << std::endl;
    }
  }
}

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
    {
      return 0;
    }
    else if (input == "pwd")
    {
      // std::cout << std::filesystem::current_path() << '\n';
      std::filesystem::path currentPath = std::filesystem::current_path();
      std::string currentPathString = currentPath.string();
      std::cout <<currentPathString << std::endl;


      //other method
      // char temp [ PATH_MAX ];
      // if ( getcwd(temp, PATH_MAX) != 0) 
      //   return std::string ( temp );

    }
    else if (firstWord == "echo")
    {
      std::string echo = input.substr(5);
      std::cout << echo << std::endl;
    }
    else if (firstWord == "type")
    {
      handleType(input);
    }
    else
    {

      std::string filepath = get_path(firstWord);
      if (filepath.empty())
      {
        std::cout << input << ": not found\n";
      }
      else
      {
        input.erase(0, input.find(" "));
        std::ifstream file(filepath);
        if (file.good())
        {
          std::string command = "exec " + filepath + input;
          std::system(command.c_str());
        }
        else
        {
          std::cout << input << ": not found\n";
        }
      }
    }
  }
}
