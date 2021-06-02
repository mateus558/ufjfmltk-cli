//
// Created by mateus on 01/06/2021.
//

#ifndef UFJFMLTK_CLI_CLUSTERERSFACTORY_H
#define UFJFMLTK_CLI_CLUSTERERSFACTORY_H

#include "cppcli/CLWidget.h"
#include "ufjfmltk/Core.hpp"
#include "ufjfmltk/Clusterer.hpp"

namespace factory {
    enum Clusterers {CHEAD=-1, KMEANS, CTAIL};

    class Clusterer;

    extern std::map<Clusterers, Clusterer*> allocated_clusterers;

    class Clusterer: public cppcli::CLWidget {
    public:
        explicit Clusterer(cppcli::CLWidget* parent = nullptr);
        explicit Clusterer(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool build() override;

        static Clusterer* make_clusterer(Clusterers clusterer, const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        static std::vector<Clusterer *> get_clusterers(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

    protected:
        std::string option_selector() override;
    protected:
        mltk::Data<> m_samples;
        std::string initialization{"random"};
        size_t clusters{3};
    };

    class KMeans: public Clusterer {
    public:
        explicit KMeans(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool operator()() override;
    };
}

#endif //UFJFMLTK_CLI_CLUSTERERSFACTORY_H
