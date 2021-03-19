#include "book_store.hpp"

#include <algorithm>  // copy
#include <stdexcept>  // invalid_argument

using namespace std;

ResizeStorageStatus resize_storage(Book *&storage, int size, int new_capacity)
{
    if (size >= new_capacity)
    {
        return ResizeStorageStatus::INSUFFICIENT_CAPACITY;
    }
    else if (size < 0)
    {
        return ResizeStorageStatus::NEGATIVE_SIZE;
    }
    else if (storage == nullptr)
    {
        return ResizeStorageStatus::NULL_STORAGE;
    }
    else
    {
        Book *new_storage = new Book[new_capacity];
        copy(storage, storage+size, new_storage);
        delete[] storage;
        storage = new_storage;
        return ResizeStorageStatus::SUCCESS;
    }

}

// 2. реализуйте конструктор ...
BookStore::BookStore(const string &name) : name_{name}
{
  // валидация аргумента
  if (name.empty())
  {
    throw invalid_argument("BookStore::name must not be empty");
  }
    name_ = name;
    storage_size_ = 0;
    storage_capacity_ = kInitStorageCapacity;
    storage_ = new Book[kInitStorageCapacity];

}

// 3. реализуйте деструктор ...
BookStore::~BookStore()
{
    delete[] storage_;
    storage_ = nullptr;
    storage_size_ = 0;
    storage_capacity_ = 0;
}

// 4. реализуйте метод ...
void BookStore::AddBook(const Book &book)
{
    if (storage_size_ == storage_capacity_)
    {

        if (resize_storage_internal(storage_capacity_+kCapacityCoefficient) == ResizeStorageStatus::SUCCESS)

        {
            storage_[storage_size_] = book;
            storage_size_++;
        }
    }
    else
    {
        storage_[storage_size_] = book;
        storage_size_++;
    }
}

// РЕАЛИЗОВАНО

const string &BookStore::GetName() const
{
  return name_;
}

int BookStore::GetSize() const
{
  return storage_size_;
}

int BookStore::GetCapacity() const
{
  return storage_capacity_;
}

const Book *BookStore::GetBooks() const
{
  return storage_;
}

ResizeStorageStatus BookStore::resize_storage_internal(int new_capacity)
{
  // изменяем размеры хранилища с копированием старых данных в хранилище нового объема
  const ResizeStorageStatus status = resize_storage(storage_, storage_size_, new_capacity);

  // если все прошло ОК, то сохраняем новый объем хранилища в объекте
  if (status == ResizeStorageStatus::SUCCESS)
  {
    storage_capacity_ = new_capacity;
  }

  return status;
}