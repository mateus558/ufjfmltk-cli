//
// Created by mateus on 01/06/2021.
//

#include "ArtificialDataWidget.h"
#include "settings.h"

ArtificialDataWidget::ArtificialDataWidget(cppcli::CLWidget *parent) :
        cppcli::CLWidget(parent, "Artificial data")
{

}

bool ArtificialDataWidget::build() {
    set_header(this->parent()->get_header());

    register_group("artificial", "Select an option:\n", cppcli::GroupType::ACTION);

    register_action("artificial", "Make 2D spirals", "1", make_spirals());
    register_action("artificial", "Make blobs", "2", make_blobs());
    register_action("artificial", "Make regression", "3", make_regression());

    add_exit_group();
    return true;
}

cppcli::Action::Type ArtificialDataWidget::make_spirals() {
    auto spirals = [this](){
        size_t size, n_classes, n_loops;
        std::cout << "Number of samples: ";
        std::cin >> size;
        std::cout << "Number of classes: ";
        std::cin >> n_classes;
        std::cout << "Number of loops: ";
        std::cin >> n_loops;

        settings::data = mltk::datasets::make_spirals(size, n_classes, true, 1.0, n_loops, 0.5,
                                                      settings::seed);
        push_message("Spirals dataset generated with " + std::to_string(size) + " samples and " +
        std::to_string(n_classes) + " classes.");
        return true;
    };
    return spirals;
}

cppcli::Action::Type ArtificialDataWidget::make_blobs() {
    auto blobs = [this](){
        size_t n_samples, n_classes, n_dims;
        std::cout << "Number of samples: ";
        std::cin >> n_samples;
        std::cout << "Number of classes: ";
        std::cin >> n_classes;
        std::cout << "Number of features: ";
        std::cin >> n_dims;

        settings::data = mltk::datasets::make_blobs(n_samples, n_classes, n_dims, 1.0, -10,
                                                    10, true, true, settings::seed).dataset;
        push_message("Blobs dataset generated with " + std::to_string(n_samples) + " samples, " +
                     std::to_string(n_classes) + " classes and " + std::to_string(n_dims) + " features.");
        return true;
    };
    return blobs;
}

cppcli::Action::Type ArtificialDataWidget::make_regression() {
    auto reg = [this](){
        size_t n_samples, n_dims;
        double noise, bias, stddev;
        std::cout << "Number of samples: ";
        std::cin >> n_samples;
        std::cout << "Number of features: ";
        std::cin >> n_dims;
        std::cout << "Bias: ";
        std::cin >> bias;
        std::cout << "Noise: ";
        std::cin >> noise;
        std::cout << "Standard deviation: ";
        std::cin >> stddev;

        settings::data = mltk::datasets::make_regression(n_samples, n_dims, bias, noise, stddev, n_dims,
                                                         true, settings::seed).dataset;
        push_message("Regression dataset generated with " + std::to_string(n_samples) + " samples and " +
        std::to_string(n_dims) + " features.");
        return true;
    };
    return reg;
}
