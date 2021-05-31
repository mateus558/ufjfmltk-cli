//
// Created by mateus on 29/05/2021.
//

#include "ClassifiersWidget.h"
#include "factory/ClassifiersFactory.h"

ClassifiersWidget::ClassifiersWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Classifier widget") {

}

bool ClassifiersWidget::build() {
    use_parent_header();
    set_cmd("classifier");

    register_group("primal_classifiers", "Primal classifiers:\n");

    register_widget("primal_classifiers", "Perceptron", "1",
                    factory::Classifier::make_classifier(factory::ClassifierChoice::IMAP, this));
    register_widget("primal_classifiers", "Fixed Margin Perceptron (FMP)", "2",
                    factory::Classifier::make_classifier(factory::ClassifierChoice::IMAP, this));
    register_widget("primal_classifiers", "Incremental Margin Algorithm (IMAp)", "3",
                    factory::Classifier::make_classifier(factory::ClassifierChoice::IMAP, this));
    register_widget("primal_classifiers", "K-Nearest Neighbors (KNN)", "4",
                    factory::Classifier::make_classifier(factory::ClassifierChoice::IMAP, this));

    register_group("dual_classifiers", "\nDual classifiers:\n");

    register_widget("dual_classifiers", "Perceptron", "5",
                    factory::Classifier::make_classifier(factory::ClassifierChoice::IMAP, this));
    register_widget("dual_classifiers", "Fixed Margin Perceptron (FMP Dual)", "6",
                    factory::Classifier::make_classifier(factory::ClassifierChoice::IMAP, this));
    register_widget("dual_classifiers", "Incremental Margin Algorithm (IMA Dual)", "7",
                    factory::Classifier::make_classifier(factory::ClassifierChoice::IMADUAL, this));
    register_widget("dual_classifiers", "Sequential Minimal Optimization (SMO)", "8",
                    factory::Classifier::make_classifier(factory::ClassifierChoice::IMADUAL, this));

    add_exit_group();
    return false;
}
