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

    add_exit_group();
    return true;
}