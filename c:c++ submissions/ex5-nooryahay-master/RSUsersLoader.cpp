//
// Created by noor dar yahya on 07/06/2022.
//
#include "RSUsersLoader.h"
#include "RecommenderSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <string.h>
#define TEN 10
#define ONE 1
void tokenize_2(std::string const &str, char delim,
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
std::vector<RSUser>
RSUsersLoader::create_users_from_file(const std::string &users_file_path,
                std::unique_ptr<RecommenderSystem> rs) noexcept(false)
{
std::ifstream my_stream(users_file_path);
std::string line;
std::getline(my_stream, line, '\n');
std::vector<std::string> file_names_year;
std::vector<std::string> file_names;
std::vector<int> file_year;
tokenize_2(line, ' ', file_names_year);
for (auto &file_name : file_names_year)
{
int pos = file_name.find('-');

std::string pro_sub = file_name.substr(pos + 1);
std::string pre_sub = file_name.substr(0, pos);
file_names.push_back(pre_sub);
file_year.push_back(std::stoi(pro_sub));
}
sp_system shared_sys = std::move(rs);
std::vector<RSUser> users_vec;
while (std::getline(my_stream, line, '\n'))
{
rank_map ranke_map(TEN, sp_movie_hash, sp_movie_equal);
std::vector<std::string> name_rate;
tokenize_2(line, ' ', name_rate);
std::string user = name_rate[0];
name_rate.erase(name_rate.begin());
for (std::size_t j = 0; j < name_rate.size(); j++)
{
sp_movie ptr_movie = shared_sys->get_movie(file_names[j],
                                           file_year[j]);
if (name_rate[j] == "NA")
{
ranke_map[ptr_movie] = 0;
} else
{
double num = std::stod(name_rate[j]);
if(num <ONE || num > TEN)
{
throw std::out_of_range("entered rate is not valid ");
}
ranke_map[ptr_movie] = num;
}
}
RSUser m(user, ranke_map, shared_sys);
users_vec.push_back(m);

}
return users_vec;
}





