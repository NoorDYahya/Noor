#include "RecommenderSystem.h"
#include "map"
#include <cmath>
#include "set"


std::pair<sp_movie,double> find_max(const std::map <sp_movie ,double>& lst_map)
{
    double max = 0;
    sp_movie mov;
    for(const auto &c:lst_map)
    {

        if(max<c.second)
        {
            mov = c.first;
            max= c.second;
        }
    }
    return std::make_pair(mov,max);
}

RecommenderSystem::RecommenderSystem ()=default;

sp_movie RecommenderSystem::add_movie(const std::string &name, int year,
                                      const std::vector<double> &features)
{
    sp_movie ptr_movie = std::make_shared<Movie>(name, year);

    big_system_[ptr_movie] = features;
    return ptr_movie;

}
double
scalar_product(const std::vector<double> &v1, const std::vector<double> &v2)
{
    double x = 0;
    for (std::size_t k = 0; k < v1.size(); k++)
    {
        x += v1[k] * v2[k];

    }
    return x;
}
std::vector<double>sum_vec(const std::vector<double> &v1,
                           const std::vector<double> &v2)
{
    std::vector<double> res(v1.size());
    for (std::size_t k = 0; k < v1.size(); k++)
    {
        res[k] = v1[k] + v2[k];

    }
    return res;

}
std::vector<double>
multi(const std::vector<double> &v1, double d )
{

    std::vector<double> res(v1.size());
    for (std::size_t k = 0; k < v1.size(); k++)
    {
        res[k] = ( v1[k] * d);

    }
    return res;
}

double vector_norm(const std::vector<double> &v1, const std::vector<double>
        &v2)
{
    return sqrt(scalar_product(v1,v2));
}

double predict(const std::vector<double> &v1, const std::vector<double> &v2)
{
    auto norm1 = vector_norm(v1, v1);
    auto norm2 = vector_norm(v2, v2);
    return scalar_product(v1,v2) / (norm1*norm2);
}

double average_func(const RSUser &user)
{
    double sum = 0;
    int ranked = 0;
    for (auto &x: user.get_ranks())
    {
        if(x.second != 0)
        {
            sum = sum + x.second;
            ranked++;
        }
    }

    return  sum / ranked;
}
sp_movie RecommenderSystem::recommend_by_content(const RSUser &user)
{

    double average = average_func(user);
    rank_map new_map  (user.get_ranks().size(), sp_movie_hash,
                       sp_movie_equal);
    for (auto &x: user.get_ranks())
    {
        if(x.second != 0)
        {
            new_map[x.first] = x.second - average;
        }
    }
    std::vector<double> prefer(user.get_ranks().size());
    for (auto &s: new_map)
    {
        if(s.second != 0)
        {
            auto vec = multi(big_system_[s.first], s.second);
            prefer = sum_vec(prefer,vec );
        }
    }
    std::map <sp_movie ,double>rate  ;
    for (auto &m : user.get_ranks())
    {
        if(m.second == 0 )
        {
            auto b = big_system_[m.first];
            rate[m.first] = predict(prefer, big_system_[m.first]);
        }
    }
    return find_max(rate).first;
}
double RecommenderSystem::predict_movie_score(const RSUser &user,
                                              const sp_movie &movie, int k)
{
    std::vector<sp_movie > ranked;
    std::map<sp_movie,double > rate;
    for(auto &m : user.get_ranks())
    {
        if(m.second != 0)
        {
            ranked.push_back(m.first);
        }
    }
    for (auto &s : ranked)
    {
        auto s_feature = big_system_[s];
        auto given_movie = big_system_[movie];
        rate[s] = predict(s_feature,given_movie);
    }
    std::map<sp_movie,double >k_movie;
    int count  = 0;
    while(count != k )
    {
        std::pair<sp_movie, double> max
                = find_max(rate);
        k_movie.insert(max);
        rate.erase(max.first);
        count++ ;
    }
    double sum = 0;
    double sum_2 =0 ;
    for( auto &v : k_movie)
    {
        sum += user.get_ranks()[v.first] * v.second;
        sum_2 += k_movie[v.first];
    }
    return sum / sum_2;
}
sp_movie RecommenderSystem::recommend_by_cf(const RSUser &user, int k)
{
    std::set<sp_movie > ranked;
    std::set<sp_movie > un_ranked;
    for(auto &m : user.get_ranks())
    {
        if(m.second != 0 )
        {
            ranked.insert(m.first);
        }
        else
        {
            un_ranked.insert(m.first);
        }
    }
    std::map<sp_movie ,double> lst_map;
    for(const auto &v : un_ranked)
    {
        double pred_rate = predict_movie_score(user,v,k);
        lst_map[v] = pred_rate;

    }
    return find_max(lst_map).first;


}


sp_movie RecommenderSystem::get_movie(const std::string &name, int year) const
{
    sp_movie new_m = std::make_shared<Movie>(name,year);
    sp_movie it = (big_system_.find(new_m))->first;
    return it;

}

std::ostream &operator<<(std::ostream &out, const RecommenderSystem &system)
{
    for (const auto & it : system.big_system_)
    {
        out << *( it.first);
    }
    return out ;
}


