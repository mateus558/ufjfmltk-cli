//
// Created by mateus on 01/06/2021.
//

#ifndef UFJFMLTK_CLI_ARTIFICIALDATAWIDGET_H
#define UFJFMLTK_CLI_ARTIFICIALDATAWIDGET_H

#include "cppcli/CLWidget.h"

class ArtificialDataWidget : public cppcli::CLWidget {
public:
    explicit ArtificialDataWidget(cppcli::CLWidget *parent = nullptr);

private:
    bool build() override;

    cppcli::Action::Type make_spirals();

    cppcli::Action::Type make_blobs();

    cppcli::Action::Type make_regresion();
};


#endif //UFJFMLTK_CLI_ARTIFICIALDATAWIDGET_H
