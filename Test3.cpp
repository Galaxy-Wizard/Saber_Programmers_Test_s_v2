// Test3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

// структуру ListNode модифицировать нельзя
struct ListNode {
	ListNode* prev;
	ListNode* next;
	ListNode* rand; // указатель на произвольный элемент данного списка, либо NULL
	std::string     data;
};

class List {
public:
	List() : head(nullptr), tail(nullptr), count(0) {}
	List(List&) = delete;
	List& operator=(List&) = delete;
	~List();

	void Serialize(FILE* file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	void Deserialize(FILE* file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

	inline ListNode* GetHead() { return head; }
	inline ListNode* GetTail() { return tail; }
	inline int GetCount() { return count; }

	inline void SetHead(ListNode* p) { head = p; }
	inline void SetTail(ListNode* p) { tail = p; }
	inline void SetCount(int p) { count = p; }


private:
	ListNode* head;
	ListNode* tail;
	int       count;
};

int main()
{
	List* local_list_source = new List();
	if (local_list_source == nullptr)
	{
		return 1;
	}

	auto CurrentItemNode1 = new ListNode();

	if (CurrentItemNode1 != nullptr)
	{
		CurrentItemNode1->next = nullptr;
		CurrentItemNode1->prev = nullptr;
		CurrentItemNode1->rand = CurrentItemNode1;
		CurrentItemNode1->data = std::string("0001");

		local_list_source->SetHead(CurrentItemNode1);
		local_list_source->SetTail(CurrentItemNode1);
	}

	auto CurrentItemNode2 = new ListNode();

	if (CurrentItemNode2 != nullptr)
	{
		CurrentItemNode1->next = CurrentItemNode2;

		CurrentItemNode2->next = nullptr;
		CurrentItemNode2->prev = CurrentItemNode1;
		CurrentItemNode2->rand = CurrentItemNode1;
		CurrentItemNode2->data = std::string("0002");

		local_list_source->SetTail(CurrentItemNode2);

	}

	auto CurrentItemNode3 = new ListNode();

	if (CurrentItemNode3 != nullptr)
	{
		CurrentItemNode2->next = CurrentItemNode3;

		CurrentItemNode3->next = nullptr;
		CurrentItemNode3->prev = CurrentItemNode2;
		CurrentItemNode3->rand = CurrentItemNode1;
		CurrentItemNode3->data = std::string("0003");

		local_list_source->SetTail(CurrentItemNode3);
	}

	auto CurrentItemNode4 = new ListNode();

	if (CurrentItemNode4 != nullptr)
	{
		CurrentItemNode3->next = CurrentItemNode4;

		CurrentItemNode4->next = nullptr;
		CurrentItemNode4->prev = CurrentItemNode3;
		CurrentItemNode4->rand = CurrentItemNode1;
		CurrentItemNode4->data = std::string("0004");

		local_list_source->SetTail(CurrentItemNode4);
	}




	List* local_list_destination = new List();
	if (local_list_source == nullptr)
	{
		delete local_list_source;
		return 1;
	}

	FILE* local_file = nullptr;



	const char local_path[] = "data_file.txt";

	auto result_1 = fopen_s(&local_file, local_path, "wb");

	if (local_file == nullptr || result_1 != 0)
	{
		delete local_list_destination;
		delete local_list_source;

		return 1;
	}

	local_list_source->Serialize(local_file);

	fclose(local_file);


	local_file = nullptr;

	auto result_2 = fopen_s(&local_file, local_path, "rb");

	if (local_file == nullptr || result_2 != 0)
	{
		delete local_list_destination;
		delete local_list_source;

		return 1;
	}

	local_list_destination->Deserialize(local_file);

	if (local_file != nullptr)
	{
		fclose(local_file);
	}


	const char local_path_test[] = "data_file_test.txt";

	local_file = nullptr;

	auto result_3 = fopen_s(&local_file, local_path_test, "wb");

	if (local_file == nullptr || result_2 != 0)
	{
		delete local_list_destination;
		delete local_list_source;

		return 1;
	}

	local_list_destination->Serialize(local_file);

	delete local_list_destination;
	delete local_list_source;

	return 0;
}

List::~List()
{
	for (ListNode* current = head; current != tail; )
	{
		if (current != nullptr)
		{
			auto current_save = current;
			current = current->next;
			delete current_save;
		}
		else
		{
			break;
		}
	}

	if (tail != nullptr)
	{
		delete tail;
	}
}

class ListNodeToStore {
public:
	ListNodeToStore() : previous(0), next(0), random(0), link_forward(nullptr), link_back(nullptr) {}
	unsigned int previous;
	unsigned int next;
	unsigned int random;
	std::string     data;
	ListNodeToStore* link_forward;
	ListNodeToStore* link_back;
};

class ListToStore {
public:
	ListToStore() : head(nullptr), tail(nullptr), count(0) {}
	ListToStore(ListToStore&) = delete;
	ListToStore& operator=(ListToStore&) = delete;
	~ListToStore();

	inline ListNodeToStore* GetHead() { return head; }
	inline ListNodeToStore* GetTail() { return tail; }
	inline int Count() { return count; }

	inline void SetHead(ListNodeToStore* p) { head = p; }
	inline void SetTail(ListNodeToStore* p) { tail = p; }
	inline void SetCount(int p) { count = p; }

private:
	ListNodeToStore* head;
	ListNodeToStore* tail;
	int       count;
};

ListToStore::~ListToStore()
{
	for (ListNodeToStore* current = head; current != tail; )
	{
		if (current != nullptr)
		{
			auto current_save = current;
			current = current->link_forward;
			delete current_save;
		}
		else
		{
			break;
		}
	}

	if (tail != nullptr)
	{
		delete tail;
	}
}

void List::Serialize(FILE* file)
{
	if (file == nullptr)
	{
		return;
	}

	ListNode* CurrentListNode = head;
	if (CurrentListNode != nullptr)
	{
		unsigned int CurrentNumber = 1;
		for (; CurrentListNode != nullptr;)
		{
			if (CurrentListNode != nullptr)
			{
				ListNodeToStore CurrentListNodeToStore;
				CurrentListNodeToStore.data = CurrentListNode->data;
				CurrentListNodeToStore.next = CurrentNumber + 1;
				CurrentListNodeToStore.previous = CurrentNumber - 1;

				CurrentListNode = CurrentListNode->next;
				CurrentNumber++;

				ListNode* CurrentListNodeRandom = head;
				unsigned int CurrentNumberRandom = 1;
				for (; CurrentListNodeRandom != CurrentListNode;)
				{
					CurrentListNodeRandom = CurrentListNodeRandom->next;
					CurrentNumberRandom++;
				}

				CurrentListNodeToStore.random = CurrentNumberRandom;

				if (CurrentListNode == tail)
				{
					CurrentListNodeToStore.next = 0;
				}

				fwrite(&CurrentListNodeToStore.previous, sizeof(unsigned int), 1, file);
				fwrite(&CurrentListNodeToStore.next, sizeof(unsigned int), 1, file);				
				fwrite(&CurrentListNodeToStore.random, sizeof(unsigned int), 1, file);

				size_t CurrentDataLength = CurrentListNodeToStore.data.length();

				fwrite(&CurrentDataLength, sizeof(size_t), 1, file);

				fwrite(CurrentListNodeToStore.data.c_str(), sizeof(char), CurrentDataLength, file);
			}
			else
			{
				break;
			}
		}
	}
}

void List::Deserialize(FILE* file)
{
	if (file == nullptr)
	{
		return;
	}

	ListToStore ListToStoreData;

	for (; feof(file) == 0;)
	{
		ListNodeToStore CurrentListNodeToStore;

		auto SizePrevious = fread(&CurrentListNodeToStore.previous, sizeof(unsigned int), 1, file);
		auto SizeNext = fread(&CurrentListNodeToStore.next, sizeof(unsigned int), 1, file);
		auto SizeRandom = fread(&CurrentListNodeToStore.random, sizeof(unsigned int), 1, file);

		size_t CurrentDataLength = 0;

		auto SizeCurrentDataLength = fread(&CurrentDataLength, sizeof(size_t), 1, file);

		char* data_buffer = nullptr;
		if (CurrentDataLength != 0)
		{
			data_buffer = new char[CurrentDataLength+1];
		}

		if (data_buffer == nullptr)
		{
			break;
		}

		auto SizeCurrentData = fread(data_buffer, sizeof(char), CurrentDataLength, file);

		data_buffer[CurrentDataLength] = char(0);

		CurrentListNodeToStore.data = std::string(data_buffer);

		delete[] data_buffer;

		CurrentListNodeToStore.link_forward = nullptr;
		CurrentListNodeToStore.link_back = nullptr;

		ListNode* CurrentListNode = new ListNode();

		if (CurrentListNode == nullptr)
		{
			return;
		}

		auto CurrentStore = ListToStoreData.GetHead();

		if (CurrentStore == nullptr)
		{
			auto Current = new ListNodeToStore();

			if (Current != nullptr)
			{
				Current->data = CurrentListNodeToStore.data;
				Current->next = CurrentListNodeToStore.next;
				Current->previous = CurrentListNodeToStore.previous;
				Current->random = CurrentListNodeToStore.random;

				ListToStoreData.SetHead(Current);
				ListToStoreData.SetTail(Current);
			}
		}
		else
		{
			auto Tail = ListToStoreData.GetTail();

			auto Current = new ListNodeToStore();

			Tail->link_forward = Current;

			Current->data = CurrentListNodeToStore.data;
			Current->link_forward = nullptr;
			Current->link_back = Tail;
			Current->next = CurrentListNodeToStore.next;
			Current->previous = CurrentListNodeToStore.previous;
			Current->random = CurrentListNodeToStore.random;

			ListToStoreData.SetTail(Current);
		}
	}

	if (ListToStoreData.GetHead() != nullptr)
	{
		for (auto CurrentToStore = ListToStoreData.GetHead(); CurrentToStore != nullptr; CurrentToStore = CurrentToStore->link_forward)
		{
			auto CurrentItem = head;

			if (CurrentItem == nullptr)
			{
				CurrentItem = new ListNode();

				if (CurrentItem == nullptr)
				{
					return;
				}

				CurrentItem->next = CurrentItem->prev = CurrentItem->rand = nullptr;

				CurrentItem->data = CurrentToStore->data;

				head = CurrentItem;
				tail = CurrentItem;
			}
			else
			{
				auto Current = new ListNode();

				if (Current == nullptr)
				{
					return;
				}
				
				auto Tail = tail;

				Tail->next = Current;

				Current->data = CurrentToStore->data;
				Current->next = nullptr;
				Current->prev = Tail;
				Current->rand = nullptr;

				tail = Current;
			}
		}

		auto Current = head;

		for (auto CurrentToStore = ListToStoreData.GetHead(); CurrentToStore != nullptr && Current != nullptr; CurrentToStore = CurrentToStore->link_forward, Current = Current->next)
		{
			unsigned int CounterRandom = 1;

			auto CurrentItemRandom = head;

			if (CounterRandom != 0)
			{
				for (; CurrentItemRandom != nullptr; CurrentItemRandom = CurrentItemRandom->next)
				{
					if (CounterRandom < CurrentToStore->random)
					{
						CounterRandom++;
					}
					else
					{
						break;
					}
				}

				Current->rand = CurrentItemRandom;
			}
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
