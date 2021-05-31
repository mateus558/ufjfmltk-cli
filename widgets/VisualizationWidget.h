//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_VISUALIZATIONWIDGET_H
#define CPPCLI_UFJFMLTK_VISUALIZATIONWIDGET_H

#include "cppcli/CLWidget.h"
#include "settings.h"

class VisualizationWidget: public cppcli::CLWidget{
public:
    explicit VisualizationWidget(CLWidget *parent = nullptr);

    bool build() override;

private:
    std::unique_ptr<mltk::visualize::Visualization<double>> m_plot;

    cppcli::Action::Type plot_2d();
    cppcli::Action::Type plot_3d();
};


#endif //CPPCLI_UFJFMLTK_VISUALIZATIONWIDGET_H
