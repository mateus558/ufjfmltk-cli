//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_FEATSELECTWIDGET_H
#define CPPCLI_UFJFMLTK_FEATSELECTWIDGET_H

#include "cppcli/CLWidget.h"

class FeatSelectWidget: public cppcli::CLWidget {
public:
    explicit FeatSelectWidget(cppcli::CLWidget *parent = nullptr);

    virtual ~FeatSelectWidget();

private:
    bool build() override;
};


#endif //CPPCLI_UFJFMLTK_FEATSELECTWIDGET_H
