//
// Created by elif on 12/10/24.
//

#ifndef LIBRARY_DTO_ASSEMBLER_HPP
#define LIBRARY_DTO_ASSEMBLER_HPP
#include "response/get-all-books-response.hpp"
#include "../domain/book.hpp"

class LibraryDtoAssembler {
public:
    static GetAllBooksResponse toGetAllBooksResponse(const std::vector<Book> &books) {
        std::vector<GetAllBooksResponse::Book> result;
        result.reserve(books.size());
        for (const auto &book: books) {
            result.emplace_back(GetAllBooksResponse::Book{
                book.title,
                book.author
            });
        }
        return GetAllBooksResponse(result);
    }

};



#endif //LIBRARY_DTO_ASSEMBLER_HPP
