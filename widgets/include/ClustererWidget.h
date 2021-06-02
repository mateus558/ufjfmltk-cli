//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_CLUSTERERWIDGET_H
#define CPPCLI_UFJFMLTK_CLUSTERERWIDGET_H

#include "cppcli/CLWidget.h"
#include "settings.h"

class ClustererWidget: public cppcli::CLWidget {
public:
    explicit ClustererWidget(cppcli::CLWidget *parent = nullptr);

    virtual ~ClustererWidget();

private:
    bool build() override;
};


#endif //CPPCLI_UFJFMLTK_CLUSTERERWIDGET_H
