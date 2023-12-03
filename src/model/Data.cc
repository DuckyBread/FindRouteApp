#include "Data.h"

namespace frp {
    void Data::set_cols(int cols) {
        if (cols < 1 || cols > 50) {
            throw std::logic_error("Incorrect amount of cols\n");
        }
        cols_ = cols;
    }

    void Data::set_rows(int rows) {
        if (rows < 1 || rows > 50) {
            throw std::logic_error("Incorrect amount of rows\n");
        }
        rows_ = rows;
    }

    void Data::set_vertical_matrix(std::vector<bool> vertical) {
        vertical_matrix_ = std::move(vertical);
    }

    void Data::set_horizontal_matrix(std::vector<bool> horizontal) {
        horizontal_matrix_ = std::move(horizontal);
    }

    int Data::get_cols() const { return cols_; }

    int Data::get_rows() const { return rows_; }

    std::pair<bool, bool> Data::IsWall(std::pair<int, int> &cell) {
        return std::pair < bool, bool > {
                vertical_matrix_[cols_ * cell.first + cell.second],
                horizontal_matrix_[cols_ * cell.first + cell.second]};
    }

    std::pair<std::vector < bool> &, std::vector<bool> &>

    Data::get_maze() {
        return std::pair < std::vector < bool > &, std::vector < bool > & > {
                vertical_matrix_, horizontal_matrix_};
    }

    std::vector<bool> Data::get_vertical_matrix() { return vertical_matrix_; };

    std::vector<bool> Data::get_horizontal_matrix() { return horizontal_matrix_; };
}