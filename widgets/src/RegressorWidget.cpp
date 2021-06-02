//
// Created by mateus on 29/05/2021.
//

#include "RegressorWidget.h"

RegressorWidget::RegressorWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Regressor widget") {

}

bool RegressorWidget::build() {
    use_parent_header();
    set_cmd("regressor");

    register_group("regressor", "Select an option:\n");

    add_exit_group();
    return true;
}