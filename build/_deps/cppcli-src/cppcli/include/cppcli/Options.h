//
// Created by mateus on 29/05/2021.
//

#ifndef CPPCLI_UFJFMLTK_OPTIONS_H
#define CPPCLI_UFJFMLTK_OPTIONS_H

#include <map>
#include <utility>
#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
#include <type_traits>

namespace cppcli {
    struct Action
    {
        typedef std::function<bool()> Type ;
    };

    template< class Callable >
    class Option{
    public:
        explicit Option(std::string  text, std::string  opt, Callable& option, bool hidden=false):
        m_hidden(hidden),
        m_text(std::move(text)),
        m_opt(std::move(opt))
        {
            if constexpr (std::is_same<Callable, Action::Type>::value){
                m_action = option;
            }else{
                m_option = &option;
            }
        }

        bool operator()(){
            if(m_update) m_update();
            if constexpr (std::is_same<Callable, Action::Type>::value){
                return (m_action) && m_action();
            }
            return (m_option) && (*m_option)();
        }

        [[nodiscard]] bool isHidden() const {
            return m_hidden;
        }

        [[nodiscard]] const std::string &getText() const {
            return m_text;
        }

        inline const std::string& getOptionCode() { return this->m_opt; }

        void setUpdate(const Action::Type &mUpdate) {
            m_update = mUpdate;
        }

    private:
        std::string m_opt{};
        std::string m_text{};
        bool m_hidden{false};
        Callable* m_option{nullptr};
        Action::Type m_action;
        Action::Type m_update{nullptr};
    };

    template< class Callable >
    class OptionGroup{
    public:
        OptionGroup() = default;
        explicit OptionGroup(std::string& name, std::string header = "", bool hidden=false): m_name(name),
        m_header(std::move(header)),
        m_hidden(hidden) {};

        bool register_option(const std::string& text, const std::string& opt, Callable& option,
                             Action::Type update_func = nullptr, bool hidden=false){
            if(exist_option(opt)) return false;
            m_options[opt] = std::make_unique<Option<Callable>>(text, opt, option, hidden);
            m_options[opt]->setUpdate(update_func);
            return true;
        }

        bool run(const std::string& opt){
            if(!exist_option(opt)) return false;
            return (*m_options[opt])();
        }

        [[nodiscard]] bool empty() const { return m_options.empty(); }

        void show(bool show_header=true) const {
            if(m_options.empty() || m_hidden) return;
            if(!m_header.empty() && show_header) std::cout << m_header << std::endl;
            for(const auto& [key, value]: m_options){
                if(!value->isHidden()) std::cout << value->getOptionCode() << " - " << value->getText() << std::endl;
            }
        }

        void help(bool show_header=true) const {
            if(m_options.empty()) return;
            if(!m_name.empty() && show_header) std::cout << m_name << std::endl;
            for(const auto& [key, value]: m_options){
                std::cout << value->getOptionCode() << " - " << value->getText() << std::endl;
            }
        }

        [[nodiscard]] inline std::string getName() const { return this->getName(); }

        inline std::string& name() { return this->getName(); }

        inline std::string header() { return this->header(); }

        bool exist_option(const std::string& opt){
            if(m_options.find(opt) == m_options.end()) return false;
            return true;
        }

        bool operator()(const std::string& opt) {
            return this->run(opt);
        }

    private:
        static bool is_number(const std::string& s){
            return !s.empty() && std::find_if(s.begin(),
                                              s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
        }

    private:
        struct option_comp {
            bool operator()(const std::string& opt1, const std::string& opt2) const {
                bool number1 = is_number(opt1), number2 = is_number(opt2);
                if(number1 && number2){
                    return std::stoi(opt1) < std::stoi(opt2);
                }else if(!number1 && !number2){
                    return opt1 < opt2;
                }else if(!number1){
                    return true;
                }
                return false;
            }
        };

        using OptionPointer = std::unique_ptr<Option<Callable>>;

        bool m_hidden{false};
        std::string m_name, m_header;
        std::map<std::string, OptionPointer, option_comp> m_options;
    };

};

#endif //CPPCLI_UFJFMLTK_OPTIONS_H
