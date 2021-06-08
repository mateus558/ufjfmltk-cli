//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_FEATSELECTWIDGET_H
#define CPPCLI_UFJFMLTK_FEATSELECTWIDGET_H

#include "cppcli/CLWidget.h"
#include "FeatSelectFactory.h"

class FeatSelectWidget: public cppcli::CLWidget {
public:
    explicit FeatSelectWidget(cppcli::CLWidget *parent = nullptr);

    virtual ~FeatSelectWidget();

private:
    bool build() override;

private:
    std::vector<factory::FeatSelect *> algorithms;
};


#endif //CPPCLI_UFJFMLTK_FEATSELECTWIDGET_H
