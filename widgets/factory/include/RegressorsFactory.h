//
// Created by mateus on 01/06/2021.
//

#ifndef UFJFMLTK_CLI_REGRESSORSFACTORY_H
#define UFJFMLTK_CLI_REGRESSORSFACTORY_H

#include "AlgorithmFactory.h"
#include "ufjfmltk/Core.hpp"
#include "ufjfmltk/Regressor.hpp"

namespace factory{
    enum Regressors {RHEAD=-1, LMS, RTAIL};

    class Regressor;

    extern std::map<Regressors, Regressor*> allocated_regressors;

    class Regressor : public AlgorithmFactory {
    public:
        explicit Regressor(cppcli::CLWidget* parent = nullptr);
        explicit Regressor(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool build() override;

        static Regressor* make_regressor(Regressors regressor, const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        static std::vector<Regressor *> get_regressors(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);
        
        void set_samples(const mltk::Data<double>& samples){ this->m_samples = samples; }

    protected:
        std::string option_selector() override;
    protected:
        mltk::Data<> m_samples;
    };

    class LMSRegressor: public Regressor {
    public:
        explicit LMSRegressor(const mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        bool operator()() override;
    };
}

#endif //UFJFMLTK_CLI_REGRESSORSFACTORY_H
