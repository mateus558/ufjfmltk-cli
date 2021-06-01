//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_DATASETWIDGET_H
#define CPPCLI_UFJFMLTK_DATASETWIDGET_H

#include "cppcli/CLWidget.h"
#include "settings.h"
#include "ArtificialDataWidget.h"


class DatasetWidget: public cppcli::CLWidget {
public:
    explicit DatasetWidget(cppcli::CLWidget* parent = nullptr);

    virtual ~DatasetWidget();

private:
    bool build() override;

    static bool valid_file(const std::string& file);

    static std::vector<std::string> list_datasets(bool list);

    cppcli::Action::Type load_dataset();

    cppcli::Action::Type show_info();

    cppcli::Action::Type show_feats();

private:

    cppcli::Action::Type divide_traintest();

    cppcli::Action::Type save_traintest();

private:
    ArtificialDataWidget *m_artificial{nullptr};
};


#endif //CPPCLI_UFJFMLTK_DATASETWIDGET_H
