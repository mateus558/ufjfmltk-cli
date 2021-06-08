//
// Created by mateus on 29/05/2021.
//

#include <settings.h>
#include "FeatSelectWidget.h"


FeatSelectWidget::FeatSelectWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Feature selection") {

}

bool FeatSelectWidget::build() {
    use_parent_header();
    set_cmd("featselect");

    register_group("featselect", "Select an option:\n");
    algorithms = factory::FeatSelect::get_featselect(settings::data, this);
    int opts = 1;
    for(auto& fs : algorithms){
        auto update = [&fs](){
            fs->set_samples(settings::data);
            fs->set_verbose(settings::verbose);
            fs->set_seed(settings::seed);
            fs->set_maxtime(settings::max_time);
            return true;
        };
        register_widget("featselect", fs->get_text(), std::to_string(opts++), fs, update);
    }
    add_exit_group();
    return true;
}

FeatSelectWidget::~FeatSelectWidget() {
    for(auto& [key, alg]: factory::allocated_featselects){
        delete alg;
    }
}
