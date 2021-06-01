//
// Created by mateus on 29/05/2021.
//

#include "ClassifiersWidget.h"
#include "factory/ClassifiersFactory.h"

ClassifiersWidget::ClassifiersWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Classifier") {

}

bool ClassifiersWidget::build() {
    use_parent_header();
    set_cmd("classifier");

    int opt = 1;

    register_group("primal_classifiers", "Primal classifiers:\n");

    auto primal_classifiers = factory::Classifier::get_primal_classifiers(settings::data, settings::train,
                                                                          settings::test, this);

    for(const auto& pclassifier: primal_classifiers){
        register_widget("primal_classifiers", pclassifier->get_text(), std::to_string(opt++), pclassifier);
    }

    register_group("dual_classifiers", "\nDual classifiers:\n");

    auto dual_classifiers = factory::Classifier::get_dual_classifiers(settings::data, settings::train,
                                                                          settings::test, this);

    for(const auto& dclassifier: dual_classifiers){
        register_widget("dual_classifiers", dclassifier->get_text(), std::to_string(opt++), dclassifier);
    }

    add_exit_group();
    return false;
}
