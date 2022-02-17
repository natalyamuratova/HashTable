#include "SeparateChainingTable.h"

SeparateChainingTable::SeparateChainingTable(int tableSize) {
	this->capacity = tableSize;
	this->size = 0;
	this->cells.resize(tableSize);
}

SeparateChainingTable::SeparateChainingTable(const SeparateChainingTable& table) {
	this->capacity = table.capacity;
	this->size = table.size;

	int n = table.capacity;
	for (int i = 0; i < n; i++) {
		this->cells[i] = table.cells[i];
	}
}

int SeparateChainingTable::hash(TKey key) {
	return key % 29 % capacity;
}

void SeparateChainingTable::insert(TKey key, TValue value) {
	int index = hash(key);

	TData cell;
	cell.key = key;
	cell.value = value;
	cells[index].push_back(cell);

	size++;
}

bool SeparateChainingTable::remove(TKey key)
{
	int index = hash(key);

	auto& bucket_list = cells[index];
	auto it = find_if(bucket_list.begin(), bucket_list.end(), [&key](const TData& d) { return d.key == key; });

	if (it == bucket_list.end()) {
		return false;
	}

	bucket_list.erase(it);
	size--;
	return true;
}

bool SeparateChainingTable::find(TKey key)
{
	int index = hash(key);

	auto& bucket_list = cells[index];
	auto it = find_if(bucket_list.begin(), bucket_list.end(), [&key](const TData& d) { return d.key == key; });

	return it == bucket_list.end();
}

void SeparateChainingTable::clear() {
	for (int i = 0; i < capacity; i++) {
		cells[i].clear();
	}

	size = 0;
}

int SeparateChainingTable::getSize()
{
	return size;
}

bool SeparateChainingTable::isEmpty() {
	return size == 0;
}

TValue SeparateChainingTable::get(TKey key)
{
	int index = hash(key);

	auto& bucket_list = cells[index];

	auto it = find_if(bucket_list.begin(), bucket_list.end(), [&key](const TData& d) { return d.key == key; });
	if (it == bucket_list.end()) {
		throw string("No value with this key");
	}

	return it->value;
}

void SeparateChainingTable::print()
{
	for (int i = 0; i < capacity; i++) {
		cout << i;
		for (auto x : cells[i]) {
			cout << "-->" << x.value;
		}
		cout << endl;
	}
}

SeparateChainingTable::~SeparateChainingTable() {
	clear();
}