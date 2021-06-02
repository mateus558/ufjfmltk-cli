//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_DATAWIDGET_H
#define CPPCLI_UFJFMLTK_DATAWIDGET_H

#include "cppcli/CLWidget.h"
#include "settings.h"

class DataWidget: public cppcli::CLWidget{
public:
    explicit DataWidget(cppcli::CLWidget *parent = nullptr);

    bool build() override;
private:
    cppcli::Action::Type print_dataset();

    cppcli::Action::Type normalize_dataset();

    cppcli::Action::Type insert_features();

    cppcli::Action::Type remove_point();

    cppcli::Action::Type remove_features();

    cppcli::Action::Type data_variance();

    cppcli::Action::Type data_radius();

    cppcli::Action::Type centers_distance();
};


#endif //CPPCLI_UFJFMLTK_DATAWIDGET_H
