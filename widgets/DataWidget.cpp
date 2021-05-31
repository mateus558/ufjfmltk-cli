//
// Created by mateus on 29/05/2021.
//

#include "DataWidget.h"

DataWidget::DataWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Data widget") {

}

bool DataWidget::build() {
    set_header(this->m_parent->get_header());
    set_cmd("data");

    register_group("main", "Select an option:\n", cppcli::GroupType::ACTION);

    register_action("main", "Insert features", "1", insert_features());
    register_action("main", "Remove features", "2", remove_features());
    register_action("main", "Remove point", "3", remove_point());
    register_action("main", "Data variance", "4", data_variance());
    register_action("main", "Data radius", "5", data_radius());
    register_action("main", "Distance from the center of the classes", "6", centers_distance());
    register_action("main", "Normalize dataset", "7", normalize_dataset());
    register_action("main", "Print dataset", "8", print_dataset());

    add_exit_group();
    return false;
}

cppcli::Action::Type DataWidget::print_dataset() {
    cppcli::Action::Type print = [this](){
        if(!settings::data.isEmpty()){
            std::cout << settings::data << std::endl;
            wait_action();
        }else push_message("Load a dataset first...");
        clear();
        return true;
    };
    return print;
}

cppcli::Action::Type DataWidget::normalize_dataset() {
    cppcli::Action::Type normalize = [this](){
        if(!settings::data.isEmpty()){

            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return normalize;
}

cppcli::Action::Type DataWidget::insert_features() {
    cppcli::Action::Type feat_ins = [this](){
        if(!settings::data.isEmpty()){

            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return feat_ins;
}

cppcli::Action::Type DataWidget::remove_point() {
    cppcli::Action::Type point_rem = [this](){
        if(!settings::data.isEmpty()){

            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return point_rem;
}

cppcli::Action::Type DataWidget::remove_features() {
    cppcli::Action::Type feat_rem = [this](){
        if(!settings::data.isEmpty()){

            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return feat_rem;
}

cppcli::Action::Type DataWidget::data_variance() {
    cppcli::Action::Type var = [this](){
        if(!settings::data.isEmpty()){

            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return var;
}

cppcli::Action::Type DataWidget::data_radius() {
    cppcli::Action::Type radius = [this](){
        if(!settings::data.isEmpty()){

            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return radius;
}

cppcli::Action::Type DataWidget::centers_distance() {
    cppcli::Action::Type centers_dist = [this](){
        if(!settings::data.isEmpty()){

            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return centers_dist;
}
