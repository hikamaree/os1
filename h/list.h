#ifndef LIST_H
#define LIST_H

#include "../lib/console.h"
template<typename T> class List {
	private:
		struct Elem {
			T *data;
			Elem *next;
			Elem(T *data, Elem *next) : data(data), next(next) {}
		};
		Elem *head, *tail;
	public:
		List() : head(0), tail(0) {}
		List(const List<T> &) = delete;
		List<T> &operator=(const List<T> &) = delete;
		void addFirst(T *data) {
			Elem *elem = new Elem(data, head);
			head = elem;
			if (!tail) { tail = head; }
		}
		void addLast(T *data) {
			Elem *elem = new Elem(data, 0);
			if (tail) {
				tail->next = elem;
				tail = elem;
			} else {
				head = tail = elem;
			}
		}

		T *removeFirst() {
			if (!head) { return 0; }
			Elem *elem = head;
			head = head->next;
			if (!head) { tail = 0; }
			T *ret = elem->data;
			delete elem;
			return ret;
		}

		T *peekFirst() {
			if (!head) { return 0; }
			return head->data;
		}

		T *removeLast() {
			if (!head) { return 0; }
			Elem *prev = 0;
			for (Elem *curr = head; curr && curr != tail; curr = curr->next) {
				prev = curr;
			}
			Elem *elem = tail;
			if (prev) { prev->next = 0; }
			else { head = 0; }
			tail = prev;
			T *ret = elem->data;
			delete elem;
			return ret;
		}

		void removeElem(T* data) {
			if(head == nullptr || data == nullptr) return;
			Elem* curr = head;
			if(head->data == data) {
				head=head->next;
				delete curr;
				return;
			}

			while(curr->next != nullptr && curr->next->data != data) {
				curr = curr->next;
			}
			if(curr->next == nullptr) return;
			Elem* tmp = curr->next;
			curr->next = curr->next->next;
			delete tmp;
		}

		T *peekLast() {
			if (!tail) { return 0; }
			return tail->data;
		}
};

#endif
