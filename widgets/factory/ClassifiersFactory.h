//
// Created by mateus on 31/05/2021.
//

#ifndef UFJFMLTK_CLI_CLASSIFIERSFACTORY_H
#define UFJFMLTK_CLI_CLASSIFIERSFACTORY_H

#include "cppcli/CLWidget.h"

namespace factory {
    enum ClassifierChoice {IMAP, IMADUAL};

    class Classifier: public cppcli::CLWidget {
    public:
        explicit Classifier(cppcli::CLWidget *parent = nullptr);

        static cppcli::CLWidget* make_classifier(ClassifierChoice classifier, cppcli::CLWidget *parent = nullptr);
    protected:
        std::string option_selector() override;
    };

    class IMAp: public Classifier {
    public:
        explicit IMAp(cppcli::CLWidget *parent = nullptr);

    private:
        bool build() override;
    };

    class IMADual: public Classifier {
    public:
        explicit IMADual(cppcli::CLWidget *parent = nullptr);

    private:
        bool build() override;
    };
}

#endif //UFJFMLTK_CLI_CLASSIFIERSFACTORY_H
