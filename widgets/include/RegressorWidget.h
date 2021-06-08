//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_REGRESSORWIDGET_H
#define CPPCLI_UFJFMLTK_REGRESSORWIDGET_H

#include "cppcli/CLWidget.h"
#include "settings.h"
#include "RegressorsFactory.h"


class RegressorWidget: public cppcli::CLWidget {
public:
    explicit RegressorWidget(cppcli::CLWidget *parent = nullptr);

    virtual ~RegressorWidget();

private:
    bool build() override;

private:
    std::vector<factory::Regressor*> regressors;
};


#endif //CPPCLI_UFJFMLTK_REGRESSORWIDGET_H
