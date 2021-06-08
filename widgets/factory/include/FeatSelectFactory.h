//
// Created by mateus on 01/06/2021.
//

#ifndef UFJFMLTK_CLI_FEATSELECTFACTORY_H
#define UFJFMLTK_CLI_FEATSELECTFACTORY_H

#include "AlgorithmFactory.h"
#include "ufjfmltk/Core.hpp"
#include "ufjfmltk/FeatureSelection.hpp"
#include "ClassifiersFactory.h"

namespace factory{
    enum FeatSelects {FHEAD=-1, GOLUB, FISHER, RFE, AOS, FTAIL};

    class FeatSelect;

    extern std::map<FeatSelects, FeatSelect*> allocated_featselects;

    using FeatSelectPointer = std::shared_ptr<mltk::featselect::FeatureSelection<double>>;

    class FeatSelect : public AlgorithmFactory {
    public:
        explicit FeatSelect(cppcli::CLWidget* parent = nullptr);
        FeatSelect(mltk::Data<>& data, const std::string& title, cppcli::CLWidget* parent = nullptr);

        bool build() override;

        static FeatSelect* make_featselect(FeatSelects featselect, mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        static std::vector<FeatSelect *> get_featselect(mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        virtual FeatSelectPointer build_learner() = 0;

        void set_samples(mltk::Data<>& samples){ this->m_samples = &samples; }

    protected:
        virtual void set_parameters() = 0;

    protected:
        mltk::Data<> *m_samples{nullptr};
        std::shared_ptr<mltk::Data<>> m_last_result;
    public:
        const std::shared_ptr<mltk::Data<>> &getLastResult() const;

    protected:
        size_t final_dim{0};
        FeatSelectPointer learner;
        ClassifierPointer classifier;
    public:
        void set_classifier(const ClassifierPointer &m_classifier);
    };

    class Golub: public FeatSelect {
    public:
        explicit Golub(mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        void set_parameters() override;

        FeatSelectPointer build_learner() override;
    };

    class Fisher: public FeatSelect {
    public:
        explicit Fisher(mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        void set_parameters() override;

        FeatSelectPointer build_learner() override;
    };

    class RFEAlg: public FeatSelect {
    public:
        explicit RFEAlg(mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        void set_parameters() override;

        FeatSelectPointer build_learner() override;
    private:
        int jump{1};
    };

    class AOSAlg: public FeatSelect {
    public:
        explicit AOSAlg(mltk::Data<>& data, cppcli::CLWidget* parent = nullptr);

        void set_parameters() override;

        FeatSelectPointer build_learner() override;
    private:
        int branching{2}, branch_form{1}, choice_form{1}, prof_look_ahead{0}, cut{0};
    };

}

#endif //UFJFMLTK_CLI_FEATSELECTFACTORY_H
