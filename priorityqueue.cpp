
#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
	if (size_ == max_size_) {
		throw std::runtime_error("Priority queue is full");
	}
	size_++;
	nodes_[size_] = kv;
	heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
	if (isEmpty()) {
		throw std::runtime_error("Priority queue is empty");
	}
	return nodes_[1];
}

KeyValuePair PriorityQueue::removeMin() {
	if (isEmpty()) {
		throw std::runtime_error("Priority queue is empty");
	}
	KeyValuePair min = nodes_[1];
	removeNode(1);
	return min;
}

bool PriorityQueue::isEmpty() const {
	return size_ == 0;
}

size_t PriorityQueue::size() const {
	return size_;
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
	if (i > ROOT) {
		size_t parent = i / 2;
		if (nodes_[i].first < nodes_[parent].first) {
			std::swap(nodes_[i], nodes_[parent]);
			heapifyUp(parent);
		}
	}
}

void PriorityQueue::heapifyDown(size_t i) {
	if (i <= size_) {
		size_t left = 2 * i;
		size_t right = 2 * i + 1;
		size_t smallest = i;
		if (left <= size_ && nodes_[left].first < nodes_[smallest].first) {
			smallest = left;
		}
		if (right <= size_ && nodes_[right].first < nodes_[smallest].first) {
			smallest = right;
		}
		if (smallest != i) {
			std::swap(nodes_[i], nodes_[smallest]);
			heapifyDown(smallest);
		}
	}
}

void PriorityQueue::removeNode(size_t i) {
	nodes_[i] = nodes_[size_];
	size_--;
	heapifyDown(i);
}

Key PriorityQueue::getKey(size_t i) {
	return nodes_[i].first;
}
