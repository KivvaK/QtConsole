// Заголовочный файл библиотеки работы со списком

#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iostream>

namespace ListLib {
    // Реализацию шаблонных функций необходимо писать прямо в .h-файле
    template <typename T>
    class List {
    private:
        struct ListNode {
            friend class List<T>;
        private:
            ListNode* next;
        public:
            T value;

            ListNode(T value) {
                this->value = value;
                this->next = nullptr;
            }
        };

        ListNode* head;
        int len;
    public:
        List() {
            head = nullptr;
            len = 0;
        }
        ~List() {
            clear();
        }

        int Len() const {
            return len;
        }

        // Часть из этих функций не реализована
        bool isempty() const;
        void clear();
        void add(T value);
        void remove(int index);
        //void insert(int index, const T& value);
        void print(std::ostream& os) const;

        //T operator[](int index);
        //const T& operator[](int index) const;
    };

    template <typename T>
    void List<T>::clear() {
        while (!isempty())
            remove(0);
    }

    template <typename T>
    bool List<T>::isempty() const {
        return head == nullptr;
    }

    template <typename T>
    void List<T>::add(T value) {
        ListNode** p = &head;
        while (*p != nullptr)
            p = &(*p)->next;
        *p = new ListNode(value);
        len++;
    }

    template <typename T>
    void List<T>::remove(int index) {
        assert(index >= 0 && index < len);

        ListNode** p = &head, *q = *p;
        for (int i = 0; i < index; i++) {
            p = &q->next;
            q = q->next;
        }

        *p = q->next;
        delete q;

        len--;
    }

    template <typename T>
    void List<T>::print(std::ostream& os) const {
        os << "[ ";
        for (ListNode* p = head; p != nullptr; p = p->next)
            os << p->value << ' ';
        os << " ]";
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const List<T>& lst) {
        lst.print(os);
        return os;
    }
}

#endif // LIST_H
