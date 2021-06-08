//
// Created by mateus on 29/05/2021.
//

#include "ClustererWidget.h"

ClustererWidget::ClustererWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Clusterer widget") {

}

bool ClustererWidget::build() {
    use_parent_header();
    set_cmd("clusterer");

    register_group("clusterer", "Select an option:\n");

    clusterers = factory::Clusterer::get_clusterers(settings::data, this);
    int opts = 1;
    for(auto& clusterer: clusterers){
        auto update = [&clusterer](){
            clusterer->set_samples(settings::data);
            clusterer->set_seed(settings::seed);
            clusterer->set_maxtime(settings::max_time);
            clusterer->set_verbose(settings::verbose);
            return true;
        };
        register_widget("clusterer", clusterer->get_text(), std::to_string(opts++), clusterer, update);
    }

    add_exit_group();
    return true;
}

ClustererWidget::~ClustererWidget() {
    for(auto& [key, alg]: factory::allocated_clusterers){
        delete alg;
    }
}
