//
// Created by mateus on 29/05/2021.
//

#include "ValidationWidget.h"
#include "factory/ClassifiersFactory.h"
#include "settings.h"

ValidationWidget::ValidationWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Classifiers validation") {

}

bool ValidationWidget::build() {
    use_parent_header();
    set_cmd("valid");

    register_group("valid_primal", "Primal classifiers:\n", cppcli::GroupType::ACTION);
    auto primal_classifiers = factory::Classifier::get_primal_classifiers(settings::data, settings::train,
                                                                          settings::test, this);
    auto dual_classifiers = factory::Classifier::get_dual_classifiers(settings::data, settings::train,
                                                                          settings::test, this);
    int opt = 1;
    for(auto& primal: primal_classifiers){
        auto valid = [this, primal](){
            primal->train_learner(false);
            (*primal)();
            auto learner = primal->get_built_classifier();
            learner->setVerbose(0);
            mltk::validation::ValidationReport report;
            if(qtde > 1) {
                report = mltk::validation::kkfold(settings::data, *learner, qtde, folds, true,
                                                  settings::seed, (int) settings::verbose);
            }else{
                report = mltk::validation::kfold(settings::data, *learner, folds, true,
                                                 settings::seed, (int) settings::verbose);
            }
            primal->train_learner(true);
            push_message("algorithm: " + primal->get_text());
            push_message("accuracy: " + std::to_string(report.accuracy));
            push_message("error: " + std::to_string(report.error));
            wait_action();
            return true;
        };
        register_action("valid_primal", primal->get_text(), std::to_string(opt++), valid);
    }

    register_group("valid_dual", "\nDual classifiers:\n", cppcli::GroupType::ACTION);
    for(auto& dual: dual_classifiers){
        auto valid = [this, dual](){
            dual->train_learner(false);
            (*dual)();
            auto learner = dual->get_built_classifier();
            learner->setVerbose(0);
            mltk::validation::ValidationReport report;
            if(qtde > 1) {
                report = mltk::validation::kkfold(settings::data, *learner, qtde, folds, true,
                                                       settings::seed, (int) settings::verbose);
            }else{
                report = mltk::validation::kfold(settings::data, *learner, folds, true,
                                                  settings::seed, (int) settings::verbose);
            }
            dual->train_learner(true);
            push_message("algorithm: " + dual->get_text());
            push_message("accuracy: " + std::to_string(report.accuracy));
            push_message("error: " + std::to_string(report.error));
            wait_action();
            return true;
        };
        register_action("valid_dual", dual->get_text(), std::to_string(opt++), valid);
    }

    register_group("valid_configs", "\nValidation configs:\n", cppcli::GroupType::ACTION);
    register_action("valid_configs", "Number of executions", "n", [this](){
        std::cout << "Number of executions [current-"<<qtde<<"]: ";
        std::cin >> qtde;
        push_message("number of executions updated to " + std::to_string(qtde));
        return true;
    });
    register_action("valid_configs", "Number of folds", "f", [this](){
        std::cout << "Number of folds [current-"<<folds<<"]: ";
        std::cin >> folds;
        push_message("number of folds updated to " + std::to_string(folds));
        return true;
    });

    add_exit_group();
    return true;
}