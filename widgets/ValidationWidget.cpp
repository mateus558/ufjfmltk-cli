//
// Created by mateus on 29/05/2021.
//

#include "ValidationWidget.h"
#include "settings.h"

ValidationWidget::ValidationWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Validation widget") {

}

bool ValidationWidget::build() {
    use_parent_header();
    set_cmd("valid");

    register_group("valid", "Select an option:\n");

    add_exit_group();
    return true;
}