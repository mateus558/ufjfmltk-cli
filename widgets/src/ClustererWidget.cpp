//
// Created by mateus on 29/05/2021.
//

#include "ClustererWidget.h"
#include "ClusterersFactory.h"

ClustererWidget::ClustererWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Clusterer widget") {

}

bool ClustererWidget::build() {
    use_parent_header();
    set_cmd("clusterer");

    register_group("clusterer", "Select an option:\n");

    auto clusterers = factory::Clusterer::get_clusterers(settings::data, this);
    int opts = 1;
    for(const auto& clusterer: clusterers){
        register_widget("clusterer", clusterer->get_text(), std::to_string(opts++), clusterer);
    }

    add_exit_group();
    return true;
}

ClustererWidget::~ClustererWidget() {
    for(auto& [key, alg]: factory::allocated_clusterers){
        delete alg;
    }
}
