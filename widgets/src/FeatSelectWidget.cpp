//
// Created by mateus on 29/05/2021.
//

#include "FeatSelectWidget.h"


FeatSelectWidget::FeatSelectWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Feature selection widget") {

}

bool FeatSelectWidget::build() {
    use_parent_header();
    set_cmd("featselect");

    register_group("featselect", "Select an option:\n");


    add_exit_group();
    return true;
}
