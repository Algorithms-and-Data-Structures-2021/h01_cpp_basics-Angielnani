#include "book.hpp"
#include <iostream>
#include <stdexcept>  // invalid_argument

using namespace std;
// 1. реализуйте конструктор ...
Book::Book(const string &title,
           const string &content,
           Genre genre,
           Publisher publisher,
           const vector<Author> &authors)
{

  // валидация аргументов
  if (title.empty())
  {
    throw invalid_argument("Book::title cannot be empty");
  }

  if (content.empty())
  {
    throw invalid_argument("Book::content cannot be empty");
  }

  if (authors.empty())
  {
    throw invalid_argument("Book::authors cannot be empty");
  }

    title_ = title;
    content_ = content;
    authors_ = authors;
    genre_ = genre;
    publisher_ = publisher;
}

// 2. реализуйте метод ...
bool Book::AddAuthor(const Author &author)
{
    for (auto avt: authors_)
    {
        auto first_name = avt.GetFullName();
        auto second_name = author.GetFullName();
        cout << first_name << ' ' << second_name;
        if (first_name == second_name)
            return false;
    }
    authors_.push_back(author);

  return true;
}

// РЕАЛИЗОВАНО

const string &Book::GetTitle() const
{
  return title_;
}

const string &Book::GetContent() const
{
  return content_;
}

Genre Book::GetGenre() const
{
  return genre_;
}

Publisher Book::GetPublisher() const
{
  return publisher_;
}

const vector<Author> &Book::GetAuthors() const
{
  return authors_;
}

void Book::SetTitle(const string &title)
{
  if (title.empty())
  {
    throw invalid_argument("Book::title cannot be empty");
  }
  title_ = title;
}

void Book::SetContent(const string &content)
{
  if (content.empty())
  {
    throw invalid_argument("Book::content cannot be empty");
  }
  content_ = content;
}

void Book::SetGenre(Genre genre)
{
  genre_ = genre;
}

void Book::SetPublisher(Publisher publisher)
{
  publisher_ = publisher;
}