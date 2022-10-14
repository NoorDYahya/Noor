//
// Created by noor dar yahya on 05/06/2022.
//
#include "RecommenderSystemLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#define TEN 10
#define ONE 1


void tokenize(std::string const &str, char delim,
                                       std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}
std::unique_ptr<RecommenderSystem> RecommenderSystemLoader::
create_rs_from_movies_file(const std::string &movies_file_path) noexcept(false)
{

std::ifstream myfile(movies_file_path);
std::string line;
auto new_system = std::make_unique<RecommenderSystem>();

if (!myfile.is_open())
{
std::cerr << "Could not open the file - "
<< std::endl;
return nullptr;

}
while (std::getline(myfile, line))
{
std::vector<std::string> out;
std::string word;
std::istringstream my_stream(line);

while (my_stream >> word)
{
out.push_back(word);
}
std::vector<std::string> out_2;
tokenize(out[0], '-', out_2);

std::vector<double> features;

for (std::size_t i = 1; i < out.size(); i++)
{
auto num = std::stod(out[i]);
if(num <ONE || num > TEN)
{
throw std::out_of_range("given rate value is invalid");
}

features.push_back(num);

}
new_system->add_movie(out_2[0], std::stoi(out_2[1]),
        features);
features.clear();
}
myfile.close();
return new_system;
}


