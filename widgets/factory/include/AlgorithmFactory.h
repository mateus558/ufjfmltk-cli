//
// Created by mateus on 08/06/2021.
//

#ifndef UFJFMLTK_CLI_ALGORITHMFACTORY_H
#define UFJFMLTK_CLI_ALGORITHMFACTORY_H
#include "cppcli/CLWidget.h"
#include "ufjfmltk/Core.hpp"

namespace factory{
    class AlgorithmFactory: public cppcli::CLWidget {
    public:
        explicit AlgorithmFactory(cppcli::CLWidget *parent = nullptr): cppcli::CLWidget(parent) {}
        explicit AlgorithmFactory(cppcli::CLWidget *parent, const std::string& title):
        cppcli::CLWidget(parent, title) {}

        void set_seed(size_t mSeed) {
            m_seed = mSeed;
        }

        void set_maxtime(size_t mMaxtime) {
            m_maxtime = mMaxtime;
        }

        void set_verbose(size_t verbose){
            m_verbose = verbose;
        }

    protected:
        size_t m_seed{0};
        size_t m_maxtime{100};
        size_t m_verbose{0};
    };
}

#endif //UFJFMLTK_CLI_ALGORITHMFACTORY_H
