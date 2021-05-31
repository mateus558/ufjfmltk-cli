//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_MLTKAPP_H
#define CPPCLI_UFJFMLTK_MLTKAPP_H

#include "cppcli/CLWidget.h"
#include "DatasetWidget.h"
#include "DataWidget.h"
#include "VisualizationWidget.h"
#include "ClassifiersWidget.h"
#include "FeatSelectWidget.h"
#include "RegressorWidget.h"
#include "ClustererWidget.h"
#include "ValidationWidget.h"

class MLTKApp: public cppcli::CLWidget {
public:
    explicit MLTKApp(cppcli::CLWidget* parent = nullptr);

    ~MLTKApp() override;

private:
    bool build() override;

    void build_configs();

private:
    DatasetWidget *m_dataset;
    DataWidget *m_data;
    VisualizationWidget *m_visual;
    ClassifiersWidget *m_classifiers;
    FeatSelectWidget *m_featselect;
    RegressorWidget *m_regressor;
    ClustererWidget *m_clusterer;
    ValidationWidget *m_validation;
};

#endif //CPPCLI_UFJFMLTK_MLTKAPP_H