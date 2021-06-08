//
// Created by mateus on 29/05/2021.
//

#include "ClassifiersWidget.h"

ClassifiersWidget::ClassifiersWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Classifier") {

}

bool ClassifiersWidget::build() {
    use_parent_header();
    set_cmd("classifier");

    int opt = 1;

    register_group("primal_classifiers", "Primal classifiers:\n");

    pclassifiers = factory::Classifier::get_primal_classifiers(settings::data, settings::train,
                                                                          settings::test, this);
    for(auto& pclassifier: pclassifiers){
        auto update = [&pclassifier](){
            pclassifier->set_train(settings::data);
            pclassifier->set_seed(settings::seed);
            pclassifier->set_maxtime(settings::max_time);
            pclassifier->set_verbose(settings::verbose);
            return true;
        };
        register_widget("primal_classifiers", pclassifier->get_text(), std::to_string(opt++), pclassifier, update);
    }

    register_group("dual_classifiers", "\nDual classifiers:\n");

    dclassifiers = factory::Classifier::get_dual_classifiers(settings::data, settings::train,
                                                                          settings::test, this);
    for(auto& dclassifier: dclassifiers){
        auto update = [&dclassifier](){
            dclassifier->set_train(settings::data);
            dclassifier->set_seed(settings::seed);
            dclassifier->set_maxtime(settings::max_time);
            dclassifier->set_verbose(settings::verbose);
            return true;
        };
        register_widget("dual_classifiers", dclassifier->get_text(), std::to_string(opt++), dclassifier, update);
    }

    add_exit_group();
    return false;
}

ClassifiersWidget::~ClassifiersWidget() {
    for(auto& [key, pclassifier]: factory::allocated_primal_classifiers){
        delete pclassifier;
    }
    for(auto& [key, dclassifier]: factory::allocated_dual_classifiers){
        delete dclassifier;
    }
}
