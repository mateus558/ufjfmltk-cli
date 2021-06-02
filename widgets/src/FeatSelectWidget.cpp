//
// Created by mateus on 29/05/2021.
//

#include <settings.h>
#include "FeatSelectWidget.h"
#include "FeatSelectFactory.h"


FeatSelectWidget::FeatSelectWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Feature selection") {

}

bool FeatSelectWidget::build() {
    use_parent_header();
    set_cmd("featselect");

    register_group("featselect", "Select an option:\n");
    auto algorithms = factory::FeatSelect::get_featselect(settings::data, this);
    int opts = 1;
    for(const auto& fs : algorithms){
        register_widget("featselect", fs->get_text(), std::to_string(opts++), fs);
    }
    add_exit_group();
    return true;
}
