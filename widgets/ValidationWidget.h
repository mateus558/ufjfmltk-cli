//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_VALIDATIONWIDGET_H
#define CPPCLI_UFJFMLTK_VALIDATIONWIDGET_H

#include "cppcli/CLWidget.h"

class ValidationWidget: public cppcli::CLWidget {
public:
    explicit ValidationWidget(cppcli::CLWidget *parent = nullptr);

private:
    bool build() override;
};


#endif //CPPCLI_UFJFMLTK_VALIDATIONWIDGET_H
