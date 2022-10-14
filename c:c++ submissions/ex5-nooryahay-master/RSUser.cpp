
// don't change those includes
#include "RSUser.h"
#include "RecommenderSystem.h"
#include <utility>
#define TEN 10
#define ONE 1

RSUser::RSUser(std::string &user_name, rank_map &user_rank_map,
               sp_system &system)
{
    user_name_ = user_name;
    user_rank_map_ = user_rank_map;
    system_ = system;
}

std::string RSUser::get_name() const
{
    return user_name_;
}

void RSUser::add_movie_to_rs(const std::string &name, int year,
                             const std::vector<double> &features,
                             double rate)
{
    if (rate < ONE || rate > TEN)
    {
        throw std::out_of_range("rate value is not valid ");
    }
    sp_movie movie = system_->add_movie(name, year, features);
    user_rank_map_[movie] = rate;
}

rank_map RSUser::get_ranks() const
{
    return user_rank_map_;
}

sp_movie RSUser::get_recommendation_by_content() const
{
    return system_->recommend_by_content(*this);
}

std::ostream &operator<<(std::ostream &out, const RSUser &user)
{
    out << "name: " << user.user_name_ << std::endl;
    out << *user.system_<<std::endl;
    return out;
}




sp_movie RSUser::get_recommendation_by_cf(int k) const
{
    return system_->recommend_by_cf(*this, k);
}

double
RSUser::get_prediction_score_for_movie(const std::string &name, int year,
                                       int k) const
{
    sp_movie new_m = system_->get_movie(name,year);
    return system_->predict_movie_score(*this, new_m, k);
}
