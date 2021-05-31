//
// Created by mateus on 31/05/2021.
//

#include "ClassifiersFactory.h"

namespace factory{

    Classifier::Classifier(cppcli::CLWidget *parent) : cppcli::CLWidget(parent) {

    }

    cppcli::CLWidget * Classifier::make_classifier(ClassifierChoice classifier, cppcli::CLWidget *parent) {
        switch (classifier) {
            case ClassifierChoice::IMAP:
                return new IMAp(parent);
            case ClassifierChoice::IMADUAL:
                return new IMADual(parent);
            default:
                return nullptr;
        }
    }

    std::string Classifier::option_selector() {
        wait_action();
        Classifier::m_local_exit = true;
        return "";
    }

    IMAp::IMAp(cppcli::CLWidget *parent) : Classifier(parent) {

    }

    bool IMAp::build() {
        return false;
    }

    IMADual::IMADual(cppcli::CLWidget *parent) : Classifier(parent) {

    }

    bool IMADual::build() {
        return false;
    }
}