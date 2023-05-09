// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include "shape.h"

std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
    shape.print();
    return os;
}

void Shape::drop_anchor(void)
{
    this->is_anchored_ = true;
}

bool Shape::is_anchored(void)
{
    return this->is_anchored_;
}
