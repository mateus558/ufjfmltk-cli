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

    extern std::map<ClassifierPrimal, cppcli::CLWidget*> allocated_primal_classifiers;
    extern std::map<ClassifierDual, cppcli::CLWidget*> allocated_dual_classifiers;

    class Classifier: public cppcli::CLWidget {
    public:
        explicit Classifier(cppcli::CLWidget *parent = nullptr);
        Classifier(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);

        static cppcli::CLWidget* make_primal_classifier(ClassifierPrimal classifier, const mltk::Data<>& samples,
                                                 const mltk::Data<>& train,
                                                 const mltk::Data<>& test,
                                                 cppcli::CLWidget *parent = nullptr);

        static cppcli::CLWidget* make_dual_classifier(ClassifierDual classifier, const mltk::Data<>& samples,
                                                        const mltk::Data<>& train,
                                                        const mltk::Data<>& test,
                                                        cppcli::CLWidget *parent = nullptr);

        static std::vector<cppcli::CLWidget*> get_primal_classifiers(const mltk::Data<>& data, const mltk::Data<>& train,
                                                                     const mltk::Data<>& test,
                                                                     cppcli::CLWidget *parent = nullptr);

        static std::vector<cppcli::CLWidget*> get_dual_classifiers(const mltk::Data<>& data, const mltk::Data<>& train,
                                                                     const mltk::Data<>& test,
                                                                     cppcli::CLWidget *parent = nullptr);


        virtual bool is_primal() const;
    protected:
        std::string option_selector() override;
        static mltk::KernelType get_kernel_type(int kernel_type);

    protected:
        mltk::Data<> m_train, m_test;
        std::unique_ptr<mltk::Learner<double>> learner;
    };

    class Perceptron: public Classifier {
    public:
        explicit Perceptron(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
    private:
        bool build() override;
        bool operator()() override;
    };

    class KNNClassifier: public Classifier {
    public:
        explicit KNNClassifier(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
    private:
        bool build() override;
        bool operator()() override;
    };

    class FMP: public Classifier {
    public:
        explicit FMP(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
    private:
        bool build() override;
        bool operator()() override;
    };

    class FMPDual: public Classifier {
    public:
        explicit FMPDual(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
    private:
        bool build() override;
        bool operator()() override;
    };

    class PerceptronDual: public Classifier {
    public:
        explicit PerceptronDual(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
    private:
        bool build() override;
        bool operator()() override;
    };

    class IMAp: public Classifier {
    public:
        explicit IMAp(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);
    private:
        bool build() override;
        bool operator()() override;
    };

    class IMADual: public Classifier {
    public:
        explicit IMADual(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);

    private:
        bool build() override;
        bool operator()() override;
    };

    class SMOClassifier: public Classifier {
    public:
        explicit SMOClassifier(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent = nullptr);

    private:
        bool build() override;
        bool operator()() override;
    };
}

#endif //UFJFMLTK_CLI_CLASSIFIERSFACTORY_H
