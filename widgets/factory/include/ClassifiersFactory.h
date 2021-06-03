//
// Created by mateus on 31/05/2021.
//

#ifndef UFJFMLTK_CLI_CLASSIFIERSFACTORY_H
#define UFJFMLTK_CLI_CLASSIFIERSFACTORY_H

#include "cppcli/CLWidget.h"
#include "ufjfmltk/Core.hpp"
#include "ufjfmltk/Classifier.hpp"
#include "ufjfmltk/Visualize.hpp"

#include <memory>
#include <map>

namespace factory {
    enum ClassifierPrimal {PHEAD=-1, PERCEPTRON, FMPP, IMAP, KNN, PTAIL};
    enum ClassifierDual {DHEAD=-1, PERCEPTROND, FMPD, IMADUAL, SMO, DTAIL};

    class Classifier;

    extern std::map<ClassifierPrimal, Classifier*> allocated_primal_classifiers;
    extern std::map<ClassifierDual, Classifier*> allocated_dual_classifiers;

    using ClassifierPointer = std::shared_ptr<mltk::classifier::Classifier<double>>;

    class Classifier: public cppcli::CLWidget {
    public:
        explicit Classifier(cppcli::CLWidget *parent = nullptr);
        Classifier(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);

        static Classifier* make_primal_classifier(ClassifierPrimal classifier, const mltk::Data<>& samples,
                                                 const mltk::Data<>& train,
                                                 const mltk::Data<>& test,
                                                 cppcli::CLWidget *parent = nullptr);

        static Classifier* make_dual_classifier(ClassifierDual classifier, const mltk::Data<>& samples,
                                                        const mltk::Data<>& train,
                                                        const mltk::Data<>& test,
                                                        cppcli::CLWidget *parent = nullptr);

        static std::vector<Classifier*> get_primal_classifiers(const mltk::Data<>& data, const mltk::Data<>& train,
                                                                     const mltk::Data<>& test,
                                                                     cppcli::CLWidget *parent = nullptr);

        static std::vector<Classifier*> get_dual_classifiers(const mltk::Data<>& data, const mltk::Data<>& train,
                                                                     const mltk::Data<>& test,
                                                                     cppcli::CLWidget *parent = nullptr);

        void train_learner(bool train) { this->m_train_learner = train; }

        virtual bool is_primal() const;

        virtual ClassifierPointer build_learner() = 0;

    protected:
        bool build() override;
        std::string option_selector() override;
        virtual void set_parameters() = 0;

        static mltk::KernelType get_kernel_type(int kernel_type);

    protected:
        mltk::Data<> m_train, m_test;
        bool m_train_learner{true};
        std::shared_ptr<mltk::classifier::Classifier<double>> learner{nullptr};
    };

    class Perceptron: public Classifier {
    public:
        explicit Perceptron(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
        bool operator()() override;

        void set_parameters() override;
        ClassifierPointer build_learner() override;
    private:
        double rate{0.5};
        int q{2};
    };

    class KNNClassifier: public Classifier {
    public:
        explicit KNNClassifier(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
        bool operator()() override;
        void set_parameters() override;
        ClassifierPointer build_learner() override;
    private:
        size_t k{3};
    };

    class FMP: public Classifier {
    public:
        explicit FMP(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
        bool operator()() override;
        void set_parameters() override;
        ClassifierPointer build_learner() override;

    private:
        int q{2};
        double gamma{0}, rate{0.5};
    };

    class FMPDual: public Classifier {
    public:
        explicit FMPDual(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
        bool operator()() override;
        void set_parameters() override;
        ClassifierPointer build_learner() override;

    private:
        double gamma{0.0}, rate{0.5}, kernel_param{0.0};
        mltk::KernelType type{mltk::KernelType::INNER_PRODUCT};
    };

    class PerceptronDual: public Classifier {
    public:
        explicit PerceptronDual(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
        bool operator()() override;
        void set_parameters() override;
        ClassifierPointer build_learner() override;

    private:
        double rate{0.5}, kernel_param = 0.0;
        mltk::KernelType type{mltk::KernelType::INNER_PRODUCT};
    };

    class IMAp: public Classifier {
    public:
        explicit IMAp(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
        bool operator()() override;
        void set_parameters() override;
        ClassifierPointer build_learner() override;

    private:
        int p{2}, q{2}, flex{0};
        double alpha_aprox{0};
    };

    class IMADual: public Classifier {
    public:
        explicit IMADual(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
        bool operator()() override;
        void set_parameters() override;
        ClassifierPointer build_learner() override;

    private:
        double rate{0.5}, kernel_param{0.0};
        mltk::KernelType type{mltk::KernelType::INNER_PRODUCT};
    };

    class SMOClassifier: public Classifier {
    public:
        explicit SMOClassifier(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
        bool operator()() override;
        void set_parameters() override;
        ClassifierPointer build_learner() override;

    private:
        double rate{0.5}, kernel_param{0.0};
        mltk::KernelType type{mltk::KernelType::INNER_PRODUCT};
    };
}

#endif //UFJFMLTK_CLI_CLASSIFIERSFACTORY_H
