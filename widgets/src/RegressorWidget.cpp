//
// Created by mateus on 29/05/2021.
//

#include "RegressorWidget.h"
#include "RegressorsFactory.h"
#include "settings.h"

RegressorWidget::RegressorWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Regressors") {

}

bool RegressorWidget::build() {
    use_parent_header();
    set_cmd("regressor");

    register_group("regressor", "Select an option:\n");
    auto algorithms = factory::Regressor::get_regressors(settings::data, this);
    int opts = 1;
    for(const auto& reg : algorithms){
        register_widget("regressor", reg->get_text(), std::to_string(opts++), reg);
    }

    add_exit_group();
    return true;
}

RegressorWidget::~RegressorWidget() {
    for(auto& [key, alg]: factory::allocated_regressors){
        delete alg;
    }
}
