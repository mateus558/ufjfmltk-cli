//
// Created by mateus on 29/05/2021.
//

#include "VisualizationWidget.h"

VisualizationWidget::VisualizationWidget(cppcli::CLWidget *parent): cppcli::CLWidget(parent,
                                                                                     "Visualization widget") {
    m_plot = std::make_unique<mltk::visualize::Visualization<double>>(false);
};

bool VisualizationWidget::build() {
    use_parent_header();
    set_cmd("visual");

    register_group("main", "Select an option:\n", cppcli::GroupType::ACTION);

    register_action("main", "Plot features in 2D", "1", plot_2d());
    register_action("main", "Plot features in 3D", "2", plot_3d());

    add_exit_group();
    return true;
}

cppcli::Action::Type VisualizationWidget::plot_2d() {
    auto vis = [this](){
        if(!settings::data.isEmpty()) {
            int x, y;
            std::cout << "Enter the feature to plot in the x-axis: ";
            std::cin >> x;
            std::cout << "Enter the feature to plot in the y-axis: ";
            std::cin >> y;
            m_plot->setSample(settings::data);
            m_plot->plot2D(x, y);
            wait_action();
            push_message("Plot open with x=" + std::to_string(x) + " and y=" + std::to_string(y));
        }else push_message("Load a dataset first...", cppcli::LogType::LOG);
        clear();
        return true;
    };
    return vis;
}

cppcli::Action::Type VisualizationWidget::plot_3d() {
    auto vis = [this](){
        if(!settings::data.isEmpty()) {
            int x, y, z;
            std::cout << "Enter the feature to plot in the x-axis: ";
            std::cin >> x;
            std::cout << "Enter the feature to plot in the y-axis: ";
            std::cin >> y;
            std::cout << "Enter the feature to plot in the z-axis: ";
            std::cin >> z;
            m_plot->setSample(settings::data);
            m_plot->plot3D(x, y, z);
            wait_action();
            push_message("Plot open with x=" + std::to_string(x) + ", y=" + std::to_string(y) + " and z=" +
            std::to_string(z));
        }else push_message("Load a dataset first...", cppcli::LogType::LOG);
        clear();
        return true;
    };
    return vis;
}
