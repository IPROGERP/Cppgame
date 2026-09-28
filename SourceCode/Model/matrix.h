#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <memory.h>
#include <iostream>

/**
 * @brief Matrix class
 * 
 * matrix class that allows to store any type of value and perform standart matrix operations
 *
*/

namespace MyMatrix{

	template <typename T>
	class Matrix{

		private:

			/**
			 * @brief amount of rows in matrix
			 */
			size_t rows{};
			/**
			 * @brief amount of columns in matrix
			 */
			size_t columns{};
			/**
			 * @brief data stored in matrix
			 */
			std::unique_ptr<T[]> data = nullptr;

		public:
			/**
			 * @brief rows getter
			 */
			size_t GetRows(){

				return rows;

			}
			/**
			 * @brief column getter
			 */
			size_t GetColumns(){

				return columns;

			}
			/**
			 * @brief method that return size of matrix aka rows * columns
			 */
			size_t size() const {

				return rows * columns;

			}
			/**
			 * @brief return true or false depending on is matrix empty or not 
			 */
			bool empty(){

				return rows * columns == 0 ? true : false;

			}
			/**
			 * @brief default constructor
			 */
			Matrix() = default;
			/**
			 * @brief constructor with rows and columns size
			 */
			Matrix(size_t irows, size_t icolumns) : rows(irows), columns(icolumns), data(std::make_unique<T[]>(irows * icolumns)){};
			/**
			 * @brief constructor with rows and columns size and filled with value provided
			 */
			Matrix(size_t irows, size_t icolumns, const T &value){

				rows = irows;
				columns = icolumns;
				data = std::make_unique<T[]>(rows * columns);
				this -> Fill(value);

			}
			/**
			 * @brief const accessing element via ()
			 */
			const T &operator()(size_t irow, size_t icolumn) const {

				if (CheckBounds(irow, icolumn)){
	
					return data[irow * columns + icolumn];

				}
				throw std::out_of_range("Index out of range");	

			}
			/**
			 * @brief accessing element via ()
			 */
			T &operator()(size_t irow, size_t icolumn){

				if (CheckBounds(irow, icolumn)){

					return data[irow * columns + icolumn];

				}
				throw std::out_of_range("Index out of range");

			}
			/**
			 * @brief const accessing element via []
			 */
			const T &operator[](size_t index) const {

				return data[index];

			}
			/**
			 * @brief accessing element via []
			 */
			T &operator[](size_t index){

					return data[index];

			}	
			/**
			 * @brief method that fills matrix with value provided
			 */
			void Fill(const T &value){

				for (size_t i = 0; i < this -> size(); i++){

					data[i] = value;

				}

			}
			/**
			 * @brief overload for operator <<
			 */
			friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &other){

				for (size_t i = 1; i < other.size() + 1; i++){

					os << other.data[i - 1];
					if (i % other.columns == 0){

						os << '\n';

					}

				}
		
				return os;

			}
			/**
			 * @brief method that generate data in matrix
			 */
			void GenerateData(){

				for (size_t i = 0; i < this -> size(); i++){

					data[i] = i;

				}

			}
			/**
			 * @brief method that checks bounds of element accesing 
			 */
			bool CheckBounds(size_t irow, size_t icolumn){

				if (irow > rows || icolumn > columns || irow < 0 || icolumn < 0){

					return false;
				
				}
				
				return true;

			}
			/**
			 * @brief method that adds row
			 */
			void AddRow(const std::vector<T>& rowValues, size_t position = std::numeric_limits<size_t>::max()){

					if (rowValues.size() != columns && columns > 0){

						throw std::invalid_argument("Row values size must match matrix columns");

					}
					
					if (position == std::numeric_limits<size_t>::max()){

						position = rows;

					}
					
					if (position > rows){

						throw std::out_of_range("Position exceeds matrix row count");

					}

					auto newData = std::make_unique<T[]>((rows + 1) * columns);
					
					for (size_t i = 0; i < position; i++){

						for (size_t j = 0; j < columns; j++){

							newData[i * columns + j] = data[i * columns + j];

						}

					}
					
					for (size_t j = 0; j < columns; j++){

						newData[position * columns + j] = rowValues[j];
						
					}
					
					for (size_t i = position; i < rows; i++){

						for (size_t j = 0; j < columns; j++){

							newData[(i + 1) * columns + j] = data[i * columns + j];

						}

					}
					
					rows++;
					data = std::move(newData);

			}
			/**
			 * @brief method that adds column
			 */
			void AddColumn(const std::vector<T>& colValues, size_t position = std::numeric_limits<size_t>::max()){

				if (colValues.size() != rows && rows > 0){

					throw std::invalid_argument("Column values size must match matrix rows");

				}
				
				if (position == std::numeric_limits<size_t>::max()){

					position = columns;

				}
				
				if (position > columns){

					throw std::out_of_range("Position exceeds matrix column count");

				}
				
				size_t newColumns = columns + 1;
				auto newData = std::make_unique<T[]>(rows * newColumns);
				
				for (size_t i = 0; i < rows; i++){

					for (size_t j = 0; j < position; j++){

						newData[i * newColumns + j] = data[i * columns + j];

					}
					
					newData[i * newColumns + position] = colValues[i];

					for (size_t j = position; j < columns; j++){

						newData[i * newColumns + j + 1] = data[i * columns + j];

					}

				}
				
				columns = newColumns;
				data = std::move(newData);
					
			}
		class Iterator{

			private:
				T *current;

			public:

				using iterator_category = std::forward_iterator_tag;
				using value_type = T;
				using difference_type = std::ptrdiff_t;
				using pointer = T*;
				using reference = T&;

				explicit Iterator(T *pointer) : current(pointer) {}
				reference operator *() const { return *current; };
				pointer operator  ->() const { return current; };

				Iterator &operator ++(){

					++current;
					return *this;

				}

				Iterator  &operator ++(int){

					current++;
					return *this;

				}

				bool operator ==(const Iterator &other) const { return current == other.current; }
				bool operator !=(const Iterator &other) const { return current != other.current; }

		};
		/**
		 * @brief getter for begin iterator
		*/
		Iterator begin() { return Iterator(data.get()); }
		/**
		 * @brief getter for end iterator
		*/
		Iterator end() { return Iterator(data.get() + rows * columns); }

	};

}

#endif
