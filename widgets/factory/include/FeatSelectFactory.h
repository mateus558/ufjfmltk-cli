//
// Created by mateus on 01/06/2021.
//

#ifndef UFJFMLTK_CLI_FEATSELECTFACTORY_H
#define UFJFMLTK_CLI_FEATSELECTFACTORY_H

#include "cppcli/CLWidget.h"
#include "ufjfmltk/Core.hpp"
#include "ufjfmltk/FeatureSelection.hpp"

namespace factory{
    enum FeatSelects {FHEAD=-1, GOLUB, FISHER, RFE, AOS, FTAIL};

    class FeatSelect;

    extern std::map<FeatSelects, FeatSelect*> allocated_featselects;

    class FeatSelect : public cppcli::CLWidget {
    public:
        explicit FeatSelect(cppcli::CLWidget* parent = nullptr);
        explicit FeatSelect(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool build() override;

        static FeatSelect* make_featselect(FeatSelects featselect, const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        static std::vector<FeatSelect *> get_featselect(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);
    protected:
        std::string option_selector() override;
    protected:
        mltk::Data<> m_samples;
    };

    class Golub: public FeatSelect {
    public:
        explicit Golub(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool operator()() override;
    };

    class Fisher: public FeatSelect {
    public:
        explicit Fisher(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool operator()() override;
    };

    class RFEAlg: public FeatSelect {
    public:
        explicit RFEAlg(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool operator()() override;
    };

    class AOSAlg: public FeatSelect {
    public:
        explicit AOSAlg(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool operator()() override;
    };

}

#endif //UFJFMLTK_CLI_FEATSELECTFACTORY_H
