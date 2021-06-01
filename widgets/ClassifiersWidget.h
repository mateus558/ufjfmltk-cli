//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_CLASSIFIERSWIDGET_H
#define CPPCLI_UFJFMLTK_CLASSIFIERSWIDGET_H

#include "cppcli/CLWidget.h"
#include "settings.h"

class ClassifiersWidget : public cppcli::CLWidget {
public:
    explicit ClassifiersWidget(cppcli::CLWidget *parent = nullptr);

    ~ClassifiersWidget() override;
private:
    bool build() override;
};


#endif //CPPCLI_UFJFMLTK_CLASSIFIERSWIDGET_H
